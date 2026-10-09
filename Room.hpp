#pragma once

#include <string>
#include "Guest.hpp"

class Room {
private:
    int number_;                    // Номер комнаты
    double price_per_night_;        // Стоимость за ночь
    std::string status_;            // "Свободен" | "Занят" | "Требуется уборка"
    Guest* current_guest_;          // АГРЕГАЦИЯ: указатель на гостя.
    // Room не создаёт и не удаляет гостя.

    bool validateRoomData(int number, double price) const;

public:
    // Конструктор по умолчанию (нужен для new Room[2] в Hotel)
    Room();

    // Конструктор с параметрами
    Room(int number, double price_per_night);

    // Деструктор
    ~Room();

    // Содержательные методы
    void checkIn(Guest* guest);// Заселение гостя (Агрегация: гость передаётся по указателю извне)
    void checkOut();// Выселение гостя
    void printInfo() const;// Вывод информации о номере

    
    [[nodiscard]] bool isAvailable() const;// Проверка, свободен ли номер для заселения

    //Геттеры
    [[nodiscard]] int getNumber() const;
    [[nodiscard]] double getPricePerNight() const;
    [[nodiscard]] std::string getStatus() const;
    [[nodiscard]] Guest* getCurrentGuest() const;
};