#include <orig.h>

#include <GL/glut.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include <cstdlib>
#include <cstdio>

static int windowID;
static int windowWidth, windowHeight;
static double angle = 0.0;
static double cameraHeight = 1.0;

void init()
{
    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
}

void doIdle()
{
    angle += 0.01;
    cameraHeight = 1.0;
    // Перерисовка
    glutPostRedisplay();
}

void reshape(int newWindowWidth, int newWindowHeight)
{
    glViewport(0,0,newWindowWidth,newWindowHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    windowWidth = newWindowWidth;
    windowHeight = newWindowHeight;
    double minZPlane = 0.01;
    double maxZPlane = 10.0;
    gluPerspective(45.0f, 1.0 * windowWidth / windowHeight, minZPlane, maxZPlane);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}

void KeyboardFunc (unsigned char key, int x, int y)
{
    switch (key)
    {
        //glutDestroyWindow(windowID);
        //exit(0);
        //break;

        default:
            break;

    }

}


void Display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    double cameraPosition[] = {cos(angle) * 2, cameraHeight * cos(angle / 3), sin(angle) * 2};
    double focusPosition[] = {0, 0, 0};
    double up[] = {0,1,0};
    gluLookAt( cameraPosition[0], cameraPosition[1], cameraPosition[2],
               focusPosition[0], focusPosition[1], focusPosition[2],
               up[0], up[1], up[2]);

    int verticalParts = 4;
    float verticalMultiplier = 2 * M_PI / verticalParts;
    int horisontalParts = 6;
    float horisontalMultiplier = 2 * M_PI / horisontalParts;

    float radius = .5;
    float partRadius = .125;

    glBegin(GL_QUADS);


    for (int i = 0; i < horisontalParts; i++) {
        float a1 = i * horisontalMultiplier;
        float a2 = (i + 1) * horisontalMultiplier;


        float cosa1 = cosf(a1 + angle * 2);
        float cosa2 = cosf(a2 + angle * 2);
        float sina1 = sinf(a1 + angle * 2);
        float sina2 = sinf(a2 + angle * 2);

        for (int j = 0; j < verticalParts; j++) {
            if (j % 2 == 0)
                if (i % 2 == 0)
                    glColor3f(0.8, 0, 0);
                else
                    glColor3f(0, 0, 1);
            else
            if (i % 2 == 0)
                glColor3f(1, 0.8, 0);
            else
                glColor3f(0, 0.8, 1);

            float b1 = j * verticalMultiplier;
            float b2 = (j + 1) * verticalMultiplier;

            float cosb1 = cos(b1);
            float cosb2 = cos(b2);
            float sinb1 = sin(b1);
            float sinb2 = sin(b2);

            glVertex3f(
                    cosa1 * cosb1 * partRadius - cosa1 * radius,
                    sina1 * cosb1 * partRadius - sina1 * radius,
                    sinb1 * partRadius
            );

            glVertex3f(
                    cosa2 * cosb1 * partRadius - cosa2 * radius,
                    sina2 * cosb1 * partRadius - sina2 * radius,
                    sinb1 * partRadius
            );

            glVertex3f(
                    cosa2 * cosb2 * partRadius - cosa2 * radius,
                    sina2 * cosb2 * partRadius - sina2 * radius,
                    sinb2 * partRadius
            );

            glVertex3f(
                    cosa1 * cosb2 * partRadius - cosa1 * radius,
                    sina1 * cosb2 * partRadius - sina1 * radius,
                    sinb2 * partRadius
            );

        }
    }

    glEnd();
    glutSwapBuffers();

}

void orig(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH);
    windowWidth = 400;
    windowHeight = 400;
    glutInitWindowSize (windowWidth,windowHeight);
    glutInitWindowPosition (0,0);
    char s[] = "Hello world";
    windowID = glutCreateWindow(s);
    glutDisplayFunc(Display);
    glutReshapeFunc(reshape);
    glutIdleFunc(doIdle);
    glutKeyboardFunc(KeyboardFunc);

    init();
    glutMainLoop();
}
