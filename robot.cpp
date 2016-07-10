#include <stdio.h>
#include <GL/glut.h>
#include <iostream>
#include <cmath>

#include "robot.h"

using namespace std;

/*
    Robot::Robot().
    This default constructor initializes all the data members to 0 and the
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
    Constructor.
    The angle between the torso and each leg, the
    starting positions, and the angle of rotation
    are initialized.
*/
Robot::Robot(GLfloat a, GLfloat x, GLfloat y,
             GLfloat z){
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
    GLfloat green_light[4] = {0.0f, 1.0f, 0.0f, 1.0f};
    glPushMatrix();

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, green_light);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, green_light);
    glScalef(3.0f, 5.0f, 2.0f);
    drawCube(2.0);
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
    glTranslatef(0.0f, 7.0f, 0.0f);
    glScalef(2.0f, 2.0f, 2.0f);
    drawCube(2.0);
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
    glScalef(0.8f, 5.0f, 0.8f);
    glTranslatef(-2.0f, -0.3f, 0.0f);
    glRotatef(angle, 1.0, 0.0, 0.0);
    glTranslatef(0.0f, -1.2f, 0.0f);
    //glutSolidCube(2.0f);
    drawCube(2.0);
    glPopMatrix();

    // Draw second leg relative to first.
    glPopMatrix();
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, blue_light);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blue_light);
    glScalef(0.8f, 5.0f, 0.8f);
    glTranslatef(2.0f, -0.3f, 0.0f);
    glRotatef(-angle, 1.0, 0.0, 0.0);
    glTranslatef(0.0f, -1.2f, 0.0f);
    drawCube(2.0);
    glPopMatrix();

    glPopMatrix();
}

void Robot::drawArms(){
    GLfloat yellow_light[4] = {1.0f, 1.0f, 0.0f, 1.0f};

    glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, yellow_light);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, yellow_light);

        // Draw the left arm.
        glPushMatrix();
            glScalef(1.0f, 3.0f, 1.0f);
            glTranslatef(-4.0f, 0.7f, 0.2f);
            //glutSolidCube(2.0f);
            drawCube(2.0);
        glPopMatrix();

        // Draw the right arm.
        glPushMatrix();
            glScalef(1.0f, 3.0f, 1.0f);
            glTranslatef(4.0f, 0.7f, 0.2f);
            drawCube(2.0);
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
    drawArms();
    drawLegs();

}

/*
    Robot::setup().

    This method performs the initial transformations to draw the
    robot in the correct location and orientation.
*/
void Robot::setup(){
    if (angle > 50.0)
       csign = -1.0;
    else if (angle < -50.0)
        csign = 1.0;

    angle = angle + 0.5*csign;

    x_pos = x_pos + 0.005*sin(yrot_angle/180.0*3.1416);
    z_pos = z_pos + 0.005*cos(yrot_angle/180.0*3.1416);

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


void Robot::drawCube(double size){
    glBegin(GL_QUADS);
        glNormal3f(0.0, 0.0, 1.0);
        glVertex3f(-0.5*size, -0.5*size, 0.5*size);
        glVertex3f(0.5*size, -0.5*size, 0.5*size);
        glVertex3f(0.5*size, 0.5*size, 0.5*size);
        glVertex3f(-0.5*size, 0.5*size, 0.5*size);

        glNormal3f(0.0, 0.0, -1.0);
        glVertex3f(-0.5*size, -0.5*size, -0.5*size);
        glVertex3f(-0.5*size, 0.5*size, -0.5*size);
        glVertex3f(0.5*size, 0.5*size, -0.5*size);
        glVertex3f(0.5*size, -0.5*size, -0.5*size);

        glNormal3f(1.0, 0.0, 0.0);
        glVertex3f(0.5*size, -0.5*size, 0.5*size);
        glVertex3f(0.5*size, -0.5*size, -0.5*size);
        glVertex3f(0.5*size, 0.5*size, -0.5*size);
        glVertex3f(0.5*size, 0.5*size, 0.5*size);

        glNormal3f(-1.0, 0.0, 0.0);
        glVertex3f(-0.5*size, -0.5*size, 0.5*size);
        glVertex3f(-0.5*size, 0.5*size, 0.5*size);
        glVertex3f(-0.5*size, 0.5*size, -0.5*size);
        glVertex3f(-0.5*size, -0.5*size, -0.5*size);

        glNormal3f(0.0, 1.0, 0.0);
        glVertex3f(-0.5*size, 0.5*size, 0.5*size);
        glVertex3f(0.5*size, 0.5*size, 0.5*size);
        glVertex3f(0.5*size, 0.5*size, -0.5*size);
        glVertex3f(-0.5*size, 0.5*size, -0.5*size);

        glNormal3f(0.0, -1.0, 0.0);
        glVertex3f(-0.5*size, -0.5*size, 0.5*size);
        glVertex3f(-0.5*size, -0.5*size, -0.5*size);
        glVertex3f(0.5*size, -0.5*size, -0.5*size);
        glVertex3f(0.5*size, -0.5*size, 0.5*size);
    glEnd();
}


