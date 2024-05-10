// lab 2
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

int xi, yi, xf, yf; // Coordinates of line endpoints
int quadrant;       // Quadrant in which the line lies

// Function to handle mouse click events
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        xi = x - 250; // Adjusting coordinates to center
        yi = 250 - y; // Adjusting coordinates to center
    }
    else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        xf = x - 250; // Adjusting coordinates to center
        yf = 250 - y; // Adjusting coordinates to center
        glutPostRedisplay();
    }
}

// Function to calculate the quadrant in which the line lies
void calculateQuadrant() {
    if (xi >= 0 && xf >= 0) {
        if (yi >= 0 && yf >= 0)
            quadrant = 1;
        else if (yi < 0 && yf < 0)
            quadrant = 4;
        else
            quadrant = 0;
    }
    else if (xi < 0 && xf < 0) {
        if (yi >= 0 && yf >= 0)
            quadrant = 2;
        else if (yi < 0 && yf < 0)
            quadrant = 3;
        else
            quadrant = 0;
    }
    else {
        quadrant = 0;
    }
}

// Function to draw a simple line using DDA algorithm
void drawSimpleLineDDA(int x1, int y1, int x2, int y2) {
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    glVertex2i(x1, y1);
    glVertex2i(x2, y2);
    glEnd();
}

// Function to draw a dotted line using DDA algorithm
void drawDottedLineDDA(int x1, int y1, int x2, int y2) {
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POINTS);
    float dx = x2 - x1;
    float dy = y2 - y1;
    float steps = fmax(abs(dx), abs(dy));
    float xIncrement = dx / steps;
    float yIncrement = dy / steps;
    float x = x1, y = y1;
    for (int i = 0; i < steps; i++) {
        if (i % 2 == 0) // Draw only every second point
            glVertex2i(round(x), round(y));
        x += xIncrement;
        y += yIncrement;
    }
    glEnd();
}

// Function to draw a dashed line using DDA algorithm
void drawDashedLineDDA(int x1, int y1, int x2, int y2) {
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    float dx = x2 - x1;
    float dy = y2 - y1;
    float steps = fmax(abs(dx), abs(dy));
    float xIncrement = dx / steps;
    float yIncrement = dy / steps;
    float x = x1, y = y1;
    int counter = 0;
    for (int i = 0; i < steps; i++) {
        if (counter % 10 < 5) { // Draw only for 5 consecutive points
            glVertex2i(round(x), round(y));
            counter++;
        }
        else {
            counter++;
        }
        x += xIncrement;
        y += yIncrement;
    }
    glEnd();
}

// Function to draw a solid line using Bresenham algorithm
void drawSolidLineBresenham(int x1, int y1, int x2, int y2) {
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POINTS);
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int x, y;
    int p = 2 * dy - dx;
    int twoDy = 2 * dy;
    int twoDyMinusDx = 2 * (dy - dx);

    if (x1 > x2) {
        x = x2;
        y = y2;
        x2 = x1;
    } else {
        x = x1;
        y = y1;
    }
    glVertex2i(x, y);

    while (x < x2) {
        x++;
        if (p < 0) {
            p += twoDy;
        } else {
            y++;
            p += twoDyMinusDx;
        }
        glVertex2i(x, y);
    }
    glEnd();
}

// Function to draw the scene
void drawScene(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    calculateQuadrant();

    switch (quadrant) {
        case 1:
            drawSimpleLineDDA(xi, yi, xf, yf);
            break;
        case 2:
            drawSolidLineBresenham(xi, yi, xf, yf);
            break;
        case 3:
            drawDottedLineDDA(xi, yi, xf, yf);
            break;
        case 4:
            drawDashedLineDDA(xi, yi, xf, yf);
            break;
        default:
            break;
    }

    glFlush();
}

// Function to initialize OpenGL
void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-250.0, 250.0, -250.0, 250.0);
}

// Main function
int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Line Drawing Algorithms");
    init();
    glutMouseFunc(mouse);
    glutDisplayFunc(drawScene);
    glutMainLoop();
    return 0;
}


// lab 3

#include <GL/glut.h>
#include <stdio.h>

int xc, yc, radius; // Center coordinates and radius of the circle

// Function to handle mouse click events
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        xc = x - 250; // Adjusting coordinates to center
        yc = 250 - y; // Adjusting coordinates to center
        glutPostRedisplay();
    }
}

