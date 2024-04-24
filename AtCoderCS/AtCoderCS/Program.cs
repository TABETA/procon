using System;
using System.IO;
using System.Collections.Generic;
using System.Collections;
using System.Linq;

internal static class AssemblyState
{
    public const bool IsDebug =
#if DEBUG
    true;
#else
    false;
#endif
}


namespace Procon
{
    public static class Lib
    {
        public static int Gcd(int a, int b) => b > a ? Gcd(b, a) : (b == 0 ? a : Gcd(b, a % b));
        public static long Gcd(long a, long b) => b > a ? Gcd(b, a) : (b == 0 ? a : Gcd(b, a % b));
        public static int Lcm(int a, int b) { return a / Gcd(a, b) * b; }
        public static long Lcm(long a, long b) { return a / Gcd(a, b) * b; }
        public static bool IsPrime(int x)
        {
            int i;
            if (x < 2) return false;
            if (x == 2) return true;
            if (x % 2 == 0) return false;
            for (i = 3; i * i <= x; i += 2) if (x % i == 0) return false;
            return true;
        }

        public class BIT
        {
            int _n;
            List<int> _bit;
            public BIT(int n)
            {
                _n = n + 1;
                _bit = new List<int>();
                for (int _ = 0; _ < n; _++)
                {
                    _bit.Add(0);
                }
            }
            public void Add(int index, int x)
            {
                for (int i = index; i < _n; i += (i & -i))
                {
                    _bit[i] += x;
                }
            }
            public int Sum(int index)
            { 
                int sum = 0;
                for (int i = index; i > 0; i -= (i & -i))
                {
                    sum += _bit[i];
                }
                return sum;
            }
        }
        public class BFS
        {
            private Queue<(int X, int Y, int Depth)> q = new Queue<(int X, int Y, int Depth)>();

            public int Search(List<List<int>> grid, Func<int, bool> f)
            {
                List<List<bool>> ispassed = new List<List<bool>>();
                for (int i = 0; i < grid.Count; i++)
                {
                    for (int j = 0; j < grid[i].Count; j++)
                    {
                        ispassed[i][j] = false;
                    }

                }
                int[] dx = new[] { 1, 0, -1, 0 };
                int[] dy = new[] { 0, 1, 0, -1 };
                while (q.Count > 0)
                {
                    var now = q.Dequeue();
                    for (int i = 0; i < 4; i++)
                    {
                        int nextx = now.X + dx[i];
                        int nexty = now.Y + dy[i];

                        if (nextx >= grid[0].Count) continue;
                        if (nextx < 0) continue;

                        if (nexty >= grid.Count) continue;
                        if (nexty < 0) continue;

                        if (ispassed[nexty][nextx]) continue;

                        ispassed[nexty][nextx] = true;
                        if (f(0))
                        {
                            return 1;
                        }
                        q.Enqueue((nextx, nexty, now.Depth + 1));
                    }
                }
                return -1;
            }
        }
        public class PriorityQueue<T> where T : IComparable<T>
        {
            private readonly T[] _array;
            private readonly IComparer _comparer;
            public int Count { get; private set; } = 0;
            public T Root => _array[0];

            public PriorityQueue(int capacity, IComparer comparer = null)
            {
                _array = new T[capacity];
                _comparer = comparer;
            }
            public void Push(T item)
            {
                _array[this.Count] = item;
                Count += 1;

                var n = Count - 1;
                while (n != 0)
                {
                    var parent = (n - 1) / 2;
                    if (Compare(_array[n], _array[parent]) > 0)
                    {
                        Swap(n, parent);
                        n = parent;
                    }
                    else
                    {
                        break;
                    }
                }
            }

            public T Pop()
            {
                Swap(0, this.Count - 1);
                Count -= 1;

                var parent = 0;
                while (true)
                {
                    var child = 2 * parent + 1;
                    if (child > Count - 1) break;
                    if (child < Count - 1 && Compare(_array[child], _array[child + 1]) < 0) child += 1;
                    if (Compare(_array[parent], _array[child]) < 0)
                    {
                        Swap(parent, child);
                        parent = child;
                    }
                    else
                    {
                        break;
                    }
                }

                return _array[Count];
            }

