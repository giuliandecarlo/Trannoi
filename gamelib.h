#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

//DICHIARAZIONE DELLE FUNZIONI NON static
void menu();
void resetcolor();
void red();
void blue();
void green();
void yellow();
void purple();
void black();
void pink();
void l_blue();
void orange();
void white();
void clear();


enum Nome_giocatore{rosso,blu,verde,bianco,viola,giallo,nero,rosa,arancione,celeste};
enum Stato_giocatore{astronauta,impostore,assassinato,defenestrato};
enum Tipo_stanza{vuota,questsemplice,questcomplicata,botola};

struct Giocatore{ 
  enum Nome_giocatore nome ;
  enum Stato_giocatore stato ;
  struct Stanza* posizione;
};

struct Stanza{
  struct Stanza* avanti;
  struct Stanza* destra;
  struct Stanza* sinistra;
  struct Stanza* indietro;
  struct Stanza* indietro_boto;
  enum Tipo_stanza tipo ;
  bool chiamata;
};
