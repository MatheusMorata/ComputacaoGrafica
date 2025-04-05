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
        glVertex3f(-1.0, 0.0, 0.0);
        glVertex3f(1.0, 0.0, 0.0);
        glVertex3f(0.0, 1.0, 0.0);
    glEnd();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // Define cor inicial do fundo (branco)

    // Define o sistema de projeção
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-3, 3, -3, 3, -3, 3);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    /*
        DESENHANDO O CASTELO DE ITAIPAVA
    */

    // PILAR CENTRAL
    quadrado();

    // PILAR DA ESQUERDA
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslated(-2.0, 0.5, 0.0);
    glScaled(1.0, 1.5, 1.0);    
    quadrado();

    // PILAR DA DIREITA
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslated(2.0, 0.5, 0.0);   
    glScaled(1.0, 1.5, 1.0);      
    quadrado();

    // TELHADO ESQUERDA
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslated(-2.0, 2.0, 0.0);  
    glScaled(1.0, 1.0, 1.0);  
    triangulo();

    // TELHADO DIREITA
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslated(2.0, 2.0, 0.0); 
    triangulo();

    // PORTA DO CASTELO
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslated(0.0, -0.5, 0.0);  
    glScaled(0.5, 0.5, 1.0); 
    quadrado();

    glFlush();
}

int main(int argc, char** argv) {
    int janela_x = 800; 
    int janela_y = 800;
    int inicial_x = 200;
    int inicial_y = 200;

    glutInit(&argc, argv);  // Inicializa o GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(janela_x, janela_y); // Tamanho da janela
    glutInitWindowPosition(inicial_x, inicial_y); // Posição inicial da janela
    glutCreateWindow("Castelo de Itaipava"); // Título da janela
    init();
    glutDisplayFunc(display);
    glutMainLoop(); // Inicia o looping de desenho

    return 0;
}