// Function to draw a circle using Bresenham algorithm
void drawCircleBresenham(int xc, int yc, int radius) {
    int x = 0, y = radius;
    int d = 3 - 2 * radius;

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POINTS);
    glVertex2i(xc + x, yc + y);
    glVertex2i(xc - x, yc + y);
    glVertex2i(xc + x, yc - y);
    glVertex2i(xc - x, yc - y);
    glVertex2i(xc + y, yc + x);
    glVertex2i(xc - y, yc + x);
    glVertex2i(xc + y, yc - x);
    glVertex2i(xc - y, yc - x);

    while (y >= x) {
        x++;

        if (d > 0) {
            y--;
            d = d + 4 * (x - y) + 10;
        } else {
            d = d + 4 * x + 6;
        }

        glVertex2i(xc + x, yc + y);
        glVertex2i(xc - x, yc + y);
        glVertex2i(xc + x, yc - y);
        glVertex2i(xc - x, yc - y);
        glVertex2i(xc + y, yc + x);
        glVertex2i(xc - y, yc + x);
        glVertex2i(xc + y, yc - x);
        glVertex2i(xc - y, yc - x);
    }
    glEnd();
}

// Function to draw the scene
void drawScene(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    drawCircleBresenham(xc, yc, radius);
    glFlush();
}

// Function to initialize OpenGL
void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-250.0, 250.0, -250.0, 250.0);
}

// Main function
int main(int argc, char **argv) {
    printf("Enter center coordinates (xc yc): ");
    scanf("%d %d", &xc, &yc);
    printf("Enter radius: ");
    scanf("%d", &radius);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Circle Drawing Algorithm");
    init();
    glutMouseFunc(mouse);
    glutDisplayFunc(drawScene);
    glutMainLoop();
    return 0;
}


// lab 4

#include <GL/glut.h>
#include <stdio.h>

int seedX, seedY; // Coordinates of the seed point
int fillChoice = 0; // 0 for flood fill, 1 for boundary fill

// Function to handle mouse click events
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        seedX = x - 250; // Adjusting coordinates to center
        seedY = 250 - y; // Adjusting coordinates to center
        glutPostRedisplay();
    }
}

// Function to draw the boundary of the polygon
void drawPolygon() {
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex2i(-100, -100);
    glVertex2i(-100, 100);
    glVertex2i(100, 100);
    glVertex2i(100, -100);
    glEnd();
}

// Function to implement flood fill (seed fill) algorithm
void floodFill(int x, int y, float fillColor[3], float interiorColor[3]) {
    float currentColor[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, currentColor);

    if (currentColor[0] == interiorColor[0] && currentColor[1] == interiorColor[1] && currentColor[2] == interiorColor[2]) {
        glColor3fv(fillColor);
        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();

        floodFill(x + 1, y, fillColor, interiorColor);
        floodFill(x - 1, y, fillColor, interiorColor);
        floodFill(x, y + 1, fillColor, interiorColor);
        floodFill(x, y - 1, fillColor, interiorColor);
    }
}

// Function to implement boundary fill algorithm
void boundaryFill(int x, int y, float fillColor[3], float borderColor[3]) {
    float currentColor[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, currentColor);

    if (currentColor[0] != borderColor[0] || currentColor[1] != borderColor[1] || currentColor[2] != borderColor[2]) {
        if (currentColor[0] != fillColor[0] || currentColor[1] != fillColor[1] || currentColor[2] != fillColor[2]) {
            glColor3fv(fillColor);
            glBegin(GL_POINTS);
            glVertex2i(x, y);
            glEnd();

            boundaryFill(x + 1, y, fillColor, borderColor);
            boundaryFill(x - 1, y, fillColor, borderColor);
            boundaryFill(x, y + 1, fillColor, borderColor);
            boundaryFill(x, y - 1, fillColor, borderColor);
        }
    }
}

// Function to display the menu and handle menu selection
void menu(int value) {
    fillChoice = value;
    glutPostRedisplay();
}

// Function to handle keyboard input
void keyboard(unsigned char key, int x, int y) {
    if (key == 'f') {
        fillChoice = 0; // Flood fill
        glutPostRedisplay();
    } else if (key == 'b') {
        fillChoice = 1; // Boundary fill
        glutPostRedisplay();
    }
}

// Function to draw the scene
void drawScene(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    drawPolygon();

    float fillColor[] = {1.0, 0.0, 0.0}; // Red color for filling
    float borderColor[] = {1.0, 1.0, 1.0}; // White color for boundary

    if (fillChoice == 0) {
        floodFill(seedX, seedY, fillColor, borderColor);
    } else if (fillChoice == 1) {
        boundaryFill(seedX, seedY, fillColor, borderColor);
    }

    glFlush();
}

// Function to initialize OpenGL
void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-250.0, 250.0, -250.0, 250.0);

    // Creating the menu
    glutCreateMenu(menu);
    glutAddMenuEntry("Flood Fill", 0);
    glutAddMenuEntry("Boundary Fill", 1);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

