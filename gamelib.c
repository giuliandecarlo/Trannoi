#include"gamelib.h"



static void uscitagioco();
static void impostagioco();
static void infogioco(unsigned short nturno,int i);
static unsigned short settimpost(unsigned short nplayer,unsigned short percentuale1,unsigned short percentuale2,unsigned short percentuale3);
static void gioca();
static void stampa_giocatori();
static void movimento(int i);
static void avanza(char muovi,int i);
static int tipostanza();
static void esegui_quest(int i);
static void deallocalista();
static int uccidi(int i);
static void sabotaggio(int i);
static void chiama_emergenza(int i);
static void usa_botola(int i);
static void finegioco();
static int memory();
static void number0();
static void number1();
static void number2();
static void number3();
static void number4();
static void number5();
static void number6();
static void number7();
static void number8();
static void number9();
static void welcome();
static void caricamento();
static void win_impostori();
static void win_astronauti();

static struct Giocatore* giocatori;
static struct Stanza* stanzainiziale;
static struct Stanza* listastanze=NULL;
static struct Stanza* listastanze_botola=NULL;
static struct Stanza* inizio_lista=NULL;
static struct Stanza* inizio_lista_botola=NULL;
static bool checkimposta=false,checkwin_imp=false,checkwin_astro=false;
static unsigned short nplayer=0;
static unsigned short ntask=0;

void menu(){                                                                    //menu' principale
if(checkimposta==false){
    welcome();//grafica iniziale
  }
  int checkscelta=0;
  char scelta;
  do{
  printf("----------------\n");
  printf("|| MAIN MENU' ||\n");
  printf("----------------\n");
  printf("Cosa vuoi fare?\n");
  printf("1)IMPOSTA GIOCO\n");
  printf("2)GIOCA\n");
  printf("3)ESCI DAL GIOCO\n");
  printf("\nScegli digitando il numero: ");
  scanf("%c",&scelta);
  switch(scelta){
    case '1':                             //se il gioco e' stato gia' impostato non si puo' piu accedere a impostagioco
      if(checkimposta==true){red();printf("Hai già impostato il gioco!\n");resetcolor();checkscelta=1;}else{
      impostagioco();
      checkscelta=1;
      }
      break;
    case '2':
    if(checkimposta==false){ //controllo che prima sia stato impostato il gioco
      checkscelta=1;
      system("clear");
      red();
      printf("Per iniziare a giocare,devi prima impostare il gioco!\n");
      resetcolor();
      sleep(2);
      system("clear");
      break;
    }else{
      gioca();
    }
      checkscelta=0;
      break;
    case '3':
      checkscelta=0;
      system("clear");
      uscitagioco();
      break;
    default:
      red();
      printf("E' stato inserito un valore errato!!Riprova\n");
      resetcolor();
      checkscelta=1;
      break;
 }
 clear();
}while(checkscelta!=0);
}

void clear(){                                                                   //funzione che elimina il buffer
  char c;
  while((c= getchar()) != '\n' && c != EOF);
}

static void uscitagioco(){                                                             //funzione che viene richiamata alla chiusura del gioco
  printf("Uscendo dal gioco.\n");
  sleep(1);
  system("clear");
  printf("Uscendo dal gioco..\n");
  sleep(1);
  system("clear");
  printf("Uscendo dal gioco...\n");
  sleep(1);
  system("clear");
  printf("Uscendo dal gioco.\n");
  sleep(1);
  system("clear");
  printf("Uscendo dal gioco..\n");
  sleep(1);
  system("clear");
  printf("Uscendo dal gioco...\n");
  sleep(1);
  system("clear");
  deallocalista();                 //chiamata la funzione che dealloca la memoria allocata
  exit(0);
}

static void impostagioco(){                                                             //funzione che fa scegliere le caratteristiche del gioco e crea la stanza iniziale
  char impredef;
  unsigned short percentuale1=0,percentuale2=0,percentuale3=0,nimpost=0;
  int checkpred=0,nrandom1,nrandom2,nrandom3;
  system("clear");
  printf("------------------\n");
  printf("|| IMPOSTAZIONI ||\n");
  printf("------------------\n");
  do{
  printf("Quanti personaggi ci sono sulla nave?[MIN:4--MAX:10] ");
  scanf("%hu",&nplayer);
  if(nplayer<4||nplayer>10){
    red();
    printf("Inserito un valore errato!!Riprova\n");
    resetcolor();
  }
  clear();
}while(nplayer<4||nplayer>10);
printf("\n\n");
printf("Il numero di impostori varia in base al numero dei giocatori:\nSe il numero dei giocatori e' minore di 6 ci sara' solamente un impostore.\nSe il numero di giocatori e' compreso tra 6 e 10 gli impostori potranno essere 1,2 o 3.\n\n");
if(nplayer>=6){  //se i giocatori sono maggiori di 5 possono capitare da 1 a 3 impostori,se sono meno di 6 ci sara' solo un impostore
 do{
 printf("Vuoi lasciare la percentuale di casualita' impostore predefinita'? [33%c-33%c-34%c]\nPremere 1 per si, 2 per no ",'%','%','%');
 scanf("%c",&impredef);
 switch(impredef){
  case'1':
    printf("Impostazione salvata correttamente.\n");
    percentuale1=33;
    percentuale2=33;
    percentuale3=34;
    checkpred=0;
    break;
  case'2':  //vengono inserite 3 percentuali e successivamente inviate alla funzione settimpost,che stabilisce il numero di impostori
    do{
      do{
    printf("Qual e' la percentuale di probabilita' che esca un solo impostore? [La somma delle percentuali deve essere 100] ");
    if(scanf("%hu",&percentuale1)!=1){clear();percentuale1=101;}//controlla se viene inserito un carattere
      if(percentuale1<0 || percentuale1>100){red(); printf("ERRORE!Riprova.\n"); resetcolor();}
    }while(percentuale1<0 || percentuale1>100); //se viene inserito un numero negativo o superiore a 100 ripete
      do{
    printf("Qual e' la percentuale di probabilita che escano 2 impostori? ");
    if(scanf("%hu",&percentuale2)!=1){clear();percentuale2=101;}
    if(percentuale2<0 || percentuale2>100){red(); printf("ERRORE!Riprova.\n"); resetcolor();}
    }while(percentuale2<0 || percentuale2>100);
      do{
    printf("Qual e' la percentuale di probabilita che escano 3 impostori? ");
    if(scanf("%hu",&percentuale3)!=1){clear();percentuale3=101;}
    if(percentuale3<0 || percentuale3>100){red(); printf("ERRORE!Riprova.\n"); resetcolor();}
  }while(percentuale3<0 || percentuale3>100);
    if((percentuale1+percentuale2+percentuale3)!=100){
      red();
      printf("La somma delle percentuali deve essere 100! Riprova\n");
      resetcolor();
       }
     }while((percentuale1+percentuale2+percentuale3)!=100);  //se la somma delle percentuali non e' 100,ripete
    checkpred=0;
    break;
  default:
    red();
    printf("Inserito un valore errato!!Riprova\n");
    resetcolor();
    checkpred=1;
    break;
  }
  clear();
 }while(checkpred==1);
 nimpost=settimpost(nplayer,percentuale1,percentuale2,percentuale3); //per stabilire il numero degli impostori richiamo la funzione settimpost dandole le 3 percentuali e il numero di giocatori
}
if(nplayer<6){nimpost=1;} //nel caso in cui i giocatori siano minori di 6 ci sarà un solo impostore
printf("Su %hu giocatori,%hu sono impostori\n",nplayer,nimpost);
giocatori=(struct Giocatore *) calloc(nplayer, sizeof(struct Giocatore)); //alloco memoria per l'array di struct Giocatori
if(giocatori==NULL){printf("ERRORE DI MEMORIA\n");exit(-1);}
unsigned short sceltacolori[10];  //creo un array di 10 elementi (come i colori)
for (unsigned short i = 0; i < 10; i++) {
    sceltacolori[i] = i;
}

for (unsigned short i = 0; i < 10; i++) {
    unsigned short temp = sceltacolori[i];
    unsigned short random_i = rand() % 10;

    sceltacolori[i] = sceltacolori[random_i];    //le posizioni vengono mescolate casualmente
    sceltacolori[random_i] = temp;
 }

for(int i=0;i<nplayer;i++){
  giocatori[i].nome=sceltacolori[i];    //assegno i colori casualmente sfruttando l'array creato prima
  giocatori[i].stato=0;                 //assegno inizialmente lo stato astronauta a tutti i giocatori
}
do{                                                                             //creati 3 numeri casuali e utilizzati per assegnare il ruolo impostore
  nrandom1=rand()%nplayer;
  nrandom2=rand()%nplayer;
  nrandom3=rand()%nplayer;
}while(nrandom1==nrandom2||nrandom1==nrandom3||nrandom2==nrandom3);             //il ciclo do..while utilizzato per evitare ripetizioni
if(nimpost==1){giocatori[nrandom1].stato=1;}
if(nimpost==2){giocatori[nrandom1].stato=1;giocatori[nrandom2].stato=1;}
if(nimpost==3){giocatori[nrandom1].stato=1;giocatori[nrandom2].stato=1;giocatori[nrandom3].stato=1;}

  do{
  printf("Quante task devono completare gli astronauti per sopravvivere?[MIN:5-MAX:15] ");
  scanf("%hu",&ntask);
  if(ntask<5||ntask>15){
    red();
    clear();
    printf("Inserito un valore errato!!Riprova\n");
    resetcolor();
  }

}while(ntask<5||ntask>15);
 stanzainiziale=(struct Stanza*) malloc(sizeof(struct Stanza));                 //creo la stanza iniziale
 stanzainiziale->avanti=NULL;                                                   //tutti i puntatori direzionali sono inizializzati a NULL
 stanzainiziale->destra=NULL;
 stanzainiziale->sinistra=NULL;
 stanzainiziale->indietro=NULL;
 stanzainiziale->tipo=0;  //la stanza iniziale e' sempre vuota
 stanzainiziale->chiamata=false;
 for(int i=0;i<nplayer;i++){                                                    //posiziono tutti i giocatori nella stanza iniziale
   giocatori[i].posizione=stanzainiziale;
 }
stanzainiziale->indietro=NULL;
stanzainiziale->indietro_boto=NULL;
 inizio_lista=stanzainiziale; //l'indirizzo della stanza iniziale viene salvato in inzio_lista
 system("clear");
 stampa_giocatori();
 sleep(6);
 printf("\nImpostazioni salvate correttamente, ora tornerai al menu' principale\n");
 sleep(3);
 checkimposta=true;
 caricamento();
}

