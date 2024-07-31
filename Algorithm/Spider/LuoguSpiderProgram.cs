/*
 * 27 28 12 4 11 12 28 cpp
 * 2 c
 * 25 7 py
 * 19 hs
 * 15 rust
 * 17 cs
 * submitTime
 */

using System.Net;
using System.Text.Json;
using System.Text.Json.Nodes;
using System.Text.RegularExpressions;
using ConsoleDump;
using HtmlAgilityPack;

const string COOKIE = @"__client_id=; _uid=";
const string USER_AGENT = @"Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/79.0.3945.130 Safari/537.36";
const string USER_ID = "";

using var httpClient = new HttpClient
{
    BaseAddress = new Uri("https://www.luogu.com.cn"),
};
httpClient.DefaultRequestHeaders.Add("user-agent", USER_AGENT);
httpClient.DefaultRequestHeaders.Add("cookie", COOKIE);

var regex = new Regex("\"(.*)\"");

async Task<string> GetHtmlContent(string url)
{
    var result = await httpClient.GetAsync(url);
    if (result.StatusCode == HttpStatusCode.OK)
        return await result.Content.ReadAsStringAsync();
    return string.Empty;
}

string? GetJsonText(string html)
{
    var doc = new HtmlDocument();
    doc.LoadHtml(html);

    var codeScriptText = doc.DocumentNode.Descendants("script").FirstOrDefault()?.InnerText ?? string.Empty;

    var encodeContent = regex.Match(codeScriptText)?.Value?.Trim('"');
    var decodeJson = System.Web.HttpUtility.UrlDecode(encodeContent);

    return decodeJson;
}

string? GetCodeFromJson(string decodeJson)
{
    var json = JsonSerializer.Deserialize<JsonNode>(decodeJson);
    return json?["currentData"]?["record"]?["sourceCode"]?.GetValue<string>();
}

async Task<string> GetRecordHtmlContent(string id) => await GetHtmlContent($"record/{id}");

// List<SolutionRecord> solutions = [];
var rand = new Random();

if (!Directory.Exists("Output"))
{
    Directory.CreateDirectory("Output");
}

for (int pageId = 0; ; pageId++)
{
    var html = await GetHtmlContent(@$"record/list?user={USER_ID}&page={pageId}");
    var jsonText = GetJsonText(html);
    if (string.IsNullOrEmpty(jsonText))
        break;

    var json = JsonSerializer.Deserialize<JsonNode>(jsonText);
    if (json is null)
        break;

    var allSolution = json?["currentData"]?["records"]?["result"]?.AsArray();
    if (allSolution is null || allSolution.Count is 0)
        break;

    var list = allSolution
        ?.Where(item => item?["problem"]?["fullScore"]?.GetValue<int>() == item?["score"]?.GetValue<int>())
        ?.Select(item => (Pid: item?["problem"]?["pid"]?.GetValue<string>(), Id: item?["id"]?.GetValue<int>(), Language: item?["language"]?.GetValue<int>() ?? -1, SubmitTime: item?["submitTime"]?.GetValue<long>() ?? 0))
        ?? [];

    list.Dump();

    foreach (var (pid, id, lang, time) in list)
    {
        if (string.IsNullOrWhiteSpace(pid) || id is null)
            continue;

        var code = GetCodeFromJson(GetJsonText(await GetRecordHtmlContent($"{id}")) ?? string.Empty);

        pid.Dump();
        id.Dump();
        var fileName = lang switch
        {
            27 or 28 or 12 or 4 or 11 or 12 => $"{pid}-{time}.cpp",
            2 => $"{pid}-{time}.c",
            25 or 7 => $"{pid}-{time}.py",
            19 => $"{pid}-{time}.hs",
            15 => $"{pid}-{time}.rs",
            17 => $"{pid}-{time}.cs",
            _ => $"{pid}-{time}",
        };

        await File.WriteAllTextAsync($"Output/{fileName}", code);

        int delayTime = rand.Next(2000, 6000);
        Console.WriteLine($"Delay: {delayTime} ms");

        await Task.Delay(delayTime);
    }
}

// await using var stream = File.Create("output.json");
// await JsonSerializer.SerializeAsync(stream, solutions);

public record struct SolutionRecord(string? Pid, int? Id, int Language, string? Code)
{
    public static implicit operator SolutionRecord(in (string? Pid, int? Id, int Language, string? Code) item) => new SolutionRecord(item.Pid, item.Id, item.Language, item.Code);
}
