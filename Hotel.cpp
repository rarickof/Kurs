#include "Hotel.hpp"
#include <iostream>

const int INITIAL_CAPACITY = 5;

// Конструктор по умолчанию
Hotel::Hotel()
    : name_("Без названия"),
    rooms_(new Room[INITIAL_CAPACITY]),
    rooms_count_(0),
    rooms_capacity_(INITIAL_CAPACITY) {}

// Конструктор с параметрами
Hotel::Hotel(const std::string& name)
    : name_(name),
    rooms_(new Room[INITIAL_CAPACITY]),
    rooms_count_(0),
    rooms_capacity_(INITIAL_CAPACITY) {
    if (name.empty()) {
        std::cout << " !!! Название отеля не может быть пустым!\n";
        name_ = "Без названия";
    }
}

Hotel::~Hotel() {
    delete[] rooms_;

    std::cout << "~Hotel() уничтожен: " << name_ << " (все номера также уничтожаются...)" << std::endl;
}

// Копирующий конструктор
Hotel::Hotel(const Hotel& other)
    : name_(other.name_),
    rooms_(new Room[other.rooms_capacity_]),
    rooms_count_(other.rooms_count_),
    rooms_capacity_(other.rooms_capacity_) {

    for (int i = 0; i < rooms_count_; ++i) {
        rooms_[i] = other.rooms_[i];
    }
}

// Оператор присваивания
Hotel& Hotel::operator=(const Hotel& other) {
    if (this == &other) {
        return *this;
    }

    delete[] rooms_;

    // Копируем данные
    name_ = other.name_;
    rooms_count_ = other.rooms_count_;
    rooms_capacity_ = other.rooms_capacity_;
    rooms_ = new Room[rooms_capacity_];

    for (int i = 0; i < rooms_count_; ++i) {
        rooms_[i] = other.rooms_[i];
    }

    return *this;
}

// Увеличение ёмкости массива
void Hotel::resizeArray() {
    int new_capacity = rooms_capacity_ * 2;
    Room* new_array = new Room[new_capacity];

    for (int i = 0; i < rooms_count_; ++i) {
        new_array[i] = rooms_[i];
    }

    delete[] rooms_;

    rooms_ = new_array;
    rooms_capacity_ = new_capacity;

}

// Вспомогательный метод
bool Hotel::roomExists(int room_number) const {
    for (int i = 0; i < rooms_count_; ++i) {
        if (rooms_[i].getNumber() == room_number) {
            return true;
        }
    }
    return false;
}

// Содержательный метод 1: Добавление номера
void Hotel::addRoom(const Room& room) {
    // Правило: Номер комнаты должен быть строго больше 0
    if (room.getNumber() <= 0) {
        std::cout << " !!! Номер комнаты должен быть больше 0. "
            << "Добавление отклонено.\n";
        return;
    }

    //  защита от копий
    if (roomExists(room.getNumber())) {
        std::cout << " !!! Номер " << room.getNumber()
            << " уже существует в отеле.\n";
        return;
    }

    // Если массив заполнен — расширение
    if (rooms_count_ >= rooms_capacity_) {
        resizeArray();
    }

    // Добавление номера в конец массива
    rooms_[rooms_count_] = room;
    ++rooms_count_;

    std::cout << " Номер " << room.getNumber() << " успешно добавлен в отель \"" << name_ << "\".\n";
}

// Содержательный метод 2: Печать свободных номеров
void Hotel::printAvailableRooms() const {
    std::cout << "=== Свободные номера в отеле \"" << name_ << "\" ===\n";
    bool found = false;

    for (int i = 0; i < rooms_count_; ++i) {
        if (rooms_[i].isAvailable()) {
            rooms_[i].printInfo();
            found = true;
        }
    }

    if (!found) {
        std::cout << "Свободных номеров нет.\n";
    }
    std::cout << "=========================================\n";
}

// Содержательный метод 3: Заселение гостя
void Hotel::checkInGuestToRoom(Guest* guest, int room_number) {
    for (int i = 0; i < rooms_count_; ++i) {
        if (rooms_[i].getNumber() == room_number) {
            rooms_[i].checkIn(guest);
            return;
        }
    }
    std::cout << " !!! Номер " << room_number << " не найден в отеле.\n";
}

// Содержательный метод 4: Выселение гостя
void Hotel::checkOutFromRoom(int room_number) {
    for (int i = 0; i < rooms_count_; ++i) {
        if (rooms_[i].getNumber() == room_number) {
            rooms_[i].checkOut();
            return;
        }
    }
    std::cout << " !!! Номер " << room_number << " не найден в отеле.\n";
}

std::string Hotel::getName() const {
    return name_;
}

int Hotel::getRoomCount() const {
    return rooms_count_;
}