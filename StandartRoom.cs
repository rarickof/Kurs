using System;

namespace KursVar_2
{
  
    public class StandartRoom : BaseRoom
    {
        //Вызов конструктора базового класса
        public StandartRoom(int number, double pricePerNight) : base(number, pricePerNight)
        {
            Console.WriteLine($"StandartRoom() создан: номер {number} \n");
        }
        public override double CalculateCost(int nights) => (nights * PricePerNight);

        public override string GetDescription() => $"{base.GetDescription()}, категория: Стандарт\n";
    }
}

    