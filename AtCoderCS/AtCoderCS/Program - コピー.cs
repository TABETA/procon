using System;
using System.Collections.Generic;
using System.Collections;
using System.Linq;

namespace Procon
{
    class Program
    {
        static int Solve(List<int> L)
        {
            for (int i = 0; i < L.Count-1; i++)
            {
                L.Skip(i+1).Select((v,idx) => { Val = v, Index = idx })
                int min = int.MaxValue;
                for (int j = i; j < L.Count; j++)
                {


                }

            }
        }
        static void Main(string[] args)
        {
            var T = int.Parse(Console.ReadLine());
            for (int i = 0; i < T; i++)
            {
                var N = int.Parse(Console.ReadLine());
                var L = Console.ReadLine().Split(' ').Select(s => int.Parse(s)).ToList();
                Console.WriteLine(Solve(L));
            }
        }
    }
}
