#include <GL/glut.h>
#include <iostream>
#include "quadtree.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#define width_screen 1000
#define height_screen 1000

quadtree A(punto(0, 0), punto(width_screen, height_screen));

void displayMe(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double w = glutGet(GLUT_WINDOW_WIDTH);
    double h = glutGet(GLUT_WINDOW_HEIGHT);
    glOrtho(0, w, 0, h, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // importante
    glTranslatef(0.5, 0.5, 0);

    A.print();

    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    //insertar 100 nodos aleatoriamente
    srand(time(NULL));
    for (int i = 0; i < 1000; i++) {
        A.insertar(rand() % 1000 + 1, rand() % 1000 + 1, rand() % 1000 + 1);
    }
    //consulta de rango
    A.consulta_rango(punto(250, 250), punto(750, 750));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(width_screen+5, height_screen+5);
    glutInitWindowPosition(100, 100);

    glutCreateWindow("QuadTree");
    glutDisplayFunc(displayMe);
    glutMainLoop();
    return 0;
}