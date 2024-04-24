using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Procon.AtCoder
{
    class ABC287
    {

        class A_ : ILOSolver
        {
            public static TestSeed[] TestSeeds = new TestSeed[]
            {
new TestSeed("3\nFor\nAgainst\nFor", "Yes"),
new TestSeed("5\nAgainst\nAgainst\nFor\nAgainst\nFor", "No"),
new TestSeed("1\nFor", "Yes")
            };

            int N;
            string result;
            public override void Input()
            {
                object _;
                (N, _) = Console.ReadLine()!.Split().Select(v => int.Parse(v)).ToArray();
                int th = N / 2;
                int f = 0;
                result = "No";
                for (int i = 0; i < N; i++)
                {
                    var s = Console.ReadLine();
                    if (s == "For")
                    {
                        if (++f > th)
                        {
                            result = "Yes";
                            return;
                        }
                    }

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
new TestSeed("3 3\n142857\n004159\n071028\n159\n287\n857", "2"),
new TestSeed("5 4\n235983\n109467\n823476\n592801\n000333\n333\n108\n467\n983", "3"),
new TestSeed("4 4\n000000\n123456\n987111\n000000\n000\n111\n999\n111", "3")
            };

            int N;
            int M;
            List<string> S = new List<string>();
            Dictionary<string, int> T = new Dictionary<string, int>();
            int result;
            public override void Input()
            {
                object _;
                (N, M, _) = Console.ReadLine()!.Split().Select(v => int.Parse(v)).ToArray();
                for (int i = 0; i < N; i++)
                {
                    var s = Console.ReadLine();
                    S.Add(s.Substring(3));
                }
                for (int i = 0; i < M; i++)
                {
                    var t = Console.ReadLine();
                    if (!T.ContainsKey(t))
                    {
                        T[t] = 0;
                    }
                }
                foreach (var s in S)
                {
                    if (T.ContainsKey(s))
                    {
                        result++;
                    }
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
            public class UnionFind
            {
                public UnionFind() { }
                private Dictionary<int, int> _parents = new Dictionary<int, int>();

                public bool Unite(int p, int c)
                {
                    var pr = Root(p);
                    var cr = Root(c);
                    if (pr.Equals(cr))
                    {
                        return false;
                    }
                    if (Count(pr) < Count(cr))
                    {
                        var _ = pr;
                        pr = cr;
                        cr = _;
                    }
                    _parents[pr] += _parents[cr];
                    _parents[cr] = pr;
                    return true;
                }
                public int Count(int n)
                {
                    return -_parents[Root(n)];
                }
                public int Root(int n)
                {
                    if (!_parents.ContainsKey(n))
                    {
                        _parents[n] = -1;
                    }
                    while (true)
                    {
                        if (_parents[n] < 0)
                        {
                            return n;
                        }
                        if (n.Equals(_parents[n]))
                        {
                            return n;
                        }
                        else
                        {
                            n = _parents[n];
                        }
                    }
                }
            }

            public static TestSeed[] TestSeeds = new TestSeed[]
            {
new TestSeed("4 3\n1 3\n4 2\n3 2", "Yes"),
new TestSeed("2 0", "No"),
new TestSeed("5 5\n1 2\n2 3\n3 4\n4 5\n5 1", "No")
            };

            int N;
            int M;
            List<int> U = new List<int>();
            List<int> V = new List<int>();
            UnionFind uf = new UnionFind();
            string result = "Yes";
            public override void Input()
            {
                object _;
                (N, M, _) = Console.ReadLine()!.Split().Select(v => int.Parse(v)).ToArray();
                if (M == 0)
                {
                    result = "No";
                    return;
                }
                if (M == 1)
                {
                    result = "Yes";
                    return;
                }

                for (int i = 0; i < M; i++)
                {
                    var (u, v, _) = Console.ReadLine()!.Split().Select(v => int.Parse(v)).ToArray();
                    U.Add(u);
                    V.Add(v);
                    if (!uf.Unite(u, v))
                    {
                        result = "No";
                    }
                }
                if (uf.Count(U[0]) != N)
                {
                    result = "No";
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
        class D_ : ILOSolver
        {
            public static TestSeed[] TestSeeds = new TestSeed[]
            {
new TestSeed("a?c\nb?", "Yes\nNo\nNo"),
new TestSeed("atcoder\n?????", "Yes\nYes\nYes\nYes\nYes\nYes"),
new TestSeed("beginner\ncontest", "No\nNo\nNo\nNo\nNo\nNo\nNo\nNo")
            };

            string S;
            string T;
            string result;
            public override void Input()
            {
                S = Console.ReadLine();
                T = Console.ReadLine();
            }

            public override void Solve()
            {
                int f = 0;
                for (int i = 0; i < T.Length; i++)
                {
                    if (T[i] == S[i] ||
                        T[i] == '?' ||
                        S[i] == '?'
                        )
                    {
                        f++;
                        continue;
                    }
                    break;
                }
                int b = 0;
                for (int i = 0; i < T.Length; i++)
                {
                    int t = T.Length - 1 - i;
                    int s = S.Length - 1 - i;
                    if (T[t] == S[s] ||
                        T[t] == '?' ||
                        S[s] == '?'
                        )
                    {
                        b++;
                        continue;
                    }
                    break;
                }
                for (int i = 0; i <= T.Length; i++)
                {
                    Console.WriteLine((T.Length - i <= b && i <= f) ? "Yes" : "No");
                }
            }
            public override void Output()
            {
                //Console.WriteLine($"{result}");
            }
        }


    }
}
