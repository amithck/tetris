#include <GL/glut.h>
#include<unistd.h>
#include <time.h>
#include <stdio.h>

float x_c = 0.0, y_c = 1.0;
int a[21][21];

void init()
{
    int i,j;
    for(i=0;i<20;i++)
    {
        for(j=0;j<21;j++)
        {
            a[i][j]=0;
        }
    }
    for(j=0;j<21;j++)
    {
        a[20][j]=1;
    }
}

void drop(int s){
    y_c -= 0.1;
    int i;
    for(i=0; i<65000000; i++);
    
    glutPostRedisplay();
}

void block(float x, float y)
{
    glLoadIdentity();

    // Drawing the tetris block
    glColor3f(1.0, 0.0, 0.0);  // Set color to red
    glRectf(x-0.1, y-0.1, x+0.1, y+0.1);  // Draw a rectangle

    glFlush();
}

void line(float x, float y){
    glLoadIdentity();

    // Drawing the tetris line piece
    glColor3f(0.0, 0.0, 1.0);  // Set color to blue

    // Draw four rectangles horizontally to form a line piece
    glRectf(x-0.2, y-0.05, x+0.2, y+0.05);  

    glFlush();
}

void s(float x, float y){

    glLoadIdentity();

    // Drawing the Tetris S piece
    glColor3f(1.0, 0.0, 0.0);  // Set color to red

     glRectf(x-0.05, y-0.05, x+0.15, y+0.05);

    // Draw the bottom rectangle
    glRectf(x-0.15, y-0.15, x+0.05, y-0.05);


    glFlush();
}

void z(float x, float y){
    glLoadIdentity();

    // Drawing the Tetris S piece
    glColor3f(1.0, 0.0, 0.0);  // Set color to red

    // Draw the top rectangle
     glRectf(x-0.15, y-0.05, x+0.05, y+0.05);

    // Draw the bottom rectangle
    glRectf(x-0.05, y-0.15, x+0.15, y-0.05);


    glFlush();
}
void l(float x, float y){

    glLoadIdentity();

    // Drawing the Tetris L piece
    glColor3f(0.0, 1.0, 0.0);  // Set color to green

   glRectf(x-0.1, y-0.3, x+0.0, y-0.0);

    // Draw the horizontal rectangle
    glRectf(x+0.0, y-0.3, x+0.1, y-0.2);

    glFlush();
}

void revl(float x, float y){
    glLoadIdentity();

    // Drawing the Tetris Reverse L block
    glColor3f(1.0, 0.0, 0.0);  // Set color to red

    glRectf(x+0.1, y-0.3, x+0.0, y-0.0);

    // Draw the horizontal rectangle
    glRectf(x+0.0, y-0.3, x-0.1, y-0.2);

    glFlush();
}

void t(float x, float y){
    glLoadIdentity();

    // Drawing the Tetris T block
    glColor3f(0.5, 0.0, 0.5);  // Set color to purple

    // Draw the vertical rectangle
    glRectf(x-0.15, y-0.1, x+0.15, y+0.0);

    // Draw the horizontal rectangle
    glRectf(x-0.05, y-0.2, x+0.05, y-0.1);

    glFlush();
}

void display(){

    int a,i;
    void (*f[])(float,float) = {&block, &line, &s, &z, &l, &revl, &t};
    time_t ti;
    srand((unsigned) time(&ti));
    a = rand() % 7;
    (*f[6])(x_c, y_c);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drop(6);
}



void arrowKeys(int key, int x, int y) 
{
    switch (key) 
    {    
       case 27 : break;
       case 100 : x_c=x_c-0.1;   
       break;
       case 102: x_c=x_c+0.1; 
       break;
    }
    glutPostRedisplay();
}


int main(int argc, char** argv)
{
    init();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Tetris Block");

    glClearColor(1.0, 1.0, 1.0, 1.0);  // Set background color to white
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);  // Set orthographic viewing volume
    glutDisplayFunc(display);
    glutSpecialFunc(arrowKeys);
    glutMainLoop();

    return 0;
}

