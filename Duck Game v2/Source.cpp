#include <cstdlib>
#include "glut.h"
#include <cmath>
#include <ctime>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>


// ������ � Enter ���� � ������ ����
using namespace std;

// ������� ����
const int windowWidth = 800;
const int windowHeight = 600;

// ��������� ��� ������������� ����
struct Duck {
    float x, y;     // ������� ����
    float dx, dy;   // ����������� ��������
    bool alive;     // ��������� ���� (���� ��� ������)
};

vector<Duck> ducks;

int score = 0;
int ammo = 10;
const float maxSpeed = 0.1f; // ������������ �������� ����

clock_t startTime;  // ����� ������ ����
bool gameWon = false;
bool gameOver = false;
double elapsedTime = 0.0;
bool paused = false;

void drawText(const string& text, float x, float y) {
    glRasterPos2f(x, y);
    for (char c : text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}

void initDucks(int numDucks) {
    ducks.clear();
    for (int i = 0; i < numDucks; ++i) {
        Duck duck;
        duck.x = rand() % windowWidth;
        duck.y = rand() % windowHeight / 2 + windowHeight / 2;
        duck.dx = ((rand() % 2 == 0) ? 1 : -1) * (0.1f + static_cast<float>(rand()) / RAND_MAX * maxSpeed);
        duck.dy = ((rand() % 2 == 0) ? 1 : -1) * (0.1f + static_cast<float>(rand()) / RAND_MAX * maxSpeed);
        duck.alive = true;
        ducks.push_back(duck);
    }
}

// ������� ��� ���������� ��������� ����
void updateDucks() {
    if (gameWon || gameOver || paused) {
        return;
    }

    bool allDucksDead = true;
    for (auto& duck : ducks) {
        if (duck.alive) {
            allDucksDead = false;
            duck.x += duck.dx;
            duck.y += duck.dy;

            // �������� �� ������� ����
            if (duck.x < 0 || duck.x > windowWidth) {
                duck.dx = -duck.dx;
            }
            if (duck.y < windowHeight / 2 || duck.y > windowHeight) {
                duck.dy = -duck.dy;
            }
        }
    }

    if (allDucksDead) {
        gameWon = true;
        elapsedTime = static_cast<double>(clock() - startTime) / CLOCKS_PER_SEC;
    }

    glutPostRedisplay(); // ��������� ����
}


// ������� ��� ��������� �����
void drawCircle(float x, float y, float radius) {
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= 360; ++i) {
        float angle = i * 3.1415 / 180.0f;
        glVertex2f(x + cos(angle) * radius, y + sin(angle) * radius);
    }
    glEnd();
}

// ������� ��� ��������� ����
void drawDuck(float x, float y) {
    // ���� ��� ����
    glColor3f(1.0f, 1.0f, 0.0f); // ������

    // �������� ���� (�������������)
    glRectf(x - 20, y - 10, x + 17, y + 7);
    glRectf(x + 15, y + 5, x + 25, y + 15);
    glRectf(x - 5, y + 3, x + 3, y + 27);
    glColor3f(0.0f, 0.0f, 0.0f);
    glRectf(x - 7, y + 1, x + 3, y + 3);
    glRectf(x - 7, y + 1, x - 5, y + 7);
    glRectf(x + 13, y + 3, x + 17, y + 5);
    glRectf(x + 22, y + 12, x + 24, y + 14);

    // ������� ��� ����� (�����)
    glColor3f(1.0f, 1.0f, 1.0f); // �����
    glRectf(x + 20, y + 10, x + 24, y + 14);

    glColor3f(0.0f, 0.0f, 0.0f);
    glRectf(x + 22, y + 12, x + 24, y + 14);
    glColor3f(1.0f, 0.5f, 0.0f); // ���������
    glRectf(x + 25, y + 8, x + 35, y + 13);
    glRectf(x - 5, y - 10, x, y - 20);
}

// ������� ��� ��������� ���� ����
void drawDucks() {
    for (const auto& duck : ducks) {
        if (duck.alive) {
            drawDuck(duck.x, duck.y);
        }
    }
}

// ������� ��� ��������� ������ ����
// ������� ��� ��������� ������ ����
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (ammo > 0 && !gameWon && !gameOver) {
            ammo--; // ��������� ���������� ��������
            y = windowHeight - y; // �������������� ���������� y
            for (auto& duck : ducks) {
                if (duck.alive && abs(duck.x - x) < 20 && abs(duck.y - y) < 10) {
                    duck.alive = false;
                    score++;
                }
            }
            // ��������, ��� �� ���� ������
            bool allDucksDead = true;
            for (const auto& duck : ducks) {
                if (duck.alive) {
                    allDucksDead = false;
                    break;
                }
            }
            if (allDucksDead) {
                gameWon = true;
                elapsedTime = static_cast<double>(clock() - startTime) / CLOCKS_PER_SEC;
            }
            // ������� ��� ���������� ����
            if (ammo == 0 && !gameWon) {
                gameOver = true;
            }
            glutPostRedisplay(); // ��������� ���� ��� ����������� ���������
        }
    }
}




