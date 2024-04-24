using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace Procon.AtCoder.EDPC
{
    class TEMPLATE : ILOSolver
    {
        public static TestSeed[] TestSeeds = new TestSeed[]
        {
                    new (
                            @"",
                            ""
                            ),
        };

        int HH;
        int W;
        List<List<int>> CELL = new();
        int result;
        public override void Input()
        {
            object _;
            (HH, W, _) = Console.ReadLine()!.Split().Select(v => int.Parse(v)).ToArray();
            CELL.Add(Enumerable.Repeat(0, W + 1).ToList());
            for (int i = 0; i < HH; i++)
            {
                var l = new List<int> { 0 };
                l.AddRange(Console.ReadLine().Select(c => c == '.' ? 0 : -1).ToList());
                CELL.Add(l);
            }
        }

        public override void Solve()
        {
            CELL[1][1] = 1;
            for (int i = 1; i < HH + 1; i++)
            {
                for (int j = 1; j < W + 1; j++)
                {
                    if (i == 1 && j == 1) continue;
                    if (CELL[i][j] != -1)
                    {
                        int c = 0;
                        if (CELL[i - 1][j] != -1)
                        {
                            c += CELL[i - 1][j];
                        }
                        if (CELL[i][j - 1] != -1)
                        {
                            c += CELL[i][j - 1];
                        }
                        CELL[i][j] = (int)(c % (1E9 + 7));
                    }
                }
            }
            result = CELL[HH][W];
        }
        public override void Output()
        {
            Console.WriteLine($"{result}");
        }
    }

    class A : ILOSolver
    {
        public static void RunAll()
        {
            if (!AssemblyState.IsDebug)
            {
                new A().Run();
            }
            else
            {
                foreach (var t in new (string Input, string Expected)[]{
                            (
                            @"4
10 30 40 20",
                            "30"
                            ),
                            (
                            @"2
10 10",
                            "0"
                            ),
                            (
                            @"6
30 10 60 10 60 50",
                            "40"
                            ),
                            })
                {
                    using var _ = new Test(t.Input, t.Expected);
                    new A().Run();
                }
            }
        }
        int N = 0;
        List<int> H = null!;
        int result;
        public override void Input()
        {
            N = int.Parse(Console.ReadLine()!);
            H = Console.ReadLine()!.Split().Select(s => int.Parse(s)).ToList();
            H.Insert(0, 0);
        }
        public override void Solve()
        {
            var DP = new int[N + 1];
            DP[0] = 0;
            for (int i = 2; i < N + 1; i++)
            {
                Func<int, int> dp = (j) => {
                    return DP[j] + Math.Abs(H[j] - H[i]);
                };
                if (i > 2)
                {
                    DP[i] = Math.Min(dp(i - 2), dp(i - 1));
                }
                else
                {
                    DP[i] = dp(i - 1);
                }
            }
            result = DP[N];
        }

        public override void Output()
        {
            Console.WriteLine($"{result}");
        }
    }
    class B : ILOSolver
    {
        public static void RunAll()
        {
            if (!AssemblyState.IsDebug)
            {
                new B().Run();
            }
            else
            {
                foreach (var t in new (string Input, string Expected)[]{
                            (
                            @"5 3
10 30 40 50 20",
                            "30"
                            ),
                            (
                            @"3 1
10 20 10",
                            "20"
                            ),
                            (
                            @"2 100
10 10",
                            "0"
                            ),
                            (
                            @"10 4
40 10 20 70 80 10 20 70 80 60",
                            "40"
                            ),
                            })
                {
                    using var _ = new Test(t.Input, t.Expected);
                    new B().Run();
                }
            }
        }
        int N = 0;
        int K = 0;
        List<int> H = null!;
        int result;
        public override void Input()
        {
            object _;
            (N, K, _) = Console.ReadLine()!.Split().Select(s => int.Parse(s)).ToArray();
            H = Console.ReadLine()!.Split().Select(s => int.Parse(s)).ToList();
            H.Insert(0, 0);
        }
        public override void Solve()
        {
            var DP = new int[N + 1];
            DP[0] = 0;
            for (int i = 2; i < N + 1; i++)
            {
                Func<int, int> dp = (j) => {
                    if (j > 0)
                    {
                        return DP[j] + Math.Abs(H[j] - H[i]);
                    }
                    else
                    {
                        return int.MaxValue;
                    }
                };
                var l = new List<int>();
                foreach (var k in Enumerable.Range(i - K, K))
                {
                    l.Add(dp(k));

                }
                DP[i] = l.Min();
            }
            result = DP[N];
        }

        public override void Output()
        {
            Console.WriteLine($"{result}");
        }
    }
    class C : ILOSolver
    {
        public static void RunAll()
        {
            if (!AssemblyState.IsDebug)
            {
                new C().Run();
            }
            else
            {
                foreach (var t in new (string Input, string Expected)[]{
                            (
                            @"3
10 40 70
20 50 80
30 60 90",
                            "210"
                            ),
                            (
                            @"1
100 10 1",
                            "100"
                            ),
                            (
                            @"7
6 7 8
8 8 3
2 5 2
7 8 6
4 6 8
2 3 4
7 5 1",
                            "46"
                            ),
                            })
                {
                    using var _ = new Test(t.Input, t.Expected);
                    new C().Run();
                }
            }
        }
        int N = 0;
        List<List<int>> ABC = new();
        int result;
        public override void Input()
        {
            N = int.Parse(Console.ReadLine()!);
            for (int i = 0; i < N; i++)
            {
                ABC.Add(Console.ReadLine()!.Split().Select(s => int.Parse(s)).ToList());
            }
            ABC.Insert(0, new());
        }
        public override void Solve()
        {
            var DP = new int[N + 1][];
            DP[0] = new int[] { 0, 0, 0 };
            for (int i = 1; i < N + 1; i++)
            {
                Func<int, int> dp = (k) => {
                    if (i > 0)
                    {
                        return new[]{
                                    DP[i-1][(k+1)%3] + ABC[i][k],
                                    DP[i-1][(k+2)%3] + ABC[i][k],
                                }.Max();
                    }
                    else
                    {
                        return int.MinValue;
                    }
                };
                DP[i] = new int[3];
                for (int k = 0; k < 3; k++)
                {
                    DP[i][k] = dp(k);
                }
            }
            result = DP[N].Max();
        }

        public override void Output()
        {
            Console.WriteLine($"{result}");
        }
    }
    class D : ILOSolver
    {
        public static void RunAll()
        {
            if (!AssemblyState.IsDebug)
            {
                new D().Run();
            }
            else
            {
                foreach (var t in new (string Input, string Expected)[]{
                            (
                            @"3 8
3 30
4 50
5 60",
                            "90"
                            ),
                            (
                            @"5 5
1 1000000000
1 1000000000
1 1000000000
1 1000000000
1 1000000000",
                            "5000000000"
                            ),
                            (
                            @"6 15
6 5
5 6
6 4
6 6
3 5
7 2",
                            "17"
                            ),
                            })
                {
                    using var _ = new Test(t.Input, t.Expected);
                    new D().Run();
                }
            }
        }
        int N = 0;
        int W = 0;
        List<List<int>> WV = new();
        long result;
        public override void Input()
        {
            object _;
            (N, W, _) = Console.ReadLine()!.Split().Select(s => int.Parse(s)).ToList();
            for (int i = 0; i < N; i++)
            {
                WV.Add(Console.ReadLine()!.Split().Select(s => int.Parse(s)).ToList());
            }
            WV.Insert(0, new List<int> { 0, 0 });
        }
        public override void Solve()
        {
            result = 0;
            var DP = new long[N + 1][];
            for (int i = 0; i < DP.Length; i++)
            {
                DP[i] = Enumerable.Repeat(0L, W + 1).ToArray();
            }
            for (int i = 1; i < N + 1; i++)
            {
                for (int w = W; w >= 0; w--)
                {
                    var prev = w + WV[i][0];
                    if (prev <= W)
                    {
                        DP[i][w] = Math.Max(DP[i - 1][w], DP[i - 1][prev] + WV[i][1]);
                    }
                    else
                    {
                        DP[i][w] = DP[i - 1][w];
                    }
                }
            }
            result = DP[N][0];
        }
        public override void Output()
        {
            Console.WriteLine($"{result}");
        }
    }
    class E : ILOSolver
    {
        public static TestSeed[] TestSeeds = new TestSeed[]
        {
                    new (
                            @"3 8
3 30
4 50
5 60",
                            "90"
                            ),
                    new (
                            @"1 1000000000
1000000000 10",
                            "10"
                            ),
                    new (
                            @"6 15
6 5
5 6
6 4
6 6
3 5
7 2",
                            "17"
                            ),
        };
        int N = 0;
        int W = 0;
        List<List<int>> WV = new();
        long result;
        public override void Input()
        {
            object _;
            (N, W, _) = Console.ReadLine()!.Split().Select(s => int.Parse(s)).ToList();
            for (int i = 0; i < N; i++)
            {
                WV.Add(Console.ReadLine()!.Split().Select(s => int.Parse(s)).ToList());
            }
            WV.Insert(0, new List<int> { 0, 0 });
        }
        public override void Solve()
        {
            const int VMAX = 10000;
            result = 0;
            var DP = new long[N + 1][];
            for (int i = 0; i < DP.Length; i++)
            {
                DP[i] = Enumerable.Repeat(-1L, VMAX + 1).ToArray();
            }
            DP[0][0] = 0;
            for (int i = 1; i < N + 1; i++)
            {
                for (int v = 0; v < VMAX + 1; v++)
                {
                    var prev = v - WV[i][1];
                    var l = new List<long> { -1 };
                    if (DP[i - 1][v] != -1)
                    {
                        l.Add(DP[i - 1][v]);
                    }
                    if (0 <= prev && prev < VMAX + 1 && DP[i - 1][prev] != -1)
                    {
                        l.Add(DP[i-1][prev] + WV[i][0]);
                    }
                    DP[i][v] = l.Max();
                    if (DP[i][v] > W)
                    {
                        DP[i][v] = -1;
                    }
                    if(DP[i][v] != -1)
                    {
                        result = Math.Max(result, v);
                    }
                }
            }
        }
        public override void Output()
        {
            Console.WriteLine($"{result}");
        }
    }
    class F : ILOSolver
    {
        public static TestSeed[] TestSeeds = new TestSeed[]
        {
                    new (
                            @"axyb
abyxb",
                            "ayb"
                            ),
                    new (
                            @"aa
xayaz",
                            "aa"
                            ),
                    new (
                            @"a
z",
                            ""
                            ),
                    new (
                            @"abracadabra
avadakedavra",
                            "aaadara"
                            ),
        };
        string s;
        string t;
        string result;
        public override void Input()
        {
            s = Console.ReadLine();
            t = Console.ReadLine();
        }
        private string dp(int i, int j)
        {
            if(i >= s.Length ) return "";
            if(j >= t.Length ) return "";
            var l = new List<string>();
            l.Add(dp(i + 1, j));
            var k = t.Substring(j).IndexOf(s[i]);
            if (k != -1)
            {
                l.Add(s[i] + dp(i + 1, j + k));
            }
            return l.Aggregate((max,cur) => max.Length > cur.Length ? max : cur );
        }
        public override void Solve()
        {
            int S = s.Length + 1;
            int T = t.Length + 1;
            var DP = new string[S][];
            for (int i = 0; i < S; i++)
            {
                DP[i] = Enumerable.Repeat("", t.Length + 1).ToArray();
            }
            for (int i = 1; i < S; i++)
            {
                for (int j = 1; j < T; j++)
                {
                    var l = new List<string>();
                    l.Add(DP[i - 1][j]);
                    l.Add(DP[i][j - 1]);
                    if (s[i-1] == t[j-1])
                    {
                        l.Add(DP[i-1][j - 1] + s[i - 1]);
                    }
                    DP[i][j] = l.Aggregate((max, cur) => max.Length > cur.Length ? max : cur);
                }
            }
            result = DP[S-1][T-1];
        }
        public override void Output()
        {
            Console.WriteLine($"{result}");
        }
    }
    class G : ILOSolver
    {
        public static TestSeed[] TestSeeds = new TestSeed[]
        {
                    new (
                            @"4 5
1 2
1 3
3 2
2 4
3 4",
                            "3"
                            ),
                    new (
                            @"6 3
2 3
4 5
5 6",
                            "2"
                            ),
                    new (
                            @"5 8
5 3
2 3
2 4
5 2
5 1
1 4
4 3
1 3",
                            "3"
                            ),
        };

        int N;
        int M;
        List<int> x = new();
        List<int> y = new();
        List<List<int>> g = new();
        int result;
        public override void Input()
        {
            object _;
            var (n, m, _) = Console.ReadLine()!.Split().Select(v => int.Parse(v)).ToArray();
            (N, M) = (n, m);
            for (int i = 0; i < N+1; i++) g.Add(new());
            for (int i = 0; i < M; i++) x.Add(0);
            for (int i = 0; i < M; i++) y.Add(0);
            for (int i = 0; i < M; i++)
            {
                (x[i], y[i], _) = Console.ReadLine()!.Split().Select(v => int.Parse(v)).ToArray();
                g[y[i]].Add(x[i]);
            }
        }
        int[] DP;

        private int dp(int i)
        {
            if (g[i].Count == 0)
            {
                DP[i] = 0;
            }
            else
            {
                var l = new List<int>();
                foreach (var v in g[i])
                {
                    if (DP[v] != -1)
                    {
                        l.Add(DP[v] + 1);
                    }
                    else
                    {
                        l.Add(dp(v) + 1);
                    }
                }
                DP[i] = l.Max();

            }
            return DP[i];
        }

        public override void Solve()
        {
            DP = Enumerable.Repeat(-1, N + 1).ToArray();
            var l = new List<int>();
            for (int i = 1; i < N+1; i++)
            {
                l.Add(dp(i));
            }
            result = l.Max();
        }
        public override void Output()
        {
            Console.WriteLine($"{result}");
        }
    }
    class H : ILOSolver
    {
        public static TestSeed[] TestSeeds = new TestSeed[]
        {
                    new (
                            @"3 4
...#
.#..
....",
                            "3"
                            ),
                    new (
                            @"5 2
..
#.
..
.#
..",
                            "0"
                            ),
                    new (
                            @"5 5
..#..
.....
#...#
.....
..#..",
                            "24"
                            ),
                    new (
                            @"20 20
....................
....................
....................
....................
....................
....................
....................
....................
....................
....................
....................
....................
....................
....................
....................
....................
....................
....................
....................
....................",
                            "345263555"
                            ),
        };

        int HH;
        int W;
        List<List<int>> CELL = new();
        int result;
        public override void Input()
        {
            object _;
            (HH, W, _) = Console.ReadLine()!.Split().Select(v => int.Parse(v)).ToArray();
            CELL.Add(Enumerable.Repeat(0, W+1).ToList());
            for (int i = 0; i < HH; i++)
            {
                var l = new List<int> { 0 };
                l.AddRange(Console.ReadLine().Select(c => c == '.' ? 0 : -1).ToList());
                CELL.Add(l);
            }
        }

        public override void Solve()
        {
            CELL[1][1] = 1;
            for (int i = 1; i < HH + 1; i++)
            {
                for (int j = 1; j < W + 1; j++)
                {
                    if (i == 1 && j == 1) continue;
                    if (CELL[i][j] != -1)
                    {
                        int c = 0;
                        if (CELL[i - 1][j] != -1)
                        {
                            c += CELL[i - 1][j];
                        }
                        if (CELL[i][j - 1] != -1)
                        {
                            c += CELL[i][j - 1];
                        }
                        CELL[i][j] = (int)(c % (1E9 + 7));
                    }
                }
            }
            result = CELL[HH][W];
        }
        public override void Output()
        {
            Console.WriteLine($"{result}");
        }
    }
    class I : ILOSolver
    {
        public static TestSeed[] TestSeeds = new TestSeed[]
        {
                    new TestSeed(
                            @"3
0.30 0.60 0.80",
                            "0.612"
                            ),
                    new TestSeed(
                            @"1
0.50",
                            "0.5"
                            ),
                    new TestSeed(
                            @"5
0.42 0.01 0.42 0.99 0.42",
                            "0.3821815872"
                            ),
        };

        int N;
        List<double> p = new List<double>();
        double[][] DP;
        double result;
        public override void Input()
        {
            object _;
            (N, _) = Console.ReadLine()!.Split().Select(v => int.Parse(v)).ToArray();
            p = Console.ReadLine()!.Split().Select(v => double.Parse(v)).ToList();
            p.Insert(0, 0.0);
        }
        private double dp(int i, int j)
        {
            if (DP[i][j] == 0)
            {
                var l = (i - 1 < 0 || j - 1 < 0)
                    ? 0
                    : DP[i - 1][j - 1] * p[i];
                var r = DP[i - 1][j] * (1 - p[i]);
                DP[i][j] = l + r;
            }
            return DP[i][j];
        }

        public override void Solve()
        {
            DP = new double[N + 1][];
            for (int i = 0; i < DP.Length; i++)
            {
                DP[i] = new double[N + 1];
            }
            result = 0.0;
            DP[1][0] = p[1];
            DP[1][1] = (1 - p[1]);
            for (int i = 1; i < N + 1; i++)
            {
                for (int j = 0; j < N + 1; j++)
                {
                    if (i == 1)
                    {
                        if (j == 0) DP[i][j] = (1 - p[i]);
                        else if (j == 1) DP[i][j] = p[i];
                        else DP[i][j] = 0;
                    }
                    var v = dp(i, j);
                    if (i == N && j > N / 2)
                    {
                        result += v;
                    }
                }
            }
        }
        public override void Output()
        {
            Console.WriteLine($"{result}");
        }
    }
    class J : ILOSolver
    {
        public static TestSeed[] TestSeeds = new TestSeed[]
        {
                    new TestSeed(@"3
1 1 1", "5.5"),
                    new TestSeed(@"1
3", "3"),
                    new TestSeed(@"2
1 2", "4.5"),
                    new TestSeed(@"10
1 3 2 3 3 2 3 2 1 3", "54.48064457488221"),
        };

        int N;
        List<int> a = new List<int>();
        double result;
        double[,,] DP;
        public override void Input()
        {
            object _;
            (N, _) = Console.ReadLine()!.Split().Select(v => int.Parse(v)).ToArray();
            a = Console.ReadLine()!.Split().Select(v => int.Parse(v)).ToList();
        }

        public double dp(int c1, int c2, int c3)
        {
            if (DP[c1, c2, c3] != 0) return DP[c1, c2, c3];
            int c0 = N - c1 - c2 - c3;//0個の皿の数
            if (c0 == N) return 0;
            double p0 = (double)c0 / N;//0個の皿が選ばれる確率
            double not_p0 = (1 - p0);//0個の皿以外が選ばれる確率
            double ans = 1 / not_p0;
            if (c1 > 0) ans += dp(c1 - 1, c2, c3) * c1 / N / not_p0;
            if (c2 > 0) ans += dp(c1 + 1, c2 - 1, c3) * c2 / N / not_p0;
            if (c3 > 0) ans += dp(c1, c2 + 1, c3 - 1) * c3 / N / not_p0;
            return DP[c1, c2, c3] = ans;
        }

        public override void Solve()
        {
            var c = new int[4];
            foreach (var v in a)
            {
                c[v]++;
            }
            DP = new double[N + 1, N + 1, N + 1];
            result = dp(c[1], c[2], c[3]);
        }
        public override void Output()
        {
            Console.WriteLine($"{result}");
        }
    }
    class K : ILOSolver
    {
        public static TestSeed[] TestSeeds = new TestSeed[]
        {
new TestSeed("2 4\n2 3", "First"),
new TestSeed("2 5\n2 3", "Second"),
new TestSeed("2 7\n2 3", "First"),
new TestSeed("3 20\n1 2 3", "Second"),
new TestSeed("3 21\n1 2 3", "First"),
new TestSeed("1 100000\n1", "Second"),
new TestSeed("2 4\n2 3", "First"),
new TestSeed("2 5\n2 3", "Second"),
new TestSeed("2 7\n2 3", "First"),
new TestSeed("3 20\n1 2 3", "Second"),
new TestSeed("3 21\n1 2 3", "First"),
new TestSeed("1 100000\n1", "Second")
        };

        int N;
        int k;
        List<int> A = new List<int>();
        string result;
        public override void Input()
        {
            object _;
            (N, k, _) = Console.ReadLine()!.Split().Select(v => int.Parse(v)).ToArray();
            A = Console.ReadLine()!.Split().Select(v => int.Parse(v)).ToList();
            DP = new int[k + 1];
        }
        int[] DP;

        public override void Solve()
        {
            for (int i = 1; i < k + 1; i++)
            {
                foreach (var a in A)
                {
                    var v = i - a;
                    if (v >= 0)
                    {
                        if (DP[v] == 0)
                        {
                            DP[i] = 1;
                        }
                    }
                }
            }
            result = DP[k] == 1 ? "First" : "Second";
        }
        public override void Output()
        {
            Console.WriteLine($"{result}");
        }
    }
    class L : ILOSolver
    {
        public static TestSeed[] TestSeeds = new TestSeed[]
        {
    new TestSeed("4\n10 80 90 30", "10"),
    new TestSeed("3\n10 100 10", "-80"),
    new TestSeed("1\n10", "10"),
    new TestSeed("10\n1000000000 1 1000000000 1 1000000000 1 1000000000 1 1000000000 1", "4999999995"),
    new TestSeed("6\n4 2 9 7 1 5", "2"),
        };

        int N;
        List<long> a = new List<long>();
        long result;
        public override void Input()
        {
            object _;
            (N, _) = Console.ReadLine()!.Split().Select(v => int.Parse(v)).ToArray();
            a = Console.ReadLine()!.Split().Select(v => long.Parse(v)).ToList();
        }

        long[,] DP;
        bool[,] f;

        private long dp(int l, int r)
        {
            if (f[l, r]) return DP[l, r];
            f[l, r] = true;
            if (l == r) return DP[l, r] = a[l - 1];
            DP[l, r] = Math.Max(a[l - 1] - dp(l + 1, r), a[r - 1] - dp(l, r - 1));
            return DP[l, r];
        }

        public override void Solve()
        {
            DP = new long[N + 1, N + 1];
            f = new bool[N + 1, N + 1];
            result = dp(1, N);
        }
        public override void Output()
        {
            Console.WriteLine($"{result}");
        }
    }

}