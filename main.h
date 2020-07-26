#ifndef _PROBA_H_
#define _PROBA_H_

/* Deklaracije callback funkcija*/
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_timer(int value);
static void on_display(void);

static void inicijalizacija(void); /*deklaracija pocetnih vrednosti*/

void crtanje_lestvica(void);

/* Identifikatori tekstura. */
static GLuint names[1];

/*globalne promenljive za poziciju i brzinu lestvica*/
static double koordinata_x_lestvice[1000], koordinata_z_lestvice[1000];
static double koordinata_y_lestvice;
static double brzina[1000];
static double brzina_lestvice;

/*poziciju kamere na z osi*/
static double dubina;

/*sirina i visina ekrana*/
static int window_width, window_height;

/*identifikatorske promenljive*/
static int kretanje_lestvica;

#endif
