while (true)
{
    Console.WriteLine("Введите регулярное выражение: ");
    string? regularExp = Console.ReadLine();
    if (regularExp != null)
    {
        string normalRegExp = RemoveUnnecessary(regularExp);
        Console.WriteLine("Введите строку: ");
        string? str = Console.ReadLine();
        if (str != null)
        {
            int idxStart = 0;
            int idxReg = 0;
            bool skip = false;
            for (int i = 0; i < str.Length; i++)
            {
                if (normalRegExp[idxReg] == '*')
                {
                    skip = true;
                    idxReg++;
                    if (idxReg == normalRegExp.Length)
                    {
                        PrintAnswer(regularExp, str, idxStart);
                        return;
                    }
                }
                if (normalRegExp[idxReg] == '+')
                {
                    ResetIdx(idxReg, i, ref idxStart);
                    idxReg++;
                    skip = true;
                }
                else if (normalRegExp[idxReg] == '.')
                {
                    ResetIdx(idxReg, i, ref idxStart);
                    idxReg++;
                }
                else
                {
                    if (str[i] == normalRegExp[idxReg])
                    {
                        ResetIdx(idxReg, i, ref idxStart);
                        idxReg++;
                        skip = false;
                    }
                    else if (!skip)
                    {
                        if (idxReg == normalRegExp.Length - 1)
                        {
                            PrintAnswer(regularExp, str, idxStart);
                            return;
                        }
                        idxStart++;
                        i = idxStart + 1;
                        idxReg = 0;
                    }
                }
                if (idxReg == normalRegExp.Length)
                {
                    PrintAnswer(regularExp, str, idxStart);
                    return;
                }
            }
        }
    }
    Console.WriteLine("нет вхождений");
}

string RemoveUnnecessary(string str)
{
    for (int i = 0; i < str.Length; i++)
    {
        if ((str[i] == '*' || str[i] == '+') && i + 1 < str.Length && str[i + 1] == '*')
        {
            str = str.Remove(i + 1, 1);
            i--;
        }
    }
    if (str[^1] == '*')
    {
        str = str.Remove(str.Length - 1, 1);
    }
    return str;
}

void PrintAnswer(string regularExp, string str, int idxStart)
{
    Console.WriteLine($"Ответ\nРегулярное выражение: { regularExp }\nСтроку: {str}\nИндекс: {idxStart} ");
}

void ResetIdx(int idxReg, int i, ref int idxStart)
{
    if (idxReg == 0)
    {
        idxStart = i;
    }
}