#pragma once
#include <string>
#include <memory>

class Guest {
private:
    std::string m_name;
    std::string m_passport;
    std::unique_ptr<std::string[]> m_requestedServices;
    int m_servicesCount;               // Сколько услуг сейчас в массиве
    int m_servicesCapacity;            // На сколько элементов выделена память

    bool validateData(const std::string& name, const std::string& passport) const;
    void resizeArray();  // Увеличение ёмкости массива в 2 раза

public:
    // Конструкторы
    Guest();
    Guest(const std::string& name, const std::string& passport);

    // Правило трёх
    Guest(const Guest& other);

    // Оператор присваивания a = b
    // Если не писать поверхностный оператор поэлементно скопирует все поля. 
    Guest& operator=(const Guest& other);

    // Содержательные методы
    void printInfo() const;
    void requestService(const std::string& serviceName);
    void cancelService(const std::string& serviceName);

    Guest& withService(const std::string& service);

    // Геттеры Guest
    [[nodiscard]] std::string getName() const;
    [[nodiscard]] std::string getPassport() const;
    [[nodiscard]] int getServicesCount() const;
};