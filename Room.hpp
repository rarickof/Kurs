#pragma once
#include <string>
#include <memory>
#include "Guest.hpp"

class Room {
private:
    int m_number;                    // Номер комнаты
    double m_pricePerNight;          // Стоимость за ночь
    std::string m_status;            // "Свободен" | "Занят" | "Требуется уборка"
    std::weak_ptr<Guest> m_currentGuest;  // АГРЕГАЦИЯ: указатель на гостя.
    // Room не создаёт и не удаляет гостя.

    bool validateRoomData(int number, double pricePerNight) const;

public:
    // Конструктор по умолчанию (нужен для new Room[2] в Hotel)
    Room();

    // Конструктор с параметрами
    Room(int number, double pricePerNight);

    // Содержательные методы
    void checkIn(std::shared_ptr<Guest> guest);      // Заселение гостя (Агрегация)
    void checkOut();                 // Выселение гостя
    void printInfo() const;          // Вывод информации о номере

    [[nodiscard]] bool isAvailable() const; // Проверка, свободен ли номер

    // Геттеры Room
    [[nodiscard]] int getNumber() const;
    [[nodiscard]] double getPricePerNight() const;
    [[nodiscard]] std::string getStatus() const;
    [[nodiscard]] std::weak_ptr<Guest> getCurrentGuest() const;
};