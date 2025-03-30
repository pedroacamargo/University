

#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>

#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>

#include <IL/il.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

GLuint vertices, verticesCount;
unsigned int t, tw, th;
unsigned char *imageData;
GLuint colorBuffer;
std::vector<float> colors;  // Store colors as a flat array (RGB)



float camX = 00, camY = 30, camZ = 40;
int startX, startY, tracking = 0;

int alpha = 0, beta = 45, r = 50;

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set the correct perspective
	gluPerspective(45,ratio,1,1000);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}



void drawTerrain() {

    // colocar aqui o código de desnho do terreno usando VBOs com TRIANGLE_STRIPS
	// glBegin(GL_TRIANGLE_STRIP);

	
	
	glBindBuffer(GL_ARRAY_BUFFER, vertices);
	glVertexPointer(3, GL_FLOAT, 0, 0);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	for (int i = 0; i < tw - 1; i++) {
		glDrawArrays(GL_TRIANGLE_STRIP, i * th * 2, th * 2);
	}

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	
	// glEnd();
}



void renderScene(void) {

	float pos[4] = {-1.0, 1.0, 1.0, 0.0};

	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(camX, camY, camZ, 
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);

	drawTerrain();

	// just so that it renders something before the terrain is built
	// to erase when the terrain is ready
	// glutWireTeapot(2.0);
	// DRAW STRIPS

// End of frame
	glutSwapBuffers();
}



void processKeys(unsigned char key, int xx, int yy) {

// put code to process regular keys in here
}



void processMouseButtons(int button, int state, int xx, int yy) {
	
	if (state == GLUT_DOWN)  {
		startX = xx;
		startY = yy;
		if (button == GLUT_LEFT_BUTTON)
			tracking = 1;
		else if (button == GLUT_RIGHT_BUTTON)
			tracking = 2;
		else
			tracking = 0;
	}
	else if (state == GLUT_UP) {
		if (tracking == 1) {
			alpha += (xx - startX);
			beta += (yy - startY);
		}
		else if (tracking == 2) {
			
			r -= yy - startY;
			if (r < 3)
				r = 3.0;
		}
		tracking = 0;
	}
}


void processMouseMotion(int xx, int yy) {

	int deltaX, deltaY;
	int alphaAux, betaAux;
	int rAux;

	if (!tracking)
		return;

	deltaX = xx - startX;
	deltaY = yy - startY;

	if (tracking == 1) {


		alphaAux = alpha + deltaX;
		betaAux = beta + deltaY;

		if (betaAux > 85.0)
			betaAux = 85.0;
		else if (betaAux < -85.0)
			betaAux = -85.0;

		rAux = r;
	}
	else if (tracking == 2) {

		alphaAux = alpha;
		betaAux = beta;
		rAux = r - deltaY;
		if (rAux < 3)
			rAux = 3;
	}
	camX = rAux * sin(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
	camZ = rAux * cos(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
	camY = rAux * 							     sin(betaAux * 3.14 / 180.0);
}


void init() {

// 	Load the height map "terreno.jpg"
	ilInit();

	ilGenImages(1, &t); // generate a texture id
	ilBindImage(t); // bind the texture id

	ilLoadImage((ILstring)"terreno.jpg"); // load the image
	ilConvertImage(IL_LUMINANCE, IL_UNSIGNED_BYTE); // convert to RGBA format

	tw = ilGetInteger(IL_IMAGE_WIDTH); // get the width of the image
	th = ilGetInteger(IL_IMAGE_HEIGHT); // get the height of the image

	imageData = ilGetData(); // get the image data


	 // colocar aqui o código de desnho do terreno usando VBOs com TRIANGLE_STRIPS
	// criar um vector com as coordenadas dos pontos
	std::vector<float> p;

	for (int i = 0; i < tw; i++) {
        for (int j = 0; j < th; j++) {
        	p.push_back(i - tw * 0.5 + 1);
        	p.push_back(imageData[i * tw + j + 1]);
        	p.push_back(j - th * 0.5);

        	p.push_back(i - tw * 0.5);
        	p.push_back(imageData[i * tw + j]);
        	p.push_back(j - th * 0.5);
        }
    }

	glGenBuffers(1, &vertices);
	glBindBuffer(GL_ARRAY_BUFFER, vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * p.size(), p.data(), GL_STATIC_DRAW);
	glEnableClientState(GL_VERTEX_ARRAY);

	for (int i = 0; i < tw; i++) {
		for (int j = 0; j < th; j++) {
			float height = imageData[i * tw + j] / 255.0f * 7;
			float brightness = 0.4f + height;  // Inverted for darker higher areas

			std::cout << "Height: " << height << ", Brightness: " << brightness << std::endl;

			colors.push_back(brightness); // R
			colors.push_back(brightness * 0.5f); // G
			colors.push_back(brightness); // B

			float height2 = imageData[i * tw + j + 1] / 255.0f * 7;
			float brightness2 = 0.2f + height2;  // Inverted for darker higher areas

			colors.push_back(brightness2); // R
			colors.push_back(brightness2 * 0.5f); // G
			colors.push_back(brightness2); // G

		}
	}

	glGenBuffers(1, &colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(float), colors.data(), GL_STATIC_DRAW);
	glEnableClientState(GL_COLOR_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glColorPointer(3, GL_FLOAT, 0, 0);

	



// 	OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


}


int main(int argc, char **argv) {

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(320,320);
	glutCreateWindow("CG@DI-UM");
		
// Required callback registry 
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);

// Callback registration for keyboard processing
	glutKeyboardFunc(processKeys);
	glutMouseFunc(processMouseButtons);
	glutMotionFunc(processMouseMotion);

	glewInit();
	init();	

// enter GLUT's main cycle
	glutMainLoop();
	
	return 0;
}

