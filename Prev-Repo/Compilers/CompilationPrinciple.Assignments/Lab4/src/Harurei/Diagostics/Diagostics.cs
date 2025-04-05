using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Hakurei.Diagostics;

internal static class DiagosticHelper
{
    public static List<string> Diagostics { get; private set; } = [];

    public static void AddDiagostic(string diagostic) => Diagostics.Add(diagostic);

    public static TReturn AddDiagosticWithReturnValue<TReturn>(string diagostic, in TReturn returnValue)
    {
        AddDiagostic(diagostic);
        return returnValue;
    }

    public static void AddRangeDiagostic(IEnumerable<string> diagostics) => Diagostics.AddRange(diagostics);

    public static void ReportDiagostics()
    {
        var prevColor = Console.ForegroundColor;
        Console.ForegroundColor = ConsoleColor.Red;

        foreach (var diagostic in Diagostics)
            Console.WriteLine(diagostic);

        Console.ForegroundColor = prevColor;
    }

    public static bool Any => Diagostics.Count is not 0;

    public static int Count => Diagostics.Count;
}
