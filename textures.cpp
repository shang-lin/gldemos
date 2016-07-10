/*
    textures.cpp.

    This program renders a 3D robot in OpenGL and adds textures to it.

*/

#ifdef WIN32
#include <windows.h>
#endif

#include <GL/glut.h>
#include <assert.h>

#include "robot.h"
#include "scenery.h"

void render();
void resize(GLsizei w, GLsizei h);
void initialize();
void handleKeystroke(int key, int x, int y);



// Global variables.
static Robot *robot;
static Scene *background;

int xresol, yresol;


// Main function.
int main(int argc, char *argv[]){
    robot = new Robot();
    background = new Scene();

    xresol = 500; yresol = 500;
    robot->toggle = 0;

    // Set the display mode.
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInit(&argc, argv);

    // Create a 500 x 500 window.
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
    delete background;

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
    gluLookAt(0.0, 10.0, 40.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    GLfloat light_pos[4] = {0.0f, 0.0f, 10.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

    // assert(background != NULL);
    // Draw the background.
    background->draw();

    // assert(robot != NULL);
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
    if (w == 0)
        w = 1;

    // Reset the projection matrix to the identity matrix.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    GLdouble aspect = (GLdouble)w / (GLdouble)h;
    gluPerspective(85.0, aspect, 1.0, 500.0);

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
    glPolygonMode(GL_FRONT, GL_FILL);

    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);

    // Turn on color tracking. This allows material properties
    // to be set using glColor.
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    //glFrontFace(GL_CCW);	  // counterclockwise polygons are out

    //Texture related commands.
    glGenTextures(5, robot->texture_objects);


    robot->makeCheckImage();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(1, &robot->texName);
    glBindTexture(GL_TEXTURE_2D, robot->texName);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, checkImageWidth, 
                 checkImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 robot->checkImage);

    GLfloat ambient_light[] = {0.5f, 0.5f, 0.5f, 1.0f};
    GLfloat diffuse_light[] = {1.0f, 1.0f, 1.0f, 1.0f};

    //glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_light);
    //glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
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
    else if (key == GLUT_KEY_F1){
        robot->toggle++;
        robot->toggle = robot->toggle % 3;
        robot->makeCheckImage();
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, checkImageWidth,
                     checkImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                     robot->checkImage);
    }


    glutPostRedisplay();
}



