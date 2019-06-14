#ifndef GAME_H
#define GAME_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>
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

    int posX;
    int posY;
    int idClient;
    int vida;
    int flag;
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
