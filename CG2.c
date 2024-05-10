//LAB -2 

#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
void displayPoint(int x, int y)
{
 glColor3f(0, 1, 0);
 glPointSize(5);
 glBegin(GL_POINTS);
 glVertex2i(x, y);
 glEnd();
}
float x01, x2, y01, y2;
int ch;
void SimpleLine(float x1, float y1, float x2, float y2)
{
 float step;
 float dx = x2 - x1;
 float dy = y2 - y1;
 if (abs(dx) > abs(dy))
 {
 step = abs(dx);
 }
 else
 step = abs(dy);
 float Xinc = dx / (float)step;
 float Yinc = dy / (float)step;
 float x = x1;
 float y = y1;
 for (int i = 0; i<= step; i++)
 {
 displayPoint(x, y);
 x = x + Xinc;
 y = y + Yinc;
 }
 glFlush();
}
void DottedLine(float x1, float y1, float x2, float y2)
{
 float step;
 float dx = x2 - x1;
 float dy = y2 - y1;
 if (abs(dx) > abs(dy))
 {
 step = abs(dx);
 }
 else
 step = abs(dy);
 float Xinc = dx / (float)step;
 float Yinc = dy / (float)step;
 float x = x1;
 float y = y1;
 displayPoint(x, y);
 for (int i = 0; i<= step; i++)
 {
 x = x + Xinc;
 y = y + Yinc;
 if (i % 3 == 0)
 {
 displayPoint(x, y);
 }
 }
 glFlush();
}
void DashedLine(float x1, float y1, float x2, float y2)
{
 float step;
 float dx = x2 - x1;
 float dy = y2 - y1;
 if (abs(dx) > abs(dy))
 {
 step = abs(dx);
 }
 else
 step = abs(dy);
 float Xinc = dx / (float)step;
 float Yinc = dy / (float)step;
 float x = x1;
 float y = y1;
 displayPoint(x, y);
 for (int i = 0; i<= step; i++)
 {
 x = x + Xinc;
 y = y + Yinc;
 if (i % 7 == 0)
 {
 displayPoint(x, y);
 }
 }
 glFlush();
}
void myMouse(int button, int state, int x, int y)
{
 static int xst, yst, pt = 0;
 if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
 {
 if (pt == 0)
 {
 xst = x;
 yst = y;
 x01 = xst;
 y01 = yst;
 pt = pt + 1;
 }
 else
 {
 x2 = x;
 y2 = y;
 if (ch == 1)
 {
 SimpleLine(xst, yst, x, y);
 }
 else if (ch == 2)
 {
 DottedLine(xst, yst, x, y);
 }
 else if (ch == 3)
 {
 DashedLine(xst, yst, x, y);
 }
 xst = x;
 yst = y;
 }
 }
 else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
 pt = 0;
 //Clear Screen
 glFlush();
}
void keyboard(unsigned char key, int x, int y)
{
 switch (key)
 {
 case 's':
 {
 ch = 1;
 glutMouseFunc(myMouse);
 break;
 }
 case 'd':
 {
 ch = 2;
 glutMouseFunc(myMouse);
 break;
 }
 case 'D':
 {
 ch = 3;
 glutMouseFunc(myMouse);
 break;
 }
 }
 glutPostRedisplay();
}
void initialize(void)
{
 glClearColor(1.0, 1.0, 1.0, 1.0);
 glClear(GL_COLOR_BUFFER_BIT);
 // gluOrtho2D(l,r,b,t)
 gluOrtho2D(0, 600, 600, 0);
}
void primitives(void)
{
 //glClearColor(1.0, 1.0, 1.0, 1.0);
 //glClear(GL_COLOR_BUFFER_BIT);
 glColor3f(1, 0, 0);
 SimpleLine(0, 300, 600, 300);
 SimpleLine(300, 0, 300, 600);
 glutKeyboardFunc(keyboard);
}
int main(int argc, char **argv)
{
 glutInit(&argc, argv);
 glutInitDisplayMode(GLUT_SINGLE);
 glutInitWindowPosition(0, 0);
 glutInitWindowSize(600, 600);
 glutCreateWindow("OpenGL - DDA Algo");
 initialize();
 printf("--------------------");
 printf("\ns. Simple Line");
 printf("\nd. Dotted Line");
 printf("\nD. Dashed Line");
 printf("\n--------------------\n");
 glutDisplayFunc(primitives);
 glutMainLoop();
 return 0;
}


