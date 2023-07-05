#include <GL/glut.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

int gridData[7][4][2]={
{{9,-1},{10,-1},{9,0},{10,0}},
{{8,-1},{9,-1},{10,-1},{11,-1}},
{{9,0},{10,0},{9,1},{8,1}},
{{8,0},{9,0},{9,1},{10,1}},
{{9,0},{9,1},{9,2},{10,2}},
{{9,0},{9,1},{9,2},{8,2}},
{{9,0},{10,0},{11,0},{10,1}}
};


float co_or[2]={0.0,1.0};
int grid[21][21];
int cur[4][2];
float rot = 0.0;
int zx=0;
int q[]={1,1,-1,-1};
int xc=0,a;

void init()
{
    int i,j;
    for(i=0;i<20;i++)
    {
        for(j=0;j<20;j++)
        {
            grid[i][j]=0;
        }
    }
    for(j=0;j<20;j++)
    {
        grid[j][20]=1;
    }
}

void randomize()
{
    time_t ti;
    srand((unsigned) time(&ti));
    a = (rand() % 2)+4;
    // a=1;
}

void gridInit()
{
    int i,j;
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            cur[i][j]=gridData[a][i][j];
        }
    }
}

void clearGrid()
{
    int i,j,k,flag=1;
    for(i=0; i<20; i++)
    {
        for(j=0;j<20;j++)
        {
            if(grid[j][i]==0)
            {
                glEnable(GL_SCISSOR_TEST);
                glScissor((j)*20,((20-i-1)*20),20,20);
                glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                glDisable(GL_SCISSOR_TEST);
            }
        }
    }
    for(i=0;i<20;i++)
    {
        for(j=10;j<20;j++)
        {
            if(grid[j][i-2]==0)
            {
                flag=0;
                break;
            }
        }
        if(flag==1)
        {
            glEnable(GL_SCISSOR_TEST);
            glScissor(0,(20-i-1)*20,420,20);
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glDisable(GL_SCISSOR_TEST);
            for(j=0;j<20;j++)
            {
                grid[j][i-3]=0;
            }
        }
    }
}


void checkGrid(){
    cur[0][1]+=1;
    cur[0][0]= gridData[a][0][0]+co_or[0]*10;
    cur[1][1]+=1;
    cur[1][0]= gridData[a][1][0]+co_or[0]*10;
    cur[2][1]+=1;
    cur[2][0]= gridData[a][2][0]+co_or[0]*10;
    cur[3][1]+=1;
    cur[3][0]= gridData[a][3][0]+co_or[0]*10;
    if(grid[cur[2][0]][cur[2][1]]==1 || grid[cur[1][0]][cur[1][1]]==1 || grid[cur[0][0]][cur[0][1]]==1 || grid[cur[3][0]][cur[3][1]]==1)
    {
        int i,j;
        co_or[0]=0.0;
        co_or[1]=1.0;
        grid[cur[3][0]][cur[3][1]-1]=1;
        grid[cur[2][0]][cur[2][1]-1]=1;
        grid[cur[1][0]][cur[1][1]-1]=1;
        grid[cur[0][0]][cur[0][1]-1]=1;
        if(grid[9][0]==1 || grid[10][0]==1 || grid[11][0]==1 || grid[12][0]==1 || grid[8][0]==1)
        {
            exit(0);
        }
        zx=0;
        xc=0;
        rot=0;
        randomize();
        clearGrid();
        gridInit();
        glutPostRedisplay();
    }
    clearGrid();
}

void drop(int s){
    co_or[(zx+1)%2]-= 0.1*q[xc];
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
    glRotatef(rot, 0, 0, 1);
    glRectf(x-0.1, y-0.1, x+0.1, y+0.1);  // Draw a rectangle

    glFlush();
}

void line(float x, float y){
    glLoadIdentity();

    // Drawing the tetris line piece
    glColor3f(0.0, 0.0, 1.0);  // Set color to blue
    glRotatef(rot, 0, 0, 1);

    // Draw four rectangles horizontally to form a line piece
    glRectf(x-0.2, y-0.0, x+0.2, y+0.1);  

    glFlush();
}

void s(float x, float y){

    glLoadIdentity();

    // Drawing the Tetris S piece
    glColor3f(1.0, 0.0, 0.0);  // Set color to red
    glRotatef(rot, 0, 0, 1);

    glRectf(x-0.1, y-0.1, x+0.1, y+0.00);

    // Draw the bottom rectangle
    glRectf(x-0.2, y-0.2, x+0.0, y-0.1);


    glFlush();
}

void z(float x, float y){
    glLoadIdentity();

    // Drawing the Tetris S piece
    glColor3f(1.0, 0.0, 0.0);  // Set color to red
    glRotatef(rot, 0, 0, 1);

    // Draw the top rectangle
     glRectf(x-0.1, y-0.1, x+0.1, y+0.0);

    // Draw the bottom rectangle
    glRectf(x+0.0, y-0.2, x+0.2, y-0.1);


    glFlush();
}
void l(float x, float y){

    glLoadIdentity();

    // Drawing the Tetris L piece
    glColor3f(0.0, 1.0, 0.0);  // Set color to green
    glRotatef(rot, 0, 0, 1);

   glRectf(x-0.1, y-0.3, x-0.0, y-0.0);

    // Draw the horizontal rectangle
    glRectf(x+0.0, y-0.3, x+0.1, y-0.2);

    glFlush();
}

void revl(float x, float y){
    glLoadIdentity();

    // Drawing the Tetris Reverse L block
    glColor3f(1.0, 0.0, 0.0);  // Set color to red
    glRotatef(rot, 0, 0, 1);

    glRectf(x-0.1, y-0.3, x+0.0, y-0.0);

    // Draw the horizontal rectangle
    glRectf(x+0.0, y-0.3, x-0.2, y-0.2);

    glFlush();
}

void t(float x, float y){
    glLoadIdentity();

    // Drawing the Tetris T block
    glColor3f(0.5, 0.0, 0.5);  // Set color to purple

    glRotatef(rot, 0, 0, 1);

    // Draw the vertical rectangle
    glRectf(x-0.2, y-0.1, x+0.1, y+0.0);

    // Draw the horizontal rectangle
    glRectf(x-0.1, y-0.2, x+0.0, y-0.1);

    glFlush();
}

void display(){

    int i;
    void (*f[])(float,float) = {&block, &line, &s, &z, &l, &revl, &t};
    (*f[a])(co_or[0], co_or[1]);
    drop(a);
}

void rotate()
{
    rot+=90.0;
    float temp;
    temp=co_or[0];
    co_or[0]=co_or[1];
    co_or[1]=temp;
    if(rot==360)
    {
        rot = 0;
        co_or[0] *=-1;
        co_or[1] *=-1;
    }
    if(rot==180)
    {
        co_or[0] *=-1;
        co_or[1] *=-1;
    }
    zx=(zx+1)%2;
    xc=(xc+1)%4;
}

void arrowKeys(int key, int x, int y) 
{
    switch (key) 
    {    
       case 27 : break;
       case 100 : co_or[zx]-=0.1;   
       break;
       case 102: co_or[zx]+=0.1; 
       break;
       case 101 : rotate();   
       break;
    }
    glutPostRedisplay();
}


int main(int argc, char** argv)
{
    init();
    randomize();
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

