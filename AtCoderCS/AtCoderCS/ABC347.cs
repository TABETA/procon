using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Procon.AtCoder
{
    class ABC347
    {
        class A_ : ILOSolver
        {
            public static TestSeed[] TestSeeds = new TestSeed[]
            {
new TestSeed("5 2\r\n2 5 6 7 10\r\n", "1 3 5\r\n"),
            };

            string result = "";
            public override void Input()
            {
                object _;
                int N, K;
                (N, K, _) = Console.ReadLine()!.Split().Select(v => int.Parse(v)).ToArray();
                var A = Console.ReadLine()!.Split().Select(v => int.Parse(v)).ToArray();
                var temp = new List<int>();
                foreach (var a in A)
                {
                    if (a % K == 0)
                    {
                        temp.Add(a / K);
                    }

                }

                result = string.Join(" ", temp);
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
new TestSeed("yay\r\n", "5\r\n"),
new TestSeed("aababc\r\n", "17\r\n"),
new TestSeed("abracadabra\r\n", "54\r\n"),
            };

            string result = "";
            public override void Input()
            {
                object _;
                var S = Console.ReadLine();
                var P = new HashSet<string>();
                for (int i = 1; i <= S.Length; i++)
                {
                    for (int j = 0; j + i <= S.Length; j++)
                    {
                        var p = S.Substring(j, i);
                        P.Add(p);
                    }

                }
                result = P.Count.ToString();
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
new TestSeed("3 2 5\r\n1 2 9\r\n", "Yes\r\n"),
new TestSeed("2 5 10\r\n10 15\r\n", "No\r\n"),
new TestSeed("4 347 347\r\n347 700 705 710\r\n", "Yes\r\n"),
new TestSeed("2 10 10\r\n1 2\r\n", "Yes\r\n"),
            };

            string result = "";
            public override void Input()
            {
                object _;
                long N, A, B;
                (N, A, B, _) = Console.ReadLine()!.Split().Select(v => long.Parse(v)).ToArray();
                var D = Console.ReadLine()!.Split().Select(v => long.Parse(v) - 1).ToArray();
                var H = new SortedSet<long>();
                foreach (var d in D)
                {
                    var h = d % (A + B);
                    H.Add(h);
                }
                result = "No";
                if ((H.Min + (A + B) - H.Max) > B)
                {
                    result = "Yes";
                    return;
                }
                var hh = H.ToArray();

                for (int i = 0; i < hh.Length - 1; i++)
                {
                    if (hh[i + 1] - hh[i] > B)
                    {
                        result = "Yes";
                        return;
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
    }

}