static void infogioco(unsigned short nturno,int i){                                    //funzione che stampa le informazioni nella schermata di gioco
  system("clear");
  if(giocatori[i].nome==0){red();}
  if(giocatori[i].nome==1){blue();}
  if(giocatori[i].nome==2){green();}
  if(giocatori[i].nome==3){white();}
  if(giocatori[i].nome==4){purple();}
  if(giocatori[i].nome==5){yellow();}
  if(giocatori[i].nome==6){black();}
  if(giocatori[i].nome==7){pink();}
  if(giocatori[i].nome==8){orange();}
  if(giocatori[i].nome==9){l_blue();}
  printf("TURNO: %hu\n",nturno);
  if(giocatori[i].nome==0){printf("NOME: Rosso\n");}
  if(giocatori[i].nome==1){printf("NOME: Blu\n");}
  if(giocatori[i].nome==2){printf("NOME: Verde\n");}
  if(giocatori[i].nome==3){printf("NOME: Bianco\n");}
  if(giocatori[i].nome==4){printf("NOME: Viola\n");}
  if(giocatori[i].nome==5){printf("NOME: Giallo\n");}
  if(giocatori[i].nome==6){printf("NOME: Nero\n");}
  if(giocatori[i].nome==7){printf("NOME: Rosa\n");}
  if(giocatori[i].nome==8){printf("NOME: Arancione\n");}
  if(giocatori[i].nome==9){printf("NOME: Celeste\n");}

  if(giocatori[i].stato==0){printf("STATO: Astronauta\n");}
  if(giocatori[i].stato==1){printf("STATO: Impostore\n");}

  if(giocatori[i].posizione->tipo==0){printf("TIPO STANZA: Vuota (%p)\n",giocatori[i].posizione);}
  if(giocatori[i].posizione->tipo==1){printf("TIPO STANZA: Task semplice (%p)\n",giocatori[i].posizione);}
  if(giocatori[i].posizione->tipo==2){printf("TIPO STANZA: Task complicata (%p)\n",giocatori[i].posizione);}
  if(giocatori[i].posizione->tipo==3){printf("TIPO STANZA: Botola (%p)\n",giocatori[i].posizione);}

  if(giocatori[i].stato==0){printf("TASK RIMANENTI: %hu\n",ntask);}
  if(giocatori[i].stato==0&&giocatori[i].posizione->chiamata==false){printf("EMERGENZA: No\n");}
  if(giocatori[i].stato==0&&giocatori[i].posizione->chiamata==true){printf("EMERGENZA: Si\n");}
  printf("GIOCATORI NELLA STESSA STANZA: ");
  for(int y=0;y<nplayer;y++){
  if(giocatori[i].posizione==giocatori[y].posizione&& i!=y){ //scorrendo l'array di giocatori stampo i nomi di chi e' nella stessa stanza
    switch(giocatori[y].nome){
    case 0:
      red();
      printf(" Rosso");
      break;
    case 1:
      blue();
      printf(" Blu");
      break;
    case 2:
      green();
      printf(" Verde");
      break;
    case 3:
      white();
      printf(" Bianco");
      break;
    case 4:
      purple();
      printf(" Viola");
      break;
    case 5:
      yellow();
      printf(" Giallo");
      break;
    case 6:
      black();
      printf(" Nero");
      break;
    case 7:
      pink();
      printf(" Rosa");
      break;
    case 8:
      orange();
      printf(" Arancione");
      break;
    case 9:
      l_blue();
      printf(" Celeste");
      break;
    default:
     break;

    }
    if(giocatori[y].stato==2){printf("(Assassinato)");}
    if(giocatori[y].stato==3){printf("(Espulso)");}
    resetcolor();
   }
  }
  if(giocatori[i].nome==0){red();}
  if(giocatori[i].nome==1){blue();}
  if(giocatori[i].nome==2){green();}
  if(giocatori[i].nome==3){white();}
  if(giocatori[i].nome==4){purple();}
  if(giocatori[i].nome==5){yellow();}
  if(giocatori[i].nome==6){black();}
  if(giocatori[i].nome==7){pink();}
  if(giocatori[i].nome==8){orange();}
  if(giocatori[i].nome==9){l_blue();}
  printf("\n\n\n\n");
}


