#include <GL/glut.h>

void Pe() {
    glPushMatrix();
        glScalef(0.2f, 1.0f, 0.2f);  // Deixa o cubo alto e estreito como um pé de cadeira
        glutSolidCube(1.0);
    glPopMatrix();
}

void Assento(){
    glPushMatrix();
        glScalef(1.2f, 0.1f, 1.2f); // Transformei em um plano
        glutSolidCube(1.0);
    glPopMatrix();
}

void Mesa(){
    glPushMatrix();
        glScalef(6.0f, 0.1f, 2.0f); // Transformei em um plano
        glutSolidCube(1.0);
    glPopMatrix();
}

void Cadeira() {
    // Pés
    glPushMatrix(); glTranslatef( 0.5f, -0.5f,  0.5f); Pe(); glPopMatrix(); // frente dir
    glPushMatrix(); glTranslatef(-0.5f, -0.5f,  0.5f); Pe(); glPopMatrix(); // frente esq
    glPushMatrix(); glTranslatef( 0.5f, -0.5f, -0.5f); Pe(); glPopMatrix(); // trás dir
    glPushMatrix(); glTranslatef(-0.5f, -0.5f, -0.5f); Pe(); glPopMatrix(); // trás esq

    // Assento
    Assento();

    // Encosto
    glPushMatrix();
        glTranslatef(0.0f, 0.5f, -0.55f);
        glRotatef(90, 1.0f, 0.0f, 0.0f);
        Assento();
    glPopMatrix();

}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Câmera
    gluLookAt(
        3.0, 3.0, 5.0,   // posição da câmera 
        0.0, 0.0, 0.0,   // olha para a origem
        0.0, 1.0, 0.0    // vetor para cima
    );
    
    Mesa();

    // Cadeira dianteira direita
    glPushMatrix();
        glTranslatef(2.0f, 0.0f, -1.0f); 
        Cadeira();
    glPopMatrix();

    // Cadeira traseira direita
    glPushMatrix();
        glTranslatef(2.0f, 0.0f, 2.0f);
        glRotatef(180, 0.0f, 1.0f, 0.0f); 
        Cadeira();
    glPopMatrix();

    // Cadeira dianteira esquerda
    glPushMatrix();
        glTranslatef(-2.0f, 0.0f, -1.0f); 
        Cadeira();
    glPopMatrix();

    // Cadeira traseira esquerda
    glPushMatrix();
        glTranslatef(-1.5f, 0.0f, 2.0f); 
        glRotatef(180, 0.0f, 1.0f, 0.0f);
        Cadeira();
    glPopMatrix();

    glFlush();
}

void reshape(GLint w, GLint h) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    GLfloat aspect = GLfloat(w) / GLfloat(h);

    if (w <= h) {
        // width is smaller, stretch out height
        glOrtho(-2.5, 2.5, -2.5/aspect, 2.5/aspect, -10.0, 10.0);
    } else {
        // height is smaller, stretch out width
        glOrtho(-2.5*aspect, 2.5*aspect, -2.5, 2.5, -10.0, 10.0);
    }
}

void init() {
    GLfloat black[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat yellow[] = { 1.0, 1.0, 0.0, 1.0 };
    GLfloat cyan[] = { 0.0, 1.0, 1.0, 1.0 };
    GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat direction[] = { 0.0, -10.0, 0.0, 1.0 };
    GLfloat direction1[] = { 0.0, 10.0, 0.0, 1.0 };

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cyan);
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialf(GL_FRONT, GL_SHININESS, 30);

    glLightfv(GL_LIGHT0, GL_AMBIENT, black);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, yellow);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);
    glLightfv(GL_LIGHT0, GL_POSITION, direction);

    glLightfv(GL_LIGHT1, GL_AMBIENT, black);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT1, GL_SPECULAR, white);
    glLightfv(GL_LIGHT1, GL_POSITION, direction1);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_DEPTH_TEST);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(80, 80);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Mesa 3D");
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    init();
    glutMainLoop();
    return 0;
}
