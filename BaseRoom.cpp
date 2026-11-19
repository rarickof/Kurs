#include "BaseRoom.hpp"
#include <iostream>

// Вспомогательный приватный метод для валидации данных
bool BaseRoom::validateRoomData(int number, double pricePerNight) const {
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

// Конструктор с параметрами
BaseRoom::BaseRoom(int number, double pricePerNight)
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

    std::cout << "BaseRoom() создан: номер " << number << "\n";
    ++m_num_of_rooms;
}

BaseRoom::BaseRoom(const BaseRoom& other)
    : m_number{ other.m_number },
    m_pricePerNight{ other.m_pricePerNight },
    m_status(other.m_status),
    m_currentGuest{ other.m_currentGuest }

{
    ++m_num_of_rooms;
}

// Оператор присваивания a = b
// Если не писать поверхностный оператор поэлементно скопирует все поля.
BaseRoom& BaseRoom::operator=(const BaseRoom& other)
{
    if (this == &other)
    {
        return *this;
    }

    m_number = other.m_number;
    m_pricePerNight = other.m_pricePerNight;
    m_status = other.m_status;
    m_currentGuest = other.m_currentGuest;

    return *this; // возврат самого объекта: a = b = c
}
// Виртуальный метод с реализацией, наследник может переопределить
std::string BaseRoom::getDescription() const {
    return "Номер " + std::to_string(m_number) +
        ", цена: " + std::to_string(m_pricePerNight) +
        ", статус:" + m_status;
}

// Содержательный метод 1: Заселение гостя
void BaseRoom::checkIn(std::shared_ptr<Guest> guest) {
    // 1. проверка входящего параметра
    if (!guest) {
        std::cout << " !!! Попытка заселить несуществующего гостя в номер " << m_number << "." << std::endl;
        return;
    }

    // 2. Проверка, не занят ли номер
    if (!m_currentGuest.expired()) {//проверка на существование
        if (auto lockedGuest = m_currentGuest.lock()) {//жив ли гость (да, возврат shared)
            std::cout << " !!! Номер " << m_number << " уже занят гостем " << lockedGuest->getName() << ". Заселение отклонено." << std::endl;
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
void BaseRoom::checkOut() {
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
void BaseRoom::printInfo() const {
    std::cout << "  Номер: " << m_number
        << " | Цена: " << m_pricePerNight << " руб./ночь"
        << " | Статус: " << m_status;

    if (auto lockedGuest = m_currentGuest.lock()) {
        std::cout << " | Гость: " << lockedGuest->getName();
    }
    std::cout << std::endl;
}
// Содержательный метод 4: Проверка доступности
bool BaseRoom::isAvailable() const {
    return (m_status == "Свободен" && m_currentGuest.expired());
}

int BaseRoom::setNumber(int number) { return m_number = number; }
// Геттеры
int BaseRoom::getNumber() const { return m_number; }
double BaseRoom::getPricePerNight() const { return m_pricePerNight; }
std::string BaseRoom::getStatus() const { return m_status; }
int BaseRoom::getUsedRooms() { return m_num_of_rooms; }