static unsigned short settimpost(unsigned short nplayer,unsigned short percentuale1,unsigned short percentuale2,unsigned short percentuale3){ //funzione che assegna in modo casuale il numero di impostori
unsigned short nrandom,nimpost;
if(nplayer>=6){
nrandom=(rand()%100)+1;  //estrae un numero compreso tra 1 e 100
if(nrandom>0&&nrandom<=percentuale1){nimpost=1;}         //in base al numero estratto viene definito il numero di impostori
if(nrandom>percentuale1&&nrandom<(percentuale1+percentuale2)){nimpost=2;}
if(nrandom>(percentuale1+percentuale2)&&nrandom<(percentuale1+percentuale2+percentuale3)){nimpost=3;}
}

if(nplayer<6){nimpost=1;} //Quando i giocatori sono meno di 6 ci sara' solamente 1 impostore
return nimpost;
}




static void gioca(){
int impcounter,astrocounter;
unsigned short turni[nplayer]; //array che ha come dimensione il numero di giocatori
unsigned short dim=nplayer,random_i,temp;
for (unsigned short i = 0; i < dim; i++) {
    turni[i] = i;                            //nell'array vengono inseriti tutti i numeri da 0 a nplayer
}

for (unsigned short i = 0; i < dim; i++) {
     temp = turni[i];
     random_i = rand() % dim;

    turni[i] = turni[random_i];             //le posizioni degli elementi vengono mescolate per creare i turni random
    turni[random_i] = temp;
 }
unsigned short nturno=1;
int x;
do{
for(unsigned short i=0;i<nplayer;i++){
impcounter=0;astrocounter=0;

  if(ntask==0){  //se vengono svolte tutte le task il gioco si ferma e vincono gli astronauti
    win_astronauti();
    finegioco();
    checkwin_astro=true;}

  for(int y=0;y<nplayer;y++){
    if(giocatori[y].stato==1){impcounter=impcounter+1;}
    if(giocatori[y].stato==0){astrocounter=astrocounter+1;}
  }
  if(impcounter==0){ //se vengono espulsi tutti gli impostori gli astronauti vincono
    win_astronauti();
    finegioco();
    checkwin_astro=true;}

  if(impcounter>astrocounter){ //se il numero di impostori e' maggiore del numero degli astronauti, gli impostori vincono
    win_impostori();
    finegioco();
    checkwin_imp=true;}

  if(turni[i]==0){  //grazie ai valori contenuti nel vettore turni verifico quale giocatore deve giocare e chiamo le funzioni necessarie al gioco
    x=0;
    if(giocatori[x].stato==0 || giocatori[x].stato==1){
    infogioco(nturno,x);
    movimento(x);
    resetcolor();
    sleep(2);
        }
      }
  if(turni[i]==1){
    x=1;
    if(giocatori[x].stato==0 || giocatori[x].stato==1){
    infogioco(nturno,x);
    movimento(x);
    resetcolor();
    sleep(2);
    }
  }
  if(turni[i]==2){
    x=2;
    if(giocatori[x].stato==0 || giocatori[x].stato==1){
    infogioco(nturno,x);
    movimento(x);
    resetcolor();
    sleep(2);
    }
  }
  if(turni[i]==3){
    x=3;
    if(giocatori[x].stato==0 || giocatori[x].stato==1){
    infogioco(nturno,x);
    movimento(x);
    resetcolor();
    sleep(2);
    }
  }
  if(turni[i]==4){
    x=4;
    if(giocatori[x].stato==0 || giocatori[x].stato==1){
    infogioco(nturno,x);
    movimento(x);
    resetcolor();
    sleep(2);
    }
  }
  if(turni[i]==5){
    x=5;
    if(giocatori[x].stato==0 || giocatori[x].stato==1){
    infogioco(nturno,x);
    movimento(x);
    resetcolor();
    sleep(2);
    }
  }
  if(turni[i]==6){
    x=6;
    if(giocatori[x].stato==0 || giocatori[x].stato==1){
    infogioco(nturno,x);
    movimento(x);
    resetcolor();
    sleep(2);
    }
  }
  if(turni[i]==7){
    x=7;
    if(giocatori[x].stato==0 || giocatori[x].stato==1){
    infogioco(nturno,x);
    movimento(x);
    resetcolor();
    sleep(2);
    }
  }
  if(turni[i]==8){
    x=8;
    if(giocatori[x].stato==0 || giocatori[x].stato==1){
    infogioco(nturno,x);
    movimento(x);
    resetcolor();
    sleep(2);
    }
  }
  if(turni[i]==9){
    x=9;
    if(giocatori[x].stato==0 || giocatori[x].stato==1){
    infogioco(nturno,x);
    movimento(x);
    resetcolor();
    sleep(2);
    }
  }
 }
 nturno=nturno+1;
}while(1);  //i turni si ripetono finche' qualcuno vince
deallocalista();
}

static void stampa_giocatori(){  //funzione che stampa tutti i giocatori della partita e i relativi ruoli
  printf("\n");
  for(int i=0;i<nplayer;i++){
    switch(giocatori[i].nome){
    case 0:
      red();
      printf("Rosso");
      resetcolor();
      break;
    case 1:
      blue();
      printf("Blu");
      resetcolor();
      break;
    case 2:
      green();
      printf("Verde");
      resetcolor();
      break;
    case 3:
      white();
      printf("Bianco");
      resetcolor();
      break;
    case 4:
      purple();
      printf("Viola");
      resetcolor();
      break;
    case 5:
      yellow();
      printf("Giallo");
      resetcolor();
      break;
    case 6:
      black();
      printf("Nero");
      resetcolor();
      break;
    case 7:
      pink();
      printf("Rosa");
      resetcolor();
      break;
    case 8:
      orange();
      printf("Arancione");
      resetcolor();
      break;
    case 9:
      l_blue();
      printf("Celeste");
      resetcolor();
      break;
    default:
     break;

    }
printf(" è un ");
  switch(giocatori[i].stato){
    case 0:
      blue();
      printf("astronauta.\n");
      resetcolor();
      break;
    case 1:
      red();
      printf("impostore.\n");
      resetcolor();
      break;

    default:
     break;
  }
  }
}

