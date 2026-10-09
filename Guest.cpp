#include "Guest.hpp"

#include <iostream>

// Начальная ёмкость динамического массива.
const int INITIAL_CAPACITY = 5;

// Вспомогательный приватный метод
bool Guest::validateData(const std::string& name,
    const std::string& passport) const {
    if (name.empty()) {
        std::cout << " !!! Имя гостя не может быть пустым!" << std::endl;
        return false;
    }
    if (passport.empty()) {
        std::cout << " !!! Номер паспорта не может быть пустым!"<< std::endl;
        return false;
    }
    return true;
}

// Увеличение ёмкости массива
void Guest::resizeArray() {
    int new_capacity = services_capacity_ * 2;
    std::string* new_array = new std::string[new_capacity];

    for (int i = 0; i < services_count_; ++i) {
        new_array[i] = requested_services_[i];
    }

    delete[] requested_services_;

    requested_services_ = new_array;
    services_capacity_ = new_capacity;

    std::cout << " Массив услуг расширен до " << services_capacity_ << " элементов." << std::endl;
}

// Конструктор по умолчанию
Guest::Guest(): name_("Неизвестный"),
    passport_("0000 000000"),
    requested_services_(new std::string[INITIAL_CAPACITY]),
    services_count_(0),
    services_capacity_(INITIAL_CAPACITY) {}

// Конструктор с параметрами
Guest::Guest(const std::string& name, const std::string& passport)
    : name_(name),
    passport_(passport),
    requested_services_(new std::string[INITIAL_CAPACITY]),
    services_count_(0),
    services_capacity_(INITIAL_CAPACITY) {
    // Проверка правила предметной области
    if (!validateData(name, passport)) {
        std::cout << " !!! Гость создан с некорректными данными. " << "Установлены значения по умолчанию." << std::endl;
        name_ = "Неизвестный";
        passport_ = "0000 000000";
    }
}

Guest::~Guest() {
    delete[] requested_services_;

    std::cout << "~Guest() уничтожен: " << name_ << " (паспорт: " << passport_ << ")" << std::endl;
}

// Копирующий конструктор
Guest::Guest(const Guest& other)
    : name_(other.name_),
    passport_(other.passport_),
    requested_services_(new std::string[other.services_capacity_]),
    services_count_(other.services_count_),
    services_capacity_(other.services_capacity_) {
    for (int i = 0; i < services_count_; ++i) {
        requested_services_[i] = other.requested_services_[i];
    }
}

// Оператор присваивания
Guest& Guest::operator=(const Guest& other) {
    if (this == &other) {
        return *this;
    }
    delete[] requested_services_;
    name_ = other.name_;
    passport_ = other.passport_;
    services_count_ = other.services_count_;
    services_capacity_ = other.services_capacity_;
    requested_services_ = new std::string[services_capacity_];

    for (int i = 0; i < services_count_; ++i) {
        requested_services_[i] = other.requested_services_[i];
    }

    return *this;
}

// Содержательный метод 1: вывод информации
void Guest::printInfo() const {
    std::cout << "=== Информация о госте ===" << std::endl;
    std::cout << "  ФИО:     " << name_ << std::endl;
    std::cout << "  Паспорт: " << passport_ << std::endl;

    if (services_count_ == 0) {
        std::cout << "  Услуги:  нет" << std::endl;
    }
    else {
        std::cout << "  Услуги:  ";
        for (int i = 0; i < services_count_; ++i) {
            std::cout << requested_services_[i];
            if (i < services_count_ - 1) {
                std::cout << ", ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << "==========================" << std::endl;
}

// Содержательный метод 2: запрос услуги
void Guest::requestService(const std::string& service_name) {
    // Проверка: название не пустое
    if (service_name.empty()) {
        std::cout << " !!! Название услуги не может быть пустым."
            << std::endl;
        return;
    }

    // Проверка: нет дубликатов
    for (int i = 0; i < services_count_; ++i) {
        if (requested_services_[i] == service_name) {
            std::cout << " !!! Услуга \"" << service_name << "\" уже запрошена гостем " << name_ << "."<< std::endl;
            return;
        }
    }

    // Если массив заполнен — расширение
    if (services_count_ >= services_capacity_) {
        resizeArray();
    }

    requested_services_[services_count_] = service_name;
    ++services_count_;

    std::cout << "  Гость " << name_ << " запросил услугу \"" << service_name << "\"." << std::endl;
}

// Содержательный метод 3: отмена услуги
void Guest::cancelService(const std::string& service_name) {
    // Поиск услуги в массиве
    int found_index = -1;
    for (int i = 0; i < services_count_; ++i) {
        if (requested_services_[i] == service_name) {
            found_index = i;
            break;
        }
    }

    // Проверка: услуга должна существовать
    if (found_index == -1) {
        std::cout << " !!! Услуга \"" << service_name << "\" не найдена в списке гостя " << name_ << "." << std::endl;
        return;
    }

    // Сдвиг элементов после найденного на одну влево
    for (int i = found_index; i < services_count_ - 1; ++i) {
        requested_services_[i] = requested_services_[i + 1];
    }
    --services_count_;
    requested_services_[services_count_] = "";

    std::cout << " Гость " << name_ << " отменил услугу \"" << service_name << "\"." << std::endl;
}

// ─── Геттеры ───
std::string Guest::getName() const {
    return name_;
}

std::string Guest::getPassport() const {
    return passport_;
}

int Guest::getServicesCount() const {
    return services_count_;
}