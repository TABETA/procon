// C# .NET 5.0
using System;
using System.Collections.Generic;
using System.Collections;
using System.Linq;

namespace Procon.Nintendo
{
    class Pre
    {
        enum Direction
        {
            Up,
            Down,
            Left,
            Right
        }
        static string Sort(string val)
        {
            return new string(val.OrderBy(c => c).ToArray());
        }
        static bool IsInside(List<List<int>> cells, int x, int y)
        {
            try
            {
                var _ = cells[y][x];
                return true;
            }
            catch (Exception)
            {
                return false;
            }
        }
        static (int X, int Y) GetNext(int x, int y, Direction dir)
        {
            switch (dir)
            {
                case Direction.Up:
                    return (x, y - 1);
                case Direction.Down:
                    return (x, y + 1);
                case Direction.Left:
                    return (x - 1, y);
                case Direction.Right:
                    return (x + 1, y);
                default:
                    throw new Exception("invalid direction");
            }
        }
        static void Solve()
        {
            var T = int.Parse(Console.ReadLine());
            for (int i = 0; i < T; i++)
            {
                var cells = new List<List<int>>();
                var q = new Queue<(int X, int Y, int Cost, Direction Dir)>();
                int y = 0;
                (int X, int Y) goal = (-1,-1);
                while (true)
                {
                    var line = Console.ReadLine();
                    if (string.IsNullOrEmpty(line))
                    {
                        break;
                    }
                    var row = new List<int>();
                    for (int x = 0; x < line.Length; x++)
                    {
                        var c = line[x];
                        switch (c)
                        {
                            case 'S':
                                row.Add(0);
                                q.Enqueue((x, y, 0, Direction.Up));
                                q.Enqueue((x, y, 0, Direction.Down));
                                q.Enqueue((x, y, 0, Direction.Left));
                                q.Enqueue((x, y, 0, Direction.Right));
                                break;
                            case 'G':
                                row.Add(-1);
                                goal = (x, y);
                                break;
                            case 'o':
                                row.Add(-1);
                                break;
                            case 'x':
                                row.Add(int.MaxValue);
                                break;
                            default:
                                throw new Exception("invalid character");
                        }
                    }
                    cells.Add(row);
                    ++y;
                }
                while (q.Count > 0)
                {
                    var n = q.Dequeue();
                    foreach (var dir in new[] {
                        Direction.Up,
                        Direction.Down,
                        Direction.Left,
                        Direction.Right,
                    })
                    {
                        var next = GetNext(n.X, n.Y, dir);
                        if (IsInside(cells, next.Y, next.X))
                        {
                            var newCost = n.Dir != dir ? n.Cost + 1 : n.Cost;
                            if (cells[next.Y][next.X] != int.MaxValue)
                            {
                                if(cells[next.Y][next.X] == -1 || cells[next.Y][next.X] >= newCost)
                                {
                                    cells[next.Y][next.X] = newCost;
                                    q.Enqueue((next.X, next.Y, newCost, dir));
                                }
                            }
                        }
                    }
                }
                Console.WriteLine(cells[goal.Y][goal.X]);

            }
        }
    }
}
