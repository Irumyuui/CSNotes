using System;
using System.CommandLine;
using System.Threading.Tasks;

namespace Hakurei
{
    internal class Program
    {
        private static async Task<int> Main(string[] args)
        {
            var rootCommand = new System.CommandLine.RootCommand("Expression tree.");

            var fileOption = new System.CommandLine.Option<string?>(
                    name: "--file",
                    description: "The c scourse file path."
            ) {
                IsRequired = true,
            };

            fileOption.AddValidator(
                result => {
                    string? filePath = result.GetValueForOption(fileOption);
                    if (filePath is null || !System.IO.File.Exists(filePath)) {
                        result.ErrorMessage = $"Invalid file path: {filePath}";
                    }
                }
            );

            rootCommand.AddOption(fileOption);

            rootCommand.SetHandler(file => Solution(file), fileOption);

            return await rootCommand.InvokeAsync(args);
        }


        private static void Solution(string? filePath)
        {
            ArgumentNullException.ThrowIfNull(filePath);

            var lines = System.IO.File.ReadAllLines(filePath);

            var tree = new Hakurei.CodeAnalyzer.Expression.ExpressionTree(lines);

            tree.PrettyPrint();

            try {
                tree.Excute().PrettyPrint();
            } catch (Exception exception) {
                Hakurei.Diagostics.DiagosticHelper.AddDiagostic(exception.Message);
            }

            Hakurei.Diagostics.DiagosticHelper.ReportDiagostics();
        }
    }
}