//LAB-3

#include<GL/glut.h>
#include<iostream>
using namespace std;
int r;
void E_way(int x, int y){
glBegin(GL_POINTS);
 glVertex2i(x+320,y+240);
 glVertex2i(y+320,x+240);
 glVertex2i(y+320, -x+240);
 glVertex2i(x+320, -y+240);
 glVertex2i(-x+320,-y+240);
 glVertex2i(-y+320,-x+240);
 glVertex2i(-y+320,x+240);
 glVertex2i(-x+320,y+240);
glEnd();
glFlush();
}
void B_circle(){
 float d;
 d = 3 - 2*r;
 int x,y;
 x = 0 ;
 y = r ;
do{
E_way(x,y);
 if(d<0){
 d=d+4*x+6;
 }
else{
 d= d+4*(x-y)+10;
 y=y-1;
 }
 x=x+1;
}while(x<y);
}
void init(){
glClearColor(1,1,1,0);
 glColor3f(1,0,0);
 gluOrtho2D(0,640,0,480);
glClear(GL_COLOR_BUFFER_BIT);
}
int main(int argc, char **argv){
cout<<"\n Enter Radius \t ";
cin>>r;
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
glutInitWindowPosition(100,100);
glutInitWindowSize(640,480);
glutCreateWindow("Circle");
init();
glutDisplayFunc(B_circle);
glutMainLoop();
 return 0;
}

//LAB-4


#include <iostream>
#include <math.h>
#include <GL/glut.h>
using namespace std;
float R=0,G=0,B=0;
int Algo;
void init(){
 glClearColor(1.0,1.0,1.0,0.0);
 glMatrixMode(GL_PROJECTION);
 gluOrtho2D(0,640,0,480);
}
void floodFill(int x, int y, float *newCol, float *oldcol){
 float pixel[3];
 glReadPixels(x,y,1,1,GL_RGB,GL_FLOAT,pixel);
 
 if(oldcol[0]==pixel[0] &&oldcol[1]==pixel[1] &&oldcol[2]==pixel[2]){
 
 glBegin(GL_POINTS);
 glColor3f(newCol[0],newCol[1],newCol[2]);
 glVertex2i(x,y);
 glEnd();
 glFlush();
 
 floodFill(x,y+1,newCol,oldcol);
 floodFill(x+1,y,newCol,oldcol);
 floodFill(x,y-1,newCol,oldcol);
 floodFill(x-1,y,newCol,oldcol);
 }
}
void boundaryFill(int x, int y, float* fillColor, float* bc){
 float color[3];
 glReadPixels(x,y,1.0,1.0,GL_RGB,GL_FLOAT,color);
 
 if((color[0]!=bc[0] || color[1]!=bc[1] || color[2]!=bc[2]) && (fillColor[0]!=color[0] || 
fillColor[1]!=color[1] || fillColor[2]!=color[2])){
 
 glColor3f(fillColor[0],fillColor[1],fillColor[2]);
 glBegin(GL_POINTS);
 glVertex2i(x,y);
 glEnd();
 glFlush();
 boundaryFill(x+1,y,fillColor,bc);
 boundaryFill(x-1,y,fillColor,bc);
 boundaryFill(x,y+1,fillColor,bc);
 boundaryFill(x,y-1,fillColor,bc);
 
 
 }
 
 return; 
}
void mouse(int btn, int state, int x, int y){
 y = 480-y;
 if(btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
 
 float bcol[] = {1,0,0};
 float oldcol[] = {1,1,1};
 float newCol[] = {R,G,B};
 
 if(Algo==1){
 boundaryFill(x,y,newCol,bcol);
 }
 if(Algo==2){
 floodFill(x,y,newCol,oldcol);
 } 
 }
}
void B_Draw(){
 glClear(GL_COLOR_BUFFER_BIT);
 glColor3f(1,0,0);
 glBegin(GL_LINE_LOOP);
 glVertex2i(150,100);
 glVertex2i(300,300);
 glVertex2i(450,100);
 glEnd();
 glFlush();
 
}
void F_Draw(){
 glClear(GL_COLOR_BUFFER_BIT);
 
 glBegin(GL_LINES);
 glColor3f(1,0,0);glVertex2i(150,100);glVertex2i(300,300);
 glEnd();
 glBegin(GL_LINE_LOOP);
 glColor3f(0,0,1);glVertex2i(300,300);glVertex2i(450,100);
 glEnd();
 glBegin(GL_LINE_LOOP);
 glColor3f(0,0,0);glVertex2i(450,100);glVertex2i(150,100);
 glEnd();
 glFlush();
 
}
void goMenu(int value){
 switch(value){
 
 case 1:
 R = 0, G = 1, B=0;
 break;
 case 2:
 R = 1, G = 1, B=0;
 break;
 case 3:
 R = 1, G = 0, B=1;
 break;
 
 }
 glutPostRedisplay();
}
int main(int argc, char** argv){
 
 cout<<"\n \t Select the Algorithm ";
 cout<<"\n \t 1. Boundary Fill Algorithm ";
 cout<<"\n \t 2. Flood Fill Algorithm \n \t";
 cin>>Algo;
 
 glutInit(&argc, argv);
 glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
 glutInitWindowSize(640,480);
 glutInitWindowPosition(200,200);
 glutCreateWindow("A4");
 init();
 glutCreateMenu(goMenu);
 glutAddMenuEntry("Color 1 Green",1);
 glutAddMenuEntry("Color 2 Yellow",2);
 glutAddMenuEntry("Color 3 Pink",3);
 glutAttachMenu(GLUT_RIGHT_BUTTON);
 
 if(Algo==1){
 glutDisplayFunc(B_Draw);
 }
 if(Algo==2){
 glutDisplayFunc(F_Draw);
 }
 glutMouseFunc(mouse);
 glutMainLoop();
 return 0;
}

