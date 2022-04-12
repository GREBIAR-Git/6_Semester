List<int> allnumbers = new();
Random rnd = new Random((new Random()).Next());
for (int i=0;i<100;i++)
{
    allnumbers.Add(rnd.Next(1, 100));
}

int b = rnd.Next(1, 100);

int a = rnd.Next(0, 100);//rnd.Next(0, b);
List<int> numbers = new();
if(a<b)
{
    for(int i=0;i<allnumbers.Count;i++)
    {
        if(allnumbers[i]>a&&allnumbers[i]<b)
        {
            numbers.Add(allnumbers[i]);
            Console.Write(i+",");
        }
    }
    if(numbers.Count!=0)
    {
        Console.WriteLine($"Количество: {numbers.Count}");
    }
    else
    {
        Console.WriteLine($"В массиве нет элементов больших A и меньше B");
    }
}
else
{
    Console.WriteLine($"А>=B");
}



