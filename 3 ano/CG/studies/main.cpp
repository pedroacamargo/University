#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>

float alpha = 45.0f, radius = 3.0f;

void drawHouse() {
    glTranslatef(-0.5,-0.5,0);
    glBegin(GL_QUADS);
        glColor3f(1,1,1);
        glVertex3f(0,0,0);
        glVertex3f(0,1,0);
        glVertex3f(1,1,0);
        glVertex3f(1,0,0);
    glEnd();

    glBegin(GL_TRIANGLES);
        glColor3f(1,0,0);
        glVertex3f(0,1,0);
        glVertex3f(0.5,1.5,0);
        glVertex3f(1,1,0);
    glEnd();
}

void renderScene(void) {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set the camera
    glLoadIdentity();
    gluLookAt(3.0f, 3.0f, 10.0f,
              3.0f, 3.0f, 0.0f,
              0.0f, 1.0f, 0.0f);

    glPushMatrix();
    glBegin(GL_LINES);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(5.0f, 0.0f, 0.0f);

        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 5.0f, 0.0f);
    glEnd();
    glPopMatrix();



    glPushMatrix();
        // glTranslatef(radius * cos(alpha),radius * sin(alpha),0);
        // glRotatef(alpha, 0, 0, 1);
        glRotatef(alpha, 0, 0, 1);
        glTranslatef(radius,0,0);
        drawHouse();

    glPopMatrix();


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

    glutCreateWindow("My Tests");
    
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);

    // glutIdleFunc(renderScene);



    glutMainLoop();

    return 0;
}