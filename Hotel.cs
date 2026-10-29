using System;

namespace Лр3
{
    class Hotel
    {
        private string _name;
        private Room[] _rooms;
        private int _roomsCount;       // Сколько номеров сейчас в массиве
        private int _roomsCapacity;    // На сколько элементов выделена память
        private const int INITIAL_CAPACITY = 5;

        // Конструктор с параметрами
        public Hotel(string name)
        {
            _rooms = new Room[INITIAL_CAPACITY];
            _roomsCapacity = INITIAL_CAPACITY;
            _roomsCount = 0;
            

            if (string.IsNullOrEmpty(name))
            {
                _name = "Без названия";
            }
            else
            {
                _name = name;
            }
        }

        // Увеличение ёмкости массива в 2 раза
        private void ResizeArray()
        {
            int newCapacity = _roomsCapacity * 2;
            Room[] newArray = new Room[newCapacity];

            // Копируем старые номера в новый массив
            for (int i = 0; i < _roomsCount; ++i)
            {
                newArray[i] = _rooms[i];
            }

            _rooms = newArray;
            _roomsCapacity = newCapacity;

            Console.WriteLine($" Массив номеров расширен до {_roomsCapacity} элементов.");
        }

        // проверка существования номера
        private bool RoomExists(int roomNumber)
        {
            for (int i = 0; i < _roomsCount; ++i)
            {
                if (_rooms[i].Number == roomNumber)
                {
                    return true;
                }
            }
            return false;
        }

        // 1: Добавление номера
        public void AddRoom(Room room)
        {
            // Правило: Номер комнаты должен быть строго больше 0
            if (room.Number <= 0)
            {
                Console.WriteLine(" !!! Номер комнаты должен быть больше 0. Добавление отклонено.\n");
                return;
            }
            // Защита от дубликатов 
            if (RoomExists(room.Number))
            {
                Console.WriteLine(" !!! Номер {0} уже существует в отеле.\n", room.Number);
                return;
            }

            if (_roomsCount >= _roomsCapacity)
            {
                ResizeArray();
            }

            // Добавление номера в конец массива
            _rooms[_roomsCount] = room;
            ++_roomsCount;

            Console.WriteLine(" Номер {0} успешно добавлен в отель {1}\".\n", room.Number, _name);
        }

        // 2: Печать свободных номеров
        public void PrintAvailableRooms()
        {
            Console.WriteLine(" === Свободные номера в отеле \" {0} \" ===\n", _name);
            bool found = false;

            for (int i = 0; i < _roomsCount; ++i)
            {
                if (_rooms[i].IsAvailable())
                {
                    Console.WriteLine(_rooms[i].ToString());
                    found = true;
                }
            }

            if (!found)
            {
                Console.WriteLine(" Свободных номеров нет.\n");
            }
            Console.WriteLine("=========================================\n");
        }

        // 3: Заселение гостя
        public void CheckInGuestToRoom(Guest guest, int roomNumber)
        {
            //поиск номера
            Room targetRoom = null;
            for (int i = 0; i < _roomsCount; ++i)
            {
                if (_rooms[i].Number == roomNumber)
                {
                    targetRoom = _rooms[i];
                    break;
                }
            }

            if (targetRoom == null)
            {
                Console.WriteLine($" !!! Номер {roomNumber} не найден в отеле.\n");
                return;
            }
            targetRoom.CheckIn(guest);
        }

        // 4: Выселение гостя
        public void CheckOutFromRoom(int roomNumber)
        {
            Room targetRoom = null;
            for (int i = 0; i < _roomsCount; ++i)
            {
                if (_rooms[i].Number == roomNumber)
                {
                    targetRoom = _rooms[i];
                    break;
                }
            }

            if (targetRoom == null)
            {
                Console.WriteLine($" !!! Номер {roomNumber} не найден в отеле.\n");
                return;
            }
            targetRoom.CheckOut();
        }

        // Свойства
        public string Name
        {
            get { return _name; }
        }

        public int RoomCount
        {
            get { return _roomsCount; }
        }
    }
}