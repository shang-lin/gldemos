/*
    shapes.cpp.

    This program renders a 3D robot in OpenGL.

*/

#ifdef WIN32
#include <windows.h>
#endif

#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

#include "robot.h"

void render();
void resize(GLsizei w, GLsizei h);
void initialize();
void handleKeystroke(int key, int x, int y);

// Global variables.
static Robot *robot;
static int xresol, yresol;


// Main function.
int main(int argc, char *argv[]){
    robot = new Robot();
    xresol = 500; yresol = 500;

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutCreateWindow("RoboViewer");


    initialize();

    // Set the OpenGL callback functions.
    // render() will be called whenever glutDisplayFunc is
    // needed, and resize(w, h) will be called whenever
    // glutReshapeFunc is needed. glutSpecialFunc is called whenever
    // a non-ASCII key is pressed.
    glutDisplayFunc(render);
    glutReshapeFunc(resize);
    glutIdleFunc(render);
    glutSpecialFunc(handleKeystroke);

    glutMainLoop();

    delete robot;
    return 0;
}

/*
    render().
    This function is called whenever the window is redrawn.
    All it does is draw a robot.
*/
void render(){
    resize(xresol, yresol);

    // Clear the window and draw the robot.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Set up the camera.
    gluLookAt(0.0, 0.0, 40.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    GLfloat light_pos[4] = {0.0f, 0.0f, 10.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);


    // Draw the robot

    robot->draw();

    // Clear the OpenGL pipeline and execute all waiting
    // commands.
    glFlush();
	glutSwapBuffers();
}


/*
    This function is called whenever the window is resized
    or maximized. The arguments are the width and height of
    the window.

    This function sets up the orthographic projection and the viewport.
*/
void resize(GLsizei w, GLsizei h){


    // Set the viewport to cover the entire window.
    glViewport(0, 0, w, h);

    // Prevent division by 0.
    if (h == 0)
        h = 1;

    // Reset the projection matrix to the identity matrix.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(85.0, (GLdouble)w / (GLdouble)h, 1.0, 150.0);

    // Reset the modelview matrix to the identity matrix.
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


}

/*
    initialize().
    This method initializes OpenGL's lighting and material
    settings.
*/
void initialize(){
    // Allow lighting and materials to have an effect.
    // By default, this is turned off. Once it is turned on,
    // lights and materials must be set for anything to appear.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);

    // Draw the front surfaces as filled polygons.
    glPolygonMode(GL_FRONT, GL_FILL);

    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Normalize normal vectors.
    glEnable(GL_NORMALIZE);


    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);  // Don't draw back (inner) surfaces.

    GLfloat ambient_light[] = {0.5f, 0.5f, 0.5f, 1.0f};
    GLfloat diffuse_light[] = {1.0f, 1.0f, 1.0f, 1.0f};

    // Initialize the light.
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);

}

/*
    handleKeystroke.
    This function is called when a non-ASCII key is pressed.
    Only the direction arrows are handled. The direction
    arrows indicate around which axis to rotate the robot.
*/
void handleKeystroke(int key, int x, int y){
    const GLfloat increment = 15.0f;
    if (key == GLUT_KEY_LEFT){
       robot->incrementRotation('y', -increment);
    }
    else if (key == GLUT_KEY_RIGHT){
        robot->incrementRotation('y', increment);
    }
    else if (key == GLUT_KEY_UP){
        robot->incrementRotation('x', increment);
    }
    else if (key == GLUT_KEY_DOWN){
        robot->incrementRotation('x', -increment);
    }

    glutPostRedisplay();
}



