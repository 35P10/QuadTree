#include "nodo.h"
#include <iostream>
#include "graficos.h"

nodo* nodo::get_hijo(int x)
{
	return hijos[x];
}

void nodo::set_hijo(int x, nodo* new_hijo) {
	hijos[x] = new_hijo;
	status = 1;
}

void nodo::set_hijos_NULL() {
	hijos[0] = nullptr;
	hijos[1] = nullptr;
	hijos[2] = nullptr;
	hijos[3] = nullptr;
}

nodo::nodo() {
	set_hijos_NULL();
}

nodo::nodo(int x, int y, int data) {
	set_hijos_NULL();
	coordenadas = punto(x, y);
	this->data = data;
}

bool nodo::get_is_select()
{
	return is_select;
}

void nodo::select_switch()
{
	is_select = !is_select;
}

int nodo::get_height() {
	return arriba_derecha.y - abajo_izquierda.y;
}

int nodo::get_width() {
	return arriba_derecha.x - abajo_izquierda.x;
}

int nodo::get_height_mid() {
	return this->get_height() / 2 + abajo_izquierda.y;
}

int nodo::get_width_mid() {
	return this->get_width() / 2 + abajo_izquierda.x;
}

void nodo::set_boundary(punto abajo_izquierda, punto arriba_derecha) {
	this->arriba_derecha = arriba_derecha;
	this->abajo_izquierda = abajo_izquierda;
}

void nodo::set_boundary(std::pair<punto, punto> _bondary) {
	this->abajo_izquierda = _bondary.first;
	this->arriba_derecha = _bondary.second;
}

int nodo::get_data() {
	return data;
}

punto nodo::get_coordenadas()
{
	return coordenadas;
}

void nodo::update_status(int x)
{
	status = x;
}

int nodo::get_status()
{
	return status;
}

std::pair<punto, punto> nodo::get_boundary() {
	return std::make_pair(abajo_izquierda, arriba_derecha);
}

std::pair<punto, punto> nodo::get_sector_boundary(int x) {
	if (x == 0) {
		return std::make_pair(punto(abajo_izquierda.x, this->get_height_mid()), punto(this->get_width_mid(), arriba_derecha.y));
	}
	else if (x == 1) {
		return std::make_pair(punto(this->get_width_mid(), this->get_height_mid()), arriba_derecha);
	}
	else if (x == 2) {
		return std::make_pair(abajo_izquierda, punto(this->get_width_mid(), this->get_height_mid()));
	}
	else {
		return std::make_pair(punto(this->get_width_mid(), abajo_izquierda.y), punto(this->arriba_derecha.x, this->get_height_mid()));
	}
}

bool nodo::is_in_range(punto _abajo_izquierda, punto _arriba_derecha)
{
	if (status == 1) {
		//comprobar si algun nodo esta en el rango
		//contiene todo el cuadrado
		//nodo izquierda abajo
		if (_abajo_izquierda.x <= abajo_izquierda.x && _abajo_izquierda.y <= abajo_izquierda.y
			&& abajo_izquierda.x <= _arriba_derecha.x && abajo_izquierda.y <= _arriba_derecha.y)
			return true;
		//nodo derecha arriba
		if (_abajo_izquierda.x <= arriba_derecha.x && _abajo_izquierda.y <= arriba_derecha.y
			&& arriba_derecha.x <= _arriba_derecha.x && arriba_derecha.y <= _arriba_derecha.y)
			return true;
		//nodo izquierda arriba
		if (_abajo_izquierda.x <= abajo_izquierda.x && _abajo_izquierda.y <= arriba_derecha.y
			&& abajo_izquierda.x <= _arriba_derecha.x && arriba_derecha.y <= _arriba_derecha.y)
			return true;
		//nodo derecha abajo
		if (_abajo_izquierda.x <= arriba_derecha.x && _abajo_izquierda.y <= abajo_izquierda.y
			&& arriba_derecha.x <= _arriba_derecha.x && abajo_izquierda.y <= _arriba_derecha.y)
			return true;
	}
	else {
		if (_abajo_izquierda.x <= coordenadas.x && _abajo_izquierda.y <= coordenadas.y
			&& coordenadas.x <= _arriba_derecha.x && coordenadas.y <= _arriba_derecha.y)
			return true;
	}
	return false;
}
void nodo::query_in_range(std::vector<nodo*>& list_of_nodes, punto abajo_izquierda, punto arriba_derecha)
{
	if (this->is_in_range(abajo_izquierda, arriba_derecha)) {
		if (this->status == 2) {
			this->select_switch();
			list_of_nodes.push_back(this);
			return;
		}
		if (this->hijos[0])this->hijos[0]->query_in_range(list_of_nodes, abajo_izquierda, arriba_derecha);
		if (this->hijos[1])this->hijos[1]->query_in_range(list_of_nodes, abajo_izquierda, arriba_derecha);
		if (this->hijos[2])this->hijos[2]->query_in_range(list_of_nodes, abajo_izquierda, arriba_derecha);
		if (this->hijos[3])this->hijos[3]->query_in_range(list_of_nodes, abajo_izquierda, arriba_derecha);
	}
}

void nodo::print_just_this()
{
	std::cout << data << " ";
}

void nodo::draw_just_this(int r, int g, int b)
{
	if (this->get_status() == 1) {
		createquad(float(this->abajo_izquierda.x), float(this->abajo_izquierda.y),
			float(this->arriba_derecha.x), float(this->arriba_derecha.y), r, g, b);
	}
	else {
		drawFilledelipse(float(this->coordenadas.x), float(this->coordenadas.y), r, g, b);
	}

}

bool nodo::is_dividible()
{
	if ((arriba_derecha.x - abajo_izquierda.x < 2) || (arriba_derecha.y - abajo_izquierda.y < 2))
		return false;
	return true;
}

void nodo::print_Nodo() {
	if (this->get_status() == 1) {
		createquad(float(this->abajo_izquierda.x), float(this->abajo_izquierda.y),
			float(this->arriba_derecha.x), float(this->arriba_derecha.y), 250, 0, 0);
	}
	else {
		if (this->get_is_select())
			drawFilledelipse(float(this->coordenadas.x), float(this->coordenadas.y), 0, 255, 0);
		else
			drawFilledelipse(float(this->coordenadas.x), float(this->coordenadas.y), 255, 0, 0);

	}
	if (this->hijos[0]) this->hijos[0]->print_Nodo();
	if (this->hijos[1]) this->hijos[1]->print_Nodo();
	if (this->hijos[2]) this->hijos[2]->print_Nodo();
	if (this->hijos[3]) this->hijos[3]->print_Nodo();
}

std::ostream& operator <<(std::ostream& o, const punto& p)
{
	return o << "(" << p.x << "," << p.y << ")" << std::endl;
}

