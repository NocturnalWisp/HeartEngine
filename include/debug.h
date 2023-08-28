#pragma once

#include <iostream>

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
        std::cout << std::endl;
    }

    template <class T>
    static void printerr(T t)
    {
        std::cerr << t;
    }

    template <class T, class... Args>
    static void printerr(T t, Args... args)
    {
        std::cerr << t;
        print(args...);
        std::cerr << std::endl;
    }
};