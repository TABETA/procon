using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Numerics;

namespace GoogleCodeJam
{
    class Program
    {
        static void set(bool?[,] b, int[] ijk)
        {
            b[ijk[2], ijk[1]] = true;
            b[ijk[2], ijk[0]] = true;
            b[ijk[1], ijk[0]] = true;
            b[ijk[1], ijk[2]] = false;
            b[ijk[0], ijk[2]] = false;
            b[ijk[0], ijk[1]] = false;
        }
        static string Solve(int N)
        {
            var n = Enumerable.Range(1, N).ToList();
            var done = new Dictionary<string, bool>();
            var isBigger = new bool?[N+1,N+1];
            for (int i = 0; i < N - 2; i++)
            {
                var ijk = n.Skip(i).Take(3).ToList();
                var key = string.Join(",",ijk.OrderBy(v => v));
                if (done.ContainsKey(key))
                {
                    continue;
                }
                done.Add(key, true);
                Console.WriteLine(string.Join(" ", ijk));
                var med = int.Parse(Console.ReadLine());
                if (med == -1)
                {
                    return string.Join(" ", n);
                }
                if (ijk[0] == med)
                {
                    if (
                        (!isBigger[ijk[1], ijk[0]].HasValue || isBigger[ijk[1], ijk[0]].Value)
                        &&
                        (!isBigger[ijk[0], ijk[2]].HasValue || isBigger[ijk[0], ijk[2]].Value)
                        )
                    {
                        n[i + 0] = ijk[2];
                        n[i + 1] = ijk[0];
                        n[i + 2] = ijk[1];
                    }
                    else
                    {
                        n[i + 0] = ijk[1];
                        n[i + 1] = ijk[0];
                    }
                    set(isBigger, n.Skip(i).Take(3).ToArray());
                    i = -1;
                }
                else if (ijk[2] == med)
                {
                    n[i + 1] = ijk[2];
                    n[i + 2] = ijk[1];
                    set(isBigger, n.Skip(i).Take(3).ToArray());
                }
            }
            return string.Join(" ", n);
        }
        static void Main(string[] args)
        {
            var TNQ = Console.ReadLine().Split(' ').Select(c => int.Parse(c)).ToList();
            int T, N, Q;
            (T, N, Q) = (TNQ[0], TNQ[1], TNQ[2]);
            for (int i = 0; i < T; i++)
            {
                Console.WriteLine(Solve(N));
                var judge = int.Parse(Console.ReadLine());
                if (judge == -1)
                {
                    return;
                }
            }
        }
    }
}
