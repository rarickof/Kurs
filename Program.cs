using System;

namespace KursVar_2
{
    // Явный вызов "деструктора"
    public sealed class IssueLog : IDisposable
    {
        private readonly string _roomNumber;

        public IssueLog(string roomNumber)
        {
            _roomNumber = roomNumber;
            Console.WriteLine($"[+] Журнал уборки открыт для номера {_roomNumber}");
        }

        public void Write(string line) => Console.WriteLine($"  {line}");
        public void Dispose() => Console.WriteLine($"[-] Журнал уборки закрыт для номера {_roomNumber}");//освобождается ресурс
    }

    // Структура для демонстрации типов-значений
    public struct Money
    {
        public float Amount;
    }

    class Program
    {

        static void Main()
        {
            Console.WriteLine("\n=== 1. Массив со стоимостью номеров ===\n");

            BaseRoom[] rooms = new BaseRoom[3];

            rooms[0] = new EconomyRoom(101, 2000);
            rooms[1] = new StandartRoom(201, 5000);
            rooms[2] = new LuxuryRoom(301, 10000);


            Console.WriteLine("\n=== 2. Виртуальные методы ===\n");

            for (int i = 0; i < 3; i++)
            {
                Console.WriteLine($"{rooms[i].CalculateCost(2)}");
            }

            Console.WriteLine("\n=== 3. Переопределение ===\n");

            for (int i = 0; i < 3; i++)
            {
                Console.WriteLine($"{rooms[i].GetDescription()}");
            }

            Console.WriteLine("\n=== 4. Копия ===");

            Guest original = new Guest("Иван Иванов", "1234 567890");
            original.RequestService("Завтрак");
            Console.WriteLine($"\nОригинал: {original}\n");
            Guest deep = original.DeepCopy();
            deep.RequestService("Парковка");
            Console.WriteLine($"\nОригинал после изменения глубокой копии: {original}\n");
            Console.WriteLine($"Глубокая копия: {deep}");

            Console.WriteLine("\n=== 5. using и IDisposable ===");

            // using гарантирует, что объект, реализующий метод Dispose(),
            // будет правильно освобождён после завершения блока кода,даже если внутри произошло исключение.
            using (var log = new IssueLog("401"))
            {
                log.Write("Гость выехал. Требуется замена белья.");
                log.Write("Проверка мини-бара.");
            } //здесь автоматически вызывается log.Dispose()
        }
    }
}