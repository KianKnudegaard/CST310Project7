#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cmath>

namespace Cube {
    const int NUM_VERTICES = 8;
    const int NUM_FACES    = 6;

    GLint vertices[NUM_VERTICES][3] = {
        {0,0,0},{0,0,1},{0,1,0},{0,1,1},
        {1,0,0},{1,0,1},{1,1,0},{1,1,1}
    };
    GLint faces[NUM_FACES][4] = {
        {1,5,7,3},{5,4,6,7},{4,0,2,6},
        {3,7,6,2},{0,1,3,2},{0,4,5,1}
    };
    GLfloat vertexColors[NUM_VERTICES][3] = {
        {0,0,0},{0,0,1},{0,1,0},{0,1,1},
        {1,0,0},{1,0,1},{1,1,0},{1,1,1}
    };

    void draw(float brightness = 1.0f) {
        glBegin(GL_QUADS);
        for (int i = 0; i < NUM_FACES; i++) {
            for (int j = 0; j < 4; j++) {
                GLfloat* c = vertexColors[faces[i][j]];
                glColor3f(c[0]*brightness, c[1]*brightness, c[2]*brightness);
                glVertex3iv((GLint*)&vertices[faces[i][j]]);
            }
        }
        glEnd();
    }
}

void drawColorCube(float r, float g, float b, float brightness) {
    float R=r*brightness, G=g*brightness, B=b*brightness;
    glBegin(GL_QUADS);
        // Front
        glColor3f(R,G,B);
        glVertex3f(0,0,1); glVertex3f(1,0,1);
        glVertex3f(1,1,1); glVertex3f(0,1,1);
        // Back
        glColor3f(R*0.7f,G*0.7f,B*0.7f);
        glVertex3f(1,0,0); glVertex3f(0,0,0);
        glVertex3f(0,1,0); glVertex3f(1,1,0);
        // Left
        glColor3f(R*0.8f,G*0.8f,B*0.8f);
        glVertex3f(0,0,0); glVertex3f(0,0,1);
        glVertex3f(0,1,1); glVertex3f(0,1,0);
        // Right
        glColor3f(R*0.9f,G*0.9f,B*0.9f);
        glVertex3f(1,0,1); glVertex3f(1,0,0);
        glVertex3f(1,1,0); glVertex3f(1,1,1);
        // Top
        glColor3f(R,G*1.1f>1?1:G*1.1f,B);
        glVertex3f(0,1,1); glVertex3f(1,1,1);
        glVertex3f(1,1,0); glVertex3f(0,1,0);
        // Bottom
        glColor3f(R*0.5f,G*0.5f,B*0.5f);
        glVertex3f(0,0,0); glVertex3f(1,0,0);
        glVertex3f(1,0,1); glVertex3f(0,0,1);
    glEnd();
}

void drawWall(float x, float r, float g, float b) {
    glBegin(GL_QUADS);
        glColor3f(r, g, b);
        glVertex3f(x, -3, -3);
        glVertex3f(x, -3,  5);
        glVertex3f(x,  5,  5);
        glVertex3f(x,  5, -3);
    glEnd();
}

static float  g_u        = 0.0f;    
static bool   g_flying   = true;   
static bool   g_rotating = false;   
static float  g_rotAngle = 0.0f;   
static float  g_offsetY  = 0.0f;    
static float  g_zoom     = 1.0f;    

static float g_cubeX[3]  = { -2.0f, 0.5f, 2.0f };
static float g_cubeVX[3] = {  0.03f,-0.02f, 0.025f };
const  float WALL_LEFT    = -3.5f;
const  float WALL_RIGHT   =  3.5f;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();

    glScalef(g_zoom, g_zoom, g_zoom);
    glTranslatef(0.0f, g_offsetY, 0.0f);
    if (g_rotating)
        glRotatef(g_rotAngle, 0.0f, 1.0f, 0.0f);

    Cube::draw(1.0f);

    drawWall(WALL_LEFT,  0.3f, 0.6f, 0.6f);

    drawWall(WALL_RIGHT, 0.6f, 0.3f, 0.6f);

    glPushMatrix();
    glTranslatef(g_cubeX[0], -1.5f, 0.3f);
    drawColorCube(0.0f, 1.0f, 1.0f, 1.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(g_cubeX[1], 1.0f, 0.5f);
    drawColorCube(1.0f, 0.0f, 1.0f, 0.6f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(g_cubeX[2], -0.5f, -0.5f);
    drawColorCube(1.0f, 0.5f, 0.0f, 1.2f);
    glPopMatrix();

    glPopMatrix();
    glFlush();
    glutSwapBuffers();
}

void timer(int v) {
    if (g_flying) {
        g_u += 0.01f;
        glLoadIdentity();
        gluLookAt(
            8*cos(g_u),  7*cos(g_u)-1,  4*cos(g_u/3)+2,
            0.5f, 0.5f, 0.5f,
            cos(g_u), 1.0f, 0.0f
        );
        for (int i = 0; i < 3; i++) {
            g_cubeX[i] += g_cubeVX[i];
            if (g_cubeX[i] < WALL_LEFT + 0.5f) { g_cubeX[i] = WALL_LEFT + 0.5f; g_cubeVX[i] = fabsf(g_cubeVX[i]); }
            if (g_cubeX[i] > WALL_RIGHT - 1.5f) { g_cubeX[i] = WALL_RIGHT - 1.5f; g_cubeVX[i] = -fabsf(g_cubeVX[i]); }
        }
    }

    if (g_rotating) {
        g_rotAngle += 1.0f;
        if (g_rotAngle >= 360.0f) g_rotAngle -= 360.0f;
    }

    glutPostRedisplay();
    glutTimerFunc(1000 / 60, timer, v);
}

void keyboard(unsigned char key, int /*x*/, int /*y*/) {
    const float MOVE_STEP = 0.1f;
    const float ZOOM_STEP = 0.1f;

    switch (key) {
        case 'r': case 'R': g_rotating = !g_rotating; break;    
        case 's': case 'S': g_flying   = false; break;         
        case 'c': case 'C': g_flying   = true;  break;           
        case 'u': case 'U':
            if (!g_flying) g_offsetY += MOVE_STEP;
            break;
        case 'd': case 'D':
            if (!g_flying) g_offsetY -= MOVE_STEP;
            break;
        case '+': g_zoom += ZOOM_STEP; break;
        case '-': g_zoom = (g_zoom > ZOOM_STEP) ?
                           g_zoom - ZOOM_STEP : ZOOM_STEP; break;
        case 27: exit(0); break;
    }
    glutPostRedisplay();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, GLfloat(w) / GLfloat(h), 0.5, 40.0);
    glMatrixMode(GL_MODELVIEW);
}

void init() {
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("The RGB Color Cube — Extended");
    glutReshapeFunc(reshape);
    glutTimerFunc(100, timer, 0);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    init();
    glutMainLoop();
}
