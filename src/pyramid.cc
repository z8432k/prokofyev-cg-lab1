#include <pyramid.h>
#include <iostream>

#include <GL/glut.h>
#define _USE_MATH_DEFINES
#include <cmath>

using namespace std;

static double angle = .0;

static void idle_cb() {

    angle += 0.0001;
    glutPostRedisplay();
}

static void render_shape() {
    glBegin(GL_TRIANGLES);

    glColor3f(1,0,0);
    glVertex3f(-5,-5,5);
    glVertex3f(0,5,0);
    glVertex3f(5,-5,5);

    glColor3f(0,1,0);
    glVertex3f(5,-5,5);
    glVertex3f(0,5,0);
    glVertex3f(5,-5,-5);

    glColor3f(0,0,1);
    glVertex3f(5,-5,-5);
    glVertex3f(0,5,0);
    glVertex3f(-5,-5,-5);

    glEnd();

    glBegin(GL_QUADS);

    glColor3f(1, 1, 0);
    glVertex3f(-5, -5, 5);
    glVertex3f(5, -5, 5);
    glVertex3f(5, -5, -5);
    glVertex3f(-5, -5, -5);

    glEnd();
}

static void render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    double cameraPos[] = {cos(angle) * 45, 15, sin(angle) * 45};
    double focusPos[] = {0, 0, 0};
    double up[] = {0,1,0};

    gluLookAt( cameraPos[0], cameraPos[1], cameraPos[2],
               focusPos[0], focusPos[1], focusPos[2],
               up[0], up[1], up[2]);

    render_shape();

    glutSwapBuffers();
}

static void reshape(int newWidth, int newHeight) {
    glViewport(0, 0, newWidth, newHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    double minZPlane = 0.01;
    double maxZPlane = 100.0;
    gluPerspective(45.0f, 1.0 * newWidth / newHeight, minZPlane, maxZPlane);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void pyramid(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH);

    glutInitWindowSize (800, 600);
    glutInitWindowPosition (0,0);

    int windowID = glutCreateWindow("Computer graphic. Lab 1.");

    glutDisplayFunc(render);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle_cb);

    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);

    glutMainLoop();
}
