using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;

namespace Procon.AtCoder.ABC214
{
    class C_ : ILOSolver
    {
        public static TestSeed[] TestSeeds = new TestSeed[]
        {
            new TestSeed("3\n4 1 5\n3 10 100", "3\n7\n8"),
            new TestSeed("4\n100 100 100 100\n1 1 1 1", "1\n1\n1\n1"),
            new TestSeed("4\n1 2 3 4\n1 2 4 7", "1\n2\n4\n7"),
            new TestSeed("8\n84 87 78 16 94 36 87 93\n50 22 63 28 91 60 64 27", "50\n22\n63\n28\n44\n60\n64\n27")
        };

        int N;
        List<int> S = new List<int>();
        List<int> T = new List<int>();
        List<(int Index, int Distance)>[] E;
        int[] V;
        Lib.PriorityQueue<int> Q;
        string result;
        public override void Input()
        {
            object _;
            (N, _) = Console.ReadLine()!.Split().Select(v => int.Parse(v)).ToArray();
            E = new List<(int Index, int Distance)>[N + 1];
            for (int i = 0; i < N + 1; i++)
            {
                E[i] = new List<(int Index, int Distance)>();

            }
            V = new int[N + 1];
            for (int i = 0; i < N + 1; i++) V[i] = int.MaxValue;
            V[0] = 0;
            S.Add(0);
            T.Add(0);
            S.AddRange(Console.ReadLine()!.Split().Select(v => int.Parse(v)).ToList());
            T.AddRange(Console.ReadLine()!.Split().Select(v => int.Parse(v)).ToList());
            for (int i = 1; i < N + 1; i++)
            {
                var s = S[i];
                var t = T[i];
                var j = i + 1 == N + 1 ? 1 : i + 1;
                E[i].Add((j, s));
                T.Add(t);
                E[0].Add((i, t));
            }
            Q = new Lib.PriorityQueue<int>(N + 1, new Comp(V));
        }

        class Comp : IComparer
        {
            public Comp(int[] vertices)
            {
                _V = vertices;
            }
            int[] _V;

            public int Compare(object? x, object? y)
            {
                var ix = x as int?;
                var iy = y as int?;
                return _V[ix.Value] < _V[iy.Value] ? 1 : -1;
            }
        }
        public override void Solve()
        {
            Q.Push(0);
            while (Q.Count > 0)
            {
                var q = Q.Pop();
                foreach (var e in E[q])
                {
                    if (e.Index == q) continue;
                    var nc = V[q] + e.Distance;
                    if (V[e.Index] > nc)
                    {
                        V[e.Index] = nc;
                        Q.Push(e.Index);
                    }
                }
            }
            result = string.Join(Environment.NewLine, V.Skip(1));
        }
        public override void Output()
        {
            Console.WriteLine($"{result}");
        }
    }

}
