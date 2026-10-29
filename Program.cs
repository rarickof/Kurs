using System;

namespace Лр3
{
    // Вспомогательный класс для демонстрации IDisposable (аналог деструктора из C++)
    public sealed class IssueLog : IDisposable
    {
        private readonly string _roomNumber;

        public IssueLog(string roomNumber)
        {
            _roomNumber = roomNumber;
            Console.WriteLine($"[+] Журнал уборки открыт для номера {_roomNumber}");
        }

        public void Write(string line) => Console.WriteLine($"  {line}");
        public void Dispose() => Console.WriteLine($"[-] Журнал уборки закрыт для номера {_roomNumber}");
    }

    // Структура для демонстрации типов-значений
    public struct Money
    {
        public float Amount;
    }

    class Program
    {
        // Правильная точка входа в C#
        static void Main()
        {
            Console.WriteLine("=== 1. Ссылки и Копии (Классы, Структуры) ===");
            // Классы (ссылочный тип)
            Guest guest1 = new Guest("Иван Иванов", "1234 567890");
            Guest guest2 = guest1;
            guest2.RequestService("Завтрак");
            Console.WriteLine($"guest1: {guest1}");
            Console.WriteLine($"Ссылки равны? {ReferenceEquals(guest1, guest2)}\n");

            // Структуры (тип-значение)
            Money price1 = new Money { Amount = 5000 };
            Money price2 = price1; // Копия значения
            price2.Amount = 7000;
            Console.WriteLine($"price1: {price1.Amount}, price2: {price2.Amount} \n");


            Console.WriteLine("=== 2. Композиция и Агрегация ===");
            Hotel myHotel = new Hotel("Мини-Отель 'Ромашка'");
            myHotel.AddRoom(new Room(101, 3000.0));
            myHotel.AddRoom(new Room(102, 4500.0));

            Guest aggregatedGuest = new Guest("Петр Петров", "9876 543210");
            myHotel.CheckInGuestToRoom(aggregatedGuest, 101); // Агрегация: гость создан снаружи
            myHotel.PrintAvailableRooms();


            Console.WriteLine("\n=== 3. Проверка правила предметной области ===");
            myHotel.CheckInGuestToRoom(new Guest("Сидоров", "1111"), 101); // Отказ: номер занят


            Console.WriteLine("\n=== 4. Освобождение ресурса (IDisposable + using) ===");

            using (var log = new IssueLog("101"))
            {
                log.Write("Гость выехал. Требуется замена белья.");
            } // автоматически вызывается log.Dispose()


            Console.WriteLine("\n=== 5. Работа Сборщика Мусора ===");

            WeakReference<Guest> weakRef;
            CreateTemporaryGuest(out weakRef);
            Console.WriteLine($"Объект жив до сборки мусора? {weakRef.TryGetTarget(out _)}");

            GC.Collect(); // Принудительная работа сборщика мусора
            GC.WaitForPendingFinalizers();

            Console.WriteLine($"Объект жив после сборки мусора? {weakRef.TryGetTarget(out _)}");
        }

        // Метод создан специально, чтобы локальная переменная temp вышла из области видимости
        // и объект стал доступен для GC (в отладочной сборке локальные переменные могут жить до конца метода)
        static void CreateTemporaryGuest(out WeakReference<Guest> weakRef)
        {
            Guest temp = new Guest("Списанный Гость", "0000");
            weakRef = new WeakReference<Guest>(temp);
        }
    }
}