#pragma once
#include <ostream>
struct punto {
    //coordenadas
    int x = 0;
    int y = 0;
    punto() { ; }
    punto(int x, int y) {
        this->x = x;
        this->y = y;
    }
};

