using System;
using System.Text.RegularExpressions;
using System.Collections.Generic;
using System.IO;
class Program
{
    struct Tuple
    {
        public string l;
        public string r;
    }
    static Dictionary<char, long> dict = new Dictionary<char, long>();
    static Regex num = new Regex(@"^(?<Count>\d+)", RegexOptions.Compiled);
    static Regex multiple = new Regex(@"^(?<Count>\d+)(\((?<Letters>.*)\)|(?<Letters>[a-z]))", RegexOptions.Compiled);
    static Regex letters = new Regex(@"^(?<Letters>[a-z]+)", RegexOptions.Compiled);

    static Tuple b(string s)
    {
        var depth = 0;
        var j = 0;
        if (s.Length == 0)
        {
            return new Tuple { l = "", r = "" };
        }
        if (s[0] != '(')
        {
            return new Tuple { l= s[0].ToString(), r = s.Length > 1 ? s.Substring(1) : "" };
        }
        for (int i = 0; i < s.Length; i++)
        {
            var c = s[i];
            if (c == '(')
            {
                depth++;
                if (depth == 1)
                {
                    j = i + 1;
                }
            }
            else if (c == ')')
            {
                depth--;
                if (depth == 0)
                {
                    return new Tuple { l = s.Substring(j, i - j), r = s.Substring(i + 1) };
                }
            }
        }
        throw new InvalidDataException();
    }

    static void solve(string s, long x)
    {
        var m = num.Match(s);
        if (m.Success)
        {
            var count = long.Parse(m.Groups["Count"].Value);
            var sub = s.Substring(m.Value.Length);
            var t = b(sub);
            solve(t.l, count*x);
            if(t.r.Length > 0) solve(t.r, x);
        }
        else
        {
            m = letters.Match(s);
            if (m.Success)
            {
                var l = m.Groups["Letters"].Value;
                foreach (var c in l)
                {
                    dict[c] += x;
                }
            }
            else
            {
                throw new Exception();
            }
            var sub = s.Substring(m.Value.Length);
            if (sub.Length > 0) solve(sub, x);
        }
    }


    static void Main()
    {
        for (int i = 0; i < 26; i++)
        {
            var c = (char)('a' + i);
            dict[c] = 0;
        }
        var S= Console.ReadLine();
        solve(S, 1);
        for (int i = 0; i < 26; i++)
        {
            var c = (char)('a' + i);
            Console.WriteLine($"{c} {dict[c]}");
        }
    }
}