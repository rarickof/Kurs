#include <iostream>
#include "LuxuryRoom.hpp"


LuxuryRoom::LuxuryRoom(int number, double basePrice)
    : BaseRoom{ number, basePrice }
{
    std::cout << "LuxuryRoom() создан: номер " << number << "\n";
}

double LuxuryRoom::calculateCost(int nights) const {
    if (nights <= MIN_STAY_NIGHT) {
        std::cout << "Нельзя забронировать номер Люкс меньше чем на 2 ночи";
        return 0.0;
    }
    // Цена за кол-во ночей и наценки за премиум обсуживание
    return (nights * getPricePerNight()) * 1.5;
}

//Замена
std::string LuxuryRoom::getDescription() const {
    std::string status;
    //Поиск первого вхождения подстроки
    const std::size_t pos = m_status.find("Свободен");
    //сравнение с константой отсутствие элемента (-1)
    if (pos != std::string::npos)
    {
        // подстрока: с позиции pos, 8 символов
        const std::string part = m_status.substr(pos, 8);
    }
    if (m_status == "Свободен")
    {
        status = " Свободен";
    }
    else {
        status = " Занят";
    }
    return "Люксовый номер:" + std::to_string(getNumber()) + status;
}

std::unique_ptr<BaseRoom> LuxuryRoom::Clone() const {
    return std::make_unique<LuxuryRoom>(*this); // Копирование всех полей
}