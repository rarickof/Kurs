#include <iostream>
#include <string>
#include <memory>

#include "Guest.hpp"
#include "Hotel.hpp"

#include "BaseRoom.hpp"
#include "EconomyRoom.hpp"
#include "StandardRoom.hpp"
#include "LuxuryRoom.hpp"

int main() {
    std::setlocale(LC_ALL, "Russian");

    std::cout << "\n=== 1. Массив со стоимостью номеров ===\n";

    // Массив умных указателей на базовый класс
    std::unique_ptr<BaseRoom> rooms[3];
    rooms[0] = std::make_unique<EconomyRoom>(101, 2000);
    rooms[1] = std::make_unique<StandardRoom>(201, 5000);
    rooms[2] = std::make_unique<LuxuryRoom>(301, 10000);

    std::cout << "\n=== 2. Виртуальные методы ===\n";

    for (int i = 0; i < 3; i++) {
        std::cout << rooms[i]->calculateCost(2) << "\n";
    }

    std::cout << "\n=== 3. Переопределение ===\n";

    for (int i = 0; i < 3; i++) {
        std::cout << rooms[i]->getDescription() << "\n";
    }

    std::cout << "\n=== 4. Виртуальный деструктор ===\n";
    for (int i = 0; i < 2; i++) {

        rooms[i].reset();
    }

    std::cout << "\n=== 5.1. Поверхностная копия ===\n";

    auto original = std::make_shared<LuxuryRoom>(400, 10000);
    std::shared_ptr<BaseRoom> shallow = original;

    std::cout << "Оригинал: " << original->getDescription() << "\n";
    std::cout << "Копия: " << shallow->getDescription() << "\n";

    shallow->setNumber(555);

    std::cout << "\nПосле изменения:\n";
    std::cout << "Оригинал: " << original->getDescription() << "\n";
    std::cout << "Копия: " << shallow->getDescription() << "\n";


    std::cout << "\n=== 5.2. Клонирование ===\n";

    std::unique_ptr<BaseRoom> twin = rooms[2]->Clone();
    std::cout << "Копия: " << twin->getDescription() << "\n";
    std::cout << "Оригинал: " << rooms[2]->getDescription() << "\n";

    twin->setNumber(999);

    std::cout << "\nПосле изменения:\n";
    std::cout << "Копия: " << twin->getDescription() << "\n";
    std::cout << "Оригинал: " << rooms[2]->getDescription() << "\n";

    std::cout << "\n=== 6. Использование this ===\n";

    Guest chainGuest("Гость", "1111 11111");
    chainGuest.withService("Завтрак");
    chainGuest.withService("Парковка");
    chainGuest.printInfo();

    std::cout << "\n=== 7. Статические члены ===\n";

    std::cout << "Количество созданных номеров " << BaseRoom::getUsedRooms() << "\n";

    std::cout << "\n=== Конец ===\n";
    return 0;
}