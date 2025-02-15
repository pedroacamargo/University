#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>


float dimensionAnimation = 0.0f;
void timer(int value) {
    dimensionAnimation += 0.1f;


    glutTimerFunc( 16, timer, 0 );
    glutPostRedisplay();
}

void renderScene(void) {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set the camera
    glLoadIdentity();
    gluLookAt(2.0f, 2.0f, 5.0f,
              0.0f, 0.0f, -1.0f,
              0.0f, 1.0f, 0.0f);

    // glBegin(GL_TRIANGLES);
    //     glVertex3f(-1.0f, -1.0f, 0.0f);
    //     glVertex3f(1.0f, -1.0f, 0.0f);
    //     glVertex3f(0.0f, 1.0f, 0.0f);
    // glEnd();

    // glutSolidCube(2);
    // glutWireCube(2.0f);
    glutWireTorus(cos(dimensionAnimation) * 2, 1.0f, 20, 20);

    glutSwapBuffers();
}

void changeSize(int w, int h) {
    // prevent a divide by zero, when window is too short
    // (you cant make a window of zero width).
    if (h == 0) h = 1;

    // windows aspect ration
    float ratio = w * 1.0 / h;

    glMatrixMode(GL_PROJECTION);

    // matriz identidade
    glLoadIdentity();

    // set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // set the correct perspective
    gluPerspective(45.0f, ratio, 1.0f, 1000.0f);

    // return to the model view matrix mode
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 600);

    glutCreateWindow("Aula 1");
    
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);

    glutTimerFunc( 0, timer, 0 );


    // glutIdleFunc(renderScene);



    glutMainLoop();

    return 0;
}