static void movimento(int i){    //funzione che gestisce le azioni del player durante i turni
  int checkavanza,checkdead=0;
  char muovi;
 do{
   clear();
 printf("\n\nPremi: [w]Per muoverti in avanti.  [d]Per muoverti verso destra.  [a]Per muoverti verso sinistra.  [f]Per rimanere fermo.\n");
 if(giocatori[i].stato==1){printf("       [k]Per uccidere.  [s]Per sabotare.  [b]Per usare la botola.  [e]Per effettuare la chiamata d'emergenza.\n");}
 if(giocatori[i].stato==0){printf("       [q]Per svolegere la task.  [e]Per effettuare la chiamata d'emergenza.\n");}
printf("\nCosa vuoi fare? ");
scanf("%c",&muovi);
switch(muovi){
  case'W':                                   //I movimenti tra le stanze vengono gestiti dalla funzione avanza()
  case'w':
    printf("Hai scelto di andare avanti.\n");
    avanza(muovi,i);
    checkavanza=1;
    break;

  case'A':
  case'a':
    printf("Hai scelto di andare a sinistra.\n");
    avanza(muovi,i);
    checkavanza=1;
    break;

  case'D':
  case'd':
    printf("Hai scelto di andare a destra.\n");
    avanza(muovi,i);
    checkavanza=1;
        break;

    case'F':
    case'f':
      printf("Hai deciso di rimanere fermo.\n");
      checkavanza=1;
      break;

    case'Q':
    case'q':
      if(giocatori[i].stato==1){
        printf("Sei un impostore, non puoi svolgere task!\n");
        checkavanza=0;
      }
      if(giocatori[i].stato==0 && (giocatori[i].posizione->tipo==0||giocatori[i].posizione->tipo==3)){
        printf("Non e' presente alcuna task qui!\n");
        checkavanza=0;
      }
      if((giocatori[i].stato==0)&&(giocatori[i].posizione->tipo==1||giocatori[i].posizione->tipo==2)){
        esegui_quest(i);
        checkavanza=1;
            }
        sleep(1);
        break;

    case'S':
    case's':
        if(giocatori[i].stato==0){
          printf("Gli astronauti non possono sabotare!\n");
          checkavanza=0;
        }
        if((giocatori[i].stato==1)&&(giocatori[i].posizione->tipo==0||giocatori[i].posizione->tipo==3)){
          printf("Non c'e' nessuna task da sabotare in questa stanza!\n");
          checkavanza=0;
        }
        if((giocatori[i].stato==1)&&(giocatori[i].posizione->tipo==1||giocatori[i].posizione->tipo==2)){
          printf("La stanza e' stata sabotata!\n");
          sabotaggio(i);
          checkavanza=1;
        }
        break;

    case'K':
    case'k':
      if(giocatori[i].stato==0){
        printf("Gli astronauti non possono uccidere!\n");
        checkavanza=0;
        }
        if(giocatori[i].stato==1){
          checkavanza=uccidi(i);
         }
        break;

    case'E':
    case'e':
          if(giocatori[i].posizione->chiamata==true){printf("E' stata gia' effettuata una chiamata d'emergenza in questa stanza!\n");checkavanza=0;}
          for(int y=0;y<nplayer;y++){
            if(giocatori[i].posizione==giocatori[y].posizione && giocatori[y].stato==2){checkdead=1;} //controllo se in quella posizione c'e' un cadavere
          }
          if(checkdead==0){printf("Non e' stato ucciso nessuno in questa stanza!\n");checkavanza=0;}
          for(int y=0;y<nplayer;y++){
          if(giocatori[i].posizione==giocatori[y].posizione && giocatori[y].stato==2 && giocatori[i].posizione->chiamata==false){
          chiama_emergenza(i);
          checkavanza=1;
          }
          if(y==(nplayer-1) && checkavanza!=1){checkavanza=0;}
        }
        break;

    case'B':
    case'b':
          if(giocatori[i].stato!=1){ //solo gli impostori possono usare la botola
            printf("Non puoi usare la botola!\n");
            checkavanza=0;
          }
          if(giocatori[i].posizione->tipo!=3){
            printf("Non c'e' nessuna botola in questa stanza!\n");
            checkavanza=0;
          }
          if(giocatori[i].stato==1 && giocatori[i].posizione->tipo==3){
          usa_botola(i);
          checkavanza=1;
          }
          break;

     default:
    printf("ERRORE!Hai inserito un valore errato!\n");
    checkavanza=0;
    break;
}
}while(checkavanza==0);
}

static int tipostanza(){   //funzione che assegna casualmente ad ogni stanza creata il tipo
  int nestratto,tipost;
  nestratto=(rand()%100)+1;
  if(nestratto>0&&nestratto<=15){  //Q. DIFFICILE
  tipost=2;
  }
  if(nestratto>15&&nestratto<=40){  //BOTOLA
  tipost=3;
  }
  if(nestratto>40&&nestratto<=70){  //Q. FACILE
  tipost=1;
  }
  if(nestratto>70&&nestratto<=100){  //VUOTA
  tipost=0;
  }
  return tipost;
}

static void esegui_quest(int i){
  int checkmem=0;
  if(giocatori[i].posizione->tipo==1){
    checkmem=memory();//se il tipo stanza e' task semplice avvia il minigioco e ne riceve l'esito
    if(checkmem==1){ //se la funzione memory restituisce 1 vuol dire che il minigioco e' stato completato con successo
    printf("Hai svolto la task semplice.\n");
    ntask=ntask-1;
    giocatori[i].posizione->tipo=0;
      }
    }
  if(giocatori[i].posizione->tipo==2){
    checkmem=memory();
    if(checkmem==1){
    printf("Hai svolto la task complicata.\n");
    giocatori[i].posizione->tipo=0;
    if(ntask==1){ntask=0;}else{    //if utilizzato per evitare che ntask diventi un numero negativo (causerebbe problemi essendo un unsigned )
    ntask=ntask-2;}}
  }
}

static void deallocalista(){ //funzione che scorre la lista stanze e dealloca la memoria allocata
   free(giocatori);//dealloco la memoria allocata per l'array di giocatori
  listastanze= inizio_lista;
  while (listastanze != NULL) { //scorre la lista
    struct Stanza* stampa = listastanze;
    listastanze = listastanze -> indietro;
  free(stampa); //dealloca le stanze
 }
}

static void avanza(char muovi,int i){
  switch(muovi){
    case'W':
    case'w':
      if(giocatori[i].posizione->avanti==NULL){   //verifico che nessun giocatore sia andato in questa direzione e abbia creato gia' la stanza
        struct Stanza* stanzanew=(struct Stanza*) malloc(sizeof(struct Stanza));
        giocatori[i].posizione->avanti=stanzanew;
        giocatori[i].posizione=stanzanew;
        stanzanew->avanti=NULL;
        stanzanew->destra=NULL;
        stanzanew->sinistra=NULL;
        stanzanew->tipo=tipostanza(); //stabilisco il tipo della stanza
        stanzanew->chiamata=false;
        stanzanew-> indietro = inizio_lista; //aggiungo la stanza alla lista delle stanze create
        inizio_lista=stanzanew;

        if(giocatori[i].posizione->tipo==3){  //se la stanza e' di tipo botola, viene aggiunta anche alla lista delle stanze botola per la funzione usa_botola
          stanzanew-> indietro_boto = inizio_lista_botola;
          inizio_lista_botola=stanzanew;
          }
        }else{         //se la stanza e' stata gia' creata da altri, il giocatore si sposta in quella direzione
          giocatori[i].posizione=giocatori[i].posizione->avanti;}
          sleep(1);
      break;
    case'A':
    case'a':
      if(giocatori[i].posizione->sinistra==NULL){
        struct Stanza* stanzanew1=(struct Stanza*) malloc(sizeof(struct Stanza));
        giocatori[i].posizione->sinistra=stanzanew1;
        giocatori[i].posizione=stanzanew1;
        stanzanew1->avanti=NULL;
        stanzanew1->destra=NULL;
        stanzanew1->sinistra=NULL;
        stanzanew1->tipo=tipostanza();
        stanzanew1->chiamata=false;
        stanzanew1-> indietro = inizio_lista;
        inizio_lista=stanzanew1;

        if(giocatori[i].posizione->tipo==3){
          stanzanew1-> indietro_boto = inizio_lista_botola;
          inizio_lista_botola=stanzanew1;
        }
        }else{
          giocatori[i].posizione=giocatori[i].posizione->sinistra;}
          sleep(1);
      break;
    case'D':
    case'd':
      if(giocatori[i].posizione->destra==NULL){
        struct Stanza* stanzanew2=(struct Stanza*) malloc(sizeof(struct Stanza));
        giocatori[i].posizione->destra=stanzanew2;
        giocatori[i].posizione=stanzanew2;
        stanzanew2->avanti=NULL;
        stanzanew2->destra=NULL;
        stanzanew2->sinistra=NULL;
        stanzanew2->tipo=tipostanza();
        stanzanew2->chiamata=false;
        stanzanew2-> indietro = inizio_lista;
        inizio_lista=stanzanew2;

        if(giocatori[i].posizione->tipo==3){
          stanzanew2-> indietro_boto = inizio_lista_botola;
          inizio_lista_botola=stanzanew2;
        }
        }else{
          giocatori[i].posizione=giocatori[i].posizione->destra;}
          sleep(1);
          break;

     default:
      printf("ERRORE!\n");
      break;
   }
  }

