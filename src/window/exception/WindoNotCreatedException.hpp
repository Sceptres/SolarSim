#ifndef WINDOW_NOT_CREATED_EXCEPTION_CLASS

#define WINDOW_NOT_CREATED_EXCEPTION_CLASS

#include <iostream>

class WindowNotCreatedException : public std::exception {
    public:
        const char* what() const noexcept override {
            return "Failed to create a window";
        }
};

#endif