            public IEnumerable<T> GetAllElements(bool withPop = true)
            {
                int count = Count;
                for (int i = 0; i < count; i++)
                {
                    if (withPop) yield return Pop();
                    else yield return _array[count - i - 1];
                }
            }

            private int Compare(T a, T b)
            {
                if (_comparer == null) return a.CompareTo(b);
                return _comparer.Compare(a, b);
            }

            private void Swap(int a, int b)
            {
                var _ = _array[a];
                _array[a] = _array[b];
                _array[b] = _;
            }
        }
    }
    public static class Extensions
    {
        public static void Deconstruct<T>(this IList<T> list, out T first, out IList<T> rest)
        {
            first = list.Count > 0 ? list[0] : default(T); // or throw
            rest = list.Skip(1).ToList();
        }

        public static void Deconstruct<T>(this IList<T> list, out T first, out T second, out IList<T> rest)
        {
            first = list.Count > 0 ? list[0] : default(T); // or throw
            second = list.Count > 1 ? list[1] : default(T); // or throw
            rest = list.Skip(2).ToList();
        }
        public static void Deconstruct<T>(this IList<T> list, out T first, out T second, out T third, out IList<T> rest)
        {
            first = list.Count > 0 ? list[0] : default(T); // or throw
            second = list.Count > 1 ? list[1] : default(T); // or throw
            third = list.Count > 2 ? list[2] : default(T); // or throw
            rest = list.Skip(3).ToList();
        }
        public static void Deconstruct<T>(this IList<T> list, out T first, out T second, out T third, out T fourth, out IList<T> rest)
        {
            first = list.Count > 0 ? list[0] : default(T); // or throw
            second = list.Count > 1 ? list[1] : default(T); // or throw
            third = list.Count > 2 ? list[2] : default(T); // or throw
            fourth = list.Count > 2 ? list[3] : default(T); // or throw
            rest = list.Skip(4).ToList();
        }
    }
    public interface ITestSeed
    {
    }
    public class TestSeed : ITestSeed
    {
        public TestSeed(string i, string e)
        {
            Input = i;
            Expected = e;
        }
        public string Input;
        public string Expected;
    }
    public class NullTestSeed : ITestSeed
    {
    }

    public static class TestFactory
    {
        public static IDisposable Create(ITestSeed seed)
        {
            var s = seed as TestSeed;
            if (s != null)
            {
                return new Test(s.Input, s.Expected);
            }
            else
            {
                return new NullTest();
            }
        }

    }
    public class NullTest : IDisposable
    {
        public NullTest()
        {
        }
        public void Dispose()
        {
        }

    }
    public class Test : IDisposable
    {
        private StringValidator _validator;
        public Test(string input, string expected)
        {
            _validator = new StringValidator(expected);
            Console.SetIn(new StringReader(input));
            Console.SetOut(_validator);
        }
        private class StringValidator : StringWriter
        {
            public List<string> Expected { get; set; }
            public List<string> Actual { get; set; }
            public bool IsValid { get; set; }
            public int Called { get; set; }
            public string Message
            {
                get
                {
                    return IsValid
                        ? "OK"
                        : string.Join(Environment.NewLine, new[] {
                            "NG.",
                            $"expected is {string.Join(Environment.NewLine, Expected)}.",
                            $"but actual is {string.Join(Environment.NewLine, Actual)}."
                        });
                }
            }
            public StringValidator(string expected)
            {
                Expected = expected.Split(new [] { "\r\n", "\r", "\n" }, StringSplitOptions.None).ToList();
                Actual = new List<string>();
                IsValid = true;
                Called = 0;
            }

            public override void Write(string? value)
            {
                if (value == Environment.NewLine) return;
                var acts = value!.ToString().Split(new[] { "\r\n", "\r", "\n" }, StringSplitOptions.None).ToList();
                for (int i = 0; i < acts.Count; i++)
                {
                    Called++;
                    Actual.Add(acts[i]);
                    try
                    {
                        IsValid &= Actual[Called - 1] == Expected[Called - 1];
                    }
                    catch (ArgumentOutOfRangeException)
                    {
                        IsValid = false;
                        break;
                    }
                }
            }
        }
        private bool _disposed = false;

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        protected virtual void Dispose(bool disposing)
        {
            if (!_disposed)
            {
                if (disposing)
                {
                    Console.SetIn(new StreamReader(Console.OpenStandardInput()));
                    Console.SetOut(new StreamWriter(Console.OpenStandardOutput()));
                    using (var sw = new StreamWriter(Console.OpenStandardOutput()) { AutoFlush = false })
                    {
                        sw.WriteLine(_validator.Message);
                    }
                    _validator.Dispose();
                }
                _disposed = true;
            }
        }

