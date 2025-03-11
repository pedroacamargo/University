#include <stdio.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

float alfa = 0.0f, beta = 0.5f, radius = 100.0f;
float camX, camY, camZ;

#define TREE_COUNT 200
#define EXCLUSION_RADIUS 40.0f
typedef struct {
	float x, y, z;
} Tree;
std::vector<Tree> trees;


void drawTree(int x, int z) {

	// Tronco
	// glColor3f(0.5f, 0.35f, 0.05f);
	// glutSolidCube(200.0f);

	glPushMatrix();
		glColor3f(0.5f, 0.35f, 0.05f);
		glTranslatef(x, 0.0f, z);
		glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
		glutSolidCone(1.0, 5.0, 10, 10);
	glPopMatrix();
	
	// Folhas
	glPushMatrix();
		glColor3f(0.0f, 1.0f, 0.0f);
		glTranslatef(x, 3.0f, z);
		glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
		glutSolidCone(2.0, 7.0, 20, 20);
	glPopMatrix();
}

void spherical2Cartesian() {

	camX = radius * cos(beta) * sin(alfa);
	camY = radius * sin(beta);
	camZ = radius * cos(beta) * cos(alfa);
}


void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}



void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(camX, camY, camZ,
		0.0, 0.0, 0.0,
		0.0f, 1.0f, 0.0f);

	glBegin(GL_TRIANGLES);
		glColor3f(0.2f, 0.8f, 0.2f);
		glVertex3f(100.0f, 0, -100.0f);
		glVertex3f(-100.0f, 0, -100.0f);
		glVertex3f(-100.0f, 0, 100.0f);

		glVertex3f(100.0f, 0, -100.0f);
		glVertex3f(-100.0f, 0, 100.0f);
		glVertex3f(100.0f, 0, 100.0f);
	glEnd();
	
	for (int i = 0; i < TREE_COUNT; i++) {
		drawTree(trees[i].x, trees[i].z);
	}
	
	
	glutSwapBuffers();
}


void processKeys(unsigned char c, int xx, int yy) {

// put code to process regular keys in here

}


void processSpecialKeys(int key, int xx, int yy) {

	switch (key) {

	case GLUT_KEY_RIGHT:
		alfa -= 0.1; break;

	case GLUT_KEY_LEFT:
		alfa += 0.1; break;

	case GLUT_KEY_UP:
		beta += 0.1f;
		if (beta > 1.5f)
			beta = 1.5f;
		break;

	case GLUT_KEY_DOWN:
		beta -= 0.1f;
		if (beta < -1.5f)
			beta = -1.5f;
		break;

	case GLUT_KEY_F4: radius -= 1.0f;
		if (radius < 1.0f)
			radius = 1.0f;
		break;

	case GLUT_KEY_F3: radius += 1.0f; break;
	}
	spherical2Cartesian();
	glutPostRedisplay();

}


void printInfo() {

	printf("Vendor: %s\n", glGetString(GL_VENDOR));
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("Version: %s\n", glGetString(GL_VERSION));

	printf("\nUse Arrows to move the camera up/down and left/right\n");
	printf("Home and End control the distance from the camera to the origin");
}


int main(int argc, char **argv) {
	srand(time(NULL));

	for (int i = 0; i < TREE_COUNT; i++) {
		Tree t;
		do {
			t.x = rand() % 200 - 100;
			t.z = rand() % 200 - 100;
		} while (std::sqrt(t.x * t.x + t.z * t.z) < EXCLUSION_RADIUS); // Check if inside the circle		

		trees.push_back(t);
	}

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("CG@DI-UM");
		
// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	
// Callback registration for keyboard processing
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	spherical2Cartesian();

	printInfo();

// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
