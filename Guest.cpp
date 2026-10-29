#include "Guest.hpp"
#include <iostream>

// Начальная ёмкость динамического массива.
const int INITIAL_CAPACITY = 5;

// Вспомогательный приватный метод
bool Guest::validateData(const std::string& name, const std::string& passport) const {
    if (name.empty()) {
        std::cout << " !!! Имя гостя не может быть пустым!" << std::endl;
        return false;
    }
    if (passport.empty()) {
        std::cout << " !!! Номер паспорта не может быть пустым!" << std::endl;
        return false;
    }
    return true;
}

// Конструктор по умолчанию
Guest::Guest()
    : m_name("Неизвестный"),
    m_passport("0000 000000"),
    m_requestedServices(std::make_unique<std::string[]>(INITIAL_CAPACITY)),
    m_servicesCount(0),
    m_servicesCapacity(INITIAL_CAPACITY) 
{}

// Конструктор с параметрами
Guest::Guest(const std::string& name, const std::string& passport)
    : m_name(name),
      m_passport(passport),
      m_requestedServices(std::make_unique<std::string[]>(INITIAL_CAPACITY)),
      m_servicesCount(0),
      m_servicesCapacity(INITIAL_CAPACITY) {

    // Проверка правила предметной области
    if (!validateData(name, passport)) {
        std::cout << " !!! Гость создан с некорректными данными.  "
            << "Установлены значения по умолчанию. " << std::endl;
        m_name = "Неизвестный";
        m_passport = "0000 000000";
    }
}

// Увеличение ёмкости массива
void Guest::resizeArray() {
    int newCapacity = m_servicesCapacity * 2;
    auto newArray = std::make_unique<std::string[]>(newCapacity);

    for (int i = 0; i < m_servicesCount; ++i) {
        newArray[i] = m_requestedServices[i];
    }

    m_requestedServices = std::move(newArray);
    m_servicesCapacity = newCapacity;

    std::cout << " Массив услуг расширен до " << m_servicesCapacity << " элементов." << std::endl;
}

// Копирующий конструктор
Guest::Guest(const Guest& other)
    : m_name(other.m_name),
    m_passport(other.m_passport),
    m_servicesCount(other.m_servicesCount),
    m_servicesCapacity(other.m_servicesCapacity),

    m_requestedServices(std::make_unique<std::string[]>(m_servicesCapacity))
{
    for (int i = 0; i < m_servicesCount; ++i) {
        m_requestedServices[i] = other.m_requestedServices[i];
    }
}

// Оператор присваивания
Guest& Guest::operator=(const Guest& other) {
    if (this == &other) {
        return *this;
    }

    m_name = other.m_name;
    m_passport = other.m_passport;
    m_servicesCount = other.m_servicesCount;
    m_servicesCapacity = other.m_servicesCapacity;
    m_requestedServices = std::make_unique<std::string[]>(m_servicesCapacity);

    for (int i = 0; i < m_servicesCount; ++i) {
        m_requestedServices[i] = other.m_requestedServices[i];
    }

    return *this;
}

// Содержательный метод 1: вывод информации
void Guest::printInfo() const {
    std::cout << "=== Информация о госте === " << std::endl;
    std::cout << "  ФИО:      " << m_name << std::endl;
    std::cout << "  Паспорт:  " << m_passport << std::endl;

    if (m_servicesCount == 0) {
        std::cout << "  Услуги:  нет" << std::endl;
    }
    else {
        std::cout << "  Услуги:  ";
        for (int i = 0; i < m_servicesCount; ++i) {
            std::cout << m_requestedServices[i];
            if (i < m_servicesCount - 1) {
                std::cout << ", ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << "==========================" << std::endl;
}

// Содержательный метод 2: запрос услуги
void Guest::requestService(const std::string& serviceName) {
    // Проверка: название не пустое
    if (serviceName.empty()) {
        std::cout << " !!! Название услуги не может быть пустым." << std::endl;
        return;
    }

    // Проверка: нет дубликатов
    for (int i = 0; i < m_servicesCount; ++i) {
        if (m_requestedServices[i] == serviceName) {
            std::cout << " !!! Услуга \"" << serviceName << "\" уже запрошена гостем " << m_name << "." << std::endl;
            return;
        }
    }

    // Если массив заполнен — расширение
    if (m_servicesCount >= m_servicesCapacity) {
        resizeArray();
    }

    m_requestedServices[m_servicesCount] = serviceName;
    ++m_servicesCount;

    std::cout << "  Гость " << m_name << " запросил услугу \"" << serviceName << "\"." << std::endl;
}

// Содержательный метод 3: отмена услуги
void Guest::cancelService(const std::string& serviceName) {
    // Поиск услуги в массиве
    int foundIndex = -1;
    for (int i = 0; i < m_servicesCount; ++i) {
        if (m_requestedServices[i] == serviceName) {
            foundIndex = i;
            break;
        }
    }

    // Проверка: услуга должна существовать
    if (foundIndex == -1) {
        std::cout << " !!! Услуга \"" << serviceName << "\" не найдена в списке гостя " << m_name << "." << std::endl;
        return;
    }

    // Сдвиг элементов после найденного на одну влево
    for (int i = foundIndex; i < m_servicesCount - 1; ++i) {
        m_requestedServices[i] = m_requestedServices[i + 1];
    }

    --m_servicesCount;
    m_requestedServices[m_servicesCount] = "";

    std::cout << " Гость " << m_name << " отменил услугу \"" << serviceName << "\"." << std::endl;
}

// Геттеры
std::string Guest::getName() const {
    return m_name;
}

std::string Guest::getPassport() const {
    return m_passport;
}

int Guest::getServicesCount() const {
    return m_servicesCount;
}