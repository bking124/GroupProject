//============================================================================
// Name        : Tetris Driver.cpp
// Author      : Dr. Booth
// Version     :
// Copyright   : Your copyright notice
// Description : Main Driver For Group Project
//============================================================================
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <iostream>
#include "GroupProject.h"
#include "SplayTree.h"
#include <stdio.h>

#include "math.h"


using namespace std;

SplayTree st;


SplayNode* accept_tree(){
    int n;
    cout << "Create splay tree: (enter 0 to finish)\n";

    cout << "\nEnter node value: ";
    cin >> n;
    while(n != 0) {
        st.insertNode(n);
        fflush(stdin);
        cout<<"\nEnter node value: ";
        cin>>n;
    }

    return st.root;
}

/*void inorder(splay* root) {
if(root!=NULL) {
inorder(root->left);
cout<<root->data;
inorder(root->right);
}
}

void preorder(splay* root) {
if(root!=NULL) {
cout<<root->data;
preorder(root->left);
preorder(root->right);
}
}

void postorder(splay* root) {
if(root!=NULL) {
postorder(root->left);
postorder(root->right);
cout<<root->data;
}*/

void drawCircle(float segments, float radius, float sx, float sy)
{
    float theta = 2 * 3.1415926 / segments;
    float tan_factor = tanf(theta);
    float radial_factor = cosf(theta);
    float x = radius;
    float y = 0;

    int cache_pt = 0;
    double cache_x;
    double cache_y;

    glBegin(GL_LINES);
    for (int ii = 0; ii < segments; ii++) {
        if(!cache_pt) {
            cache_x = x+sx;
            cache_y = y+sy;
            cache_pt = 1;
        }
        else {
            //glVertex2f(cache_x,cache_y);
            glVertex2f(x + sx, y + sy);
            cache_x = x+sx;
            cache_y = y+sy;
        }
    float tx = -y;
    float ty = x;
    x += tx * tan_factor;
    y += ty * tan_factor;
    x *= radial_factor;
    y *= radial_factor;
    }

    glEnd();
}

void draw_line(float x1,float y1,float x2, float y2) {
    glBegin(GL_LINES);
    glVertex2f(x1,y1);
    glVertex2f(x2,y2);
    glEnd();
}

void draw_text(char* text,float x, float y) {
    GLvoid *font_style = GLUT_BITMAP_TIMES_ROMAN_24;
    glRasterPos3f(x, y, 0);
    for (int i = 0; text[i] != '\0'; i++){
        glutBitmapCharacter(font_style, text[i]);
    }
}

void drawNode(SplayNode* t_root,float x1,float y1,int level) {
    if (t_root==NULL)
        return;
    float segments = 25;
    float radius = 1.0;
    float left_angle = 245;
    float right_angle = 115;
    float branch_length = 12 - level*2.5;
    float angle_change = 20;

    // Draw the current circle
    drawCircle(segments,radius,x1,y1);

    char buff[5];
    itoa(t_root->getData(),buff,10);
    draw_text(buff,x1,y1);

    if(t_root->getLeft() != NULL) {
        // Draw the Left circle
        float angle = left_angle - level*angle_change;
        double radian = angle*3.14/180;
float m = (double)tan((double)radian);
float x2 = x1 + branch_length * sin((double) radian);
float y2 = y1 + branch_length * cos((double) radian);
drawNode(t_root->getLeft(),x2,y2,level+1);
draw_line(x1,y1,x2,y2);
}
if(t_root->getRight() != NULL) {
// Draw the Right circle
float angle = right_angle + level*angle_change;
float radian = angle*3.14/180;
float m = (double)tan((double)radian);
float x2 = x1 + branch_length * sin((double) radian);
float y2 = y1 + branch_length * cos((double) radian);
drawNode(t_root->getRight(),x2,y2,level+1);
draw_line(x1,y1,x2,y2);
}
}
void display(void) {
glClearColor (0.0,0.0,0.0,1.0);
glClear (GL_COLOR_BUFFER_BIT);
glLoadIdentity();
glTranslatef(0,10,-30);
glColor3f(1,1,1);
drawNode(st.root,0,0,0);
glutSwapBuffers();
}
void reshape (int w, int h) {
glViewport (0, 0, (GLsizei)w, (GLsizei)h);
glMatrixMode (GL_PROJECTION);
glLoadIdentity ();
gluPerspective (60, (GLfloat)w / (GLfloat)h, 0.1, 100.0);
glMatrixMode (GL_MODELVIEW);
}
void keyboard(unsigned char key, int x, int y)
{
switch (key) {
case 27:
exit(0);
break;
}
}
int main (int argc, char **argv) {
    accept_tree();
    st.printPreorder();
    //inorder(root);

    // OPENGL Drawing functions
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE);
    glutInitWindowSize (1200, 800);
    glutInitWindowPosition (0, 0);
    glutCreateWindow ("A splay tree");

    // Register function pointers to the drawing framework
    glutDisplayFunc (display);
    glutIdleFunc (display);
    glutReshapeFunc (reshape);
    glutKeyboardFunc (keyboard);
    glutMainLoop ();

    return 0;
}