static int uccidi(int i){
  int k,nestratto,perctotale=0,check_uccidi=0;
  printf("Tra i giocatori presenti nella tua stanza chi vuoi uccidere?\n");
  for(int y=0;y<nplayer;y++){
    if(giocatori[i].posizione==giocatori[y].posizione&& i!=y && giocatori[y].stato==0){ //scorro tutti i giocatori, verificando chi e' nella stessa posizione
      switch(giocatori[y].nome){                                                        //escludendo gli altri impostori
      case 0:
        printf("%d) Rosso\n",y);
        check_uccidi=1;
        break;
      case 1:
        printf("%d) Blu\n",y);
        check_uccidi=1;
        break;
      case 2:
        printf("%d) Verde\n",y);
        check_uccidi=1;
        break;
      case 3:
        printf("%d) Bianco\n",y);
        check_uccidi=1;
        break;
      case 4:
        printf("%d) Viola\n",y);
        check_uccidi=1;
        break;
      case 5:
        printf("%d) Giallo\n",y);
        check_uccidi=1;
        break;
      case 6:
        printf("%d) Nero\n",y);
        check_uccidi=1;
        break;
      case 7:
        printf("%d) Rosa\n",y);
        check_uccidi=1;
        break;
      case 8:
        printf("%d) Arancione\n",y);
        check_uccidi=1;
        break;
      case 9:
        printf("%d) Celeste\n",y);
        check_uccidi=1;
        break;
      default:
      clear();
       break;

      }
    }
  }
  if(check_uccidi==0){printf("Non c'e' nessuno da poter uccidere qui!\n");return 0;}
  scanf("%d",&k);
  if(k<0||k>10){printf("Hai inserito un valore errato!\n"); return 0;}//if utile nel caso venga inserito un carattere ,evita il segmentation fault e fa apparire un messaggio d'errore
  if(giocatori[k].stato!=0){
    printf("Puoi uccidere solo astronauti!\n");
    return 0;
   }
   if(i==k ||giocatori[i].posizione!=giocatori[k].posizione){
     printf("Hai inserito un valore errato!\n");
     return 0;
   }
  if(giocatori[i].posizione==giocatori[k].posizione && i!=k && giocatori[k].stato==0){
    giocatori[k].stato=2;
    printf("Il giocatore e' stato assassinato.\n");
   }
 for(int y=0;y<nplayer;y++){                                                    //conta il numero di astronauti presenti nella stanza attuale
 if(giocatori[i].posizione==giocatori[y].posizione){
   if(giocatori[y].stato==0){perctotale=perctotale+50;}                         //e in base al numero aumenta la percentuale
    }
if(giocatori[i].posizione->indietro==giocatori[y].posizione){ //controllo quanti astronauti ci sono nella stanza precedente, in base al numero aumento la percentuale
  if(giocatori[y].stato==0){perctotale=perctotale+20;}
  }
 }
nestratto=rand()%100;                                                    //in base alle percentuali calcolate viene stabilita la possibile espulsione dell'impostore
if(nestratto>0 && nestratto<perctotale){
  printf("Qualcuno ti ha scoperto! Sei stato espulso!!\n");
  giocatori[i].stato=3;
  return 1;
}else{printf("Fortunatamente nessuno ti ha visto!\n");return 1;}
}

static void chiama_emergenza(int i){                                                   //La funzione puo' essere chiamata solo nel caso ci sia un cadavere nella stanza
  int impcount=0,astrocount=0,perc_astro=0,perc_imp=0,somma_perc,nestratto,emergency_check=0;
  giocatori[i].posizione->chiamata=true;
  for(int y=0;y<nplayer;y++){                                                   //conta il numero di impostori e di astronauti presenti nella stanza
  if(giocatori[i].posizione==giocatori[y].posizione){
  if(giocatori[y].stato==1){impcount=impcount+1;}
  if(giocatori[y].stato==0){astrocount=astrocount+1;}
  }
 }
perc_imp=30+(astrocount*20)-(impcount*30);                                      //calcola le percentuali di espulsione
if(perc_imp<0){perc_imp=0;}
perc_astro=30+(impcount*20)-(astrocount*30);
if(perc_astro<0){perc_astro=0;}
somma_perc=perc_imp+perc_astro;
nestratto=(rand()%somma_perc)+1;                                                //casualmente (ma basandosi sulle percentuali)sceglie se deve essere espulso un impostore o un astronauta
if(nestratto>0 && nestratto<perc_imp && impcount!=0){
  printf("E' stato espulso un impostore!\n");
  for(int y=0;y<nplayer;y++){
    if(giocatori[i].posizione==giocatori[y].posizione && giocatori[y].stato==1){
      giocatori[y].stato=3;
      break;
      }
    }
    emergency_check=1;
  }
if(nestratto>perc_imp && nestratto<somma_perc && astrocount!=0){
  printf("E' stato espulso un astronauta!\n");
  for(int y=0;y<nplayer;y++){
    if(giocatori[i].posizione==giocatori[y].posizione && giocatori[y].stato==0){
      giocatori[y].stato=3;
      break;
      }
    }
    emergency_check=1;
 }
 if(emergency_check==0){printf("Non e' stato espulso nessuno!\n");}
}

static void sabotaggio(int i){                                                         //funzione che trasforma la stanza da tipo task semplice/complicata in vuota
  giocatori[i].posizione->tipo=0;
}


