#include <GL/glut.h>

void jogoAmericano(){
    glPushMatrix();
        glScalef(1.2f, 0.01f, 1.2f);
        glutSolidCube(1.0);
    glPopMatrix();
}

void Copo() {
    GLUquadric* quad = gluNewQuadric();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glColor4f(0.8f, 0.9f, 1.0f, 0.3f); // Cor de vidro (azulada e translúcida)

    // Base do copo (um disco grosso)
    glPushMatrix();
        glTranslatef(0.0f, -0.4f, 0.0f);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        gluDisk(quad, 0.0f, 0.25f, 64, 1); // Disco base
        glTranslatef(0.0f, 0.0f, -0.02f);  // Deixa um pouco espesso
        gluCylinder(quad, 0.25f, 0.25f, 0.02f, 64, 1); // Base com volume
    glPopMatrix();

    // Corpo do copo (cilindro afunilado)
    glPushMatrix();
        glTranslatef(0.0f, -0.4f, 0.0f);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(quad, 0.25f, 0.20f, 0.8f, 64, 64); // Corpo
    glPopMatrix();

    gluDeleteQuadric(quad);
}

void Prato(){
    GLUquadric* quad = gluNewQuadric();

    // Cor cinza fosco (cerâmica simples)
    glColor3f(0.6f, 0.6f, 0.6f);

    // Base do prato (um disco pequeno no fundo)
    glPushMatrix();
        glTranslatef(0.0f, -0.05f, 0.0f); // Levemente abaixo
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        gluDisk(quad, 0.0f, 0.08f, 64, 1); // Centro do prato
    glPopMatrix();

    // Parte interna arredondada (como funil raso)
    for (float i = 0; i < 10; i++) {
        float r1 = 0.08f + i * 0.012f;
        float r2 = r1 + 0.012f;
        float h = 0.005f;

        glPushMatrix();
            glTranslatef(0.0f, -0.05f + i * h, 0.0f);
            glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
            gluCylinder(quad, r1, r2, h, 64, 1);
        glPopMatrix();
    }

    // Borda externa
    glPushMatrix();
        glTranslatef(0.0f, 0.0f, 0.0f);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(quad, 0.2f, 0.22f, 0.02f, 64, 1); // Borda levemente aberta
    glPopMatrix();

    gluDeleteQuadric(quad);
}

