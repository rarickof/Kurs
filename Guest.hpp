#pragma once
#include <string>

class Guest {
private:
    std::string name_;
    std::string passport_;

    std::string* requested_services_;  // Указатель на массив строк
    int services_count_;               // Сколько услуг сейчас в массиве
    int services_capacity_;            // На сколько элементов выделена память

    bool validateData(const std::string& name, const std::string& passport) const;
    void resizeArray();  // Увеличивание ёмкость массива в 2 раза

public:
    // Конструкторы
    Guest();
    Guest(const std::string& name, const std::string& passport);

    // Деструктор
    ~Guest();

    Guest(const Guest& other);
    Guest& operator=(const Guest& other);

    // Содержательные методы
    void printInfo() const;
    void requestService(const std::string& service_name);
    void cancelService(const std::string& service_name);

    // Геттеры
    [[nodiscard]] std::string getName() const;
    [[nodiscard]] std::string getPassport() const;
    [[nodiscard]] int getServicesCount() const;
};