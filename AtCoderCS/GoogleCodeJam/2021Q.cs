using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace Q2021
{
    class A
    {
        static int Solve(List<int> L)
        {
            int result = 0;
            for (int i = 0; i < L.Count - 1; i++)
            {
                var j = L.Skip(i).Select((v, idx) => (Val: v, Index: idx)).Aggregate((m, current) => (current.Val < m.Val) ? current : m).Index + i;
                L.Reverse(i, j-i+1);
                result += j - i + 1;
            }
            return result;
        }
    }
    class B
    {
        static int Solve(int CJ, int JC, string Z)
        {
            int result = 0;
            var array = Z.ToArray();
            char leading = array[0];
            for (int i = 1; i < array.Length; i++)
            {
                switch (array[i])
                {
                    case '?':
                        if (leading != '?')
                        {
                            array[i] = leading;
                        }
                        break;
                    default:
                        if (leading == '?')
                        {
                            for (int j = 0; j < i; j++)
                            {
                                array[j] = array[i];
                            }
                        }
                        leading = array[i];
                        break;
                }
            }
            var s = string.Join("", array);
            result = Regex.Matches(s, @"CJ").Count * CJ + Regex.Matches(s, @"JC").Count * JC;
            return result;
        }
    }
    class C
    {

        static string Solve(int N, int C)
        {
            string result = "IMPOSSIBLE";
            long min = N - 1;
            long max = (N - 1) * (N + 2) / 2;
            if (min <= C && C <= max)
            {
                var l = Enumerable.Repeat(1, N - 1).ToList();
                for (int i = 0; i < l.Count; i++)
                {
                    long sum = l.Sum();
                    if (sum == C)
                    {
                        break;
                    }
                    long remain = C - (sum - l[i]);
                    long limit = N - i;
                    long add = Math.Min(remain, limit);
                    l[i] = (int)add;
                }
                var seq = Enumerable.Range(1, N).ToList();
                for (int i = l.Count - 1; i >= 0; --i)
                {
                    seq.Reverse(i, (int)l[i]);

                }
                result = string.Join(" ", seq);
            }
            return result;
        }
    }
}
