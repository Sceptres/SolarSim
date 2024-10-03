#ifndef COLOR_CLASS

#define COLOR_CLASS

class Color {
    public:
        Color(float r, float g, float b, float a);
        Color(float r, float g, float b);
        const float r;
        const float g;
        const float b;
        const float a;
};

#endif