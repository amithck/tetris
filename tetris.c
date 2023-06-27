#include <GL/glut.h>
#include<unistd.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

float x_c = 0.0, y_c = 1.0;
int grid[21][21];

void init()
{
    int i,j;
    for(i=0;i<20;i++)
    {
        for(j=0;j<21;j++)
        {
            grid[i][j]=0;
        }
    }
    for(j=0;j<21;j++)
    {
        grid[j][20]=1;
    }
}

int test[][3]={{9,0},{11,0},{10,1}};
int cur[3][3];

void gridInit()
{
    int i,j;
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            cur[i][j]=test[i][j];
        }
    }
}

void clearGrid()
{
    int i,j,k;
    for(i=0; i<21; i++)
    {
        for(j=0;j<21;j++)
        {
            if(grid[j][i]==1)
            {
                glEnable(GL_SCISSOR_TEST);
                glScissor(0,((20-i)*20),400,400);
                glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                glDisable(GL_SCISSOR_TEST);
                goto left;
            }
        }
    }
    left:
    for(k=i;k>0;k--)
    {
     for(j=0;j<21;j++)
        {
            if(grid[j][k]==1)
            {
                glEnable(GL_SCISSOR_TEST);
                glScissor(0,k*20,j*20,20);
                glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                glDisable(GL_SCISSOR_TEST);
                goto right;
            }
        }   
    }
    right:
    for(k=i;k>0;k--)
    {
     for(j=20;j>=0;j--)
        {
            if(grid[j][k]==1)
            {
                glEnable(GL_SCISSOR_TEST);
                glScissor(j*20,k*20,400,20);
                glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                glDisable(GL_SCISSOR_TEST);
                return;
            }
        }   
    }
}

void checkGrid(){
    cur[0][1]+=1;
    cur[0][0]= test[0][0]+x_c*10;
    cur[1][1]+=1;
    cur[1][0]= test[1][0]+x_c*10;
    cur[2][1]+=1;
    cur[2][0]= test[2][0]+x_c*10;
    if(grid[cur[2][0]][cur[2][1]]==1 || grid[cur[1][0]][cur[1][1]]==1 || grid[cur[0][0]][cur[0][1]]==1)
    {
        x_c=0.0;
        y_c=1.0;
        grid[cur[2][0]][cur[2][1]-2]=1;
        grid[cur[2][0]][cur[2][1]-1]=1;
        grid[cur[1][0]][cur[1][1]-1]=1;
        grid[cur[0][0]][cur[0][1]-1]=1;
        if(grid[10][0]==1)
        {
            exit(0);
        }
        clearGrid();
        gridInit();
        glutPostRedisplay();
    }
    clearGrid();
}

void drop(int s){
    y_c -= 0.1;
    int i;
    for(int i=0;i<65000000;i++);
    checkGrid();
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
    gridInit();
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

