#include <iostream>
#include <string>

#include "Guest.hpp"
#include "Room.hpp"
#include "Hotel.hpp"

int main() {
    std::setlocale(LC_ALL, "Russian");

    std::cout << "=== 1. Статическая инициализация и работа по ссылке ===\n";
    Guest staticGuest("Иван Иванов", "1234 567890");
    Guest& refGuest = staticGuest;
    refGuest.printInfo();

    std::cout << "\n=== 2. Динамическая инициализация и работа по указателю ===\n";
    Guest* dynGuest = new Guest("Петр Петров", "9876 543210");
    dynGuest->printInfo();

    std::cout << "\n=== 3. Массивы объектов ===\n";
    // 1) Динамический массив объектов (вызывается конструктор по умолчанию)
    Room* roomsArray = new Room[2];
    roomsArray[0] = Room(101, 3000.0);
    roomsArray[1] = Room(102, 4500.0);

    // 2) Массив динамических объектов (массив указателей)
    Guest** guestsArray = new Guest * [2];
    guestsArray[0] = new Guest("Сидоров А.", "1111 111111");
    guestsArray[1] = new Guest("Алексеев Б.", "2222 222222");

    std::cout << "\n=== 4. Проверка правила предметной области ===\n";
    Room testRoom(202, 5000.0);
    std::cout << "--- Корректное действие: ---\n";
    testRoom.checkIn(&staticGuest); // Успешное заселение
    std::cout << "--- Попытка нарушить правило (номер уже занят): ---\n";
    testRoom.checkIn(dynGuest);     // Ожидается отказ и сообщение об ошибке

    std::cout << "\n=== 5. Композиция и Агрегация (Время жизни) ===\n";
    Guest* aggregatedGuest = new Guest("Гость-Агрегатор", "3333 333333");
    {
        std::cout << ">>> Вход во вложенный блок...\n";

        // Hotel - целое (композиция) создается статически
        Hotel myHotel("Мини-Отель 'Ромашка'");

        // Room - часть (композиция) добавляется по значению 
        // копируется в динамический массив внутри Hotel
        myHotel.addRoom(Room(301, 6000.0));
        myHotel.addRoom(Room(302, 7000.0));

        // Агрегация: заселяем гостя, который был создан снаружи блока
        // Номер хранит указатель на него, но не владеет им
        myHotel.checkInGuestToRoom(aggregatedGuest, 301);

        std::cout << "--- Состояние отеля внутри блока ---\n";
        myHotel.printAvailableRooms();

        std::cout << ">>> Выходим из блока. Ожидайте деструкторов Hotel и Room...\n";
    }

    std::cout << "\n=== 6. Проверка, что агрегированный объект выжил ===\n";
    // Гость жив, Отель и Номер уничтожены
    aggregatedGuest->printInfo();

    std::cout << "\n=== 7. Освобождение динамической памяти ===\n";
    delete dynGuest;

    delete[] roomsArray;

    for (int i = 0; i < 2; ++i) {
        delete guestsArray[i];
    }
    delete[] guestsArray;

    delete aggregatedGuest;

    std::cout << "\n=== Конец программы. Статические объекты уничтожаются автоматически ===\n";
    return 0;
}