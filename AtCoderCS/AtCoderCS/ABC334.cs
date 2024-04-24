using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Procon.AtCoder
{
    class ABC334
    {

        class A_ : ILOSolver
        {
            public static TestSeed[] TestSeeds = new TestSeed[]
            {
new TestSeed("300 100", "Bat"),
new TestSeed("334 343", "Glove")

            };

            int B;
            int G;
            string result;
            public override void Input()
            {
                object _;
                (B, G, _) = Console.ReadLine()!.Split().Select(v => int.Parse(v)).ToArray();
                result = B > G ? "Bat" : "Glove";
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
new TestSeed("5 3 -1 6", "3"),
new TestSeed("-2 2 1 1", "0"),
new TestSeed("-177018739841739480 2436426 -80154573737296504 585335723211047198", "273142010859")

            };

            long A;
            long M;
            long L;
            long R;
            string result;
            public override void Input()
            {
                object _;
                (A, M, L, R, _) = Console.ReadLine()!.Split().Select(v => long.Parse(v)).ToArray();
                var l = (L - A) / M;//1 + 2 / 2 = 1
                l = l * M;//2
                var r = (R - A) - l;//1 + 2 - 2 = 1
                var d = r / M;
                var m = A + l;
                result = $"{d + ((L <= m && m <= R) ? 1 : 0)}";
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
