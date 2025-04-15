#include <GL/glut.h>
#include <math.h>

void init();
void display();

void circulo(double radius){
    int d;

    glBegin(GL_POLYGON);
    for(d = 0; d < 32; d++){
        double angle =  (6.14/32) * d;
        glVertex3f(radius*cos(angle), radius*sin(angle), 0);
    }
    glEnd();
}

void quadrado(){
         
    glBegin(GL_POLYGON);
        // Vértices do quadrado
        glVertex3f(1.0, 1.0, 0.0);   
        glVertex3f(-1.0, 1.0, 0.0);  
        glVertex3f(-1.0, -1.0, 0.0);
        glVertex3f(1.0, -1.0, 0.0);
    glEnd();
}

void triangulo(){

    glBegin(GL_POLYGON);
        // Vértices do triângulo
        glVertex3f(0.0, -1.0, 0.0);
        glVertex3f(-1.0, 0.0, 0.0);
        glVertex3f(1.0, 0.0, 0.0);
    glEnd();
}

void roda(){

    glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);
        glTranslated(1.0, 0.8, 0.0);
        glScaled(0.8, 0.8, 0.0);
        circulo(1.0);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.8, 0.8, 0.8);
        glTranslated(1.0, 0.8, 0.0);
        glScaled(0.6, 0.6, 0.0);
        circulo(1.0);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);
        glTranslated(1.0, 0.8, 0.0);
        glScaled(0.2, 0.2, 0.0);
        circulo(1.0);

    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0, 0.0, 0.0); 
        glTranslated(1.0, 0.8, 0.0); 

        glBegin(GL_LINES);
        for (int i = 0; i < 8; i++) {
            float angle = i * M_PI / 4.0; 
            float x = 0.8 * cos(angle);  
            float y = 0.8 * sin(angle);
            glVertex2f(0.0f, 0.0f);       
            glVertex2f(x, y);           
        }
        glEnd();
    glPopMatrix();

}

void chassi(){

    glColor3f(1.0, 0.0, 0.0); // Define cor do quadrado (Vermelho)
    // Quadrado inferior
    glPushMatrix();  
        glScaled(2.5, 0.5, 1.0);     
        quadrado();
    glPopMatrix();
        
    // Quadrado superior
    glPushMatrix();
        glTranslated(0.8, -0.9, 0.0);
        glScaled(1.0, 0.4, 0.0);
        quadrado();
    glPopMatrix();
}

void carro() {

    // Roda traseira
    glPushMatrix();
        glTranslated(0.5, 0.0, 0.0);
        roda(); 
    glPopMatrix();

    // Roda dianteira
    glPushMatrix();
        glTranslated(-2.5, 0.0, 0.0);
        roda();
    glPopMatrix();

    chassi();
}

void grama(){
    
    glColor3f(0.0, 1.0, 0.0); // Cor: verde
    glPushMatrix();
        glTranslated(0.0, 6.0, 0.0);
        glScaled(6.0, 2.0, 1.0);
        quadrado();
    glPopMatrix();
}

void asfalto(){

    glColor3f(0.5, 0.5, 0.5); // Cor: cinza
    glPushMatrix();
        glTranslated(0.0, 3.0, 0.0);
        glScaled(6.0, 1.4, 1.0);
        quadrado();
    glPopMatrix();

}

void ceu(){

    glColor3f(0.0, 0.8, 1.0); // Cor: azul

    glPushMatrix();
        glTranslated(0.0, -3.0, 0.0);
        glScaled(6.0, 4.0, 1.0);
        quadrado();
    glPopMatrix();
}

void montanha(){

    glColor3f(0.0, 1.0, 0.0); // Cor: verde
    triangulo();

}

void sol(){

    glColor3f(1.0, 1.0, 0.0); // Cor: amarelo
    circulo(1.0);

}

void aerogerador(){

    glColor3f(1.0, 0.0, 0.0);

    // Tentativa de uma hélice
    glBegin(GL_POLYGON);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.5, -0.1, 0.0);
        glVertex3f(1.5, 0.0, 0.0);
        glVertex3f(0.5, 0.1, 0.0);
    glEnd();


}

void init(){
    glClearColor(1.0, 1.0, 1.0, 1.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(6, -6, 6, -6, 6, -6);
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    /* DESENHE AQUI */

    ceu();

    glPushMatrix();
        glTranslated(-4.0, -4.5, 1.0);
        sol();
    glPopMatrix();

    // Montanha da esquerda
    glPushMatrix();
        glTranslated(4.0, -0.7, 1.0);
        glScaled(4.0, 3.5, 1.0);
        montanha();
    glPopMatrix();

    // Montanha do meio
    glPushMatrix();
        glTranslated(1.0, -0.7, 1.0);
        glScaled(4.0, 4.0, 1.0);
        montanha();
    glPopMatrix();

    // Montanha da direita
    glPushMatrix();
        glTranslated(-4.0, -0.7, 1.0);
        glScaled(-3.0, 2.0, 1.0);
        montanha();
    glPopMatrix();

    glPushMatrix();
        glTranslated(0.0, -2.0, 0.0);
        glScaled(1.0, 0.8, 1.0);
        asfalto();
    glPopMatrix();
    
    glPushMatrix();
        glTranslated(0.0, -5.0, 1.0);
        aerogerador();
    glPopMatrix();

    grama();
    asfalto();

    glPushMatrix();
        glTranslated(0.0, 0.8, 0.0);
        carro();
    glPopMatrix();

    glFlush();
}

int main(int argc, char** argv){
    int janela_x = 800;
    int janela_y = 600;
    int inicial_x = 300;
    int inicial_y = 300;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(janela_x, janela_y);
    glutInitWindowPosition(inicial_x, inicial_y);
    glutCreateWindow("Renault 19");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
