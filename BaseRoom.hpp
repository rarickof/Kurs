#pragma once
#include <string>
#include <memory>
#include <iostream>
#include "Guest.hpp"

class BaseRoom {
private:
    int m_number;                    // Номер комнаты
    double m_pricePerNight;          // Стоимость за ночь
    std::weak_ptr<Guest> m_currentGuest;
    std::shared_ptr<BaseRoom> m_base_room{};
    //позволяет инициализировать поле прямо в классе
    inline static int m_num_of_rooms{ 0 };//Количество созданных номеров

    bool validateRoomData(int number, double pricePerNight) const;

public:

    // Конструктор с параметрами
    BaseRoom(int number, double pricePerNight);

    //Конструктор копирования
    BaseRoom(const BaseRoom& other);

    // Оператор присваивания a = b
    // Если не писать поверхностный оператор поэлементно скопирует все поля. 
    BaseRoom& operator=(const BaseRoom& other);// глубокое присваивание

    //Нужен для отчистки сначала памяти наследника,
    //затем памяти базы
    virtual ~BaseRoom() {
        std::cout << "~BaseRoom(): номер " << m_number << "\n";
    }

    // Виртуальный метод с реализацией, наследник может переопределить
    virtual std::string getDescription() const;

    // Чистый виртуальный метод делает класс абстрактным, нельзя создать объект
    // нет реализации
    virtual double calculateCost(int nights) const = 0;
    //производный класс должен переопределить эту функцию и вернуть указатель на копию самого себя
    virtual std::unique_ptr<BaseRoom> Clone() const = 0;

    // Содержательные методы
    void checkIn(std::shared_ptr<Guest> guest);      // Заселение гостя (Агрегация)
    void checkOut();                 // Выселение гостя
    void printInfo() const;          // Вывод информации о номере
    bool isAvailable() const;

    int setNumber(int number);

    // Геттеры Room
    [[nodiscard]] int getNumber() const;
    [[nodiscard]] double getPricePerNight() const;
    [[nodiscard]] std::string getStatus() const;

    [[nodiscard]] static int getUsedRooms();
protected:
    // "Свободен" | "Занят" | "Требуется уборка"
    std::string m_status;
};