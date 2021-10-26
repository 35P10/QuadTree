#include "quadtree.h"
#include <iostream>
#include <ostream>


quadtree::quadtree(punto abajo_izquierda, punto arriba_derecha) {
    root = new nodo();
    root->set_boundary(abajo_izquierda, arriba_derecha);
    root->update_status(1);
}

void quadtree::insertar(int x, int y, int data) {
    nodo* new_nodo = new nodo(x, y, data);
    nodo* iterator = root;
    nodo* iterator_padre = iterator;
    /*
        _______________________
        |          |          |
        |     1    |    2     |
        _______________________
        |          |          |
        |     3    |    4     |
        _______________________

    */
    //hallar al sector al que pertenece 
    int h = iterator->get_height_mid();
    int w = iterator->get_width_mid();
    int final_sector;

    while (iterator) {
        iterator_padre = iterator;
        if (iterator->get_coordenadas().x == x && iterator->get_coordenadas().y == y) {
            //Nodo repetido
            return;
        }
        if (!iterator->is_dividible()) return;

        if (y > iterator->get_height_mid()) { //se encuentra en los sectores superiores
            if (x < iterator->get_width_mid()) {//sector 1
                iterator = iterator->get_hijo(0);
                final_sector = 0;
            }
            else { //sector 2
                iterator = iterator->get_hijo(1);
                final_sector = 1;

            }
        }
        else {  //sector 3
            if (x < iterator->get_width_mid()) {
                iterator = iterator->get_hijo(2);
                final_sector = 2;
            }
            else { //sector 4
                iterator = iterator->get_hijo(3);
                final_sector = 3;

            }
        }
    }

    iterator_padre->set_hijo(final_sector, new_nodo);
    iterator_padre->get_hijo(final_sector)->set_boundary(iterator_padre->get_sector_boundary(final_sector));

}


std::vector<nodo*> quadtree::get_query_list()
{
    return query_list;
}

void quadtree::reset_queary_list()
{
    for (auto i : query_list)
        i->select_switch();
    query_list.clear();
}

std::vector<nodo*> quadtree::consulta_rango(punto abajo_izquierda, punto arriba_derecha) {
    reset_queary_list();
    sector_consulta = new nodo();
    sector_consulta->set_boundary(abajo_izquierda, arriba_derecha);
    sector_consulta->update_status(1);

    root->query_in_range(query_list, abajo_izquierda, arriba_derecha);

    return query_list;
}


void quadtree::print()
{
    root->print_Nodo();
    sector_consulta->draw_just_this(0, 250, 250);
}


