using System;
using System.Collections;
using static System.Console;

class Sloution {
    public static void Solve() {
        int n = int.Parse(ReadLine());
        var line = ReadLine().Split();
        long pre = long.Parse(line[0]);
        long ans = pre;
        for (int i = 1; i < n; i ++) {
            long now = long.Parse(line[i]);
            if (now > pre) {
                ans += now - pre;
            }
            pre = now;
        }
        WriteLine(ans);
    }
}

internal class Program {
    static void Main(string[] args) {
        Sloution.Solve();        
    }
}