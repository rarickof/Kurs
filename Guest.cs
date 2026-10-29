using System;

namespace Лр3 
{ 
    public class Guest
    {
        private string _name;
        private string _passport;

        private string[] _requestedServices;
        private int _servicesCount;       // Сколько услуг сейчас в массиве
        private int _servicesCapacity;    // На сколько элементов выделена память

        private const int INITIAL_CAPACITY = 5; // Начальная ёмкость динамического массива

        private bool ValidateData(string name, string passport)
        {
            if (String.IsNullOrEmpty(name))
            {
                Console.WriteLine(" !!! Имя гостя не может быть пустым!");
                return false;
            }
            if (String.IsNullOrEmpty(passport))
            {
                Console.WriteLine(" !!! Номер паспорта не может быть пустым!");
                return false;
            }
            return true;
        }

        // Конструктор с параметрами
        public Guest(string name, string passport)
        {
            _requestedServices = new string[INITIAL_CAPACITY];
            _servicesCount = 0;
            _servicesCapacity = INITIAL_CAPACITY;

            if (!ValidateData(name, passport))
            {
                Console.WriteLine(" !!! Гость создан с некорректными данными. \n     Установлены значения по умолчанию.");
                _name = "Неизвестный";
                _passport = "0000 000000";
            }
            else
            {
                _name = name;
                _passport = passport;
            }
        }

        // Увеличение ёмкости массива в 2 раза
        private void ResizeArray()
        {
            int newCapacity = _servicesCapacity * 2;
            string[] newArray = new string[newCapacity];

            // Старые элементы в новый массив
            for (int i = 0; i < _servicesCount; i++)
            {
                newArray[i] = _requestedServices[i];
            }

            _requestedServices = newArray;
            _servicesCapacity = newCapacity;

            Console.WriteLine(" Массив услуг расширен до {0} элементов.", _servicesCapacity);
        }

        // 1: вывод информации
        public override string ToString()
        {
            string services = "нет"; // Значение по умолчанию

            if (_servicesCount > 0)
            {
                services = _requestedServices[0];
                for (int i = 1; i < _servicesCount; i++)
                {
                    services += ", " + _requestedServices[i];
                }
            }

            return $"Гость: {_name} | Паспорт: {_passport} | Услуги: {services}";
        
        }

        // 2: запрос услуги
        public void RequestService(string serviceName) {
            // Проверка: нет дубликатов
            for (int i = 0; i < _servicesCount; i++)
            {
                if (_requestedServices[i] == serviceName)
                {
                    Console.WriteLine(" !!! Услуга {0} уже запрошена гостем {1}.", serviceName, _name);
                    return;
                }
            }

            // Если массив заполнен — расширение
            if (_servicesCount >= _servicesCapacity)
            {
                ResizeArray();
            }

            // Добавление строки в конец массива
            _requestedServices[_servicesCount] = serviceName;
            ++_servicesCount;

            Console.WriteLine(" Гость {0} запросил услугу {1}.", _name, serviceName);
        }

        // 3: отмена услуги
        public void CancelService(string serviceName)
        {
            // Поиск услуги в массиве
            int foundIndex = -1;
            for (int i = 0; i < _servicesCount; i++)
            {
                if (_requestedServices[i] == serviceName)
                {
                    foundIndex = i;
                    break;
                }
            }

            // Проверка: услуга должна существовать
            if (foundIndex == -1)
            {
                Console.WriteLine($" !!! Услуга {serviceName} не найдена в списке гостя {_name}.");
                return;
            }

            // Сдвиг элементов после найденного на одну позицию влево
            for (int i = foundIndex; i < _servicesCount - 1; i++)
            {
                _requestedServices[i] = _requestedServices[i + 1];
            }

            // Уменьшаем счётчик и очищаем последний элемент
            --_servicesCount;
            _requestedServices[_servicesCount] = "";

            Console.WriteLine(" Гость {0} отменил услугу {1}.", _name, serviceName);
        }

        // Свойства
        public string Name
        {
            get { return _name; }
        }

        public string Passport
        {
            get { return _passport; }
        }

        public int ServicesCount
        {
            get { return _servicesCount; }
        }
    }
}