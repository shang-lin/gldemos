#include <stdio.h>
#include <GL/glut.h>
#include <iostream>
#include <cmath>

#include "robot.h"
using namespace std;

/*
    Robot::Robot.
    This constructor initializes all the data members to 0 and the
    rotation axis to the y-axis.
*/
Robot::Robot(){
    angle = 0.0f;
    x_pos = 0.0f;
    y_pos = 0.0f;
    z_pos = 0.0f;
    csign = 1.0f;

    xrot_angle = 0.0f;
    yrot_angle = 0.0f;

}


/*
    Robot::drawCube.

    This method draws a cube at the position x, y, z using quads.
*/
void Robot::drawCube(GLfloat x, GLfloat y, GLfloat z){
}

/*
    Robot::drawTorso().
    This method draws the robot's torso as a green
    3x5x2 cube.
*/
void Robot::drawTorso(){
    GLfloat green_light[4] = {0.0f, 1.0f, 0.0f, 1.0f};
    glPushMatrix();

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, green_light);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, green_light);
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
    GLfloat red_light[4] = {1.0f, 0.0f, 0.0f, 1.0f};
    glPushMatrix();

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, red_light);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, red_light);
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
    GLfloat blue_light[4]={0.0f, 0.0f, 1.0f, 1.0f};
    glPushMatrix();

        // Draw first leg.
        glPushMatrix();
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, blue_light);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blue_light);
            glScalef(1.0f, 5.0f, 1.0f);
            glTranslatef(-20.0f, -20.0f, 0.0f);
            glRotatef(angle, 1.0, 0.0, 0.0);
            glutSolidCube(20.0f);
        glPopMatrix();

        // Draw second leg relative to first.
        glPushMatrix();
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, blue_light);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blue_light);
            glScalef(1.0f, 5.0f, 1.0f);
            glTranslatef(20.0f, -20.0f, 0.0f);
            glRotatef(-angle, 1.0, 0.0, 0.0);
            glutSolidCube(20.0f);
        glPopMatrix();

    glPopMatrix();
}

/*
    Robot::drawArms().

    This method draws the robot's arms as two cubes with side lengths
    in 1:4:1 proportion.
*/
void Robot::drawArms(){
    GLfloat blue_light[4] = {0.0f, 0.0f, 1.0f, 1.0f};

    glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, blue_light);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blue_light);

        // Draw the left arm.
        glPushMatrix();
            glScalef(1.0f, 4.0f, 1.0f);
            glTranslatef(-40.0f, 1.0f, 0.0f);
            glutSolidCube(20.0f);
        glPopMatrix();

        // Draw the right arm.
        glPushMatrix();
            glScalef(1.0f, 4.0f, 1.0f);
            glTranslatef(40.0f, 1.0f, 0.0f);
            glutSolidCube(20.0f);
        glPopMatrix();
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

    drawTorso();
    drawHead();
    drawLegs();
    drawArms();
}

/*
    Robot::setup().

    This method performs the initial transformations to draw the
    robot in the correct location and orientation.
*/
void Robot::setup(){
    if (angle > 30.0)
        csign = -1.0;
    else if (angle < -30.0)
        csign = 1.0;

    angle = angle + 0.1*csign;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    x_pos = x_pos + 0.05*sin(yrot_angle/180.0*3.1416);
    z_pos = z_pos + 0.05*cos(yrot_angle/180.0*3.1416);

    glTranslatef(x_pos, y_pos, z_pos);
    glRotatef(xrot_angle, 1.0f, 0.0f, 0.0f);
    glRotatef(yrot_angle, 0.0f, 1.0f, 0.0f);
}

/*
    Robot::incrementRotation.
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
