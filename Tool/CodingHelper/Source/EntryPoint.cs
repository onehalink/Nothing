using System.Runtime.Serialization;
using System.Text;


var BuildPCH = (string path, string[] filters, string prefix = "") =>
{
    var InFolder = Path.GetFileName(path);

    var Output = path + ".h";
    //if (File.Exists(Output)) return;
    if (File.Exists(Output)) File.Delete(Output);

    var files = new List<string>();
    foreach (var filter in filters)
        foreach (var file in Directory.GetFiles(path, filter, SearchOption.TopDirectoryOnly))
            files.Add(file);

    var directories = new List<string>();
    foreach (var directory in Directory.GetDirectories(path, "*", SearchOption.TopDirectoryOnly))
    {
        var entry = Path.GetFileName(directory);

        bool isContinue = false;
        foreach (var file in files)
        {
            if (entry == Path.GetFileNameWithoutExtension(file))
            {
                isContinue = true;
                break;
            }
        }

        if (isContinue) continue;

        directories.Add(directory);
    }

    var sb = new StringBuilder();
    sb.AppendLine("#pragma once");
    sb.AppendLine();

    foreach (var file in files)
    {
        sb.AppendLine($"#include \"{prefix}{InFolder}/{Path.GetFileName(file)}\"");
    }

    //File.WriteAllText(Output, sb.ToString());
    //return;

    sb.AppendLine();

    foreach (var filter in filters)
        foreach (var directory in directories)
        {
            foreach (var file in Directory.GetFiles(directory, filter, SearchOption.AllDirectories))
            {
                var relative = InFolder + file.Replace(path, "");
                relative = relative.Replace('\\', '/');

                sb.AppendLine($"#include \"{prefix}{relative}\"");
            }

            sb.AppendLine();
        }

    File.WriteAllText(Output, sb.ToString());
};


var ReplaceSymbol = (string path, string replaced, string newSymbol = "") =>
{
    var sb = new StringBuilder(File.ReadAllText(path));
    sb.Replace(replaced, newSymbol);

    File.Delete(path);
    File.WriteAllText(path, sb.ToString());
};


var BuildCSource = (string[] filenames) =>
{
    foreach (var filename in filenames)
    {
        if (
        !filename.EndsWith(".h") ||
        !File.Exists(filename)
        )
            continue;

        var CHeader = filename.Substring(Math.Max(filename.LastIndexOf('/'), filename.LastIndexOf('\\')) + 1);

        var CSourcePath = filename.Replace(".h", ".c");
        if (File.Exists(CSourcePath))
            continue;

        var lines = File.ReadAllLines(filename);

        var APISet = "";
        {
            var prefix = "extern ENGINE_API ";
            var suffix = ";";

            foreach (var line in lines)
                if (line.StartsWith(prefix))
                {
                    APISet = line.Replace(prefix, "").Replace(suffix, "");
                    break;
                }
        }

        var IsUpperCaseLetter = (char code) =>
        {
            return code >= 'A' && code <= 'Z';
        };

        var IsLowerCaseLetter = (char code) =>
        {
            return code >= 'a' && code <= 'z';
        };

        var IsFunctionPointer = (string text) =>
        {
            if (text.Length < 4)
                return false;

            if (text[0] != '\t')
                return false;

            if (
                !IsLowerCaseLetter(text[1]) &&
                !IsUpperCaseLetter(text[1])
            )
                return false;

            if (!text.Contains("(*"))
                return false;

            return true;
        };

        var FunctionPointers = new List<string>();
        var Definitions = new List<string>();

        foreach (var line in lines)
        {
            if (!IsFunctionPointer(line))
                continue;

            var Return = "";
            {
                var begin = 1;
                var end = line.IndexOf('(');

                Return = line.Substring(begin, end - begin);
            }

            var Name = "";
            {
                var begin = line.IndexOf('(') + 2;
                var end = line.IndexOf(')');

                Name = line.Substring(begin, end - begin);
            }

            var Arguments = "";
            {
                var begin = line.LastIndexOf('(') + 1;
                var end = line.LastIndexOf(')');

                Arguments = line.Substring(begin, end - begin);
            }

            var Definition = $"static {Return} {Name}({Arguments})" + "\n{\n\n}";

            FunctionPointers.Add(Name);
            Definitions.Add(Definition);
        }

        var sb = new System.Text.StringBuilder();

        sb.AppendLine($"#include \"{CHeader}\"");
        sb.AppendLine();
        sb.AppendLine();
        sb.AppendLine();

        foreach (var Definition in Definitions)
        {
            sb.AppendLine(Definition);
            sb.AppendLine();
        }

        sb.AppendLine();
        sb.AppendLine($"{APISet} =");
        sb.AppendLine("{");
        foreach (var FunctionPointer in FunctionPointers) sb.AppendLine($"\t{FunctionPointer},");
        sb.AppendLine("};");

        File.WriteAllText(CSourcePath, sb.ToString());
    }
};


var CodingAnalyzer = (string path, string[] filters) =>
{
    var totalCodingLines = 0;
    foreach (var filter in filters)
        foreach (var file in Directory.EnumerateFiles(path, filter, SearchOption.AllDirectories))
        {
            foreach (var line in File.ReadAllLines(file))
            {
                if (line.Length > 0)
                    totalCodingLines++;
            }
        }

    Console.WriteLine($"Total coding lines: {totalCodingLines}");
};


BuildPCH(@"C:\UserCustom\Nothing\CPlusPlus\Engine\Source\Runtime\Core\Base", new[] { "*.h" });
BuildPCH(@"C:\UserCustom\Nothing\CPlusPlus\Engine\Source\Runtime\Core\Template", new[] { "*.h" });
BuildPCH(@"C:\UserCustom\Nothing\CPlusPlus\Engine\Source\Runtime\Core", new[] { "*.h" });

//BuildPCH(@"C:\UserCustom\Nothing\CPlusPlus\Engine\Source\Runtime", new[] { "*.h" }, "../");

//CodingAnalyzer(@"C:\UserCustom\Nothing\CPlusPlus\Engine\Source", new[] { "*.h", "*.c", "*.cpp" });