static void usa_botola(int i){
  int n1=0,n2=0,nstanze_botola=0,nstanze=0;
  listastanze=inizio_lista;
  listastanze_botola=inizio_lista_botola;

  while (listastanze_botola != NULL) {  //controlla il numero di stanze di tipo botola
    listastanze_botola = listastanze_botola -> indietro_boto;
    nstanze_botola=nstanze_botola+1;
  }
  if(nstanze_botola<=1){ //se le botole sono minori o uguali ad 1 ,l'impostore che usa la botola va in una stanza casuale
    printf("Non ci sono altre botole,ti sposti in una stanza casuale!\n");
    while (listastanze != NULL) {
      listastanze = listastanze -> indietro;
      nstanze=nstanze+1;  //conto il numero di stanze scorrendo la lista
   }
   do{
     n1=rand()%nstanze; //estratto un numero casuale compreso tra 0 e il numero di stanze
   listastanze=inizio_lista;
   for(int x=0;x<n1;x++){
     listastanze = listastanze->indietro;
   }
 }while(listastanze==giocatori[i].posizione); //do..while usato per evitare che il giocatore si ritrovi nella stessa posizione di partenza
   giocatori[i].posizione=listastanze;


 }else{ //se le stanze di tipo botola sono maggiori di 1 ,l'impostore si sposta in un altra stanza di tipo botola
   printf("Hai usato la botola\n");
   do{
 n2=rand()%nstanze_botola; //estratto numero compreso tra 0 e il numero di stanze di tipo botola
listastanze_botola=inizio_lista_botola;
for(int x=0;x<n2;x++){
  listastanze_botola = listastanze_botola->indietro_boto;
  }
 }while(listastanze_botola==giocatori[i].posizione); //do..while usato per evitare che il giocatore si ritrovi nella stessa posizione di partenza
  giocatori[i].posizione=listastanze_botola;
 }
}

static void finegioco(){       //menu' che compare solo alla fine del gioco
  char sceltafine;
  int checksceltafine;
  do{
  printf("\n\nOra cosa vuoi fare?\n");
  printf("1) AVVIA NUOVA PARTITA\n");
  printf("2) ESCI DAL GIOCO\n");
  printf("Scegli digitando il numero: ");
  scanf("%c",&sceltafine);
  switch(sceltafine){
    case'1':                     //se si vuole iniziare una nuova partita le impostazioni vengono resettate e la memoria delle stanze e i giocatori viene liberata
      deallocalista();  //dealloco la memoria allocata per le stanze create
      checkwin_imp=false;
      checkwin_astro=false;
      checkimposta=false;
      listastanze=NULL;
      listastanze_botola=NULL;
      inizio_lista=NULL;
      inizio_lista_botola=NULL;
      menu();
      checksceltafine=1;
      break;
    case'2':
      uscitagioco();
      checksceltafine=1;
      break;
    default:
      red();
      printf("Inserito un valore errato!!Riprova");
      resetcolor();
      checksceltafine=0;
      break;
   }
  clear();
 }while(checksceltafine==0);
}
//DEFINIZIONI DELLE FUNZIONI DI TIPO GRAFICO O 'SECONDARIE' RISPETTO AL pdf

void resetcolor() {
  printf("\033[0m");
}

void red() {
  printf("\e[0;31m");
}

void blue() {
  printf("\033[0;34m");
}

void green() {
  printf("\033[0;32m");
}

void yellow() {
  printf("\e[1;93m");
}

void purple() {
  printf("\e[0;35m");
}

void black(){
  printf("\e[0;37m");
}

void pink(){
  printf("\e[0;95m");
}

void l_blue(){
  printf("\033[0;36m");
}

void white(){
  printf("\e[0;37m");
}

void orange(){
  printf("\e[1;33m");
}

static void welcome(){                                                                 //funzione che contiene la grafica iniziale del gioco
  system("clear");
  red();
  printf("PER EVITARE PROBLEMI DI TIPO GRAFICO E' CONSIGLIATO INGRANDIRE LO SCHERMO.\n");
  resetcolor();
  sleep(2);
  system("clear");
  printf(" *                                           .               °              \n");
  printf("      *              .           *                   .                 .    \n");
  printf("                        .                                                   \n");
  printf("       .                                                                    \n");
  printf(" *                          *           .                 .              °  \n");
  printf("     .                  .                                                   \n");
  printf("         .                     *          .         *          .            \n");
  printf("                °                              .                   .        \n");
  printf("         .         .                                   .                    \n");
  printf("                 .                     °                        *           \n");
  printf("   .                                           .           *           .    \n");
  sleep(1);
  system("clear");
  printf(" *                     *                     .                              \n");
  printf("      *              .                °              .                 .    \n");
  printf("                        .                                                   \n");
  printf("       .                                                   *                \n");
  printf(" *              .           *           .                                °  \n");
  printf("     .                  .                                                   \n");
  printf("         .                                .                    .            \n");
  printf("                °         *                     .                  .        \n");
  printf("         .         .         ,              *          .                    \n");
  printf("                 .                     °                        *           \n");
  printf("   .             *               *                                     .    \n");
  sleep(1);
  system("clear");
  printf(" *                     *                     .                              \n");
  printf("      *              .                               .                 .    \n");
  printf("                        .                                                   \n");
  printf("       . ████████╗██████╗  █████╗ ███╗   ██╗███╗   ██╗ ██████╗ ██╗          \n");
  printf(" *       ╚══██╔══╝██╔══██╗██╔══██╗████╗  ██║████╗  ██║██╔═══██╗██║       °  \n");
  printf("            ██║   ██████╔╝███████║██╔██╗ ██║██╔██╗ ██║██║   ██║██║          \n");
  printf("         .  ██║   ██╔══██╗██╔══██║██║╚██╗██║██║╚██╗██║██║   ██║██║          \n");
  printf("            ██║   ██║  ██║██║  ██║██║ ╚████║██║ ╚████║╚██████╔╝██║ .        \n");
  printf("         .  ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═══╝ ╚═════╝ ╚═╝          \n");
  printf("                 .                     °                        *           \n");
  printf("   .             *               *                                     .    \n");
  sleep(1);
  system("clear");
  printf("                 .                          *                    °          \n");
  printf("      *                         °                    .                 .    \n");
  printf("                        .                                                   \n");
  printf("       . ████████╗██████╗  █████╗ ███╗   ██╗███╗   ██╗ ██████╗ ██╗          \n");
  printf("         ╚══██╔══╝██╔══██╗██╔══██╗████╗  ██║████╗  ██║██╔═══██╗██║  .       \n");
  printf("            ██║   ██████╔╝███████║██╔██╗ ██║██╔██╗ ██║██║   ██║██║          \n");
  printf("    °       ██║   ██╔══██╗██╔══██║██║╚██╗██║██║╚██╗██║██║   ██║██║          \n");
  printf("            ██║   ██║  ██║██║  ██║██║ ╚████║██║ ╚████║╚██████╔╝██║        * \n");
  printf("         .  ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═══╝ ╚═════╝ ╚═╝          \n");
  printf("                 .                     °                        *           \n");
  printf("     *                      .                   .                      .    \n");
  sleep(1);
  system("clear");
  printf(" *                     *                     .                              \n");
  printf("      *              .                               .                 .    \n");
  printf("                        .                                                   \n");
  printf("       . ████████╗██████╗  █████╗ ███╗   ██╗███╗   ██╗ ██████╗ ██╗          \n");
  printf(" *       ╚══██╔══╝██╔══██╗██╔══██╗████╗  ██║████╗  ██║██╔═══██╗██║       °  \n");
  printf("            ██║   ██████╔╝███████║██╔██╗ ██║██╔██╗ ██║██║   ██║██║          \n");
  printf("         .  ██║   ██╔══██╗██╔══██║██║╚██╗██║██║╚██╗██║██║   ██║██║          \n");
  printf("            ██║   ██║  ██║██║  ██║██║ ╚████║██║ ╚████║╚██████╔╝██║ .        \n");
  printf("         .  ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═══╝ ╚═════╝ ╚═╝          \n");
  printf("                 .                     °                        *           \n");
  printf("   .             *               *                                     .    \n");
printf("Premere Invio per iniziare!!\n");
clear();
system("clear");
printf(" *                     *                     .                              \n");
printf("      *              .                               .                 .    \n");
printf("                        .                                                   \n");
printf("       . ████████╗██████╗  █████╗ ███╗   ██╗███╗   ██╗ ██████╗ ██╗          \n");
printf(" *       ╚══██╔══╝██╔══██╗██╔══██╗████╗  ██║████╗  ██║██╔═══██╗██║       °  \n");
printf("            ██║   ██████╔╝███████║██╔██╗ ██║██╔██╗ ██║██║   ██║██║          \n");
printf("         .  ██║   ██╔══██╗██╔══██║██║╚██╗██║██║╚██╗██║██║   ██║██║          \n");
printf("            ██║   ██║  ██║██║  ██║██║ ╚████║██║ ╚████║╚██████╔╝██║ .        \n");
printf("         .  ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═══╝ ╚═════╝ ╚═╝          \n");
printf("                 .                     °                        *           \n");
printf("   .             *               *                                     .    \n");
}

