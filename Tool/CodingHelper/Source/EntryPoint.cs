
using System.IO;
using System.Text;


var BuildPCHForFolder = (string path, bool filterFile = true, bool rewrited = true, string prefix = "", string filter = "*.h") =>
{
    if (!Path.Exists(path))
        return;

    var folder = Path.GetFileName(path);

    var outputFileExtension = ".h";
    var outputFileName = path + outputFileExtension;
    if (File.Exists(outputFileName) && !rewrited)
        return;

    var files = new List<string>();
    foreach (var file in Directory.EnumerateFiles(path, filter, SearchOption.TopDirectoryOnly))
        files.Add(file);

    var directories = new List<string>();
    foreach (var directory in Directory.GetDirectories(path, "*", SearchOption.TopDirectoryOnly))
    {
        var currentFolder = Path.GetFileName(directory);

        bool shouldAddDirectory = true;
        foreach (var file in files)
            if (currentFolder == Path.GetFileNameWithoutExtension(file))
            {
                shouldAddDirectory = false;
                break;
            }

        if (!shouldAddDirectory)
            continue;

        //Console.WriteLine(directory);
        directories.Add(directory);
    }

    // Build PCH
    {
        var sb = new StringBuilder();
        sb.AppendLine("#pragma once");
        sb.AppendLine();

        foreach (var file in files)
        {
            var entry = Path.GetFileName(file);

            if(filterFile)
                if (entry.StartsWith("_"))
                    continue;

            sb.AppendLine($"#include \"{prefix}{folder}/{entry}\"");
        }

        sb.AppendLine();

        foreach (var directory in directories)
        {
            foreach (var file in Directory.GetFiles(directory, filter, SearchOption.AllDirectories))
            {
                if (filterFile)
                {
                    var name = Path.GetFileName(file);
                    if (
                        name.StartsWith("_") ||
                        name == "Windows.h"
                        )
                        continue;
                }

                var relative = (folder + file.Replace(path, "")).Replace('\\', '/');

                sb.AppendLine($"#include \"{prefix}{relative}\"");
            }

            sb.AppendLine();
        }

        File.WriteAllText(outputFileName, sb.ToString());
    }
};


var BuildPCHForEngine = (string root) =>
{
    BuildPCHForFolder(Path.Combine(root, "Core"));

   // return;

    BuildPCHForFolder(root, true, true, "../");

    {
        var runtimeHeaderPath = root + ".h";
        var engineHeaderPath = root + "/../Include/Engine.h";

        {
            var include = Path.GetDirectoryName(engineHeaderPath);
            if(!Directory.Exists(include))
                Directory.CreateDirectory(include);
        }

        if (File.Exists(runtimeHeaderPath))
        {
            var prefix = File.ReadAllText("Text.txt");

            var sb = new StringBuilder();
            sb.AppendLine(prefix);

            var lines = File.ReadAllLines(runtimeHeaderPath);
            // ignore 0 and 1 lines
            if (lines.Length > 1)
                for (int i = 2; i < lines.Length; i++)
                    sb.AppendLine(lines[i]);

            File.Delete(runtimeHeaderPath);

            File.WriteAllText(engineHeaderPath, sb.ToString());
        }
    }
};


var ReplaceSymbol = (string path, string from, string to) =>
{
    var sb = new StringBuilder(File.ReadAllText(path)).Replace(from, to);

    File.Delete(path);
    File.WriteAllText(path, sb.ToString());
};



BuildPCHForEngine("C:\\Dev\\Rebase\\CPlusPlus\\Engine\\Source\\Runtime");

//ReplaceSymbol(@"C:\\Dev\\Rebase\\CPlusPlus\\Engine\\Source\\Runtime\\Core\\Mathematics\\Vector.h", "Vectors&&", "const Vectors&");
