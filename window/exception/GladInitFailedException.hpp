#ifndef GLAD_INIT_FAILED_EXCEPTION_CLASS

#define GLAD_INIT_FAILED_EXCEPTION_CLASS

#include <iostream>

class GladInitFailedException : public std::exception {
    public:
        const char* what() const noexcept override {
            return "Failed to initialize GLAD";
        }
};

#endif