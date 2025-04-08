#include <GL/glut.h>

void init();
void display();

void quadrado() {
    glColor3f(0, 0, 0); // Define cor do quadrado (preto)
     
    glBegin(GL_LINE_LOOP);
        // Vértices do quadrado
        glVertex3f(1.0, 1.0, 0.0);   
        glVertex3f(-1.0, 1.0, 0.0);  
        glVertex3f(-1.0, -1.0, 0.0);
        glVertex3f(1.0, -1.0, 0.0);
    glEnd();
}

void triangulo() {
    glColor3f(1, 0, 0); // Define cor do triângulo (vermelho)
     
    glBegin(GL_LINE_LOOP);
        // Vértices do triângulo
        glVertex3f(0.0, 1.0, 0.0);
        glVertex3f(-1.0, 0.0, 0.0);
        glVertex3f(1.0, 0.0, 0.0);
    glEnd();
}

void init(){
    glClearColor(1.0, 1.0, 1.0, 1.0);

    // Projeção
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-6, 6, -6, 6, -6, 6);
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    /* DESENHANDO UM FOGUETE */

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslated(0.0, 1.0, 0.0);
    glScaled(1.0, 2.0, 1.0); 
    quadrado();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslated(0.0, 3.0, 0.0);
    triangulo();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslated(-1.0, -1.0, 0.0);  
    glRotated(90.0, 0.0, 0.0, 1.0); 
    glScaled(1.0, 1.0, 1.0);  
    triangulo();

    glFlush();
}

int main(int argc, char** argv){
    int janela_x = 800;
    int janela_y = 800;
    int inicial_x = 200;
    int inicial_y = 200;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(janela_x, janela_y);
    glutInitWindowPosition(inicial_x, inicial_y);
    glutCreateWindow("Foguete");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}