﻿while (true)
{
    Console.WriteLine("Введите регулярное выражение: ");
    string? regularExp = Console.ReadLine();
    if (!string.IsNullOrEmpty(regularExp))//1
    {
        string normalRegExp = RemoveUnnecessary(regularExp);//2
        Console.WriteLine("Введите строку: ");
        string? str = Console.ReadLine();
        if (!string.IsNullOrEmpty(str))//8
        {
            Console.WriteLine("Начало");
            if(!Parser(normalRegExp, str, regularExp))
            {
                Console.WriteLine("нет вхождений");//27
            }
        }
    }
}

string RemoveUnnecessary(string str)
{
    for (int i = 0; i < str.Length; i++)//2
    {
        if ((str[i] == '*' || str[i] == '+') && i + 1 < str.Length && str[i + 1] == '*')//3
        {
            str = str.Remove(i + 1, 1);//4
            i--;
        }
    }
    if (str[^1] == '*'&& str[0]!= str[^1])//5
    {
        str = str.Remove(str.Length - 1, 1);//6
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

bool Parser(string normalRegExp, string str, string regularExp)
{
    Console.WriteLine("1");
    int idxStart = 0;//1
    int idxReg = 0;
    bool skip = false;
    Console.WriteLine("2");
    for (int i = 0; i < str.Length; i++)//2
    {
        Console.WriteLine("3");
        if (normalRegExp[idxReg] == '*')//3
        {
            Console.WriteLine("4");
            skip = true;//4
            idxReg++;
            Console.WriteLine("5");
            if (idxReg == normalRegExp.Length)//5
            {
                Console.WriteLine("6");
                PrintAnswer(regularExp, str, idxStart);//6
                return true;
            }
        }
        Console.WriteLine("7");
        if (normalRegExp[idxReg] == '+')//7
        {
            Console.WriteLine("8");
            ResetIdx(idxReg, i, ref idxStart);//8
            Console.WriteLine("9");
            idxReg++;//9
            skip = true;
        }
        else if (normalRegExp[idxReg] == '.')//10
        {
            Console.WriteLine("10\n11");
            ResetIdx(idxReg, i, ref idxStart);//11
            idxReg++;
        }
        else
        {
            Console.WriteLine("10");
            Console.WriteLine("12");
            if (str[i] == normalRegExp[idxReg])//12
            {
                Console.WriteLine("13");
                ResetIdx(idxReg, i, ref idxStart);//13
                Console.WriteLine("14");
                idxReg++;//14
                skip = false;
            }
            else if (!skip)//15
            {
                Console.WriteLine("15");
                Console.WriteLine("16");
                if (idxReg == normalRegExp.Length)//16
                {
                    Console.WriteLine("6");
                    PrintAnswer(regularExp, str, idxStart);//6
                    return true;
                }
                Console.WriteLine("17");
                i = idxStart;//17
                idxReg = 0;
            }
            else
            {
                Console.WriteLine("15");
            }
        }
        Console.WriteLine("18");
        if (idxReg == normalRegExp.Length)//18
        {
            Console.WriteLine("6");
            PrintAnswer(regularExp, str, idxStart);//6
            return true;
        }
    }
    Console.WriteLine("19");
    return false;
}