// Main function
int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Polygon Filling Algorithms");
    init();
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(drawScene);
    glutMainLoop();
    return 0;
}


//  lab 5 

#include <GL/glut.h>
#include <stdio.h>

#define INSIDE 0
#define LEFT 1
#define RIGHT 2
#define BOTTOM 4
#define TOP 8

int winLeft = 100, winRight = 400, winBottom = 100, winTop = 400; // Window coordinates
int vpLeft = 50, vpRight = 450, vpBottom = 50, vpTop = 450; // Viewport coordinates

int clip(int x, int y) {
    int code = INSIDE;

    if (x < winLeft)
        code |= LEFT;
    else if (x > winRight)
        code |= RIGHT;
    if (y < winBottom)
        code |= BOTTOM;
    else if (y > winTop)
        code |= TOP;

    return code;
}

void cohenSutherlandLineClip(int x1, int y1, int x2, int y2) {
    int code1, code2;
    int accept = 0, done = 0;

    code1 = clip(x1, y1);
    code2 = clip(x2, y2);

    do {
        if (!(code1 | code2)) {
            accept = 1;
            done = 1;
        } else if (code1 & code2) {
            done = 1;
        } else {
            int x, y;
            int codeOut = code1 ? code1 : code2;

            if (codeOut & TOP) {
                x = x1 + (x2 - x1) * (winTop - y1) / (y2 - y1);
                y = winTop;
            } else if (codeOut & BOTTOM) {
                x = x1 + (x2 - x1) * (winBottom - y1) / (y2 - y1);
                y = winBottom;
            } else if (codeOut & RIGHT) {
                y = y1 + (y2 - y1) * (winRight - x1) / (x2 - x1);
                x = winRight;
            } else if (codeOut & LEFT) {
                y = y1 + (y2 - y1) * (winLeft - x1) / (x2 - x1);
                x = winLeft;
            }

            if (codeOut == code1) {
                x1 = x;
                y1 = y;
                code1 = clip(x1, y1);
            } else {
                x2 = x;
                y2 = y;
                code2 = clip(x2, y2);
            }
        }
    } while (!done);

    if (accept) {
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_LINES);
        glVertex2i(x1, y1);
        glVertex2i(x2, y2);
        glEnd();
    }
}

void drawWindow() {
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex2i(winLeft, winBottom);
    glVertex2i(winLeft, winTop);
    glVertex2i(winRight, winTop);
    glVertex2i(winRight, winBottom);
    glEnd();
}

void drawViewport() {
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex2i(vpLeft, vpBottom);
    glVertex2i(vpLeft, vpTop);
    glVertex2i(vpRight, vpTop);
    glVertex2i(vpRight, vpBottom);
    glEnd();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Clip the line from (50, 50) to the clicked position
        cohenSutherlandLineClip(50, 50, x, 500 - y); // 500-y to adjust OpenGL coordinates
        glutPostRedisplay();
    }
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 'q') {
        exit(0);
    }
}

void drawScene(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    drawWindow();
    drawViewport();
    glFlush();
}

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 500.0, 0.0, 500.0);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Cohen-Sutherland Polygon Clipping");
    init();
    glutDisplayFunc(drawScene);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}


//lab 6

#include <GL/glut.h>
#include <math.h>

float points[3][2] = {{-50, -50}, {50, -50}, {0, 50}}; // Initial coordinates of the object

void drawObject() {
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_TRIANGLES);
    glVertex2f(points[0][0], points[0][1]);
    glVertex2f(points[1][0], points[1][1]);
    glVertex2f(points[2][0], points[2][1]);
    glEnd();
}

void drawAxis() {
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_LINES);
    glVertex2f(-200, 0);
    glVertex2f(200, 0);
    glVertex2f(0, -200);
    glVertex2f(0, 200);
    glEnd();
}

void scale(float sx, float sy) {
    for (int i = 0; i < 3; i++) {
        points[i][0] *= sx;
        points[i][1] *= sy;
    }
}

void rotate(float angle, float cx, float cy) {
    angle = angle * (M_PI / 180); // Convert angle from degrees to radians

    for (int i = 0; i < 3; i++) {
        float x = points[i][0] - cx;
        float y = points[i][1] - cy;

        points[i][0] = x * cos(angle) - y * sin(angle) + cx;
        points[i][1] = x * sin(angle) + y * cos(angle) + cy;
    }
}