void Luminaria(){
    glPushMatrix();
        glScalef(0.2f, 0.8f, 0.2f);
        glutSolidCube(1.0);
    glPopMatrix();
}

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
        glScalef(7.0f, 0.1f, 3.0f); // Transformei em um plano
        glutSolidCube(1.0);
    glPopMatrix();

    // Pés
    glPushMatrix(); glTranslatef( -3.0f, -1.0f, -1.0f); glScalef(1.0f, 1.9f, 1.0f); Pe(); glPopMatrix(); 
    glPushMatrix(); glTranslatef( -3.0f, -1.0f, 1.2f); glScalef(1.0f, 1.9f, 1.0f); Pe(); glPopMatrix(); 
    glPushMatrix(); glTranslatef( 3.0f, -1.0f, -1.0f); glScalef(1.0f, 1.9f, 1.0f); Pe(); glPopMatrix(); 
    glPushMatrix(); glTranslatef( 3.0f, -1.0f, 1.2f); glScalef(1.0f, 1.9f, 1.0f); Pe(); glPopMatrix(); 

    // jogo americano
    glPushMatrix(); glTranslatef(-1.8f, 0.0f, -0.8f); glScalef(1.5f, 1.0f, 0.8f); jogoAmericano(); glPopMatrix();
    glPushMatrix(); glTranslatef(1.8f, 0.0f, -0.8f); glScalef(1.5f, 1.0f, 0.8f); jogoAmericano(); glPopMatrix();
    glPushMatrix(); glTranslatef(-1.8f, 0.0f, 0.8f); glScalef(1.5f, 1.0f, 0.8f); jogoAmericano(); glPopMatrix();
    glPushMatrix(); glTranslatef(1.8f, 0.0f, 0.8f); glScalef(1.5f, 1.0f, 0.8f); jogoAmericano(); glPopMatrix();

    // Pratos
    glPushMatrix(); glTranslatef(-2.4, 0.1f, -0.5f); Prato(); glPopMatrix();
    glPushMatrix(); glTranslatef(-2.4, 0.1f, 1.2f); Prato(); glPopMatrix();
    glPushMatrix(); glTranslatef(2.4, 0.1f, -0.5f); Prato(); glPopMatrix();
    glPushMatrix(); glTranslatef(2.4, 0.1f, 1.2f); Prato(); glPopMatrix();

    // Copos
    glPushMatrix(); glTranslatef(-2.9, 0.2f, 0.0f); glScalef(0.6f, 0.6f, 0.6f); glRotatef(180,1.0f, 0.0f, 0.0f); Copo(); glPopMatrix();
    glPushMatrix(); glTranslatef(-1.8, 0.2f, 0.4f); glScalef(0.6f, 0.6f, 0.6f); glRotatef(180,1.0f, 0.0f, 0.0f); Copo(); glPopMatrix();
    glPushMatrix(); glTranslatef(1.8, 0.2f, 0.0f); glScalef(0.6f, 0.6f, 0.6f); glRotatef(180,1.0f, 0.0f, 0.0f); Copo(); glPopMatrix();
    glPushMatrix(); glTranslatef(2.9, 0.2f, 0.4f); glScalef(0.6f, 0.6f, 0.6f); glRotatef(180,1.0f, 0.0f, 0.0f); Copo(); glPopMatrix();

    // Luminaria
    glPushMatrix(); glTranslatef(0.0f, 0.4f, 0.0f); Luminaria(); glPopMatrix();
}

void Cadeira() {
    // Pés
    glPushMatrix(); glTranslatef( 0.5f, -0.5f,  0.5f); Pe(); glPopMatrix(); // frente dir
    glPushMatrix(); glTranslatef(-0.5f, -0.5f,  0.5f); Pe(); glPopMatrix(); // frente esq
    glPushMatrix(); glTranslatef( 0.5f, -0.5f, -0.5f); Pe(); glPopMatrix(); // trás dir
    glPushMatrix(); glTranslatef(-0.5f, -0.5f, -0.5f); Pe(); glPopMatrix(); // trás esq

    // diagonais 
    glPushMatrix(); 
        glTranslatef(0.0f, -0.5f, -0.5f);
        glScalef(1.2f, 1.0f, 0.5f); 
        glRotatef(50, 0.0f, 0.0f, 1.0f);
        Pe();
    glPopMatrix();

    glPushMatrix(); 
        glTranslatef(0.0f, -0.5f, -0.5f); 
        glScalef(1.2f, 1.0f, 0.5f); 
        glRotatef(-50, 0.0f, 0.0f, 1.0f);
        Pe();
    glPopMatrix();

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
        -1.0, 2.0, 4.0,   // posição da câmera 
        0.0, 0.0, 0.0,   // olha para a origem
        0.0, 1.0, 0.0    // vetor para cima
    );
    
    Mesa();

    // Cadeira dianteira direita
    glPushMatrix();
        glTranslatef(2.0f, -0.2f, -1.0f); 
        Cadeira();
    glPopMatrix();

    // Cadeira traseira direita
    glPushMatrix();
        glTranslatef(2.0f, -0.2f, 2.0f);
        glRotatef(180, 0.0f, 1.0f, 0.0f); 
        Cadeira();
    glPopMatrix();

    // Cadeira dianteira esquerda
    glPushMatrix();
        glTranslatef(-2.0f, -0.2f, -1.0f); 
        Cadeira();
    glPopMatrix();

    // Cadeira traseira esquerda
    glPushMatrix();
        glTranslatef(-1.5f, -0.2f, 2.0f); 
        glRotatef(180, 0.0f, 1.0f, 0.0f);
        Cadeira();
    glPopMatrix();

    jogoAmericano();

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
