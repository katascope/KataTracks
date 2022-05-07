/*
long index = 29400;
for (int i=0;i<=21;i++)
{
    Console.WriteLine("  " + index + ",fx_palette_red,");
    index += 390;
}*/

for (int i = 1; i < 255; i++)
{

    Console.Write("fx_stripmask_" + i + ",");
    if (i % 8 == 0)
    {
        Console.WriteLine("");
        Console.Write("  ");
    }
}
