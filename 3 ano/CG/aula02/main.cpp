#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>
#include <iostream>

typedef struct {
	float radius;  // Distance from the center
	float theta;   // Horizontal angle (left/right)
	float phi;    // Vertical angle (up/down)
} OrbitalCamera;
OrbitalCamera orbitalCamera = {5.0f, 5.0f, 5.0f};

typedef struct {
	float x;
	float y;
	float z;
} Translation;
Translation translation = {0.0f, 0.0f, 0.0f};

float rotationAngle = 0.0f;




GLenum cullFace = GL_BACK;

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

	gluLookAt(
			// Convert spherical coordinates to Cartesian coordinates
			orbitalCamera.radius * cos(orbitalCamera.theta) * sin(orbitalCamera.phi),
			orbitalCamera.radius * cos(orbitalCamera.phi),
			orbitalCamera.radius * sin(orbitalCamera.theta) * sin(orbitalCamera.phi),

			0.0, 0.0, 0.0,
			  
			0.0f, 1.0f, 0.0f
		);


	glBegin(GL_LINES);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(10.0f, 0.0f, 0.0f);

		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 10.0f, 0.0f);

		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 10.0f);
	glEnd();


	glPushMatrix();
	// put the geometric transformations here
	glTranslatef(translation.x, translation.y, translation.z);
	glRotatef(rotationAngle, 0.0f, 1.0f, 1.0f);
	glScalef(1.0f, 1.0f, 1.0f);

	glBegin(GL_TRIANGLES);

// put pyramid drawing instructions here
		
		// 🔺 Front Face
		glColor3f(1.0f, 0.0f, 0.0f); // Red
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);

		// // 🔺 Right Face
		glColor3f(0.0f, 1.0f, 0.0f); // Green
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);

		// 🔺 Back Face
		glColor3f(0.0f, 0.0f, 1.0f); // Blue
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);

		// 🔺 Left Face
		glColor3f(1.0f, 1.0f, 0.0f); // Yellow
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);

	glEnd();

	glBegin(GL_QUADS);
		glColor3f(0.5f, 0.5f, 0.5f); // Gray
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
	glEnd();

	glPopMatrix();

	glutPostRedisplay();

	// End of frame
	glutSwapBuffers();
}



// write function to process keyboard events
void processKeys(unsigned char c, int xx, int yy) {
	std::cout << c << std::endl;

	if (c == 'W' || c == 'w') {
		translation.z += 0.1f;
	} else if (c == 'S' || c == 's') {
		translation.z -= 0.1f;
	} else if (c == 'A' || c == 'a') {
		translation.x -= 0.1f;
	} else if (c == 'D' || c == 'd') {
		translation.x += 0.1f;
	} else if (c == 'R' || c == 'r') {
		rotationAngle += 5.0f;
	} else if (c == 'T' || c == 't') {
		rotationAngle -= 5.0f;
	} 


	if (c == 'Q' || c == 'q') {
		glutDestroyWindow(glutGetWindow());
		exit(0);
	}

	if (c == 'C' || c == 'c') {
		if (cullFace == GL_FRONT) {
			cullFace = GL_BACK;
		} else {
			cullFace = GL_FRONT;
		}

		glCullFace(cullFace);
		glutPostRedisplay();
	}
}

void processSpecialKeys(int key, int xx, int yy) {
	std::cout << key << std::endl;

	switch (key) {
		case GLUT_KEY_UP:
			orbitalCamera.phi += 0.1f;
			break;
		case GLUT_KEY_DOWN:
			orbitalCamera.phi -= 0.1f;
			break;
		case GLUT_KEY_LEFT:
			orbitalCamera.theta += 0.1f;
			break;
		case GLUT_KEY_RIGHT:
			orbitalCamera.theta -= 0.1f;
			break;
	}

	glutPostRedisplay();

	std::cout << "Camera Orientation: " << orbitalCamera.radius << " " << orbitalCamera.theta << " " << orbitalCamera.phi << std::endl;
}





int main(int argc, char **argv) {

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("CG@DI-UM");
		
// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);

	
// put here the registration of the keyboard callbacks
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);


//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	// glEnable(GL_CULL_FACE);
	// glCullFace(cullFace);
	// glFrontFace(GL_CCW);
	// glPolygonMode(GL_BACK, GL_POINT);

// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