//LAB-5



#include <GL/glut.h>
#include <stdio.h>
#define INSIDE 0
#define LEFT 1
#define RIGHT 2
#define BOTTOM 4
#define TOP 8
#define X_MIN -100
#define X_MAX 100
#define Y_MIN -100
#define Y_MAX 100
int computeRegionCode(int x, int y) {
 int code = INSIDE;
 if (x < X_MIN)
 code |= LEFT;
 else if (x > X_MAX)
 code |= RIGHT;
 if (y < Y_MIN)
 code |= BOTTOM;
 else if (y > Y_MAX)
 code |= TOP;
 return code;
}
void clipLine(int x0, int y0, int x1, int y1) {
 int code0 = computeRegionCode(x0, y0);
 int code1 = computeRegionCode(x1, y1);
 int accept = 0;
 while (1) {
 if (!(code0 | code1)) { // Both endpoints are inside
 accept = 1;
 break;
 } else if (code0 & code1) { // Both endpoints are outside
 break;
 } else { // Some part of the line is inside
 int x, y;
 int code = code0 ? code0 : code1;
 if (code & TOP) { // Point is above the window
 x = x0 + (x1 - x0) * (Y_MAX - y0) / (y1 - y0);
 y = Y_MAX;
 } else if (code & BOTTOM) { // Point is below the window
 x = x0 + (x1 - x0) * (Y_MIN - y0) / (y1 - y0);
 y = Y_MIN;
 } else if (code & RIGHT) { // Point is to the right of the window
 y = y0 + (y1 - y0) * (X_MAX - x0) / (x1 - x0);
 x = X_MAX;
 } else if (code & LEFT) { // Point is to the left of the window
 y = y0 + (y1 - y0) * (X_MIN - x0) / (x1 - x0);
 x = X_MIN;
 }
 if (code == code0) {
 x0 = x;
 y0 = y;
 code0 = computeRegionCode(x0, y0);
 } else {
 x1 = x;
 y1 = y;
 code1 = computeRegionCode(x1, y1);
 }
 }
 }
 if (accept) {
 glColor3f(1.0, 1.0, 1.0); // Set color to white
 glBegin(GL_LINES);
 glVertex2i(x0, y0);
 glVertex2i(x1, y1);
 glEnd();
 }
}
void display() {
 glClear(GL_COLOR_BUFFER_BIT);
 
 glColor3f(0.0, 1.0, 0.0); // Set color to green
 glBegin(GL_LINE_LOOP);
 glVertex2i(50, 50);
 glVertex2i(80, 90);
 glVertex2i(120, 50);
 glVertex2i(90, 20);
 glEnd();
 
 clipLine(50, 50, 80, 90);
 clipLine(80, 90, 120, 50);
 clipLine(120, 50, 90, 20);
 clipLine(90, 20, 50, 50);
 
 glFlush();
}
void init() {
 glClearColor(0.0, 0.0, 0.0, 1.0); // Set clear color to black
 gluOrtho2D(-150, 150, -150, 150); // Set orthographic projection
}
int main(int argc, char **argv) {
 glutInit(&argc, argv);
 glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
 glutInitWindowSize(500, 500); // Set window size
 glutInitWindowPosition(100, 100); // Set window position
 glutCreateWindow("Cohen-Sutherland Polygon Clipping");
 init();
 glutDisplayFunc(display);
 glutMainLoop();
 return 0;
}

