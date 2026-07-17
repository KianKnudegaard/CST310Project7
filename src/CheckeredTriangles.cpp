#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cstdlib>

#define red     {0xff, 0x00, 0x00}
#define yellow  {0xff, 0xff, 0x00}
GLubyte texture[][3] = {
    red, yellow,
    yellow, red,
};
static float g_angle    = 0.0f;
static bool  g_spinning = true; 
static float g_offsetX  = 0.0f;  
static float g_offsetY  = 0.0f; 
static float g_zoom     = 1.0f;   

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(80, GLfloat(width) / height, 1, 40);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(2, -1, 5, 0, 0, 0, 0, 1, 0);

    glEnable(GL_TEXTURE_2D);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 3,
                 2, 2,
                 0,
                 GL_RGB,
                 GL_UNSIGNED_BYTE,
                 texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();

    glScalef(g_zoom, g_zoom, g_zoom);
    glTranslatef(g_offsetX, g_offsetY, 0.0f);
    glRotatef(g_angle, 0.0f, 0.0f, 1.0f);  

    glBegin(GL_TRIANGLES);
        glTexCoord2f(0.5, 1.0);  glVertex2f(-3,  3);
        glTexCoord2f(0.0, 0.0);  glVertex2f(-3,  0);
        glTexCoord2f(1.0, 0.0);  glVertex2f( 0,  0);

        glTexCoord2f(4,   8);    glVertex2f( 3,  3);
        glTexCoord2f(0.0, 0.0);  glVertex2f( 0,  0);
        glTexCoord2f(8,   0.0);  glVertex2f( 3,  0);

        glTexCoord2f(5,   5);    glVertex2f( 0,  0);
        glTexCoord2f(0.0, 0.0);  glVertex2f(-1.5,-3);
        glTexCoord2f(4,   0.0);  glVertex2f( 1.5,-3);
    glEnd();

    glPopMatrix();
    glFlush();
}

void timer(int v) {
    if (g_spinning) {
        g_angle += 2.0f;            
        if (g_angle >= 360.0f)
            g_angle -= 360.0f;
        glutPostRedisplay();
    }
    glutTimerFunc(1000 / 60, timer, v);
}

void keyboard(unsigned char key, int /*x*/, int /*y*/) {
    const float MOVE_STEP = 0.2f;
    const float ZOOM_STEP = 0.1f;

    switch (key) {
        case 'p': case 'P': g_spinning = false; break;          
        case 'c': case 'C': g_spinning = true;  break;        
        case 'u': case 'U': g_offsetY += MOVE_STEP; break;     
        case 'd': case 'D': g_offsetY -= MOVE_STEP; break;      
        case 'l': case 'L': g_offsetX -= MOVE_STEP; break;     
        case 'r': case 'R': g_offsetX += MOVE_STEP; break;     
        case '+': g_zoom += ZOOM_STEP; break;          
        case '-': g_zoom = (g_zoom > ZOOM_STEP) ?             
                           g_zoom - ZOOM_STEP : ZOOM_STEP; break;
        case 27: exit(0); break;                         
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(520, 390);
    glutCreateWindow("Textured Triangles");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(1000 / 60, timer, 0);
    glutMainLoop();
}
