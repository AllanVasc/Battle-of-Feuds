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

ALLEGRO_BITMAP *BackgroundMenu; //Imagens do menu
ALLEGRO_BITMAP *gameName;
ALLEGRO_BITMAP *gameIcon;
ALLEGRO_BITMAP *HTPwasd;
ALLEGRO_BITMAP *HTPK;
ALLEGRO_BITMAP *HTPReturn;
ALLEGRO_BITMAP *botaoPlay;
ALLEGRO_BITMAP *botaoHTP;
ALLEGRO_BITMAP *botaoExit;

ALLEGRO_BITMAP *skeletonButton; //Botões dos personagens
ALLEGRO_BITMAP *ripperButton;
ALLEGRO_BITMAP *deathKnightButton;
ALLEGRO_BITMAP *ogreButton;
ALLEGRO_BITMAP *goblinButton;
ALLEGRO_BITMAP *skeleton05Button;

ALLEGRO_BITMAP *texturaMapa; //Variaveis do mapa!
ALLEGRO_BITMAP *detalhesDoChao;
ALLEGRO_BITMAP *grama;   
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

ALLEGRO_BITMAP *heart;

//========================


//========================
// SOUNDS 

ALLEGRO_AUDIO_STREAM *menuGameSong;
ALLEGRO_AUDIO_STREAM *deathSong;
ALLEGRO_AUDIO_STREAM *victorySong;
ALLEGRO_AUDIO_STREAM *conflictSong;

//========================


//========================
//Structs

typedef struct DADOS{ //Struct usada no inicio do server

    char mensagem[100];
    int valor;
    int Sprite;

} DADOS;

typedef struct {

  int posX;
  int posY;

} Posicao;

typedef struct{ //Struct com os dados da sprite selecionada pelo client
   
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

typedef struct{ //Struct das configurações do personagem

  Posicao pos;
  int qualPers;
  int vida;
  char direcao;
  int colunaSprite;
  MoveSprite spriteJogador;

} Personagem;

typedef struct {  //Struct usada em todo o jogo! 

  Personagem jogador[MAX_CHAT_CLIENTS];
  int qtdPlayers;

} Inicio;

typedef struct {

    int posX;             //Flag 0 = Pacote de movimentação
    int posY;             //Flag 1 = Pacote de perda de vida
    int idClient;         //Flag 2 = Pacote dizendo que o client especifico morreu!
    int vida;             //Flag 3 = Pacote dizendo qual client morreu! 
    int flag;             //Flag 4 = Pacote dizendo qual client Venceu!
    char direcao;

} DadosInGame;

//========================

//Funções iniciais da alegro!
bool coreInit();
bool windowInit(int W, int H, char title[]);
bool inputInit();
void allegroEnd();

//Funções para controle do FPS
void startTimer();
double getTimer();
void FPSLimit();

//Funções para carregar todos os arquivos usados
bool loadGraphics();
bool fontInit();

//Função para realizar a leitura das entradas do teclado no chat
void readInput(ALLEGRO_EVENT event, char str[], int limit);


#endif
