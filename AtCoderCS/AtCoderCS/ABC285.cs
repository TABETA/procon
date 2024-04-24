using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace Procon.AtCoder.ABC285
{
    class A : ILOSolver
    {
        public static TestSeed[] TestSeeds = new TestSeed[]
        {
                    new TestSeed(
                            @"1 2",
                            "Yes"
                            ),
                    new TestSeed(
                            @"2 8",
                            "No"
                            ),
                    new TestSeed(
                            @"14 15",
                            "No"
                            ),

        };

        int a;
        int b;
        string result;
        public override void Input()
        {
            object _;
            (a, b, _) = Console.ReadLine()!.Split().Select(v => int.Parse(v)).ToArray();
        }

        public override void Solve()
        {
            result = (b == (a * 2) || b == (a * 2 + 1)) ? "Yes" : "No";
        }
        public override void Output()
        {
            Console.WriteLine($"{result}");
        }
    }
    class B : ILOSolver
    {
        public static TestSeed[] TestSeeds = new TestSeed[]
        {
                    new TestSeed(
                            @"6
abcbac",
                            @"5
1
2
0
1"
                            ),

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
            result = "";
            for (int i = 1; i < N; i++)
            {
                var l = 0;
                for (int j = 0; j < N - i; j++)
                {
                    if (S[j] != S[i + j])
                    {
                        ++l;
                    }
                    else
                    {
                        break;
                    }
                }
                result += $"{l}" + Environment.NewLine;
            }
        }
        public override void Output()
        {
            Console.WriteLine($"{result}");
        }
    }
    class C : ILOSolver
    {
        public static TestSeed[] TestSeeds = new TestSeed[]
        {
                    new TestSeed(
                            @"AB",
                            @"28"
                            ),

                    new TestSeed(
                            @"C",
                            @"3"
                            ),
                    new TestSeed(
                            @"BRUTMHYHIIZP",
                            @"10000000000000000"
                            ),
        };

        string S;
        long result;
        public override void Input()
        {
            S = Console.ReadLine();
        }

        public override void Solve()
        {
            result = 0;
            long j = 1;
            for (int i = S.Length - 1; i >= 0; i--)
            {
                long v = (S[i] - '@') * j;
                result += v;
                j *= 26;
            }
        }
        public override void Output()
        {
            Console.WriteLine($"{result}");
        }
    }
//    class D : ILOSolver
//    {
//        public static TestSeed[] TestSeeds = new TestSeed[]
//        {
//                    new TestSeed(
//                            @"3
//a b
//c d
//b a",
//                            @"No"
//                            ),
//                    new TestSeed(
//                            @"2
//b m
//m d",
//                            @"Yes"
//                            ),

//                    new TestSeed(
//                            @"3
//a b
//b c
//c a",
//                            @"No"
//                            ),
//                    new TestSeed(
//                            @"5
//aaa bbb
//yyy zzz
//ccc ddd
//xxx yyy
//bbb ccc",
//                            @"Yes"
//                            ),
//        };
//        int N;
//        Dictionary<string, string> ST = new Dictionary<string, string>();
//        string result;
//        public override void Input()
//        {
//            N = int.Parse(Console.ReadLine());
//            var UF = new Lib.UnionFind<string>();
//            for (int i = 0; i < N; i++)
//            {
//                object _;
//                var (s, t, _) = Console.ReadLine().Split().ToArray();
//                result = "Yes";
//                if (!UF.Unite(s, t))
//                {
//                    result = "No";
//                }
//            }
//        }

//        public override void Solve()
//        {

//        }
//        public override void Output()
//        {
//            Console.WriteLine($"{result}");
//        }
//    }

    class E : ILOSolver
    {
        public static TestSeed[] TestSeeds = new TestSeed[]
        {
                    new TestSeed(
                            @"2
b m
m d",
                            @"Yes"
                            ),

                    new TestSeed(
                            @"3
a b
b c
c a",
                            @"No"
                            ),
                    new TestSeed(
                            @"5
aaa bbb
yyy zzz
ccc ddd
xxx yyy
bbb ccc",
                            @"Yes"
                            ),
        };
        int N;
        List<int> A = new List<int>();
        string result;
        public override void Input()
        {

            N = int.Parse(Console.ReadLine());
            A = Console.ReadLine().Split().Select(s => int.Parse(s)).ToList();
        }
        private long dp(int i)
        {
            return Math.Max(dp(i + 1), dp(i + 1));
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