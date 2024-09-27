#ifndef PPM_CAPTURE_CLASS
#define PPM_CAPTURE_CLASS

#include <iostream>
#include <fstream>
#include <string>
#include <glad/glad.h>

class PPMCapture {
    public:
        PPMCapture();
        void Dump(std::string prefix, unsigned int width, unsigned int height);
        unsigned int getId();

    private:
        unsigned int idCounter;
};

#endif