#pragma once

#include <iostream>

namespace HeartEngine
{
class Debug
{
public:
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

    template <class T>
    static void printerr(T t)
    {
        std::cerr << t << std::endl;
    }

    template <class T, class... Args>
    static void printerr(T t, Args... args)
    {
        std::cerr << t;
        print(args...);
        std::cerr << std::endl;
    }
};
}