//LAB-6

 
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
float vertices[4][2] = {
 {-25, -25}, // Bottom-left
 {25, -25}, // Bottom-right
 {25, 25}, // Top-right
 {-25, 25} // Top-left
};
void drawObject() {
 glBegin(GL_POLYGON);
 glColor3f(1.0, 0.0, 0.0); // Set color to red
 for (int i = 0; i < 4; i++) {
 glVertex2fv(vertices[i]);
 }
 glEnd();
}
void scale(float sx, float sy) {
 for (int i = 0; i < 4; i++) {
 vertices[i][0] *= sx;
 vertices[i][1] *= sy;
 }
}
void rotate(float angle, float px, float py) {
 float radians = angle * M_PI / 180.0;
 for (int i = 0; i < 4; i++) {
 float x = vertices[i][0];
 float y = vertices[i][1];
 vertices[i][0] = px + (x - px) * cos(radians) - (y - py) * sin(radians);
 vertices[i][1] = py + (x - px) * sin(radians) + (y - py) * cos(radians);
 }
}
void reflect(int axis) {
 // Axis: 0 - X-axis, 1 - Y-axis
 if (axis == 0) { // Reflection about X-axis
 for (int i = 0; i < 4; i++) {
 vertices[i][1] *= -1;
 }
 } else if (axis == 1) { // Reflection about Y-axis
 for (int i = 0; i < 4; i++) {
 vertices[i][0] *= -1;
 }
 }
}
void display() {
 glClear(GL_COLOR_BUFFER_BIT);
 drawObject();
 glFlush();
}
void handleKeypress(unsigned char key, int x, int y) {
 switch (key) {
 case 's': // Scale the object
 scale(1.5, 1.5);
 break;
 case 'r': // Rotate the object about an arbitrary point
 rotate(45, 0, 0); // Rotate 45 degrees about the origin
 break;
 case 'x': // Reflect the object about the X-axis
 reflect(0);
 break;
 case 'y': // Reflect the object about the Y-axis
 reflect(1);
 break;
 }
 glutPostRedisplay(); // Redraw the scene
}
void init() {
 glClearColor(1.0, 1.0, 1.0, 1.0); // Set clear color to white
 gluOrtho2D(-50, 50, -50, 50); // Set orthographic projection
}
int main(int argc, char **argv) {
 glutInit(&argc, argv);
 glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
 glutInitWindowSize(500, 500); // Set window size
 glutCreateWindow("2D Transformations");
 init();
 glutDisplayFunc(display);
 glutKeyboardFunc(handleKeypress);
 glutMainLoop();
 return 0;
}

//LAB - 7-1

