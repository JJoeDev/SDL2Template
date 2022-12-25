#pragma once
#include <iostream>

// This will either take two floats for a position, or default it to 0, 0
struct Vector2f {
    Vector2f(float X, float Y) : x(X), y(Y) { }
    Vector2f() : x(0.0f), y(0.0f) { }

    // This can print the x and y position for debugging
    void print() {
        std::cout << x << ", " << y << std::endl;
    }

    float x, y;
};