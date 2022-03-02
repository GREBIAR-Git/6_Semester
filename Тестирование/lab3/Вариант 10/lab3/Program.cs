List<int> allnumbers = new();
Random rnd = new Random((new Random()).Next());
for (int i=0;i<100;i++)
{
    allnumbers.Add(rnd.Next(1, 100));
}

int a = rnd.Next(1, 100);

int b = rnd.Next(0, a);

List<int> numbers = new();

for(int i=0;i<allnumbers.Count;i++)
{
    if(allnumbers[i]<a&&allnumbers[i]>b)
    {
        numbers.Add(allnumbers[i]);
        Console.Write(i+",");
    }
}


Console.WriteLine($"Количество: {numbers.Count}");
