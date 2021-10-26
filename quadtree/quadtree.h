#pragma once

#include "nodo.h"
#include <vector>

class quadtree {
private:
    nodo* root;
    std::vector<nodo*> query_list;
    nodo* sector_consulta = nullptr;

public:
                        quadtree(punto abajo_izquierda, punto arriba_derecha);
    void                insertar(int x, int y, int data);
    std::vector<nodo*>  get_query_list();
    void                reset_queary_list();
    std::vector<nodo*>  consulta_rango(punto abajo_izquierda, punto arriba_derecha);
    void                print();
};

