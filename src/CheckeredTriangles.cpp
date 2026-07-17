// =============================================================================
// CheckeredTriangles.cpp  —  Part 1
//
// Original: textured triangles using a 2x2 checkered pattern.
//
// Added features:
//   Spin 360 degrees continuously via timer
//   P       — pause spinning
//   C       — continue spinning
//   U       — move image up
//   D       — move image down
//   L       — move image left
//   R       — move image right
//   +       — zoom in
//   -       — zoom out
// =============================================================================

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cstdlib>

// -----------------------------------------------------------------------------
// Texture: 2x2 red/yellow checkered pattern
// -----------------------------------------------------------------------------
#define red     {0xff, 0x00, 0x00}
#define yellow  {0xff, 0xff, 0x00}
GLubyte texture[][3] = {
    red, yellow,
    yellow, red,
};

// -----------------------------------------------------------------------------
// State variables
// -----------------------------------------------------------------------------
static float g_angle    = 0.0f;   // current rotation angle (degrees)
static bool  g_spinning = true;   // true = spinning, false = paused
static float g_offsetX  = 0.0f;   // horizontal translation
static float g_offsetY  = 0.0f;   // vertical translation
static float g_zoom     = 1.0f;   // zoom scale factor

// -----------------------------------------------------------------------------
// reshape: fixes camera and uploads texture on window resize.
// -----------------------------------------------------------------------------
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

// -----------------------------------------------------------------------------
// display: clears and draws three textured triangles with current transforms.
// -----------------------------------------------------------------------------
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();

    // Apply zoom, translation, and rotation to the entire scene
    glScalef(g_zoom, g_zoom, g_zoom);
    glTranslatef(g_offsetX, g_offsetY, 0.0f);
    glRotatef(g_angle, 0.0f, 0.0f, 1.0f);   // spin around Z axis

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

// -----------------------------------------------------------------------------
// timer: advances spin angle and requests a redraw at ~60 fps.
// -----------------------------------------------------------------------------
void timer(int v) {
    if (g_spinning) {
        g_angle += 2.0f;            // 2 degrees per frame
        if (g_angle >= 360.0f)
            g_angle -= 360.0f;
        glutPostRedisplay();
    }
    glutTimerFunc(1000 / 60, timer, v);
}

// -----------------------------------------------------------------------------
// keyboard: handles all key inputs.
// -----------------------------------------------------------------------------
void keyboard(unsigned char key, int /*x*/, int /*y*/) {
    const float MOVE_STEP = 0.2f;
    const float ZOOM_STEP = 0.1f;

    switch (key) {
        case 'p': case 'P': g_spinning = false; break;          // pause
        case 'c': case 'C': g_spinning = true;  break;          // continue
        case 'u': case 'U': g_offsetY += MOVE_STEP; break;      // up
        case 'd': case 'D': g_offsetY -= MOVE_STEP; break;      // down
        case 'l': case 'L': g_offsetX -= MOVE_STEP; break;      // left
        case 'r': case 'R': g_offsetX += MOVE_STEP; break;      // right
        case '+': g_zoom += ZOOM_STEP; break;                    // zoom in
        case '-': g_zoom = (g_zoom > ZOOM_STEP) ?               // zoom out
                           g_zoom - ZOOM_STEP : ZOOM_STEP; break;
        case 27: exit(0); break;                                 // ESC
    }
    glutPostRedisplay();
}

// -----------------------------------------------------------------------------
// main
// -----------------------------------------------------------------------------
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