static void caricamento(){
  system("clear");
  printf("Caricamento in corso.\n");
  sleep(1);
  system("clear");
  printf("Caricamento in corso..\n");
  sleep(1);
  system("clear");
  printf("Caricamento in corso...\n");
  sleep(1);
  system("clear");
  printf("Caricamento in corso.\n");
  sleep(1);
  system("clear");
  printf("Caricamento in corso..\n");
  sleep(1);
  system("clear");
  printf("Caricamento in corso...\n");
  sleep(1);
  system("clear");
}

static void win_impostori(){
  system("clear");
  printf("\e[0;91m");
  printf("\n");
  printf("  ██████╗ ██╗     ██╗        ██╗███╗   ███╗██████╗  ██████╗ ███████╗████████╗ ██████╗ ██████╗ ██╗        ██╗  ██╗ █████╗ ███╗   ██╗███╗   ██╗ ██████╗     ██╗   ██╗██╗███╗   ██╗████████╗ ██████╗   \n");
  printf(" ██╔════╝ ██║     ██║        ██║████╗ ████║██╔══██╗██╔═══██╗██╔════╝╚══██╔══╝██╔═══██╗██╔══██╗██║        ██║  ██║██╔══██╗████╗  ██║████╗  ██║██╔═══██╗    ██║   ██║██║████╗  ██║╚══██╔══╝██╔═══██╗  \n");
  printf(" ██║  ███╗██║     ██║        ██║██╔████╔██║██████╔╝██║   ██║███████╗   ██║   ██║   ██║██████╔╝██║        ███████║███████║██╔██╗ ██║██╔██╗ ██║██║   ██║    ██║   ██║██║██╔██╗ ██║   ██║   ██║   ██║  \n");
  printf(" ██║   ██║██║     ██║        ██║██║╚██╔╝██║██╔═══╝ ██║   ██║╚════██║   ██║   ██║   ██║██╔══██╗██║        ██╔══██║██╔══██║██║╚██╗██║██║╚██╗██║██║   ██║    ╚██╗ ██╔╝██║██║╚██╗██║   ██║   ██║   ██║  \n");
  printf(" ╚██████╔╝███████╗██║        ██║██║ ╚═╝ ██║██║     ╚██████╔╝███████║   ██║   ╚██████╔╝██║  ██║██║        ██║  ██║██║  ██║██║ ╚████║██║ ╚████║╚██████╔╝     ╚████╔╝ ██║██║ ╚████║   ██║   ╚██████╔╝  \n");
  printf("  ╚═════╝ ╚══════╝╚═╝        ╚═╝╚═╝     ╚═╝╚═╝      ╚═════╝ ╚══════╝   ╚═╝    ╚═════╝ ╚═╝  ╚═╝╚═╝        ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═══╝ ╚═════╝       ╚═══╝  ╚═╝╚═╝  ╚═══╝   ╚═╝    ╚═════╝   \n");
  resetcolor();
  printf("\n\n");
  clear();
}

static void win_astronauti(){
  system("clear");
  printf("\e[0;34m");
  printf("\n");
  printf(" ██████╗ ██╗     ██╗         █████╗ ███████╗████████╗██████╗  ██████╗ ███╗   ██╗ █████╗ ██╗   ██╗████████╗██╗        ██╗  ██╗ █████╗ ███╗   ██╗███╗   ██╗ ██████╗     ██╗   ██╗██╗███╗   ██╗████████╗ ██████╗\n");
  printf("██╔════╝ ██║     ██║        ██╔══██╗██╔════╝╚══██╔══╝██╔══██╗██╔═══██╗████╗  ██║██╔══██╗██║   ██║╚══██╔══╝██║        ██║  ██║██╔══██╗████╗  ██║████╗  ██║██╔═══██╗    ██║   ██║██║████╗  ██║╚══██╔══╝██╔═══██╗\n");
  printf("██║  ███╗██║     ██║        ███████║███████╗   ██║   ██████╔╝██║   ██║██╔██╗ ██║███████║██║   ██║   ██║   ██║        ███████║███████║██╔██╗ ██║██╔██╗ ██║██║   ██║    ██║   ██║██║██╔██╗ ██║   ██║   ██║   ██║\n");
  printf("██║   ██║██║     ██║        ██╔══██║╚════██║   ██║   ██╔══██╗██║   ██║██║╚██╗██║██╔══██║██║   ██║   ██║   ██║        ██╔══██║██╔══██║██║╚██╗██║██║╚██╗██║██║   ██║    ╚██╗ ██╔╝██║██║╚██╗██║   ██║   ██║   ██║\n");
  printf("╚██████╔╝███████╗██║        ██║  ██║███████║   ██║   ██║  ██║╚██████╔╝██║ ╚████║██║  ██║╚██████╔╝   ██║   ██║        ██║  ██║██║  ██║██║ ╚████║██║ ╚████║╚██████╔╝     ╚████╔╝ ██║██║ ╚████║   ██║   ╚██████╔╝\n");
  printf(" ╚═════╝ ╚══════╝╚═╝        ╚═╝  ╚═╝╚══════╝   ╚═╝   ╚═╝  ╚═╝ ╚═════╝ ╚═╝  ╚═══╝╚═╝  ╚═╝ ╚═════╝    ╚═╝   ╚═╝        ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═══╝ ╚═════╝       ╚═══╝  ╚═╝╚═╝  ╚═══╝   ╚═╝    ╚═════╝\n");
  resetcolor();
  printf("\n\n");
  clear();
}

