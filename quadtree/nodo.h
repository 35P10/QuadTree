#pragma once
#include <utility>
#include "punto.h"
#include <vector>

class nodo {
private:
    punto   coordenadas;
    int     data;

    nodo* hijos[4];

    int     status = 2; //1->cuadrado(tiene al menos un hijo) 2->punto,hoja(no tiene hijos) 3->NULL

    //perimetro
    punto   arriba_derecha;
    punto   abajo_izquierda;

    bool     is_select = false; //solo es para identificar de que color pintar un punto
                            //en caso de ser seleccionado en un range query
public:
    nodo* get_hijo(int x);
    void    set_hijo(int x, nodo* new_hijo);
    void    set_hijos_NULL();
    nodo();
    nodo(int x, int y, int data);
    bool    get_is_select();
    void    select_switch();
    int     get_height();
    int     get_width();
    int     get_height_mid();
    int     get_width_mid();
    void    set_boundary(punto abajo_izquierda, punto arriba_derecha);
    void    set_boundary(std::pair<punto, punto> _bondary);
    int     get_data();
    punto   get_coordenadas();
    void    update_status(int);
    int     get_status();
    void    print_Nodo();
    void    print_just_this();
    void    draw_just_this(int r, int g, int b);
    bool    is_dividible();
    std::pair<punto, punto> get_boundary();
    std::pair<punto, punto> get_sector_boundary(int x);
    bool    is_in_range(punto abajo_izquierda, punto arriba_derecha);
    void    query_in_range(std::vector<nodo*>& list_of_nodes, punto abajo_izquierda, punto arriba_derecha);
};



