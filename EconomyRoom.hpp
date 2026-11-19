#pragma once
#include "BaseRoom.hpp"

class EconomyRoom : public BaseRoom {
private:
    //немедленная инициализация неизменяемого общего значения
    static constexpr int MIN_STAY_NIGHTS = 1;  // минимальный срок
public:
    EconomyRoom(int number, double basePrice);
    
    ~EconomyRoom() {
        std::cout << "~EconomyRoom: номер " << getNumber() << "\n";
    }
    //переопределение — предоставления в производном классе новой реализации метода,
    //свойства, индексатора или события, которые уже есть в базовом классе.
    double calculateCost(int nights) const override;//проверка, что метод действительно переопределяет виртуальный метод базы.

    std::string getDescription() const override;

    std::unique_ptr<BaseRoom> Clone() const override;
};