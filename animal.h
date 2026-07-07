#pragma once

#include <string>
#include <iostream>
#include <type_traits>
#include <stdint.h>

class Animal
{
public:
    Animal() noexcept
    {
        std::cout << "Default construct Animal Object!" << std::endl;
    }
    ~Animal() noexcept
    {
        std::cout << "Destruct Animal Object!" << std::endl;
    }
    Animal(const Animal& animal) : name_(animal.GetName()), age_(animal.GetAge())
    {
        std::cout << "Copy construct Animal Object!" << std::endl;
    }
    Animal& operator=(const Animal&) = default;
    Animal(Animal &&animal) : name_(std::move(animal.GetName())), age_(std::move(animal.GetAge()))
    {
        std::cout << "Move construct Animal Object!" << std::endl;
    }
    Animal& operator=(Animal&&) = default;
private:
    std::string name_{"Unnamed"};
    uint8_t age_{0};
public: 
    const std::string& GetName() const noexcept
    {
        return name_;
    }
    const uint8_t& GetAge() const noexcept
    {
        return age_;
    }

    std::string& GetName() noexcept
    {
        return name_;
    }
    uint8_t& GetAge() noexcept
    {
        return age_;
    }

    template <typename String, typename = typename std::enable_if_t<std::is_same<std::decay_t<String>, std::string>::value>>
    void SetName(String && name)
    {
        name_ = std::forward<String>(name);
    }

    template <typename T>
    void SetAge(T && age)
    {
        age_ = std::forward<T>(age);
    }
};