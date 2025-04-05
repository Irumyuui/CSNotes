using Utility;

#if DEBUG
DebugMain();
#endif

// string? st = "true";

// if (st is not null && st is not "true" or "false") {
    // Console.WriteLine('-' is not '+' and not '-');
// }

#if RELEASE
ReleaseMain();
#endif

#if RELEASE
void ReleaseMain() {
    string commandUse = $"Use: {Environment.GetCommandLineArgs()[0]} -in:path/to/c.json -in:path/to/a.c -out:path/to/output.txt -print-id:[true|false] -with-token:[true|false]";

    if (args.Length != 5) {
        System.Console.WriteLine(commandUse);
        Environment.Exit(-1);
        return;
    }

    var argsList = args.ToArray();

    string jsonPath   = argsList[0],
        cPath      = argsList[1],
        outputPath = argsList[2],
        printId    = argsList[3],
        withToken   = argsList[4];

    if (!jsonPath.StartsWith("-in:")
    || !jsonPath.EndsWith(".json")
    || !cPath.StartsWith("-in:")
    || !cPath.EndsWith(".c")
    || !outputPath.StartsWith("-out:")
    || !printId.StartsWith("-print-id:")
    || printId[10..] is not "true" and not "false"
    || !withToken.StartsWith("-with-token:")
    || withToken[12..] is not "true" and not "false") {
        System.Console.WriteLine(commandUse);
        System.Environment.Exit(-1);
    }

    jsonPath = jsonPath[4..];
    cPath = cPath[4..];
    outputPath = outputPath[5..];
    bool isPrintId  = printId[10..] == "true",
        isWithToken = withToken[11..] == "true";

    var alanyzer = LexerAnalyzer.ReadWithJsonFile(jsonPath);
    var codeText = LexerAnalyzer.PretreatmentSourceCodeText(File.ReadAllLines(cPath, System.Text.Encoding.UTF8));
    alanyzer.ScannerLoadPretreatmentSourceCodeText(codeText);
    alanyzer.StarAnalyzer(isWithToken);
    if (isPrintId) {
        Console.WriteLine(alanyzer);
    }
    alanyzer.WriteFile(outputPath);
}
#endif

#if DEBUG
void DebugMain() {
    // 从 c.json 中读取 json
    const string cJsonConfigPath = "./config/c.json";
    const string cCodePath = "./config/a.c";

    string[] codeText = File.ReadAllLines(cCodePath, System.Text.Encoding.UTF8);

    var alanyzer = Utility.LexerAnalyzer.ReadWithJsonFile(cJsonConfigPath);
    var pretreatmentSourceCodeText = Utility.LexerAnalyzer.PretreatmentSourceCodeText(codeText);
    alanyzer.ScannerLoadPretreatmentSourceCodeText(pretreatmentSourceCodeText);
    alanyzer.StarAnalyzer(true);
    Console.WriteLine(alanyzer);
    alanyzer.PrintResult();
}
#endif