        ~Test()
        {
            Dispose(false);
        }
    }

    interface ISolver
    {
        void Run();
    }
    abstract class ILOSolver : ISolver
    {
        public ILOSolver()
        {
        }
        public void Run()
        {
            Input();
            Solve();
            Output();
        }
        public abstract void Input();
        public abstract void Solve();
        public abstract void Output();
    }


    class Program
    {

        static void Main(string[] args)
        {
            RunAll(typeof(ABC333_D));
        }
        private static ITestSeed[] GetTestSeeds(Type t)
        {
#if DEBUG
            return t.GetField("TestSeeds")!.GetValue(t) as TestSeed[];
#else
                return new ITestSeed[] { new NullTestSeed()};
#endif
        }
        public static void RunAll(Type t)
        {
            foreach (var s in GetTestSeeds(t)!)
            {
                using var _ = TestFactory.Create(s);
                var inst = Activator.CreateInstance(t) as ISolver;
                inst!.Run();
            }
        }

    }
}


namespace Procon
{
    class ABC333_D : ILOSolver
    {
        public static TestSeed[] TestSeeds = new TestSeed[]
        {
            new TestSeed("9\n1 2\n2 3\n2 4\n2 5\n1 6\n6 7\n7 8\n7 9", "5"),
            new TestSeed("6\n1 2\n2 3\n2 4\n3 5\n3 6", "1"),
            new TestSeed("24\n3 6\n7 17\n7 20\n7 11\n14 18\n17 21\n6 19\n5 22\n9 24\n11 14\n6 23\n8 17\n9 12\n4 17\n2 15\n1 17\n3 9\n10 16\n7 13\n2 16\n1 16\n5 7\n1 3", "12")
        };
        string result = "";
        int N = 0;
        Dictionary<int, List<int>> D = new Dictionary<int, List<int>>();
        public override void Input()
        {
            N = int.Parse(Console.ReadLine());
            var U = new List<int>();
            var V = new List<int>();
            for (int i = 0; i < N-1; i++)
            {
                var (u,v,_) = Console.ReadLine()!.Split().Select(v => int.Parse(v)).ToArray();
                if (!D.ContainsKey(u))
                {
                    D[u] = new List<int>();
                }
                D[u].Add(v);
                if (!D.ContainsKey(v))
                {
                    D[v] = new List<int>();
                }
                D[v].Add(u);
            }
        }
        private void solve2()
        {
            int max = 0;
            foreach (var item in D[1])
            {
                max = Math.Max(max, dfs(item, 1));
            }
            result = (N - max).ToString();
        }
        private int dfs(int me, int from)
        {
            int res = 1;
            foreach (var item in D[me])
            {
                if (item == from) continue;
                res += dfs(item, me);
            }
            return res;
        }
        private void solve1()
        {
            if (D[1].Count == 1)
            {
                result = "1";
                return;
            }
            var nodeCounts = new List<int>();
            for (int i = 0; i < D[1].Count; i++)
            {
                var h = new HashSet<int> { 1 };
                hoge(D[1][i], ref h);
                nodeCounts.Add(h.Count);
            }
            nodeCounts.Sort();
            var count = nodeCounts.Take(D[1].Count - 1).Aggregate((accum, v) => accum + v) - (D[1].Count - 2);
            result = count.ToString();
        }
        private void hoge(int start, ref HashSet<int> visited)
        {
            if (visited.Contains(start))
            {
                return;
            }
            visited.Add(start);
            foreach (var item in D[start])
            {
                hoge(item, ref visited);
            }
        }
        public override void Solve()
        {
            solve2();
        }
        public override void Output()
        {
            Console.WriteLine($"{result}");
        }
    }
}
