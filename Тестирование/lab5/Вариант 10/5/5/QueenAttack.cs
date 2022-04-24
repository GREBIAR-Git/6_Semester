namespace _5
{
    public static class QueenAttack
    {
        public static int QueenAttackCells()
        {
            if (ReadLine(out int n, out int k))
            {
                Position queen = new();
                if (ReadLine(out queen.r, out queen.c))
                {
                    Position[] barriers = new Position[k];
                    for (int i = 0; i < k; i++)
                    {
                        if (!ReadLine(out barriers[i].r, out barriers[i].c))
                        {
                            return -1;
                        }
                    }
                    return CellSearchForAttack(n, queen, barriers);
                }
            }
            return -1;
        }

        static bool ReadLine(out int arg1, out int arg2)
        {
            string? str = Console.ReadLine();
            if (!string.IsNullOrEmpty(str))
            {
                string[] arg = str.Split(' ');
                if (arg.Length == 2)
                {
                    arg1 = int.Parse(arg[0]);
                    arg2 = int.Parse(arg[1]);
                    return true;
                }
            }
            arg1 = 0;
            arg2 = 0;
            return false;
        }

        public static int CellSearchForAttack(int n, Position queen, Position[] barriers)
        {
            int cellsAttack = 0;
            for (int i = queen.r - 1; i > 0; i--)
            {
                if (IsFigure(i, queen.c, barriers))
                {
                    break;
                }
                cellsAttack++;
            }
            for (int i = queen.r + 1; i <= n; i++)
            {
                if (IsFigure(i, queen.c, barriers))
                {
                    break;
                }
                cellsAttack++;
            }

            for (int i = queen.c - 1; i > 0; i--)
            {
                if (IsFigure(queen.r, i, barriers))
                {
                    break;
                }
                cellsAttack++;
            }
            for (int i = queen.c + 1; i <= n; i++)
            {
                if (IsFigure(queen.r, i, barriers))
                {
                    break;
                }
                cellsAttack++;
            }

            for (int i = queen.r - 1, f = queen.c - 1; i > 0 && f > 0; i--, f--)
            {
                if (IsFigure(i, f, barriers))
                {
                    break;
                }
                cellsAttack++;
            }
            for (int i = queen.r + 1, f = queen.c + 1; i <= n && f <= n; i++, f++)
            {
                if (IsFigure(i, f, barriers))
                {
                    break;
                }
                cellsAttack++;
            }

            for (int i = queen.r - 1, f = queen.c + 1; i > 0 && f <= n; i--, f++)
            {
                if (IsFigure(i, f, barriers))
                {
                    break;
                }
                cellsAttack++;
            }
            for (int i = queen.r + 1, f = queen.c - 1; i <= n && f > 0; i++, f--)
            {
                if (IsFigure(i, f, barriers))
                {
                    break;
                }
                cellsAttack++;
            }
            return cellsAttack;
        }

        static bool IsFigure(int r, int c, Position[] barriers)
        {
            for (int i = 0; i < barriers.Length; i++)
            {
                if (barriers[i].r == r && barriers[i].c == c)
                {
                    return true;
                }
            }
            return false;
        }
    }

    public struct Position
    {
        public int r;
        public int c;
        public Position(int r, int c)
        {
            this.r = r;
            this.c = c;
        }
    }
}