//i) Bezier

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<SDL2/SDL.h>
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
int mousePosX , mousePosY ;
int xnew , ynew ;
void drawCircle(int xc, int yc, int x, int y)
{
SDL_RenderDrawPoint(renderer,xc+x,yc+y) ;
SDL_RenderDrawPoint(renderer,xc-x,yc+y);
SDL_RenderDrawPoint(renderer,xc+x,yc-y);
SDL_RenderDrawPoint(renderer,xc-x,yc-y);
SDL_RenderDrawPoint(renderer,xc+y,yc+x);
SDL_RenderDrawPoint(renderer,xc-y,yc+x);
SDL_RenderDrawPoint(renderer,xc+y,yc-x);
SDL_RenderDrawPoint(renderer,xc-y,yc-x);
}
void circleBres(int xc, int yc, int r)
{
int x = 0, y = r;
int d = 3 - 2 * r;
while (y >= x)
{
drawCircle(xc, yc, x, y);
x++;
if (d > 0)
{
y--;
d = d + 4 * (x - y) + 10;
}
else
d = d + 4 * x + 6;
drawCircle(xc, yc, x, y);
}
}
void bezierCurve(int x[] , int y[])
{
double xu = 0.0 , yu = 0.0 , u = 0.0 ;
int i = 0 ;
for(u = 0.0 ; u <= 1.0 ; u += 0.0001)
{
xu = pow(1-u,3)*x[0]+3*u*pow(1-u,2)*x[1]+3*pow(u,2)*(1-u)*x[2]
+pow(u,3)*x[3];
yu = pow(1-u,3)*y[0]+3*u*pow(1-u,2)*y[1]+3*pow(u,2)*(1-u)*y[2]
+pow(u,3)*y[3];
SDL_RenderDrawPoint(renderer , (int)xu , (int)yu) ;
}
}
int main(int argc, char* argv[])
{
if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
{
if(SDL_CreateWindowAndRenderer(640, 480, 0, &window, &renderer) == 0)
{
SDL_bool done = SDL_FALSE;
int i = 0 ;
int x[4] , y[4] , flagDrawn = 0 ;
while (!done)
{
SDL_Event event;
SDL_SetRenderDrawColor(renderer, 0, 0, 0, 
SDL_ALPHA_OPAQUE);
SDL_RenderClear(renderer);
SDL_SetRenderDrawColor(renderer, 255, 255, 255, 
SDL_ALPHA_OPAQUE);
if(i==4)
{
bezierCurve(x , y) ;
flagDrawn = 1 ;
}
SDL_SetRenderDrawColor(renderer, 128, 128, 128, 
SDL_ALPHA_OPAQUE);
circleBres(x[0] , y[0] , 8) ;
SDL_SetRenderDrawColor(renderer, 255, 0, 0, 
SDL_ALPHA_OPAQUE);
SDL_RenderDrawLine(renderer , x[0] , y[0] , x[1] , y[1]) ;
SDL_SetRenderDrawColor(renderer, 128, 128, 128, 
SDL_ALPHA_OPAQUE);
circleBres(x[1] , y[1] , 8) ;
SDL_SetRenderDrawColor(renderer, 255, 0, 0, 
SDL_ALPHA_OPAQUE);
SDL_RenderDrawLine(renderer , x[1] , y[1] , x[2] , y[2]) ;
SDL_SetRenderDrawColor(renderer, 128, 128, 128, 
SDL_ALPHA_OPAQUE);
circleBres(x[2] , y[2] , 8) ;
SDL_SetRenderDrawColor(renderer, 255, 0, 0, 
SDL_ALPHA_OPAQUE);
SDL_RenderDrawLine(renderer , x[2] , y[2] , x[3] , y[3]) ;
SDL_SetRenderDrawColor(renderer, 128, 128, 128, 
SDL_ALPHA_OPAQUE);
circleBres(x[3] , y[3] , 8) ;
if (SDL_PollEvent(&event))
{
if (event.type == SDL_QUIT)
{
done = SDL_TRUE;
}
if(event.type == SDL_MOUSEBUTTONDOWN)
{
/*If left mouse button down then store 
that point as control point*/
if(event.button.button == 
SDL_BUTTON_LEFT)
{
if(i < 4)
{
printf("Control 
Point(P%d):(%d,%d)\n"
,i,mousePosX,mousePosY) ;
x[i] = mousePosX ;
y[i] = mousePosY ;
i++ ;
}
}
}
if(event.type == SDL_MOUSEMOTION)
{
xnew = event.motion.x ;
ynew = event.motion.y ;
int j ;
if(flagDrawn == 1)
{
for(j = 0 ; j < i ; j++)
{
if((float)sqrt(abs(xnew-x[j]) * 
abs(xnew-x[j]) 
+ abs(ynew-y[j]) * 
abs(ynew-y[j])) < 8.0)
{
x[j] = xnew ;
y[j] = ynew ;
printf("Changed Control 
Point(P%d):(%d,%d)\n"
,j,xnew,ynew) ;
}
}
}
mousePosX = xnew ;
mousePosY = ynew ;
}
}
SDL_RenderPresent(renderer);
}
}
if (renderer)
{
SDL_DestroyRenderer(renderer);
}
if (window)
{
SDL_DestroyWindow(window);
}
}
SDL_Quit();
return 0;
}

