#include "Room.hpp"
#include <iostream>

// Вспомогательный приватный метод для валидации данных
bool Room::validateRoomData(int number, double pricePerNight) const {
    if (number <= 0) {
        std::cout << " !!! Номер комнаты должен быть > 0. Получено: " << number << std::endl;
        return false;
    }
    if (pricePerNight <= 0.0) {
        std::cout << " !!! Цена за ночь должна быть > 0. Получено: " << pricePerNight << std::endl;
        return false;
    }
    return true;
}

// Конструктор по умолчанию
Room::Room()
    : m_number(0),
    m_pricePerNight(0.0),
    m_status("Свободен"),
    m_currentGuest() {}

// Конструктор с параметрами
Room::Room(int number, double pricePerNight)
    : m_number(number),
    m_pricePerNight(pricePerNight),
    m_status("Свободен"),
    m_currentGuest() {

    // Проверка правила предметной области
    if (!validateRoomData(number, pricePerNight)) {
        std::cout << " !!! Номер создан с некорректными данными. Установлены значения по умолчанию." << std::endl;
        m_number = 0;
        m_pricePerNight = 0.0;
    }
}

// Содержательный метод 1: Заселение гостя
void Room::checkIn(std::shared_ptr<Guest> guest) {
    // 1. проверка входящего параметра
    if (!guest) {
        std::cout << " !!! Попытка заселить несуществующего гостя в номер " << m_number << "." << std::endl;
        return;
    }

    // 2. Проверка, не занят ли номер
    if (!m_currentGuest.expired()) {//проверка на существование
        if (auto lockedGuest = m_currentGuest.lock()) {//жив ли гость (да, возврат shared)
            std::cout << " !!! Номер " << m_number << " уже занят гостем " << lockedGuest->getName()  << ". Заселение отклонено." << std::endl;
        }
        return;
    }

    // 3. Проверка статуса номера (жизненный цикл)
    if (m_status != "Свободен") {
        std::cout << " !!! Номер " << m_number << " не готов к заселению (статус: \"" << m_status << "\")." << std::endl;
        return;
    }

    m_currentGuest = guest;  // Агрегация: сохранение указателя
    m_status = "Занят";      // Смена состояния
    std::cout << " Гость " << guest->getName() << " заселён в номер " << m_number << "." << std::endl;
}

// Содержательный метод 2: Выселение гостя
void Room::checkOut() {
    auto lockedGuest = m_currentGuest.lock();
    // Проверка: в номере должен кто-то жить
    if (!lockedGuest) {
        std::cout << " !!! Номер " << m_number << " уже пуст. Нет человека для выселения." << std::endl;
        return;
    }

    // Сохранение имени в локальную переменную перед обрывом связи
    std::string guestName = lockedGuest->getName();

    m_currentGuest.reset();

    // Жизненный цикл: после выезда номер переходит в состояние "Требуется уборка"
    m_status = "Требуется уборка";

    std::cout << " Гость " << guestName << " выехал из номера " << m_number << ". Номер требует уборки." << std::endl;
}

// Содержательный метод 3: Вывод информации
void Room::printInfo() const {
    std::cout << "  Номер: " << m_number
        << " | Цена: " << m_pricePerNight << " руб./ночь"
        << " | Статус: " << m_status;

    if (auto lockedGuest = m_currentGuest.lock()) {
        std::cout << " | Гость: " << lockedGuest->getName();
    }
    std::cout << std::endl;
}

// Содержательный метод 4: Проверка доступности
bool Room::isAvailable() const {
    return (m_status == "Свободен" && m_currentGuest.expired());
}

// Геттеры
int Room::getNumber() const {
    return m_number;
}

double Room::getPricePerNight() const {
    return m_pricePerNight;
}

std::string Room::getStatus() const {
    return m_status;
}

std::weak_ptr<Guest> Room::getCurrentGuest() const {
    return m_currentGuest;
}