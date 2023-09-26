#pragma once

#include <iostream>
#include <exception>
#include <string>

namespace HeartEngine
{
class Debug
{
public:
#ifdef DEBUG
    #define PRINT(...) print(__VA_ARGS__)
#else
    #define PRINT(...) doNothing()
#endif

    template <class T>
    static void print(T t)
    {
        std::cout << t << std::endl;
    }

    template <class T, class... Args>
    static void print(T t, Args... args)
    {
        std::cout << t;
        print(args...);
    }

    static void doNothing() {}
};

class HeartException : public std::exception
{
public:
    HeartException(std::string_view string)
    {
        message.append(string);
    }

    HeartException(std::initializer_list<std::string_view> strings)
    {
        for (auto& str : strings)
            message.append(str);
    }

    const char* what()
    {
        return std::string()
            .append("HeartEngine Error: ")
            .append(message)
            .c_str();
    }
private:
    void append(const std::string& p_message) { message.append(p_message); }

    std::string message;
};
}