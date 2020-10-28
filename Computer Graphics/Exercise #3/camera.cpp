#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// Handling of the keypress event.
void handleKeypress(unsigned char key, //The key that was pressed
                    int x, int y) {    //The current mouse coordinates
    switch (key) {
        case 27: //Escape key
            exit(0); //Exit the program
    }
}

// Initialization function of the scene.
// Ignore this function for a while.
void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat lmodel_ambient[] = { 0.8, 0.0, 0.0, 0.0 };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
}

// Handling a reshape request for the window.
// Ignore this function for a while.
void reshape(int w, int h) {
    float ratio = (float)w/ (float)h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, ratio, 1.0, 425.0);
}

// This function is for drawing the main scene.
void draw() {
    // Initial setup of the scene.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Where will the camera point to.
    gluLookAt(
        300.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    );
    // Set the colour of the object.
    glColor3f(1.0, 0.0, 0.0);

    // Drawing the cube.
    glutSolidCube(100.0);

    // Whatever you've drawn, now it will become visible.
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    // Basic initialization.
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    // Setting the window properties.
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Camera Application");

    // Main functionalities of the executable.
    glutKeyboardFunc(handleKeypress);
    glutReshapeFunc(reshape);
    glutDisplayFunc(draw);

    // Initialization of the scene.
    init();

    // Going to main loop;
    glutMainLoop();

    return 0;
} 