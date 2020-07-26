#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <time.h>
#include "main.h"

/*makro za razlikovanje ID kod timer funkcija i broj milisekundi na koliko se pozivaju takve funkcije*/
#define TIMER_ID 0
#define TIMER_ID1 1
#define TIMER_ID2 2
#define TIMER_INTERVAL 20

/*makro za maksimalan broj karaktera*/
#define MAX_BROJ_KARAKTERA 256

/*makro za gravitaciju*/
#define GRAVITACIJA 0.0001;

int main(int argc, char **argv){
    /* Inicijalizuje se GLUT */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    /* Kreira se prozor */
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    
    inicijalizacija();
    /* Registruju se callback funkcije */
    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);

    /* Obavlja se OpenGL inicijalizacija */
    glClearColor(0.94, 0.81, 0.99, 0);
    glEnable(GL_DEPTH_TEST);
    
    /* Program ulazi u glavnu petlju */
    glutMainLoop();

    return 0;
}

static void inicijalizacija(){
    /*postavljanje pocetnih vrednosti promenljivima*/
    srand(time(NULL));
    koordinata_y_lestvice = -1;
    brzina_lestvice = 0.03;

    dubina = 1000;    
    double pomeraj = 1.5;
  
    unsigned int i = 0;
    koordinata_z_lestvice[0] = 999;
    
    for(i = 0; i<100; i++){
        /*postavljanje vrednosti na z osi lestvicama*/
        if(i != 0)
            koordinata_z_lestvice[i] = koordinata_z_lestvice[i-1] - pomeraj - 1;
        double random_broj = rand()/(float)RAND_MAX;
        /*na slucajan nacin se bira x koordinata lestvicama i pravac kretanja*/
        int pozicija_x_koordinate;
        if(random_broj >=0.5)
            pozicija_x_koordinate = 1;
        else
            pozicija_x_koordinate = -1;
        double random_smer = rand()/(float)RAND_MAX;
        if(random_smer >= 0.5)
            brzina[i] = brzina_lestvice;
        else
            brzina[i] = -brzina_lestvice;
        /*postavljanje brzine kretanja lestvica*/
        if(i != 0 && (i % 10) == 0){
            brzina_lestvice += 0.005;
           
        }
        koordinata_x_lestvice[i] = 2*pozicija_x_koordinate*rand()/(float)RAND_MAX;
    }
    kretanje_lestvica = 0;
}

static void on_keyboard(unsigned char key, int x, int y){
    
    switch (key) {
    case 27:
        /* Zavrsava se program. */
        exit(0);
        break;
    }
}

static void on_reshape(int width, int height){
    window_width = width;
    window_height = height;
}

static void on_display(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    /* Podesava se vidna tacka. */
    glViewport(0, 0, window_width, window_height);

    /* Podesava se projekcija. */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30, (float) window_width / window_height, 1, 1000);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, dubina, 
              0, 0, 0, 
              0, 1, 0);
    
    glEnable(GL_DEPTH_TEST);

    /*postavljanje slike vode*/
    unsigned int i = 1000;
    while(i>= 20){
            
        glBindTexture(GL_TEXTURE_2D, names[0]);
        glBegin(GL_QUADS);
            glNormal3f(0, 0, 1);

            glTexCoord2f(0, 0);
            glVertex3f(-2, -1, i);

            glTexCoord2f(1, 0);
            glVertex3f(2, -1, i);

            glTexCoord2f(1, 1);
            glVertex3f(2, -1, i-20);

            glTexCoord2f(0, 1);
            glVertex3f(-2, -1, i-20);
        glEnd();
        i = i - 20;
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    crtanje_lestvica();
    
    /* Nova slika se salje na ekran. */
    glutSwapBuffers();
}

/*funkcije za kretanje lestvica*/
static void on_timer(int value){
    
    if (value != TIMER_ID)
        return;

    glutPostRedisplay();
    
    if (kretanje_lestvica) {
        glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
    }
}

/*crtanje lestvica*/
void crtanje_lestvica(){    
    glDisable(GL_LIGHTING);
    /*Podesavanje osvetljenja za sve lestvice*/
    unsigned int i = 0;
    for(i=0; i<1000; i++){
        GLfloat pozicija_svetla[] = { 1, 100, 100, 0 };
        GLfloat ambijentalno_svetlo[] = { 0.3, 0.3, 0.3, 1 };
        GLfloat difuzno_svetlo[] = { 0.7, 0.7, 0.7, 1 };
        GLfloat spekularno_svetlo[] = { 0.9, 0.9, 0.9, 1 };
        
        GLfloat ambijentalna_refleksija[] = { 0.6, 0.3, 0.1, 1 };
        GLfloat difuzna_refleksija[] = { 0.7, 0.55, 0.25, 1 };
        GLfloat spekularna_refleksija[] = { 1, 1, 1, 1 };

        GLfloat shininess = 20;
        
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glLightfv(GL_LIGHT0, GL_POSITION, pozicija_svetla);
        glLightfv(GL_LIGHT0, GL_AMBIENT, ambijentalno_svetlo);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, difuzno_svetlo);
        glLightfv(GL_LIGHT0, GL_SPECULAR, spekularno_svetlo);

        glMaterialfv(GL_FRONT, GL_AMBIENT, ambijentalna_refleksija);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, difuzna_refleksija);
        glMaterialfv(GL_FRONT, GL_SPECULAR, spekularna_refleksija);
        glMaterialf(GL_FRONT, GL_SHININESS, shininess);
        /*crtanje lestvica*/
        glPushMatrix();
            glTranslatef(koordinata_x_lestvice[i], koordinata_y_lestvice, koordinata_z_lestvice[i]);
            glScalef(6, 0.7, 4);
            glutSolidCube(0.2);
        glPopMatrix();
    }
    
}
