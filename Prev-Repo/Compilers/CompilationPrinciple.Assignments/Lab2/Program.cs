using System.CommandLine;

internal class Program
{
    private static async Task<int> Main(string[] args)
    {
        var rootCommand = new RootCommand("Basic Syntactic Analyzer");

        var fileOption = new Option<string?>(
            name: "--file",
            description: "The c source code file path"
        )
        {
            IsRequired = true
        };
        fileOption.AddValidator(result =>
        {
            string? filePath = result.GetValueForOption(fileOption);
            if (filePath is null || !File.Exists(filePath))
            {
                result.ErrorMessage = $"Invalid file path: {filePath}";
            }
        });

        var outputOption = new Option<bool>(
            name: "--call-chain",
            description: "Output call chain in analyzer."
        );
        outputOption.AddValidator(result =>
        {
            bool? opt = result.GetValueForOption(outputOption);
            if (opt is null)
            {
                result.ErrorMessage = $"Invalid type : {opt}";
            }
        });

        rootCommand.AddOption(fileOption);
        rootCommand.AddOption(outputOption);

        rootCommand.SetHandler((file, outputOpt) => BeginSyntacticAnalyzer(file!, outputOpt), fileOption, outputOption);

        return await rootCommand.InvokeAsync(args);
    }

    private static void BeginSyntacticAnalyzer(string file, bool withFuncChain)
    {
        bool result = false;
        try
        {
            result = new Crt.CSyntac.SyntacticAnalyzer(
                    new Crt.CLex.LexecalAnalyzer(File.ReadLines(file).ToArray())
                ).Analyze(withFuncChain);
        }
        catch (Exception e)
        {
            Console.WriteLine(e.Message);
        }

        Console.WriteLine(result);
    }
}
