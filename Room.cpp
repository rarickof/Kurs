#include "Room.hpp"

#include <iostream>

bool Room::validateRoomData(int number, double price) const {
    if (number <= 0) {
        std::cout << " !!! Номер комнаты должен быть > 0. " << "Получено: " << number << std::endl;
        return false;
    }
    if (price <= 0.0) {
        std::cout << " !!! Цена за ночь должна быть > 0. " << "Получено: " << price << std::endl;
        return false;
    }
    return true;
}

// Конструктор по умолчанию
Room::Room(): 
    number_(0), 
    price_per_night_(0.0),
    status_("Свободен"), 
    current_guest_(nullptr) {}

// Конструктор с параметрами
Room::Room(int number, double price_per_night): 
    number_(number), 
    price_per_night_(price_per_night), 
    status_("Свободен"), 
    current_guest_(nullptr) {

    // Проверка правила:
    // Номер комнаты больше 0, цена больше 0».
    if (!validateRoomData(number, price_per_night)) {
        std::cout << " !!! Номер создан с некорректными данными. " << "Установлены значения по умолчанию." << std::endl;
        number_ = 0;
        price_per_night_ = 0.0;
    }
}

Room::~Room() {
    std::cout << "~Room() уничтожен: номер " << number_ << std::endl;
}

// Содержательный метод 1: Заселение гостя
void Room::checkIn(Guest* guest) {
    // Проверка правила:
    // Нельзя заселить гостя в номер, который уже занят.
    if (guest == nullptr) {
        std::cout << " !!! Попытка заселить несуществующего гостя " << "в номер " << number_ << "." << std::endl;
        return;
    }

    if (current_guest_ != nullptr) {
        std::cout << " !!! Номер " << number_ << " уже занят гостем " << current_guest_->getName() << ". Заселение отклонено." << std::endl;
        return;
    }

    if (status_ != "Свободен") {
        std::cout << " !!! Номер " << number_ << " не готов к заселению (статус: \"" << status_ << "\")." << std::endl;
        return;
    }

    // Всё в порядке — заселение
    current_guest_ = guest;  // Агрегация: сохранение указателя
    status_ = "Занят";       // Смена состояня (жизненный цикл)
    std::cout << " Гость " << guest->getName() << " заселён в номер " << number_ << "." << std::endl;
}

// Содержательный метод 2: Выселение гостя
void Room::checkOut() {
    // Проверка: в номере должен кто-то жить
    if (current_guest_ == nullptr) {
        std::cout << " !!! Номер " << number_ << " уже пуст. Нет человека для выселения." << std::endl;
        return;
    }

    std::string guest_name = current_guest_->getName();

    current_guest_ = nullptr;

    // Жизненный цикл: после выезда номер переходит
    // в состояние "Требуется уборка", а не "Свободен"
    status_ = "Требуется уборка";

    std::cout << " Гость " << guest_name << " выехал из номера " << number_ << ". Номер требует уборки." << std::endl;
}

// Содержательный метод 3: Вывод информации
void Room::printInfo() const {
    std::cout << "  Номер: " << number_ << " | Цена: " << price_per_night_ << " руб./ночь"  << " | Статус: " << status_;

    if (current_guest_ != nullptr) {
        std::cout << " | Гость: " << current_guest_->getName();
    }
    std::cout << std::endl;
}

// ─── Содержательный метод 4: Проверка доступности ───
bool Room::isAvailable() const {
    return (status_ == "Свободен" && current_guest_ == nullptr);
}

int Room::getNumber() const {
    return number_;
}

double Room::getPricePerNight() const {
    return price_per_night_;
}

std::string Room::getStatus() const {
    return status_;
}

Guest* Room::getCurrentGuest() const {
    return current_guest_;
}