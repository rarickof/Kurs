#pragma once
#include <string>
#include <memory>
#include "Room.hpp"


class Hotel {
private:
    std::string m_name;
    std::unique_ptr<Room[]> m_rooms;
    int m_roomsCount;           // Сколько номеров сейчас в массиве
    int m_roomsCapacity;        // На сколько элементов выделена память

    bool roomExists(int roomNumber) const;
    void resizeArray();         // Увеличение ёмкости массива в 2 раза

public:
    // Конструкторы
    Hotel();
    Hotel(const std::string& name);
    
    // Правило трёх (глубокое копирование)
    Hotel(const Hotel& other);
    Hotel& operator=(const Hotel& other);

    // Содержательные методы
    void addRoom(const Room& room);
    void printAvailableRooms() const;
    void checkInGuestToRoom(std::shared_ptr<Guest> guest, int roomNumber);
    void checkOutFromRoom(int roomNumber);

    // Геттеры Hotel
    [[nodiscard]] std::string getName() const;
    [[nodiscard]] int getRoomCount() const;
};