#pragma once

#include <string>
#include "Room.hpp"

class Hotel {
private:
    std::string name_;

    Room* rooms_;
    int rooms_count_;       // Сколько номеров сейчас в массиве
    int rooms_capacity_;    // На сколько элементов выделена память

    bool roomExists(int room_number) const;
    void resizeArray();     // Увеличивание ёмкость массива в 2 раза

public:
    // Конструкторы
    Hotel();
    Hotel(const std::string& name);

    // Деструктор
    ~Hotel();

    Hotel(const Hotel& other);
    Hotel& operator=(const Hotel& other);

    // Содержательные методы
    void addRoom(const Room& room);
    void printAvailableRooms() const;
    void checkInGuestToRoom(Guest* guest, int room_number);
    void checkOutFromRoom(int room_number);

    // Геттеры
    [[nodiscard]] std::string getName() const;
    [[nodiscard]] int getRoomCount() const;
};