#include <iostream>
#include "EconomyRoom.hpp"


EconomyRoom::EconomyRoom(int number, double basePrice)
    : BaseRoom{ number, basePrice }
{
    std::cout << "EconomyRoom() создан: номер " << number << "\n";
}

double EconomyRoom::calculateCost(int nights) const {
    // Цена за кол-во ночей
    return (nights * getPricePerNight());
}

//Дополнение
std::string EconomyRoom::getDescription() const {
    return BaseRoom::getDescription() + ", категория: Эконом\n";
}

std::unique_ptr<BaseRoom> EconomyRoom::Clone() const {
    return std::make_unique<EconomyRoom>(*this); // Копирование всех полей
}

