using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab3
{
    internal class Program
    {
        static void Main(string[] args)
        {
            while(true)
            {
                Console.WriteLine("a*x^2+b*x+c=0");
                double a = ReadLine("a");
                double b = ReadLine("b");
                double c = ReadLine("c");

                double D = Math.Pow(b, 2) - 4 * a * c;

                if (D < 0)
                {
                    double x_r = (- b) / (2 * a);
                    double x_i = (Math.Sqrt(-D)) / (2 * a);
                    Console.WriteLine("x1 = " + x_r + " + (" + x_i + ")i");
                    Console.WriteLine("x2 = " + x_r + " - (" + x_i + ")i");
                }
                else
                {
                    double x1 = (Math.Sqrt(D) - b) / (2 * a);
                    double x2 = (-Math.Sqrt(D) - b) / (2 * a);
                    Console.WriteLine("x1 = " + x1);
                    Console.WriteLine("x2 = " + x2);
                }
                Console.WriteLine("\n\n");
            }
        }

        static double ReadLine(string name)
        {
            double value;
            while (true)
            {
                try
                {
                    Console.Write(name + " = ");
                    string val = Console.ReadLine();
                    value = double.Parse(val);
                    break;
                }
                catch
                {
                    continue;
                }
            }
            return value;
        }
    }
}
