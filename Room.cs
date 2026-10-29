using System;

namespace Лр3
{
    class Room
    {

        private int _number;                    // Номер комнаты
        private double _pricePerNight;          // Стоимость за ночь
        private string _status;                // "Свободен" | "Занят" | "Требуется уборка"
        private Guest _currentGuest;           // АГРЕГАЦИЯ: указатель на гостя.
        // Room не создаёт и не удаляет гостя.

        private bool ValidateRoomData(int number, double pricePerNight)
        {
            if (number <= 0) {
                Console.WriteLine(" !!! Номер комнаты должен быть > 0. Получено: {0}", number);
                return false;
            }
            if (pricePerNight <= 0.0) {
                Console.WriteLine(" !!! Цена за ночь должна быть > 0. Получено: {0}", pricePerNight);
                return false;
            }
            return true;
        }

        // Конструктор с параметрами
        public Room(int number, double pricePerNight)
        {
            _number = number;
            _pricePerNight = pricePerNight;
            _status = "Свободен";
            _currentGuest = null;
    
            // Проверка правила предметной области
            if (!ValidateRoomData(number, pricePerNight))
            {
                Console.WriteLine(" !!! Номер создан с некорректными данными. Установлены значения по умолчанию.");
                _number = 0;
                _pricePerNight = 0.0;
            }
        }
        // 1: Заселение гостя
        public void CheckIn(Guest guest)
        {
            // проверка входящего параметра
            if (guest == null)
            {
                Console.WriteLine(" !!! Попытка заселить несуществующего гостя в номер {0}.", _number);
                return;
            }

            // проверка не занят ли номер
            if (_currentGuest != null)
            {
                Console.WriteLine(" !!! Номер {0} уже занят гостем {1}. Заселение отклонено.", _number, _currentGuest.Name);
                return;
            }

            // проверка статуса номера
            if (_status != "Свободен")
            {
                Console.WriteLine(" !!! Номер {0} не готов к заселению (статус: \"{1}\").", _number, _status);
                return;
            }

            _currentGuest = guest;  // Агрегация: сохранение указателя
            _status = "Занят";      // Смена состояния
            Console.WriteLine(" Гость {0} заселён в номер {1}.", guest.Name, _number);
        }

        // 2: Выселение гостя
        public void CheckOut() {
            // Проверка: в номере должен кто-то жить
            if (_currentGuest == null) 
            {
                Console.WriteLine(" !!! Номер {0} уже пуст. Нет человека для выселения.", _number);
                return;
            }

            // Запоминание имени
            string guestName = _currentGuest.Name;
            _currentGuest = null; // Обрывание агрегации
            // Жизненный цикл: после выезда номер переходит в состояние "Требуется уборка"
            _status = "Требуется уборка";

            Console.WriteLine(" Гость {0} выехал из номер {1}. Номер требует уборки.", guestName, _number);
        }

        // 3: Вывод информации
        public override string ToString()
        {
            // Базовая строка
            string result = $"Номер: {_number} | Цена: {_pricePerNight} руб./ночь | Статус: {_status}";

            // Проверка номера на гостя
            if (_currentGuest != null)
            {
                // Если гость есть, дополнение информацией о нем в конец строки
                result += $" | Гость: {_currentGuest.Name}";
            }
            return result;
        }

        // 4: Проверка доступности
        public bool IsAvailable() 
        {
            return (_status == "Свободен" && _currentGuest == null);
        }

        // Свойства
        public int Number
        {
            get { return _number; }
        }

        public double PricePerNight
        {
            get {return _pricePerNight;}
        }

        public string Status
        {
            get {return _status;}
        }

        public Guest CurrentGuest
        {
            get {return _currentGuest;}
        }
    }
}