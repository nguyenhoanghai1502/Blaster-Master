using System;
using System.Numerics;

namespace ConsoleApp1
{
    class Program
    {
        static void Main(string[] args)
        {
            int n;
            n = Convert.ToInt32(Console.ReadLine());
            do
            {
                int x1, y1, x2, y2;
                Console.WriteLine("Nhap so cot bat dau: ");
                x1 = Convert.ToInt32(Console.ReadLine());
                Console.WriteLine("Nhap so cot ket thuc: ");
                x2 = Convert.ToInt32(Console.ReadLine());
                Console.WriteLine("Nhap so hang bat dau: ");
                y1 = Convert.ToInt32(Console.ReadLine());
                Console.WriteLine("Nhap so hang ket thuc: ");
                y2 = Convert.ToInt32(Console.ReadLine());
                Console.Write(n+" "+"1" + " " + x1 + " " + y1 + " " + (x2-x1) + " " + (y2-y1) + " ");
                InRaManHinh(x1 / 64, y1 / 64, x2 / 64, y2 / 64);
                Console.WriteLine();
                n = Convert.ToInt32(Console.ReadLine());
            } while (n != -1);
        }
        static void InRaManHinh(int x1, int y1, int x2, int y2)
        {
            for(int i = y1; i <= y2; i++)
            {
                
                for(int j = x1; j <= x2; j++)
                {
                    Console.Write(j+ " " + i+" ");
                }
            }
        }
    }
}
