#pragma once
#include <GL/glut.h>

void createquad(float bot_left_x, float bot_left_y, float top_right_x, float top_right_y, int r, int g, int b) {

    // double w = glutGet(GLUT_WINDOW_WIDTH);
    // double h = glutGet(GLUT_WINDOW_HEIGHT);

    glColor3ub(r, g, b);
    glBegin(GL_LINE_LOOP);
    glVertex2f(bot_left_x, bot_left_y); //left_bot
    glVertex2f(bot_left_x, top_right_y); //left_top
    glVertex2f(top_right_x, top_right_y); //right_top
    glVertex2f(top_right_x, bot_left_y); //right_bot

    glEnd();
}

void drawFilledelipse(GLfloat x, GLfloat y, int r, int g, int b) {
    int i;
    int triangleAmount = 20; //# of triangles used to draw circle
    float PI = 3.1415;
    GLfloat radius = 7.0f;
    GLfloat twicePi = 2.0f * PI;
    glColor3ub(r, g, b);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // center of circle
    for (i = 0; i <= triangleAmount; i++) {
        glVertex2f(
            x + ((radius + 1) * cos(i * twicePi / triangleAmount)),
            y + ((radius - 1) * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
}