//LAB - 7-2

//ii) Koch Curve

#include <GL/glut.h>
#include <math.h>
void drawLine(float x1, float y1, float x2, float y2) {
 glBegin(GL_LINES);
 glVertex2f(x1, y1);
 glVertex2f(x2, y2);
 glEnd();
}
void kochCurve(float x1, float y1, float x2, float y2, int iterations) {
 if (iterations == 0) {
 drawLine(x1, y1, x2, y2);
 return;
 }
 float deltaX = (x2 - x1) / 3.0;
 float deltaY = (y2 - y1) / 3.0;
 float xA = x1 + deltaX;
 float yA = y1 + deltaY;
 float xC = x2 - deltaX;
 float yC = y2 - deltaY;
 float xB = xA + (xC - xA) * 0.5 - (yC - yA) * sqrt(3) / 2.0;
 float yB = yA + (yC - yA) * 0.5 + (xC - xA) * sqrt(3) / 2.0;
 kochCurve(x1, y1, xA, yA, iterations - 1);
 kochCurve(xA, yA, xB, yB, iterations - 1);
 kochCurve(xB, yB, xC, yC, iterations - 1);
 kochCurve(xC, yC, x2, y2, iterations - 1);
}
void display() {
 glClear(GL_COLOR_BUFFER_BIT);
 glColor3f(1.0, 1.0, 1.0); // Set line color to white
 float x1 = -0.5, y1 = 0.0;
 float x2 = 0.5, y2 = 0.0;
 int iterations = 4;
 kochCurve(x1, y1, x2, y2, iterations);
 glFlush();
}
void init() {
 glClearColor(0.0, 0.0, 0.0, 0.0); // Set background color to black
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 gluOrtho2D(-1.0, 1.0, -1.0, 1.0); // Set orthographic projection
}
int main(int argc, char **argv) {
 glutInit(&argc, argv);
 glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
 glutInitWindowSize(500, 500);
 glutCreateWindow("Koch Curve");
 init();
 glutDisplayFunc(display);
 glutMainLoop();
 return 0;
}

//LAB - 8


#include <GL/glut.h>
float squareX = 0.0; // Initial x position of the square
void drawSquare() {
 glBegin(GL_QUADS);
 glColor3f(1.0, 0.0, 0.0); // Set color to red
 glVertex2f(squareX, 50);
 glVertex2f(squareX + 50, 50);
 glVertex2f(squareX + 50, 100);
 glVertex2f(squareX, 100);
 glEnd();
}
void display() {
 glClear(GL_COLOR_BUFFER_BIT);
 drawSquare();
 glFlush();
}
void update(int value) {
 
 squareX += 2.0;
 
 
 if (squareX > glutGet(GLUT_WINDOW_WIDTH))
 squareX = -50.0;
 
 
 glutPostRedisplay();
 
 
 glutTimerFunc(30, update, 0);
}
void init() {
 glClearColor(1.0, 1.0, 1.0, 1.0); // Set clear color to white
 gluOrtho2D(0, 400, 0, 200); // Set orthographic projection
}
int main(int argc, char **argv) {
 glutInit(&argc, argv);
 glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
 glutInitWindowSize(400, 200);
 glutCreateWindow("Animation");
 init();
 glutDisplayFunc(display);
 glutTimerFunc(0, update, 0); // Start the animation timer
 glutMainLoop();
 return 0;
}



