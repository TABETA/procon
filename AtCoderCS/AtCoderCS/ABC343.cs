using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Procon.AtCoder
{
    class ABC343
    {

        class A_ : ILOSolver
        {
            public static TestSeed[] TestSeeds = new TestSeed[]
            {
new TestSeed("2 5", "0"),
new TestSeed("0 0", "1"),


            };

            int A;
            int B;
            int result;
            public override void Input()
            {
                object _;
                (A, B, _) = Console.ReadLine()!.Split().Select(v => int.Parse(v)).ToArray();

                result = A + B == 0 ? 1 : 0;
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
new TestSeed("4\r\n0 1 1 0\r\n1 0 0 1\r\n1 0 0 0\r\n0 1 0 0\r\n", "2 3\r\n1 4\r\n1\r\n2\r\n"),


            };

            int N;
            string result;
            public override void Input()
            {
                object _;
                N = int.Parse(Console.ReadLine());
                var results = new List<string>();
                for (int i = 0; i < N; i++)
                {
                    var A = string.Join(" ", Console.ReadLine()!.Split().Select((v, idx) => v == "1" ? $"{idx + 1}" : "").Where(v => v != ""));
                    results.Add(A);
                }
                result = string.Join(Environment.NewLine, results);
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
new TestSeed("345", "343"),
new TestSeed("6", "1"),
new TestSeed("123456789012345", "1334996994331"),


            };

            string result;
            private bool IsKaibun(long v)
            {
                var n = v.ToString();
                var N = n.Length;
                for (int i = 0, j = N - 1; i < j; i++, j--)
                {
                    if (n[i] != n[j])
                    {
                        return false;
                    }
                }
                return true;
            }
            public override void Input()
            {
                object _;
                long N = long.Parse(Console.ReadLine());
                while (N > 0)
                {
                    N = (long)Math.Pow((long)Math.Cbrt(N), 3);
                    if (IsKaibun(N))
                    {
                        break;
                    }
                    --N;
                }
                result = N.ToString();

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
new TestSeed("3 4\r\n1 10\r\n3 20\r\n2 10\r\n2 10\r\n", "2\r\n3\r\n2\r\n2\r\n"),
new TestSeed("1 3\r\n1 3\r\n1 4\r\n1 3\r\n", "1\r\n1\r\n1\r\n"),
new TestSeed("10 10\r\n7 2620\r\n9 2620\r\n8 3375\r\n1 3375\r\n6 1395\r\n5 1395\r\n6 2923\r\n10 3375\r\n9 5929\r\n5 1225\r\n","2\r\n2\r\n3\r\n3\r\n4\r\n4\r\n5\r\n5\r\n6\r\n5\r\n"),


            };

            string result;

            public override void Input()
            {
                object _;
                long N;
                long T;
                (N, T, _) = Console.ReadLine()!.Split().Select(v => long.Parse(v)).ToArray();
                var S = Enumerable.Repeat(0L, (int)N).ToList();
                var D = new Dictionary<long, int>();
                D[0] = (int)N;
                var temp = new List<int>();
                for (int i = 0; i < T; i++)
                {
                    int A, B;
                    (A, B, _) = Console.ReadLine()!.Split().Select(v => int.Parse(v)).ToArray();
                    int v = A - 1;
                    if (D[S[v]] == 1)
                    {
                        D.Remove(S[v]);
                    }
                    else
                    {
                        --D[S[v]];
                    }
                    S[v] += B;
                    if (!D.ContainsKey(S[v]))
                    {
                        D[S[v]] = 1;
                    }
                    else
                    {
                        ++D[S[v]];
                    }
                    temp.Add(D.Keys.Count);
                }
                result = string.Join(Environment.NewLine, temp);
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
