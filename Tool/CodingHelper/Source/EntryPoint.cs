using System.Runtime.Serialization;
using System.Text;


var BuildPCH = (string path, string[] filters, string prefix = "") =>
{
    var InFolder = Path.GetFileName(path);

    var Output = path + ".h";
    if (File.Exists(Output)) return;
    //if (File.Exists(Output)) File.Delete(Output);

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


BuildPCH(@"C:\UserCustom\Nothing\CPlusPlus\Engine\Source\Runtime\Core\Base", new[] { "*.h" });
BuildPCH(@"C:\UserCustom\Nothing\CPlusPlus\Engine\Source\Runtime\Core\Template", new[] { "*.h" });
BuildPCH(@"C:\UserCustom\Nothing\CPlusPlus\Engine\Source\Runtime\Core", new[] { "*.h" });

BuildPCH(@"C:\UserCustom\Nothing\CPlusPlus\Engine\Source\Runtime", new[] { "*.h" }, "../");