List<int> range = new() { 11, 122, 1233, 12344, 123455, 1234566 };
int sum = 0;
for (int i = 0; i < range.Count; i++)
{
    if (sum >= 130000)
    {
        System.Console.WriteLine("Сумма: " + sum + "\nПоследнее слагаемое: " + range[i] + "\nНомер слагаемого: " + (i + 1));
        break;
    }
}

    while (sum>=130000)
{
    range.Add(current*10+pos);
}


for (int i = 0; i < range.Count; i++)
{
    for (int f = i; f < range.Count; f++)
    {
        if (range[i] < range[f])
        {
            int save = range[i];
            range[i] = range[f];
            range[f] = save;
        }
    }
    sum += range[i];
    if (sum >= 130000)
    {
        System.Console.WriteLine("Сумма: " + sum + "\nПоследнее слагаемое: " + range[i] + "\nНомер слагаемого: " + (i + 1));
        break;
    }
}