void reflect(char axis) {
    if (axis == 'x') {
        for (int i = 0; i < 3; i++) {
            points[i][1] *= -1;
        }
    } else if (axis == 'y') {
        for (int i = 0; i < 3; i++) {
            points[i][0] *= -1;
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxis();
    drawObject();
    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-200, 200, -200, 200);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("2D Transformations");

    init();

    printf("Enter the transformation to perform:\n");
    printf("1. Scaling\n");
    printf("2. Rotation about arbitrary point\n");
    printf("3. Reflection (x or y)\n");
    int choice;
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Enter scaling factors (sx sy): ");
            float sx, sy;
            scanf("%f %f", &sx, &sy);
            scale(sx, sy);
            break;
        case 2:
            printf("Enter rotation angle (in degrees): ");
            float angle;
            scanf("%f", &angle);
            printf("Enter arbitrary point (cx cy): ");
            float cx, cy;
            scanf("%f %f", &cx, &cy);
            rotate(angle, cx, cy);
            break;
        case 3:
            printf("Enter reflection axis (x or y): ");
            char axis;
            scanf(" %c", &axis);
            reflect(axis);
            break;
        default:
            printf("Invalid choice\n");
            return 1;
    }

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}


//lab 7 

//bezier curve 

#include <GL/glut.h>
#include <stdio.h>

int nCtrlPts = 4; // Number of control points
GLfloat ctrlPts[4][3] = {{-40, -40, 0}, {-10, 40, 0}, {10, -40, 0}, {40, 40, 0}}; // Control points

void drawBezierCurve() {
    glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, nCtrlPts, &ctrlPts[0][0]);
    glEnable(GL_MAP1_VERTEX_3);

    glLineWidth(2.0);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= 100; i++)
        glEvalCoord1f((GLfloat) i / 100.0);
    glEnd();
    glFlush();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawBezierCurve();
    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-100.0, 100.0, -100.0, 100.0);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bezier Curve Fractal");

    init();

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}


// koch curve 

#include <GL/glut.h>
#include <stdio.h>

typedef struct {
    float x, y;
} Point2D;

Point2D v[3] = {{-50, -50}, {0, 50}, {50, -50}}; // Initial vertices of the triangle

void drawKochCurve(Point2D a, Point2D b, int n) {
    if (n == 0) {
        glBegin(GL_LINES);
        glVertex2f(a.x, a.y);
        glVertex2f(b.x, b.y);
        glEnd();
    } else {
        Point2D mid[5];
        mid[0].x = (2 * a.x + b.x) / 3;
        mid[0].y = (2 * a.y + b.y) / 3;
        mid[1].x = (a.x + b.x) / 2 + (b.y - a.y) / (2 * sqrt(3));
        mid[1].y = (a.y + b.y) / 2 - (b.x - a.x) / (2 * sqrt(3));
        mid[2].x = (a.x + 2 * b.x) / 3;
        mid[2].y = (a.y + 2 * b.y) / 3;
        mid[3].x = (a.x + b.x) / 2 - (b.y - a.y) / (2 * sqrt(3));
        mid[3].y = (a.y + b.y) / 2 + (b.x - a.x) / (2 * sqrt(3));

        drawKochCurve(a, mid[0], n - 1);
        drawKochCurve(mid[0], mid[1], n - 1);
        drawKochCurve(mid[1], mid[2], n - 1);
        drawKochCurve(mid[2], mid[3], n - 1);
        drawKochCurve(mid[3], b, n - 1);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    drawKochCurve(v[0], v[1], 3);
    drawKochCurve(v[1], v[2], 3);
    drawKochCurve(v[2], v[0], 3);
    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-100.0, 100.0, -100.0, 100.0);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Koch Curve Fractal");

    init();

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}


// lab 8 

#include <GL/glut.h>
#include <stdio.h>

float squareX = -50.0; // Initial x-coordinate of the square
float squareY = -50.0; // Initial y-coordinate of the square
float speed = 1.0;      // Speed of the square

void drawSquare() {
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex2f(squareX, squareY);
    glVertex2f(squareX + 20, squareY);
    glVertex2f(squareX + 20, squareY + 20);
    glVertex2f(squareX, squareY + 20);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawSquare();
    glFlush();
}

void update(int value) {
    // Update the position of the square
    squareX += speed;
    squareY += speed;

    // Reverse direction when hitting window boundaries
    if (squareX > 100 || squareX < -100)
        speed *= -1;
    if (squareY > 100 || squareY < -100)
        speed *= -1;

    glutPostRedisplay();
    glutTimerFunc(16, update, 0); // 60 FPS
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-100.0, 100.0, -100.0, 100.0);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Simple Animation");

    init();

    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);
    glutMainLoop();
    return 0;
}

