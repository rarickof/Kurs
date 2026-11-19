#include <iostream>
#include "StandardRoom.hpp"


StandardRoom::StandardRoom(int number, double basePrice)
    : BaseRoom{ number, basePrice }
{
    std::cout << "StandardRoom() создан: номер " << number << "\n";
}

double StandardRoom::calculateCost(int nights) const {
    // Цена за кол-во ночей
    return (nights * getPricePerNight());
}

std::string StandardRoom::getDescription() const {
    return BaseRoom::getDescription() + ", категория: Стандарт\n" ;
}

std::unique_ptr<BaseRoom> StandardRoom::Clone() const {
    return std::make_unique<StandardRoom>(*this); // Копирование всех полей
}