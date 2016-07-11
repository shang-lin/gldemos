#include <stdio.h>
#include <GL/glut.h>
#include <iostream>

#include "robot.h"
using namespace std;

/*
    Constructor.
    This initializes all the data members to 0 and the
    rotation axis to the y-axis.
*/
Robot::Robot(){
    angle = 0.0f;
    x_pos = 0.0f;
    y_pos = 0.0f;
    z_pos = 0.0f;

    xrot_angle = 0.0f;
    yrot_angle = 0.0f;

}

/*
    Constructor.
    The angle between the torso and each leg, the
    starting positions, and the angle of rotation
    are initialized.
*/
Robot::Robot(GLfloat a=0.0f, GLfloat x=0.0f, GLfloat y=0.0f,
             GLfloat z=0.0f){
    // Make sure that the angle is non-negative.
    assert(a >= 0.0f);

    // Set the angle and the coordinates.
    angle = a;
    x_pos = x;
    y_pos = y;
    z_pos = z;
    xrot_angle = 0.0f;
    yrot_angle = 0.0f;
}


/*
    Robot::drawTorso().
    This method draws the robot's torso as a green
    3x5x2 cube.
*/
void Robot::drawTorso(){
    glPushMatrix();
    glNormal3f(1.0f, 0.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glScalef(3.0f, 5.0f, 2.0f);
    glutSolidCube(20.0f);
    glPopMatrix();
}

/*
    Robot::drawHead().
    This method draws the robot's head as a red 2x2x2
    cube.
*/
void Robot::drawHead(){
    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, 70.0f, 0.0f);
    glScalef(2.0f, 2.0f, 2.0f);
    glutSolidCube(20.0f);
    glPopMatrix();
}

/*
    Robot::drawLegs().
    This method draws the robot's legs. Each leg is a
    blue 1x5x1 cube.
*/
void Robot::drawLegs(){
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 1.0f);
    glScalef(1.0f, 5.0f, 1.0f);

    // Draw first leg.
    glTranslatef(-20.0f, -20.0f, 0.0f);
    glutSolidCube(20.0f);

    // Draw second leg relative to first.
    glTranslatef(40.0f, 0.0f, 0.0f);
    glutSolidCube(20.0f);

    glPopMatrix();
}

/*
    Robot::draw().
    This method draws the entire robot by calling each of the
    methods to draw each part of the robot.
*/
void Robot::draw(){

    // Set up the robot in the correct orientation.
    setup();

    // Draw all parts of the robot.
    drawTorso();
    drawHead();
    drawLegs();
}

/*
    Robot::setup().

    This method performs the initial transformations to draw the
    robot in the correct location and orientation.
*/
void Robot::setup(){
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(x_pos, y_pos, z_pos);
    glRotatef(xrot_angle, 1.0f, 0.0f, 0.0f);
    glRotatef(yrot_angle, 0.0f, 1.0f, 0.0f);
}

/*
    Robot::incrementRotation.

    This method increments the angles of rotation around the x-axis
    and the y-axis.

*/
int Robot::incrementRotation(char axis, GLfloat increment){
    switch(axis){
    case 'x':
    xrot_angle += increment;
    break;

    case 'y':
        yrot_angle = yrot_angle + increment;
        break;
    default:
        return -1;
    }

    return 0;
}

