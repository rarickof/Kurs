#pragma once
#include "BaseRoom.hpp"

//Запрет на наследование
class LuxuryRoom final : public BaseRoom
{
private:
    //немедленная инициализация неизменяемого общего значения
    // constexpr вычисления на этапе компиляции
    static constexpr  int MIN_STAY_NIGHT = 2;
public:
    LuxuryRoom(int number, double basePrice);

    ~LuxuryRoom() {
        std::cout << "~LuxuryRoom: номер " << getNumber() << "\n";
    }
    //переопределение — предоставления в производном классе новой реализации метода,
    //свойства, индексатора или события, которые уже есть в базовом классе.
    double calculateCost(int nights) const override;//проверка, что метод действительно переопределяет виртуальный метод базы.

    std::string getDescription() const override;

    std::unique_ptr<BaseRoom> Clone() const override;
};