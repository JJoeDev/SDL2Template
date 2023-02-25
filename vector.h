#ifndef VECTOR_H
#define VECTOR_H

struct Vector2f { // A simple way to store two floats as X and Y
    Vector2f(float X, float Y) : x(X), y(Y) { }
    Vector2f() : x(0.0), y(0.0) { }

    float x, y;
};

struct Vector2i { // A simple way to store two ints as X and Y
    Vector2i(int X, int Y) : x(X), y(Y) { }
    Vector2i() : x(0), y(0) { }

    int x, y;
};

#endif