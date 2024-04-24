using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Procon.AtCoder
{
    class ABC348
    {

        class A_ : ILOSolver
        {
            public static TestSeed[] TestSeeds = new TestSeed[]
            {
new TestSeed(
    "7\r\n",
    "ooxooxo\r\n"),

            };

            string result = "";
            public override void Input()
            {
                var (v, _) = Console.ReadLine()!.Split().Select(v => int.Parse(v)).ToArray();

                for (int i = 0; i < v; i++)
                {
                    result += ((i + 1) % 3 == 0) ? "x" : "o";
                }

            }

            public override void Solve()
            {
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
new TestSeed(
    "4\r\n0 0\r\n2 4\r\n5 0\r\n3 4\r\n",
    "3\r\n3\r\n1\r\n1\r\n"),
new TestSeed(
    "6\r\n3 2\r\n1 6\r\n4 5\r\n1 3\r\n5 5\r\n9 8\r\n",
    "6\r\n6\r\n6\r\n6\r\n6\r\n4\r\n"),
            };

            string result = "";
            public override void Input()
            {

                var N = int.Parse(Console.ReadLine());
                var X = new List<int>();
                var Y = new List<int>();
                for (int i = 0; i < N; i++)
                {
                    var (x, y, _) = Console.ReadLine()!.Split().Select(v => int.Parse(v)).ToArray();
                    X.Add(x);
                    Y.Add(y);
                }
                var R = new List<List<double>>();
                for (int i = 0; i < N; i++)
                {
                    R.Add(new List<double>());
                    for (int j = 0; j < N; j++)
                    {
                        R[i].Add(0);
                    }
                }
                for (int i = 0; i < N; i++)
                {
                    for (int j = i + 1; j < N; j++)
                    {
                        var l = X[i] - X[j];
                        var ll = l * l;
                        var r = Y[i] - Y[j];
                        var rr = r * r;
                        var dist = Math.Sqrt(ll + rr);
                        R[i][j] = R[j][i] = dist;
                    }
                }
                for (int i = 0; i < N; i++)
                {
                    double max = 0;
                    int index = 0;
                    for (int j = 0; j < N; j++)
                    {
                        var v = R[i][j];
                        if (max < v)
                        {
                            max = v;
                            index = j + 1;
                        }
                    }
                    result += $"{index}" + Environment.NewLine;
                }
            }

            public override void Solve()
            {
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
new TestSeed(
    "4\r\n100 1\r\n20 5\r\n30 5\r\n40 1\r\n",
    "40\r\n"),
new TestSeed(
    "10\r\n68 3\r\n17 2\r\n99 2\r\n92 4\r\n82 4\r\n10 3\r\n100 2\r\n78 1\r\n3 1\r\n35 4\r\n",
    "35\r\n"),

            };

            string result = "";
            public override void Input()
            {

                var N = int.Parse(Console.ReadLine());
                var A = new List<long>();
                var C = new List<long>();
                for (int i = 0; i < N; i++)
                {
                    var (x, y, _) = Console.ReadLine()!.Split().Select(v => int.Parse(v)).ToArray();
                    A.Add(x);
                    C.Add(y);
                }
                var D = new Dictionary<long, long>();



                for (int i = 0; i < N; i++)
                {
                    var c = C[i];
                    var a = A[i];
                    if (D.ContainsKey(c))
                    {
                        D[c] = Math.Min(D[c], a);
                    }
                    else
                    {
                        D[c] = a;
                    }
                }
                result = D.Max(d => d.Value).ToString();

            }

            public override void Solve()
            {
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
new TestSeed(
    "",
    ""),
new TestSeed(
    "",
    ""),
new TestSeed(
    "",
    ""),


            };

            string result = "";
            public override void Input()
            {

                var (H, W, _) = Console.ReadLine()!.Split().Select(v => int.Parse(v)).ToArray();
                var A = new List<List<char>>();
                A.Add(new List<char>());
                int row;
                int col;
                for (int i = 1; i <= H; i++)
                {
                    var a = Console.ReadLine();
                    A.Add(new List<char>());
                    A[i].Add(' ');
                    for (int j = 1; j <= a.Length; j++)
                    {
                        var c = a[j - 1];
                        A[i].Add(c);
                        if (c == 'S')
                        {
                            row = i;
                            col = j;
                        }

                    }
                }
                var N = int.Parse(Console.ReadLine());
                var R = new List<int>();
                var C = new List<int>();
                var E = new List<int>();

                for (int i = 0; i < N; i++)
                {
                    var (r, c, e, _) = Console.ReadLine()!.Split().Select(v => int.Parse(v)).ToArray();
                    R.Add(r);
                    C.Add(c);
                    E.Add(e);
                }

            }

            public override void Solve()
            {
            }
            public override void Output()
            {
                Console.WriteLine($"{result}");
            }
        }
        class Z_ : ILOSolver
        {
            public static TestSeed[] TestSeeds = new TestSeed[]
            {
new TestSeed(
    "4\r\n1 2\r\n1 3\r\n2 4\r\n1 1 1 2\r\n",
    "5\r\n"),
new TestSeed(
    "2\r\n2 1\r\n1 1000000000\r\n",
    "1\r\n"),
new TestSeed(
    "7\r\n7 3\r\n2 5\r\n2 4\r\n3 1\r\n3 6\r\n2 1\r\n2 7 6 9 3 4 6\r\n",
    "56\r\n"),


            };

            string result = "";
            Dictionary<int, List<int>> Edges = new Dictionary<int, List<int>>();
            int[][] DP;
            public override void Input()
            {
                var N = int.Parse(Console.ReadLine());
                DP = new int[N][];
                for (int i = 0; i < DP.Length; i++)
                {
                    DP[i] = new int[N];
                    for (int j = 0; j < DP[i].Length; j++)
                    {
                        DP[i][j] = -1;
                    }
                }
                for (int i = 0; i < N - 1; i++)
                {
                    var (a, b, _) = Console.ReadLine()!.Split().Select(v => int.Parse(v)).ToArray();
                    --a; --b;
                    if (!Edges.ContainsKey(a))
                    {
                        Edges[a] = new List<int>();
                    }
                    Edges[a].Add(b);
                    DP[a][b] = 1;

                    if (!Edges.ContainsKey(b))
                    {
                        Edges[b] = new List<int>();
                    }
                    Edges[b].Add(a);
                    DP[b][a] = 1;
                }
                var C = Console.ReadLine()!.Split().Select(v => long.Parse(v)).ToArray();
                var min = long.MaxValue;
                for (int i = 0; i < N; i++)
                {
                    long sum = 0L;
                    for (int j = 0; j < N; j++)
                    {
                        int edges = dp(i, j, new HashSet<int>());
                        sum += C[j] * edges;
                    }
                    min = Math.Min(min, sum);
                }
                result = min.ToString();
            }
            int dp(int c, int t, HashSet<int> visited)
            {
                if (DP[c][t] != -1)
                {
                    return DP[c][t];
                }
                if (c == t)
                {
                    DP[c][t] = DP[t][c] = 0;
                    return 0;// currentとtargetが同じなので0
                }
                visited.Add(c);
                if (!Edges.ContainsKey(c))
                {
                    DP[c][t] = DP[t][c] = -1;
                    return -1; // 到達不可能(-1)を返す
                }

                int edgesCount = -1;
                foreach (var next in Edges[c])
                {
                    if (!visited.Contains(next))
                    {
                        int edges = dp(next, t, new HashSet<int>(visited));
                        if (edges != -1)
                        {
                            edgesCount = edges + 1;
                        }

                    }
                }
                DP[c][t] = DP[t][c] = edgesCount;
                return edgesCount;
            }
            public override void Solve()
            {
            }
            public override void Output()
            {
                Console.WriteLine($"{result}");
            }
        }
    }


}
