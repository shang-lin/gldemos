#ifndef _ROBOT_H_
#define _ROBOT_H_

// For Windows only.
#ifdef WIN32
#include <windows.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>
#include <assert.h>

/*
    This class represents a 3D robot with a head, a torso,
    and two legs.
*/
class Robot{

public:
    // Data members.
    GLfloat angle;       // This is the angle between the robot's
                         // legs and its torso when the robot walks.
    GLfloat csign;

    // These are the angles by which the robot is rotated about
    // the x and y axes.
    GLfloat xrot_angle;
    GLfloat yrot_angle;


    // These are the coordinates where the robot will be
    // drawn.
    GLfloat x_pos, y_pos, z_pos;

    void drawTorso();    // Draws the robot's upper body.
    void drawLegs();     // Draws the robot's legs.
    void drawHead();     // Draws the robot's head.
    void drawArms();
    void drawCube(double size);  // Draw a unit cube centered on the origin

public:
    void setup();        // Sets up the location where
                         // the robot is to be drawn.
public:
    Robot();
    Robot(GLfloat a,     // Constructor sets the angle and
          GLfloat x,     // the x, y, z starting coordinates.
          GLfloat y,
          GLfloat z);

    void draw();         // Draws the robot.

    // Increments angles of rotation.
    int incrementRotation(char axis, GLfloat incr);
};



#endif
