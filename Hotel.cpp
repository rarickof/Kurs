#include "Hotel.hpp"
#include <iostream>

// Начальная ёмкость динамического массива.
const int INITIAL_CAPACITY = 5;

// Конструктор по умолчанию
Hotel::Hotel()
    : m_name("Без названия"),
      m_rooms(std::make_unique<Room[]>(INITIAL_CAPACITY)),
      m_roomsCount(0),
      m_roomsCapacity(INITIAL_CAPACITY) {}

// Конструктор с параметрами
Hotel::Hotel(const std::string& name)
    : m_name(name),
      m_rooms(std::make_unique<Room[]>(INITIAL_CAPACITY)),
      m_roomsCount(0),
      m_roomsCapacity(INITIAL_CAPACITY) {
    // Проверка правила: название не может быть пустым
    if (name.empty()) {
        std::cout << " !!! Название отеля не может быть пустым!\n";
        m_name = "Без названия";
    }
}

// Копирующий конструктор (глубокое копирование)
Hotel::Hotel(const Hotel& other)
    : m_name(other.m_name),
      m_roomsCount(other.m_roomsCount),
      m_roomsCapacity(other.m_roomsCapacity), 
      
      m_rooms(std::make_unique<Room[]>(m_roomsCapacity)) 
{
    for (int i = 0; i < m_roomsCount; ++i) {
        m_rooms[i] = other.m_rooms[i];
    }
}

// Оператор присваивания
Hotel& Hotel::operator=(const Hotel& other) {
    // Защита от самоприсваивания
    if (this == &other) {
        return *this;
    }

    // Копируем данные
    m_name = other.m_name;
    m_roomsCount = other.m_roomsCount;
    m_roomsCapacity = other.m_roomsCapacity;
    m_rooms = std::make_unique<Room[]>(m_roomsCapacity);

    for (int i = 0; i < m_roomsCount; ++i) {
        m_rooms[i] = other.m_rooms[i];
    }

    return *this;
}

// Увеличение ёмкости массива
void Hotel::resizeArray() {
    int newCapacity = m_roomsCapacity * 2;
    auto newArray = std::make_unique<Room[]>(newCapacity);

    for (int i = 0; i < m_roomsCount; ++i) {
        newArray[i] = m_rooms[i];
    }

    m_rooms = std::move(newArray);
    m_roomsCapacity = newCapacity;
}

// Вспомогательный метод
bool Hotel::roomExists(int roomNumber) const {
    for (int i = 0; i < m_roomsCount; ++i) {
        if (m_rooms[i].getNumber() == roomNumber) {
            return true;
        }
    }
    return false;
}

// Содержательный метод 1: Добавление номера
void Hotel::addRoom(const Room& room) {
    // Правило: Номер комнаты должен быть строго больше 0
    if (room.getNumber() <= 0) {
        std::cout << " !!! Номер комнаты должен быть больше 0. Добавление отклонено.\n";
        return;
    }

    // Защита от дубликатов
    if (roomExists(room.getNumber())) {
        std::cout << " !!! Номер " << room.getNumber() << " уже существует в отеле.\n";
        return;
    }

    // Если массив заполнен — расширение
    if (m_roomsCount >= m_roomsCapacity) {
        resizeArray();
    }

    // Добавление номера в конец массива
    m_rooms[m_roomsCount] = room;
    ++m_roomsCount;

    std::cout << " Номер " << room.getNumber() << " успешно добавлен в отель \"" << m_name << "\".\n";
}

// Содержательный метод 2: Печать свободных номеров
void Hotel::printAvailableRooms() const {
    std::cout << "=== Свободные номера в отеле \"" << m_name << "\" ===\n";
    bool found = false;

    for (int i = 0; i < m_roomsCount; ++i) {
        if (m_rooms[i].isAvailable()) {
            m_rooms[i].printInfo();
            found = true;
        }
    }

    if (!found) {
        std::cout << "Свободных номеров нет.\n";
    }
    std::cout << "=========================================\n";
}

// Содержательный метод 3: Заселение гостя
void Hotel::checkInGuestToRoom(std::shared_ptr<Guest> guest, int roomNumber) {
    for (int i = 0; i < m_roomsCount; ++i) {
        if (m_rooms[i].getNumber() == roomNumber) {
            m_rooms[i].checkIn(guest);
            return;
        }
    }
    std::cout << " !!! Номер " << roomNumber << " не найден в отеле.\n";
}

// Содержательный метод 4: Выселение гостя
void Hotel::checkOutFromRoom(int roomNumber) {
    for (int i = 0; i < m_roomsCount; ++i) {
        if (m_rooms[i].getNumber() == roomNumber) {
            m_rooms[i].checkOut();
            return;
        }
    }
    std::cout << " !!! Номер " << roomNumber << " не найден в отеле.\n";
}

// Геттеры
std::string Hotel::getName() const {
    return m_name;
}

int Hotel::getRoomCount() const {
    return m_roomsCount;
}