#ifndef GAME_H
#define GAME_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define FPS 60
#define WIDTH  1024
#define HEIGHT 768
#define IP_MAX_SIZE 100
#define MAX_CHAT_CLIENTS 6

double startingTime;

ALLEGRO_DISPLAY *main_window;
ALLEGRO_EVENT_QUEUE *eventsQueue;  

//========================
//FONT AND BITMAP POINTERS

ALLEGRO_FONT *ubuntu;
ALLEGRO_FONT *start;
ALLEGRO_FONT *fonteHTP;
ALLEGRO_FONT *fonteHTPTitulo;

ALLEGRO_BITMAP *BackgroundMenu;
ALLEGRO_BITMAP *gameName;
ALLEGRO_BITMAP *gameIcon;
ALLEGRO_BITMAP *HTPwasd;
ALLEGRO_BITMAP *HTPJ;
ALLEGRO_BITMAP *HTPK;
ALLEGRO_BITMAP *HTPReturn;
ALLEGRO_BITMAP *botaoPlay;
ALLEGRO_BITMAP *botaoHTP;
ALLEGRO_BITMAP *botaoExit;
ALLEGRO_BITMAP *texturaMapa;
ALLEGRO_BITMAP *detalhesDoChao;
ALLEGRO_BITMAP *charSprite;
ALLEGRO_BITMAP *heart;
ALLEGRO_BITMAP *skeletonButton;
ALLEGRO_BITMAP *ripperButton;
ALLEGRO_BITMAP *deathKnightButton;
ALLEGRO_BITMAP *ogreButton;
ALLEGRO_BITMAP *goblinButton;
ALLEGRO_BITMAP *skeleton05Button;

ALLEGRO_BITMAP *grama;   //Variaveis do mapa!
ALLEGRO_BITMAP *pedra;
ALLEGRO_BITMAP *cerca;
ALLEGRO_BITMAP *obstaculos;
ALLEGRO_BITMAP *objetos;
//========================


//========================
//SPRITES

ALLEGRO_BITMAP *Sprite_Skeleton0;
ALLEGRO_BITMAP *Sprite_Ripper01;
ALLEGRO_BITMAP *Sprite_DeathKnight02;
ALLEGRO_BITMAP *Sprite_Ogre03;
ALLEGRO_BITMAP *Sprite_Goblin04;
ALLEGRO_BITMAP *Sprite_Skeleton05;


//========================


//========================
// SOUNDS 

ALLEGRO_AUDIO_STREAM *menuGameSong;
ALLEGRO_AUDIO_STREAM *deathSong;
ALLEGRO_AUDIO_STREAM *victorySong;
ALLEGRO_AUDIO_STREAM *conflictSong;

// ALLEGRO_SAMPLE *SwordAttackSound;
// ALLEGRO_SAMPLE *SwordAttackSound2;
// ALLEGRO_SAMPLE *SwordAttackSound3;
// ALLEGRO_SAMPLE *SwordAttackSound4;
// ALLEGRO_SAMPLE *SwordAttackSound5;
// ALLEGRO_SAMPLE *SwordAttackSound6;

//========================


//========================
//Structs

typedef struct DADOS{

    char mensagem[100];
    int valor;
    int Sprite;

} DADOS;

typedef struct {

  int posX;
  int posY;

} Posicao;

typedef struct{ //Struct com os dados da sprite selecionada
   
    int linhaW;         
    int linhaS;
    int linhaA;
    int linhaD;
    int limiteMovimentacaoW;
    int limiteMovimentacaoS;
    int limiteMovimentacaoA;
    int limiteMovimentacaoD;
    int linhaAtaqueW;
    int linhaAtaqueS;
    int linhaAtaqueA;
    int linhaAtaqueD;
    int limiteAtaqueW;
    int limiteAtaqueS;
    int limiteAtaqueA;
    int limiteAtaqueD;
    int espacamento;
    int inicio;

} MoveSprite;

typedef struct{

  Posicao pos;
  int qualPers;
  int vida;
  char direcao;
  int colunaSprite;
  MoveSprite spriteJogador;

} Personagem;

typedef struct {

  Personagem jogador[MAX_CHAT_CLIENTS];
  int qtdPlayers;

} Inicio;

typedef struct {

    int posX;             //Flag 0 = Pacote de movimentação
    int posY;             //Flag 1 = Pacote de perda de vida
    int idClient;         //Flag 2 = Pacote dizendo que o client morreu!
    int vida;             //Flag 3 = Pacote dizendo qual client morreu! 
    int flag;             //Flag 4 = Pacote dizendo qual client Venceu!
    char direcao;

} DadosInGame;

//========================

//MAIN ALLEGRO FUNCTIONS
bool coreInit();
bool windowInit(int W, int H, char title[]);
bool inputInit();
void allegroEnd();

//FPS CONTROL FUNCTIONS
void startTimer();
double getTimer();
void FPSLimit();

//RESOURCE LOADING FUNCTIONS
bool loadGraphics();
bool fontInit();

//INPUT READING FUNCTION
void readInput(ALLEGRO_EVENT event, char str[], int limit);


#endif
