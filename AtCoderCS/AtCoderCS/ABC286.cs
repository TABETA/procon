using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;


namespace Procon.AtCoder.ABC286
{
    class A_ : ILOSolver
    {
        public static TestSeed[] TestSeeds = new TestSeed[]
        {
new TestSeed("8 1 3 5 7\n1 2 3 4 5 6 7 8", "5 6 7 4 1 2 3 8"),
new TestSeed("5 2 3 4 5\n2 2 1 1 1", "2 1 1 2 1"),
new TestSeed("2 1 1 2 2\n50 100", "100 50"),
new TestSeed("10 2 4 7 9\n22 75 26 45 72 81 47 29 97 2", "22 47 29 97 72 81 75 26 45 2"),
new TestSeed("8 1 3 5 7\n1 2 3 4 5 6 7 8", "5 6 7 4 1 2 3 8"),
new TestSeed("5 2 3 4 5\n2 2 1 1 1", "2 1 1 2 1"),
new TestSeed("2 1 1 2 2\n50 100", "100 50"),
new TestSeed("10 2 4 7 9\n22 75 26 45 72 81 47 29 97 2", "22 47 29 97 72 81 75 26 45 2")
        };

        int N, P, Q, R, S;
        List<int> A = new List<int>();
        string result;
        public override void Input()
        {
            var _ = Console.ReadLine()!.Split().Select(v => int.Parse(v)).ToArray();
            var i = 0;
            (N, P, Q, R, S) = (_[i++], _[i++] - 1, _[i++] - 1, _[i++] - 1, _[i++] - 1);
            A = Console.ReadLine()!.Split().Select(v => int.Parse(v)).ToList();
        }


        public override void Solve()
        {
            var n = Q - P + 1;
            for (int i = 0; i < n; i++)
            {
                var _ = A[P + i];
                A[P + i] = A[R + i];
                A[R + i] = _;
            }
            result = string.Join(" ", A);
        }
        public override void Output()
        {
            Console.WriteLine($"{result}");
        }
    }
    class B_ : ILOSolver
    {
        public static TestSeed[] TestSeeds = new TestSeed[]
        {
new TestSeed("4\nnaan", "nyaan"),
new TestSeed("4\nnear", "near"),
new TestSeed("8\nnational", "nyationyal"),
new TestSeed("4\nnaan", "nyaan"),
new TestSeed("4\nnear", "near"),
new TestSeed("8\nnational", "nyationyal")
        };

        int N;
        string S;
        string result;
        public override void Input()
        {
            object _;
            (N, _) = Console.ReadLine()!.Split().Select(v => int.Parse(v)).ToArray();
            S = Console.ReadLine();
        }

        public override void Solve()
        {
            result = Regex.Replace(S, @"na", "nya");
        }
        public override void Output()
        {
            Console.WriteLine($"{result}");
        }
    }

    class C_ : ILOSolver
    {
        public static TestSeed[] TestSeeds = new TestSeed[]
        {
new TestSeed("5 1 2\nrrefa", "3"),
new TestSeed("8 1000000000 1000000000\nbcdfcgaa", "4000000000"),
        };

        long N, A, B;
        string S;
        long result;
        public override void Input()
        {
            object _;
            (N, A, B, _) = Console.ReadLine()!.Split().Select(v => long.Parse(v)).ToArray();
            S = Console.ReadLine();
        }
        private int Diff(string s)
        {
            int r = 0;
            for (int i = 0; i < N / 2; i++)
            {
                if (s[i] != s[(int)(N - 1 - i)])
                {
                    ++r;
                }
            }
            return r;
        }

        public override void Solve()
        {
            if (Diff(S) == 0) return;
            result = long.MaxValue;
            for (int i = 0; i <= N / 2; i++)
            {
                var s = S.Substring(i, S.Length - i) + S.Substring(0, i);
                var d = Diff(s);
                result = Math.Min(i * A + d * B, result);
            }
        }
        public override void Output()
        {
            Console.WriteLine($"{result}");
        }
    }
    class D_ : ILOSolver
    {
        public static TestSeed[] TestSeeds = new TestSeed[]
        {
new TestSeed("2 19\n2 3\n5 6", "Yes"),
new TestSeed("2 18\n2 3\n5 6", "No"),
new TestSeed("3 1001\n1 1\n2 1\n100 10", "Yes"),
        };

        int N, X;
        List<(int Price, int Count)> AB = new List<(int Price, int Count)>();
        string result;
        public override void Input()
        {
            object _;
            (N, X, _) = Console.ReadLine()!.Split().Select(v => int.Parse(v)).ToArray();
            AB.Add((0, 0));
            for (int i = 0; i < N; i++)
            {
                var (a, b, _) = Console.ReadLine()!.Split().Select(v => int.Parse(v)).ToList();
                AB.Add((a, b));
            }
        }
        bool[,] flag;
        int[,] DP;
        private int f(int i, int remain)
        {
            if (flag[i, remain])
            {
                return DP[i, remain];
            }
            flag[i, remain] = true;
            if (remain == 0)
            {
                return 0;
            }
            var ab = AB[i];
            for (int j = 0; j <= ab.Count; j++)
            {
                var rr = remain - ab.Price * j;
                if (rr == 0)
                {
                    return DP[i, remain] = 0;
                }
                if (rr < 0)
                {
                    break;
                }
                if (i + 1 <= N)
                {
                    var v = f(i + 1, rr);
                    if (v == 0)
                    {
                        return DP[i, remain] = 0;
                    }
                }
            }
            return DP[i, remain] = -1;
        }
        public override void Solve()
        {
            flag = new bool[N + 1, X + 1];
            DP = new int[N + 1, X + 1];
            result = f(0, X) == 0 ? "Yes" : "No";


        }
        public override void Output()
        {
            Console.WriteLine($"{result}");
        }
    }

}