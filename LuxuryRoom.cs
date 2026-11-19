using System;

namespace KursVar_2
{
    //Запрет наследования
    public sealed class LuxuryRoom : BaseRoom
    {
        public string Isbn;

        //немедленная инициализация неизменяемого общего значения
        private static readonly int MIN_STAY_NIGHT = 2;
        private string status;

        //Вызов конструктора базового класса
        public LuxuryRoom(int number, double pricePerNight) : base(number, pricePerNight)
        {
            Console.WriteLine($"LuxuryRoom() создан: номер {number} \n");
        }
        public override double CalculateCost(int nights)
        {
            if (nights <= MIN_STAY_NIGHT)
            {
                Console.WriteLine($"Нельзя забронировать номер Люкс меньше чем на 2 ночи");
                return 0.0;
            }
            return (nights * PricePerNight) * 1.5;
        }
        public override string GetDescription() 
        {
            if (_status.Equals("Свободен"))
            {
                status = " Свободен";
            }
            else
            {
                status = " Занят";
            }
            return $"Люксовый номер: {Number}, Статус: {status}"; 
        }
        //Проверяет, что obj не равен null.
        //Проверяет, что obj действительно является экземпляром класса 
        //Если проверки прошли, безопасно приводит obj к типу LuxuryRoom и сохраняет в новую переменную other.
        public override bool Equals(object? obj) =>
           obj is LuxuryRoom other && Number == other.Number;//&& сравнение obj и Isbn
        //Метод возвращает хеш-код — целое число, которое представляет объект. Это нужно для быстрой работы хеш-таблиц
        public override int GetHashCode() => Number.GetHashCode();
    }
}

    