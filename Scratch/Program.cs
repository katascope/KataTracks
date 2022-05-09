using System;

namespace Scratch
{
    class Program
    {
        static ulong BitRotateColor(ulong v)
        {
            ulong carry = ((v << 4) & 0x0F000000) >> 24;
            ulong value = ((v << 4) & 0x00FFFFFF) | carry;
            return value;
        }
        static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");
            ulong v = 0x00FF0000;
            ulong value = BitRotateColor(v);

            for (int i=0;i<6;i++)
            {
                Console.WriteLine("Value : {0:X}",v);
                v = BitRotateColor(v);
            }

            int foo;
            foo = 1;
        }
    }
}
