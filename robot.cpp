#include <stdio.h>
#include <GL/glut.h>
#include <iostream>
#include <cmath>

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
        //glColor3f(0.0f, 1.0f, 0.0f);
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, green_light);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, green_light);
        glScalef(3.0f, 5.0f, 2.0f);

        //texture mapping
        glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
        glBindTexture(GL_TEXTURE_2D, texName);

        glBegin(GL_QUADS);

        glTexCoord2f(0.0, 0.0);
        glVertex3f(-0.5*2.0, -0.5*2.0, 0.5*2.0);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(-0.5*2.0, 0.5*2.0, 0.5*2.0);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(0.5*2.0, 0.5*2.0, 0.5*2.0);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(0.5*2.0, -0.5*2.0, 0.5*2.0);

        glEnd();

        glDisable(GL_TEXTURE_2D);
        glPopMatrix();

        drawCube(2.0);
    glPopMatrix();
}

/*
    Robot::drawHead().
    This method draws the robot's head as a red 2x2x2
    cube.

    // TODO: Map face texture onto it.
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

    //glColor3f(0.0f, 0.0f, 1.0f);

    // Draw first leg.
    glPushMatrix();
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, blue_light);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blue_light);
    glTranslatef(-2.0f, -3.8f, 0.0f);
    glRotatef(angle, 1.0, 0.0, 0.0);
    glTranslatef(0.0f, -5.0f, 0.0f);
    glScalef(0.8f, 5.0f, 0.8f);
    drawCube(2.0);
    glPopMatrix();

    // Draw second leg relative to first.
    glPopMatrix();
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, blue_light);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blue_light);

    glTranslatef(2.0f, -3.8f, 0.0f);
    glRotatef(-angle, 1.0, 0.0, 0.0);
    glTranslatef(0.0f, -5.0f, 0.0f);
    glScalef(0.8f, 5.0f, 0.8f);
    //glutSolidCube(2.0f);
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
            glTranslatef(-4.0f, 0.7f, 0.2f);
            glRotatef(angle, 1.0f, 0.0f, 0.0f);
            glScalef(1.0f, 3.0f, 1.0f);
            drawCube(2.0);
         glPopMatrix();

        // Draw the right arm.
        glPushMatrix();
            glTranslatef(4.0f, 0.7f, 0.2f);
            glRotatef(-angle, 1.0f, 0.0f, 0.0f);
            glScalef(1.0f, 3.0f, 1.0f);
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

    //glRotatef(90.0, 0.0, 1.0, 0.0);
    // Draw all parts of the robot.

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
    if (angle > 20.0)
        csign = -1.0;
    else if (angle < -20.0)
        csign = 1.0;

    angle = angle + 0.1*csign;

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
    glBegin(GL_POLYGON);
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(-0.5*size, -0.5*size, 0.5*size);
    glVertex3f(0.5*size, -0.5*size, 0.5*size);
    glVertex3f(0.5*size, 0.5*size, 0.5*size);
    glVertex3f(-0.5*size, 0.5*size, 0.5*size);
    glEnd();
    glBegin(GL_POLYGON);
        glNormal3f(0.0, 0.0, -1.0);
        glVertex3f(-0.5*size, -0.5*size, -0.5*size);
        glVertex3f(-0.5*size, 0.5*size, -0.5*size);
        glVertex3f(0.5*size, 0.5*size, -0.5*size);
        glVertex3f(0.5*size, -0.5*size, -0.5*size);
    glEnd();

    glBegin(GL_POLYGON);
        glNormal3f(1.0, 0.0, 0.0);
        glVertex3f(0.5*size, -0.5*size, 0.5*size);
        glVertex3f(0.5*size, -0.5*size, -0.5*size);
        glVertex3f(0.5*size, 0.5*size, -0.5*size);
        glVertex3f(0.5*size, 0.5*size, 0.5*size);
    glEnd();

    glBegin(GL_POLYGON);
        glNormal3f(-1.0, 0.0, 0.0);
        glVertex3f(-0.5*size, -0.5*size, 0.5*size);
        glVertex3f(-0.5*size, 0.5*size, 0.5*size);
        glVertex3f(-0.5*size, 0.5*size, -0.5*size);
        glVertex3f(-0.5*size, -0.5*size, -0.5*size);
    glEnd();

    glBegin(GL_POLYGON);
        glNormal3f(0.0, 1.0, 0.0);
        glVertex3f(-0.5*size, 0.5*size, 0.5*size);
        glVertex3f(0.5*size, 0.5*size, 0.5*size);
        glVertex3f(0.5*size, 0.5*size, -0.5*size);
        glVertex3f(-0.5*size, 0.5*size, -0.5*size);
    glEnd();

    glBegin(GL_POLYGON);
        glNormal3f(0.0, -1.0, 0.0);
        glVertex3f(-0.5*size, -0.5*size, 0.5*size);
        glVertex3f(-0.5*size, -0.5*size, -0.5*size);
        glVertex3f(0.5*size, -0.5*size, -0.5*size);
        glVertex3f(0.5*size, -0.5*size, 0.5*size);
    glEnd();
}

/*

*/
void Robot::makeCheckImage(void){
    int i, j, k, c;

    if (toggle == 0){
        // Make a green background. Every pixel is green
        for (i=0; i<checkImageHeight; i++){
            for (j=0; j<checkImageWidth; j++){
                for (k=0; k<4; k++){
                    checkImage[i][j][k]=0;
                    if (k==3 || k==1)
                        checkImage[i][j][k] = 255;
                }
            }
        }

        //Draw cloth pattern.
        for (i=0; i<checkImageHeight; i++){
            for (j=24; j<39; j++){
               if (j<36 && j>=27)
                   checkImage[i][j][0] = 255;
               if ((i<12 && i>=4) || (i<28 && i>=20)
                    || (i<44 && i>=36) || (i<60 && i>=52))
                   checkImage[i][j][1]=0;
            }

        }
    }
    //Checker board pattern
    else if (toggle == 1){
        for (i=0; i<checkImageHeight; i++){
            for (j=0; j<checkImageWidth; j++){
                // From OpenGL Reference Manual.
                c = ((((i&0x8)==0)^((j&0x8)==0)))*255;
                    checkImage[i][j][0] = (GLubyte) c;
                    checkImage[i][j][1] = (GLubyte) c;
                    checkImage[i][j][2] = (GLubyte) c;
                    checkImage[i][j][3] = (GLubyte) 255;
            }
        }
    }
    // Face pattern.
    else if (toggle == 2){
        for (i=0; i<checkImageHeight; i++){
            for (j=0; j<checkImageWidth; j++){
               // Circle is (x-a)^2 + (y-b)^2 = r^2.
               // a is 22, y is 42, radius is 4.
               // Mouth is a 4 x 32 rectangle.
               if ((((j-22) * (j-22) + (i-42) * (i-42)) <= 16)
                   || (((j-42) * (j-42) + (i-42) * (i-42)) <= 16)
                   || ( (j >= 16 && j <= 48) && (i>=26 && i <= 30))){
                   checkImage[i][j][0] = 255;
                   checkImage[i][j][1] = 255;
                   checkImage[i][j][2] = 0;
                   checkImage[i][j][3] = 255;
               }
               else{
                   checkImage[i][j][0] = 0;
                   checkImage[i][j][1] = 0;
                   checkImage[i][j][2] = 255;
                   checkImage[i][j][3] = 255;
               }
            }
        }
    }
}

/*
    This method sets up the face texture for the robot's head.
    TODO: Make texture appear on face.
*/
void Robot::drawFaceTexture(){
    glGenTextures(2, &texName);
    glBindTexture(GL_TEXTURE_2D, texName);

    int i, j;

    for (i=0; i<checkImageHeight; i++){
        for (j=0; j<checkImageWidth; j++){
            if ((((j-22)*(j-22)+(i-42)*(i-42))<=16)
                   || (((j-42)*(j-42)+(i-42)*(i-42))<=16)
                   || ( (j>=16 && j<=48) && (i>=26 && i<=30))){
                face_image[i][j][0]=255;
                face_image[i][j][1]=255;
                face_image[i][j][2]=0;
                face_image[i][j][3]=255;
            }
            else{
                checkImage[i][j][0]=0;
                checkImage[i][j][1]=0;
                checkImage[i][j][2]=255;
                checkImage[i][j][3]=255;
            }
        }
    }
}

