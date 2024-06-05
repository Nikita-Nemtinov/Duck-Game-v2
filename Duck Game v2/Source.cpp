#include <cstdlib>
#include "glut.h"
#include <cmath>
#include <ctime>

using namespace std;
// Размеры окна
const int windowWidth = 800;
const int windowHeight = 600;

// Функция для отрисовки круга
void drawCircle(float x, float y, float radius) {
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= 360; ++i) {
        float angle = i * 3.1415 / 180.0f;
        glVertex2f(x + cos(angle) * radius, y + sin(angle) * radius);
    }
    glEnd();
}
// Функция для отрисовки утки
void drawDuck(float x, float y) {
    // Цвет для тела
    glColor3f(1.0f, 1.0f, 0.0f); // Желтый

    // Основное тело (прямоугольник)
    glRectf(x - 20, y - 10, x + 17, y + 7);
    glRectf(x + 15, y + 5, x + 25, y + 15);
    glRectf(x - 5, y + 3, x + 3, y + 27);
    glColor3f(0.0f, 0.0f, 0.0f);
    glRectf(x - 7, y + 1, x + 3, y + 3);
    glRectf(x - 7, y + 1, x - 5, y + 7);
    glRectf(x + 13, y + 3, x + 17, y + 5);
    glRectf(x + 22, y + 12, x + 24, y + 14);

    // Квадрат для глаза (белый)
    glColor3f(1.0f, 1.0f, 1.0f); // Белый
    glRectf(x + 20, y + 10, x + 24, y + 14);

    glColor3f(0.0f, 0.0f, 0.0f);
    glRectf(x + 22, y + 12, x + 24, y + 14);
    glColor3f(1.0f, 0.5f, 0.0f); // Оранжевый
    glRectf(x + 25, y + 8, x + 35, y + 13);
    glRectf(x - 5, y - 10, x, y - 20);

}

// Функция для отрисовки земли
void drawGround() {
    glColor3f(0.4f, 0.4f, 0.0f); // Коричневый цвет для земли
    glRectf(0, 0, windowWidth, 100);

    srand(std::time(nullptr));
    int min_val = 100;
    int max_val = 130;

    glColor3f(0.3f, 0.8f, 0.3f); // Зеленый цвет для травы
    for (float x = 0; x < windowWidth; x += 5) {
        float random_y = min_val + std::rand() % (max_val - min_val + 1);
        glRectf(x, 70, x + 5, random_y);
    }


}

// Функция для отрисовки дерева
void drawTree() {
    float x = 100;
    // Ствол дерева
    glColor3f(0.4f, 0.2f, 0.0f); // Коричневый цвет
    glRectf(x - 10, 100, x + 10, 300);
    glRectf(x + 10, 210, x + 60, 225);
    glRectf(x - 10, 250, x - 50, 265);

    // Тень дерева
    glColor3f(0.4f, 0.05f, 0.0f);
    glRectf(x - 10, 100, x - 3, 250);
    glRectf(x - 10, 265, x - 3, 300);
    glRectf(x + 10, 210, x + 60, 217);
    glRectf(x - 3, 250, x - 50, 257);

    // Листва крутая
    glColor3f(0.3f, 0.6f, 0.3f);
    drawCircle(x + 60, 220, 20);
    drawCircle(x - 50, 260, 18);
    drawCircle(x + 25, 305, 25);
    drawCircle(x - 25, 305, 25);
    glColor3f(0.3f, 0.8f, 0.3f);
    drawCircle(x + 60, 225, 20);
    drawCircle(x - 50, 265, 18);
    drawCircle(x, 325, 25);
    drawCircle(x - 25, 310, 25);
    drawCircle(x + 25, 310, 25);

    //Второе дерево
    x = 600;
    glColor3f(0.3f, 0.6f, 0.3f);
    drawCircle(x, 100, 50);
    drawCircle(x + 5, 160, 30);
    glColor3f(0.3f, 0.8f, 0.3f);
    drawCircle(x + 8, 163, 28);
    drawCircle(x + 8, 103, 48);
}

// Функция для отрисовки собаки
void drawDog(float x, float y) {
    // Тело
    glColor3f(0.6f, 0.35f, 0.2f); // Коричневый цвет
    glRectf(x - 20, y - 15, x + 20, y + 30);

    // Голова
    glRectf(x - 10, y + 30, x + 10, y + 50);

    // Уши
    glBegin(GL_TRIANGLES);
    glVertex2f(x - 10, y + 50);
    glVertex2f(x - 20, y + 40);
    glVertex2f(x, y + 40);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(x + 10, y + 50);
    glVertex2f(x + 20, y + 40);
    glVertex2f(x, y + 40);
    glEnd();

    // Обводка
    glColor3f(0.0f, 0.0f, 0.0f);
    glRectf(x - 10, y + 40, x - 18, y + 42);
    glRectf(x + 10, y + 40, x + 18, y + 42);
    glRectf(x - 10, y + 30, x + 10, y + 32);
    glRectf(x - 20, y - 15, x - 18, y + 30);
    glRectf(x - 20, y + 28, x - 8, y + 30);
    // Глаза
    glColor3f(1.0f, 1.0f, 1.0f); // Белый цвет
    glRectf(x - 7, y + 40, x - 3, y + 44);
    glRectf(x + 3, y + 40, x + 7, y + 44);
    glColor3f(0.0f, 0.0f, 0.0f);
    glRectf(x - 4, y + 41, x - 6, y + 43);
    glRectf(x + 4, y + 41, x + 6, y + 43);

    // Нос
    glColor3f(0.0f, 0.0f, 0.0f); // Черный цвет
    glRectf(x - 3, y + 34, x + 3, y + 38);

    // Оружие (прямоугольник)
    glColor3f(0.5f, 0.5f, 0.5f); // Серый цвет
    glRectf(x + 10, y + 20, x + 50, y + 26);
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(x - 4, y + 11);
    glVertex2f(x - 4, y + 21);
    glVertex2f(x + 10, y + 21);
    glEnd();
    glRectf(x + 10, y + 20, x + 50, y + 22);
    glRectf(x + 10, y + 20, x + 12, y + 26);
    glRectf(x + 10, y + 24, x + 50, y + 26);
    glRectf(x + 48, y + 20, x + 50, y + 26);
    glRectf(x + 46, y + 26, x + 43, y + 28);
}


// Функция для отрисовки
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Отрисовка деревьев
    drawTree();

    // Отрисовка собаки
    drawDog(200, 110);

    // Отрисовка земли и травы
    drawGround();



    // Отрисовка утки
    drawDuck(400, 300);



    glFlush();
}



// Инициализация OpenGL
void init() {
    glClearColor(0.5f, 0.8f, 0.92f, 1.0f); // Цвет фона (голубое небо)
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, windowWidth, 0, windowHeight);
}

// Основная функция
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);

    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Duck Hunt");


    glutDisplayFunc(display);
    init();
    glutMainLoop();
    return 0;
}