// ������� ��� ��������� �����
void drawGround() {
    glColor3f(0.4f, 0.4f, 0.0f); // ���������� ���� ��� �����
    glRectf(0, 0, windowWidth, 100);

    srand(std::time(nullptr));
    int min_val = 100;
    int max_val = 130;

    glColor3f(0.3f, 0.8f, 0.3f); // ������� ���� ��� �����
    for (float x = 0; x < windowWidth; x += 5) {
        float random_y = min_val + std::rand() % (max_val - min_val + 1);
        glRectf(x, 70, x + 5, random_y);
    }
}

// ������� ��� ��������� ������
void drawTree() {
    float x = 100;
    // ����� ������
    glColor3f(0.4f, 0.2f, 0.0f); // ���������� ����
    glRectf(x - 10, 100, x + 10, 300);
    glRectf(x + 10, 210, x + 60, 225);
    glRectf(x - 10, 250, x - 50, 265);

    // ���� ������
    glColor3f(0.4f, 0.05f, 0.0f);
    glRectf(x - 10, 100, x - 3, 250);
    glRectf(x - 10, 265, x - 3, 300);
    glRectf(x + 10, 210, x + 60, 217);
    glRectf(x - 3, 250, x - 50, 257);

    // ������ ������
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

    // ������ ������
    x = 600;
    glColor3f(0.3f, 0.6f, 0.3f);
    drawCircle(x, 100, 50);
    drawCircle(x + 5, 160, 30);
    glColor3f(0.3f, 0.8f, 0.3f);
    drawCircle(x + 8, 163, 28);
    drawCircle(x + 8, 103, 48);
}

// ������� ��� ��������� ������
void drawDog(float x, float y) {
    // ����
    glColor3f(0.6f, 0.35f, 0.2f); // ���������� ����
    glRectf(x - 20, y - 15, x + 20, y + 30);

    // ������
    glRectf(x - 10, y + 30, x + 10, y + 50);

    // ���
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

    // �������
    glColor3f(0.0f, 0.0f, 0.0f);
    glRectf(x - 10, y + 40, x - 18, y + 42);
    glRectf(x + 10, y + 40, x + 18, y + 42);
    glRectf(x - 10, y + 30, x + 10, y + 32);
    glRectf(x - 20, y - 15, x - 18, y + 30);
    glRectf(x - 20, y + 28, x - 8, y + 30);
    // �����
    glColor3f(1.0f, 1.0f, 1.0f); // ����� ����
    glRectf(x - 7, y + 40, x - 3, y + 44);
    glRectf(x + 3, y + 40, x + 7, y + 44);
    glColor3f(0.0f, 0.0f, 0.0f);
    glRectf(x - 4, y + 41, x - 6, y + 43);
    glRectf(x + 4, y + 41, x + 6, y + 43);

    // ���
    glColor3f(0.0f, 0.0f, 0.0f); // ������ ����
    glRectf(x - 3, y + 34, x + 3, y + 38);

    // ������ (�������������)
    glColor3f(0.5f, 0.5f, 0.5f); // ����� ����
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

// ������� ��� ���������
// ������� ��� ���������
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // ��������� ��������
    drawTree();

    // ��������� ������
    drawDog(200, 110);

    // ��������� ����� � �����
    drawGround();

    // ��������� ����
    drawDucks();

    // ����������� ����� � ���������� ��������
    glColor3f(1.0f, 1.0f, 1.0f); // ����� ����
    drawText("Score: " + to_string(score), 50, 50);
    drawText("Ammo: " + to_string(ammo), 700, 50);

    // �������� �� ��������
    if (gameOver && !gameWon) {
        drawText("Game Over", windowWidth / 2 - 50, windowHeight / 2);
        cout << "Game Over" << endl; // ������� ���������� �����
    }

    // �������� �� �������
    if (gameWon) {
        drawText("You Win!", windowWidth / 2 - 50, windowHeight / 2);
        drawText("Time: " + to_string(elapsedTime) + " sec", windowWidth / 2 - 50, windowHeight / 2 - 30);
    }

    // �������� �� �����
    if (paused) {
        drawText("Paused", windowWidth / 2 - 30, windowHeight / 2);
    }

    glFlush();
}



// ������������� OpenGL
void init() {
    glClearColor(0.5f, 0.8f, 0.92f, 1.0f); // ���� ���� (������� ����)
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, windowWidth, 0.0, windowHeight);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case ' ': // ����� �� ������
        paused = !paused;
        if (paused) {
            glutIdleFunc(nullptr); // ���������������� ���������� ����
        }
        else {
            glutIdleFunc(updateDucks); // ������������ ���������� ����
        }
        break;
    case 13: // ������������� ���� �� Enter
        paused = false;
        if (!gameWon && !gameOver) {
            glutIdleFunc(updateDucks); // ������������ ���������� ����
        }
        break;
    }
}

int main(int argc, char** argv) {
    srand(static_cast<unsigned int>(time(0)));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Duck Hunt");

    init();
    initDucks(5); // ������������� 5 ����
    startTime = clock(); // ������ �������

    glutDisplayFunc(display);
    glutIdleFunc(updateDucks);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard); // ��������� ��������� ����������

    glutMainLoop();
    return 0;
}