static int memory(){  //Gioco del memory quando viene chiamata la funzione esegui_quest
  int start=0;
  do{
  system("clear");
  printf("MEMORY:\n");
  printf("Per poter svolgere correttamente la task, dovrai memorizzare i 5 numeri che vedrai apparire e inserirli nell'ordine giusto quando ti sara' chiesto di farlo..");
  printf("Premi 1 quando sei pronto!!\n");
  scanf("%d",&start);
  if(start!=1){clear();}
}while(start!=1);
  int n1=0,n2=0,n3=0,n4=0,n5=0,n1u=0,n2u=0,n3u=0,n4u=0,n5u=0,checkmemory=0;
  time_t t;
  srand((unsigned)time(&t));
  n1=rand()%10; //vengono estratti 5 numeri casuali compresi tra 0 e 9
  n2=rand()%10;
  n3=rand()%10;
  n4=rand()%10;
  n5=rand()%10;
  system("clear");
  if(n1==0){number0();} //e chiamate le relative funzioni che stampano i numeri tramite i printf
  if(n1==1){number1();}
  if(n1==2){number2();}
  if(n1==3){number3();}
  if(n1==4){number4();}
  if(n1==5){number5();}
  if(n1==6){number6();}
  if(n1==7){number7();}
  if(n1==8){number8();}
  if(n1==9){number9();}

  if(n2==0){number0();}
  if(n2==1){number1();}
  if(n2==2){number2();}
  if(n2==3){number3();}
  if(n2==4){number4();}
  if(n2==5){number5();}
  if(n2==6){number6();}
  if(n2==7){number7();}
  if(n2==8){number8();}
  if(n2==9){number9();}

  if(n3==0){number0();}
  if(n3==1){number1();}
  if(n3==2){number2();}
  if(n3==3){number3();}
  if(n3==4){number4();}
  if(n3==5){number5();}
  if(n3==6){number6();}
  if(n3==7){number7();}
  if(n3==8){number8();}
  if(n3==9){number9();}

  if(n4==0){number0();}
  if(n4==1){number1();}
  if(n4==2){number2();}
  if(n4==3){number3();}
  if(n4==4){number4();}
  if(n4==5){number5();}
  if(n4==6){number6();}
  if(n4==7){number7();}
  if(n4==8){number8();}
  if(n4==9){number9();}

  if(n5==0){number0();}
  if(n5==1){number1();}
  if(n5==2){number2();}
  if(n5==3){number3();}
  if(n5==4){number4();}
  if(n5==5){number5();}
  if(n5==6){number6();}
  if(n5==7){number7();}
  if(n5==8){number8();}
  if(n5==9){number9();}

  do{
  printf("Inserisci il primo numero che hai visto:[compreso tra 0 e 9] "); //si richiede i numeri visti
  if(scanf("%d",&n1u)!=1){clear();n1u=10;}//se viene inserito un carattere pulisce il buffer e fa apparire l'errore
  if(n1u<0||n1u>9){printf("Puoi inserire solo numeri compresi tra 0 e 9!!Riprova\n");}
}while(n1u<0||n1u>9);
  if(n1==n1u){checkmemory=checkmemory+1;}  //se il numero inserito corrisponde al numero apparso checkmemory aumenta di 1
  do{
  printf("Inserisci il secondo numero che hai visto:[compreso tra 0 e 9] ");
  if(scanf("%d",&n2u)!=1){clear();n2u=10;}
  if(n2u<0||n2u>9){printf("Puoi inserire solo numeri compresi tra 0 e 9!!Riprova\n");}
}while(n2u<0||n2u>9);
  if(n2==n2u){checkmemory=checkmemory+1;}
  do{
  printf("Inserisci il terzo numero che hai visto:[compreso tra 0 e 9] ");
  if(scanf("%d",&n3u)!=1){clear();n3u=10;}
  if(n3u<0||n3u>9){printf("Puoi inserire solo numeri compresi tra 0 e 9!!Riprova\n");}
}while(n3u<0||n3u>9);
  if(n3==n3u){checkmemory=checkmemory+1;}
  do{
  printf("Inserisci il quarto numero che hai visto:[compreso tra 0 e 9] ");
  if(scanf("%d",&n4u)!=1){clear();n4u=10;}
  if(n4u<0||n4u>9){printf("Puoi inserire solo numeri compresi tra 0 e 9!!Riprova\n");}
}while(n4u<0||n4u>9);
  if(n4==n4u){checkmemory=checkmemory+1;}
  do{
  printf("Inserisci il quinto numero che hai visto:[compreso tra 0 e 9] ");
  if(scanf("%d",&n5u)!=1){clear();n5u=10;}
  if(n5u<0||n5u>9){printf("Puoi inserire solo numeri compresi tra 0 e 9!!Riprova\n");}
}while(n5u<0||n5u>9);
  if(n5==n5u){checkmemory=checkmemory+1;}

  if(checkmemory==5){printf("Complimenti!\n");return 1; //se checkmemory e' uguale a 5 vuol dire che tutti i numeri inseriti corrispondono
}else{
  printf("Hai fallito la prova, riprova al prossimo turno\n");return 0;}
}




void number0(){
printf("     ██████╗   \n");
printf("    ██╔═████╗  \n");
printf("    ██║██╔██║  \n");
printf("    ████╔╝██║  \n");
printf("    ╚██████╔╝  \n");
printf("     ╚═════╝   \n");
sleep(2);
system("clear");
sleep(1);
}

void number1(){
printf("     ██╗\n");
printf("    ███║\n");
printf("    ╚██║\n");
printf("     ██║\n");
printf("     ██║\n");
printf("     ╚═╝\n");
sleep(2);
system("clear");
sleep(1);
}


void number2(){
printf("    ██████╗\n");
printf("    ╚════██╗\n");
printf("     █████╔╝\n");
printf("    ██╔═══╝\n");
printf("    ███████╗\n");
printf("    ╚══════╝\n");
sleep(2);
system("clear");
sleep(1);
}


void number3(){
printf("    ██████╗\n");
printf("    ╚════██╗\n");
printf("     █████╔╝\n");
printf("     ╚═══██╗\n");
printf("    ██████╔╝\n");
printf("    ╚═════╝\n");
sleep(2);
system("clear");
sleep(1);
}

void number4(){
printf("    ██╗  ██╗\n");
printf("    ██║  ██║\n");
printf("    ███████║\n");
printf("    ╚════██║\n");
printf("         ██║\n");
printf("         ╚═╝\n");
sleep(2);
system("clear");
sleep(1);
}

void number5(){
printf("    ███████╗\n");
printf("    ██╔════╝\n");
printf("    ███████╗\n");
printf("    ╚════██║\n");
printf("    ███████║\n");
printf("    ╚══════╝\n");
sleep(2);
system("clear");
sleep(1);
}

void number6(){
printf("     ██████╗\n");
printf("    ██╔════╝ \n");
printf("    ███████╗\n");
printf("    ██╔═══██╗\n");
printf("    ╚██████╔╝\n");
printf("     ╚═════╝\n");
sleep(2);
system("clear");
sleep(1);
}

void number7(){
printf("    ███████╗\n");
printf("    ╚════██║\n");
printf("        ██╔╝\n");
printf("       ██╔╝\n");
printf("       ██║\n");
printf("       ╚═╝\n");
sleep(2);
system("clear");
sleep(1);
}

void number8(){
printf("     █████╗\n");
printf("    ██╔══██╗\n");
printf("    ╚█████╔╝\n");
printf("    ██╔══██╗\n");
printf("    ╚█████╔╝\n");
printf("     ╚════╝\n");
sleep(2);
system("clear");
sleep(1);
}

void number9(){
printf("     █████╗\n");
printf("    ██╔══██╗\n");
printf("    ╚██████║\n");
printf("     ╚═══██║\n");
printf("     █████╔╝\n");
printf("     ╚════╝\n");
sleep(2);
system("clear");
sleep(1);
}
