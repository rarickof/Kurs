#include <iostream>
#include <string>
#include <memory>

#include "Guest.hpp"
#include "Room.hpp"
#include "Hotel.hpp"

int main() {
    std::setlocale(LC_ALL, "Russian");

    std::cout << "=== 1. Статическая инициализация и работа по ссылке ===\n";
    Guest staticGuest("Иван Иванов", "1234 567890");
    Guest& refGuest = staticGuest;
    refGuest.printInfo();

    std::cout << "\n=== 2. unique_ptr Динамический объект ===\n";
    auto dynGuest = std::make_unique<Guest>("Петр Петров", "9876 543210");//выделение памяти
    dynGuest->printInfo();

    std::cout << "\n=== 3. unique_ptr Передача владения через std::move ===\n";
    auto guestForMove = std::make_unique<Guest>("Временный гость", "5555 555555");
    std::cout << "guestForMove до move: " << (guestForMove ? "владеет" : "пуст") << "\n";

    auto movedGuest = std::move(guestForMove);
    std::cout << "guestForMove после move: " << (guestForMove ? "владеет" : "пуст") << "\n";
    std::cout << "movedGuest: " << (movedGuest ? "владеет" : "пуст") << "\n";
    movedGuest->printInfo();

    std::cout << "\n=== 4. unique_ptr<[]> Массивы ===\n";
    auto roomsArray = std::make_unique<Room[]>(2);
    roomsArray[0] = Room(101, 3000.0);
    roomsArray[1] = Room(102, 4500.0);
    roomsArray[0].printInfo();

    std::unique_ptr<Guest> guestsArray[2];
    guestsArray[0] = std::make_unique<Guest>("Сидоров А.", "1111 111111");
    guestsArray[1] = std::make_unique<Guest>("Алексеев Б.", "2222 222222");
    guestsArray[0]->printInfo();

    std::cout << "\n=== 5. Проверка правила предметной области ===\n";
    Room testRoom(202, 5000.0);
    std::cout << "--- Корректное действие: ---\n";
    testRoom.checkIn(std::make_shared<Guest>("Тестовый", "0000"));
    std::cout << "--- Попытка нарушить правило: ---\n";
    testRoom.checkIn(std::make_shared<Guest>("Второй", "1111"));


    std::cout << "\n=== 6. shared_ptr: счётчик владельцев ===\n";
    auto aggregatedGuest = std::make_shared<Guest>("Гость-Агрегатор", "3333 333333");
    std::cout << "Счётчик: " << aggregatedGuest.use_count() << "\n";//кол-во ссылок

    {
        std::shared_ptr<Guest> secondOwner = aggregatedGuest;
        std::cout << "После копирования счётчик: " << aggregatedGuest.use_count() << "\n";

        std::cout << "______Вход во вложенный блок____\n";

        Hotel myHotel("Мини-Отель 'Ромашка'");
        myHotel.addRoom(Room(301, 6000.0));
        myHotel.addRoom(Room(302, 7000.0));

        myHotel.checkInGuestToRoom(aggregatedGuest, 301);

        std::cout << "--- Состояние отеля ---\n";
        myHotel.printAvailableRooms();

        std::cout << "______Выход из блока____\n";
    }


    std::cout << "\n=== 7. shared_ptr выжил ===\n";
    std::cout << "Счётчик: " << aggregatedGuest.use_count() << "\n";
    aggregatedGuest->printInfo();


    std::cout << "\n=== 8. Освобождение shared_ptr ===\n";
    aggregatedGuest.reset();
    std::cout << "Объект уничтожен.\n";

    std::cout << "\n=== Конец ===\n";
    return 0;
}