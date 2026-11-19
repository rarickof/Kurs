using System;

namespace KursVar_2
{
   
    public class EconomyRoom : BaseRoom
    {
        //Вызов конструктора базового класса
        public EconomyRoom(int number, double pricePerNight) : base(number, pricePerNight)
        {
            Console.WriteLine($"EconomyRoom() создан: номер {number} \n");
        }
        //переопределение — предоставления в производном классе новой реализации метода,
        //свойства, индексатора или события, которые уже есть в базовом классе.
        public override double CalculateCost(int nights) => (nights * PricePerNight);

        public override string GetDescription() => $"{base.GetDescription()}, категория: Эконом\n";
    }
}

    