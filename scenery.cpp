/* scenery.cpp */
// Defines the non-inline methods of class Scene.


#include <GL/gl.h>
#include <GL/glu.h>
#include "scenery.h"

/*
    This method draws the current scene.
    args: SceneType s - The type of scene. Right now only the default
                        is handled.
*/
void Scene::draw(){
    if (current_scene == DEFAULT){

        glPushMatrix();

            // Set up lights and materials.
            GLfloat yellow_light[4] = {1.0f, 1.0f, 0.0f, 1.0f};
            GLfloat dark_yellow_light[4] = {0.8f, 1.0f, 0.0f, 1.0f};
            GLfloat blue_light[4] = {0.0f, 0.0f, 0.7f, 1.0f};
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, yellow_light);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, yellow_light);

            // Draw the first segment of ground.
            glBegin(GL_POLYGON);
                glNormal3f(0.0, 1.0, 0.0);
                glVertex3f(100.0, -20.0, 100.0);
                glVertex3f(100.0, -20.0, -50.0);
                glVertex3f(-100.0, -20.0, -50.0);
                glVertex3f(-100.0, -20.0, 100.0);
            glEnd();

            // Second segment.
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, dark_yellow_light);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, dark_yellow_light);
            glBegin(GL_POLYGON);
                glNormal3f(0.0, 1.0, 0.0);
                glVertex3f(100.0, -20.0, -50.0);
                glVertex3f(100.0, -20.0, -100.0);
                glVertex3f(-100.0, -20.0, -100.0);
                glVertex3f(-100.0, -20.0, -50.0);
            glEnd();

            // Third segment.
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, yellow_light);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, yellow_light);
            glBegin(GL_POLYGON);
                glNormal3f(0.0, 1.0, 0.0);
                glVertex3f(100.0, -20.0, -100.0);
                glVertex3f(100.0, -20.0, -200.0);
                glVertex3f(-100.0, -20.0, -200.0);
                glVertex3f(-100.0, -20.0, -100.0);
            glEnd();

            // Fourth segment.
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, blue_light);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blue_light);
            glBegin(GL_POLYGON);
                glNormal3f(0.0, 1.0, 0.0);
                glVertex3f(100.0, -20.0, -200.0);
                glVertex3f(100.0, -20.0, -300.0);
                glVertex3f(-100.0, -20.0, -300.0);
                glVertex3f(-100.0, -20.0, -200.0);
            glEnd();

            // Fifth segment.
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, yellow_light);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, yellow_light);
            glBegin(GL_POLYGON);
                glNormal3f(0.0, 1.0, 0.0);
                glVertex3f(100.0, -20.0, -300.0);
                glVertex3f(100.0, -20.0, -400.0);
                glVertex3f(-100.0, -20.0, -300.0);
                glVertex3f(-100.0, -20.0, -400.0);
            glEnd();

        glPopMatrix();
    }
}
