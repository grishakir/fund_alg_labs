#pragma once
#include <exception>
#include <string>
class tree_exception :
    public std::exception
{
    std::string base;
public:
    tree_exception(std::string message) : base(message) {};
    const char* what() const noexcept {
        return base.c_str();
    }
};




