using Microsoft.CodeAnalysis.CSharp.Scripting;
using System;

namespace lab2
{
    internal class Program
    {
        static void Main(string[] args)
        {
            while (true)
            {
                Console.Write("Input: ");
                string expression = Console.ReadLine();
                if (string.IsNullOrEmpty(expression))
                {
                    Console.Write("Empty expression");
                    continue;
                }
                try
                {
                    var result = Parse(expression);
                    Console.WriteLine(result.ToString());
                }
                catch (Exception e)
                {
                    Console.Write(e.ToString()); // e. первая штучка говорит какая именна ошибка
                }
            }
        }


        static double Parse(string expression)
        {
            return CSharpScript.EvaluateAsync<double>(expression).Result;
        }
    }
}
