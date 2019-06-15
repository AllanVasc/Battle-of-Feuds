#include "ACore.h"
#include "server.h"
#include <stdio.h>
#include <string.h>

#define MSG_MAX_SIZE 350
#define BUFFER_SIZE (MSG_MAX_SIZE + 100)
#define LOGIN_MAX_SIZE 13
#define MAX_CHAT_CLIENTS 6

//Variaveis globais

int qtdJogadores = 0;
char movimento;
DADOS aux;
DADOS aux2;
Inicio pacote;
DadosInGame pacoteInGame;
int idPlayerHittado;
int qtdJogadoresMortos = 0;
int idWinner;

int map[24][32] = {      {17, 20, 19, 20, 18, 20, 18, 20, 18, 20, 18, 20, 20, 20, 18, 20, 20, -5, 20, 20, 17, 20, 20, 18, 20, 20, 20, 18, 20, 20, 18,18},
                         {20, 19, 20, 17, 19, 20, 17, 19, -5, 20, 18, 20, 6 , 6 , 6 , 6 , 6 , -1, -2, -6, 20, 20, 18, 20, 20, 18, 20, 20,-55,-56, 20, 20},
                         {18, 18, 20, 18, -4, -2, -2, -2, -3, 15, 16, 16, 16, 16, 16, 16, 16, 16, 14, -1, -2, -2, 18, 20, 20, 20, 18, 17,-57,-58, 20,19},
                         {18, 17, 18, 19, -5, 20, 17, 6 , 6 , 16, 16, 16, 16,-33,-37,-38, 16, 16, 16, 16, 6 , 6 , 20, 18, -5, 17, 18, 20,-59,-60, 18, 20},
                         {17, 17, -4, -2, -3, 18, 15,-22,-23, 16, 16, 16, 16,-34,-39,-40,-61,-62, 16, 16, 16, 16, 14, 20, -1, -2, -2, -6, 18, 20, 20,18},
                         {20, 20, -5, 17, 20, 15,-24,-25,-26, 16, 16, 16, 16,-35,-41,-42,-63,-64, 16, 16, 16, 16, 16, 14, 20, 20, 20, -5, 18,-83,-79,-80},
                         {18, -4, -3, 20, 15, 16,-27,-28,-29, 16, 16, 16, 16,-36,-43,-44,-65, 16, 16, 16, 16, 16, 16, 16, 6 , 20, 17, -5, 20,-83,-81,-82},
                         {20, -5, 19, 8 , 16, 16,-30,-31,-32, 16, 16, 16, 16, 16, 16,-66, 16, 16, 16, 16,-67,-68,-69,-70, 16, 9 , 20, -5, 20, 18, 20, 20},
                         {17, -5, 20, 8 , 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,-71,-72,-73,-74, 16, 9 , 17, -5, 18, 20, 20,19},
                         {20, -5, 20, 8 , 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,-88,-89, 16,-88,-89, 16,-75,-76,-77,-78, 16, 9 , 20, -5, 20, 19, 20,17},
                         {18, -1, -6, 8 , 16, 16, 16,-84,-85, 16, 16, 16, 16, 16,-90,-91, 16,-90,-91, 16, 16, 16, 16, 16, 16, 9 , 18, 20, 17, 20, 17,18},
                         {20, 18, 20, 8 , 16, 16, 16,-86,-87, 16, 16, 16, 16, 16,-94,-95, 16,-94,-95, 16, 16, 16, 16, 16, 16, 9 , 18, 20, 20, 17, 20, 20},
                         {18, 17, 20, 8 , 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,-92,-93, 16,-92,-93, 16, 16, 16, 16, 16, 16, 9 , 20, -5, 20, 18, 17, 20},   
                         {20, 18, 18, 8 , 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 13, -4, -2, -3, 19, 17, 20,18},
                         {20, -4, -3, 15, 16, 16, 16,-22,-23, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 9 , -5, 20, 20, 20, 18, 20, 20},
                         {18, -5, 8 , 16, 16, 16,-24,-25,-26, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 9 , -5, 20, 19,-14,-15, 17, 20},
                         {20, -5, 8 , 16, 16, 16,-27,-28,-29, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 13, 20, 18, -5, 18, 20,-16,-17, 18,17},
                         {20, -5, 8 , 16, 16, 16,-30,-31,-32, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 20, -4, -2, -3, 17, 17,-18,-19, 20, 20},
                         {15, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,-51,-52, 16, 16, 13, 20, -5, 20, 18, 20,-50,-20,-21, 20, 20},
                         {16, 16, 16, -7, -8,-13, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,-53,-54, 16, 13, 20, 20, 17, 18, 20, 20, 19, 18, 20,-48, 20},
                         {16, 16, 16, -9,-10,-11, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 12, 18, -4, -2, 20,-49, 20,-48, 20, 20, 20, 20,18},
                         {10, 11, 16, 16, 16,-12, 16, 11, 11, 11, 11, 16, 16, 16, 16, 16, 16, 16, 16, 20, 17, -5, 20, 18, 20, 20, 17, 18, 20,-49, 20,19},
                         {18, 20, 10, 11, 11, 11, 12, -2, -2, -2, -6, 11, 11, 16, 16, 16, 16, 16, 12, 20, 18, -5, 17, 20, 19,-50, 20, 20,-48, 19, 17,-50},
                         {20, 18, 20, 20, 20, 20, 18, 20, 20, 18, -1, -2, -2, 8 , 16, 16, 16, 16, 9 , -2, -2, -3, 20, 20, 18, 20, 20, 20, 17, 20, 20, 20}  };


///////Funções

int canMove(char direcao , int id);
int canHit();

int main() {

  int i;
  char client_names[MAX_CHAT_CLIENTS][LOGIN_MAX_SIZE];
  char str_buffer[BUFFER_SIZE], aux_buffer[BUFFER_SIZE];
  serverInit(MAX_CHAT_CLIENTS);
  puts("Servidor esta rodando!\n");

  int comecar = 1;
  int InGame = 0 ;

  while(1){

    while (comecar){   //Momento do chat e da configuração dos personagens!

      int id = acceptConnection();

      if (id != NO_CONNECTION){

        aux2.valor = id;                              //Mandando o ID para o client!
        sendMsgToClient(&aux2, sizeof(DADOS), id);
        printf("mandei o id: [%d]\n", aux2.valor);

        recvMsgFromClient(client_names[id], id, WAIT_FOR_IT);     //Enviando a mensagem de conexão!
        sprintf(aux2.mensagem, "%s-%d: connected to chat", client_names[id],id);
        aux2.valor = -1;
        broadcast(&aux2, sizeof(DADOS));
        printf("%s connected id = %d\n", client_names[id], id);
        aux2.mensagem[0]='\0';

        qtdJogadores++;                     //Configurando o personagem!  
        pacote.jogador[id].qualPers = id;
        pacote.jogador[id].direcao = 's';
        pacote.jogador[id].vida = 5;
        pacote.jogador[id].pos.posX = 0 + id;
        pacote.jogador[id].pos.posY = 0 + id;
        pacote.jogador[id].colunaSprite = 0;

      }

      struct msg_ret_t msg_ret = recvMsg(&aux);

      if (msg_ret.status == MESSAGE_OK) {

        if(aux.valor == -1){

          sprintf(aux2.mensagem, "%s-%d: %s", client_names[msg_ret.client_id],msg_ret.client_id, aux.mensagem);
          aux2.valor = -1;
          broadcast(&aux2, sizeof(DADOS));
          aux2.mensagem[0]='\0';

        }

        else if(aux.valor == -2){

          aux.valor = -3;
          broadcast(&aux, sizeof(DADOS));
          comecar = 0;
          InGame = 1;
          break;

        }

        else if(aux.valor == -4){

          pacote.jogador[msg_ret.client_id].qualPers = aux.Sprite;
          printf("Jogador: [%d] escolheu a sprite: [%d]\n", msg_ret.client_id, pacote.jogador[msg_ret.client_id].qualPers );

        }

      } else if (msg_ret.status == DISCONNECT_MSG) {

        sprintf(str_buffer, "%s disconnected", client_names[msg_ret.client_id]);
        printf("%s disconnected, id = %d is free\n",client_names[msg_ret.client_id], msg_ret.client_id);
        broadcast(str_buffer, (int)strlen(str_buffer) + 1);
        qtdJogadores--;

      }
    }

    pacote.qtdPlayers = qtdJogadores;      //Envio de todos os jogadores para todos os clients!
    broadcast(&pacote, sizeof(Inicio));
    printf("Dados de todos os personagens enviados...\n");
    printf("Jogo ira começar...\n");
    qtdJogadoresMortos = 0;

    while(InGame){  //Enquanto o jogo estiver rolando!

      struct msg_ret_t mensagemMov = recvMsg(&movimento); //Recebendo qual movimento foi feito

      if(mensagemMov.status == MESSAGE_OK){

        int id = mensagemMov.client_id;

        switch (movimento){

          case 'w':

            if( canMove( movimento , id ) ){  //Realiza o movimento     

              (pacote.jogador[id].pos.posY) --; //Atualiza o backup de players do server!
              pacote.jogador[id].direcao = 'w';

              pacoteInGame.posY = (pacote.jogador[id].pos.posY); //Configurando o pacote para envio
              pacoteInGame.posX = (pacote.jogador[id].pos.posX);
              pacoteInGame.idClient = id;
              pacoteInGame.vida = (pacote.jogador[id].vida);
              pacoteInGame.flag = 0;
              pacoteInGame.direcao = 'w';
              broadcast(&pacoteInGame, sizeof(DadosInGame));

            }

            else {            // Se encontrou um obstáculo, ele precisa rotacionar a sprite sem tirar do lugar!

              pacote.jogador[id].direcao = 'w'; //Atualiza o backup de players do server!

              pacoteInGame.posY = (pacote.jogador[id].pos.posY); //Configurando o pacote para envio
              pacoteInGame.posX = (pacote.jogador[id].pos.posX);
              pacoteInGame.idClient = id;
              pacoteInGame.vida = (pacote.jogador[id].vida);
              pacoteInGame.flag = 0;
              pacoteInGame.direcao = 'w';
              broadcast(&pacoteInGame, sizeof(DadosInGame));

            }

          break;

          case 's':

            if( canMove( movimento , id ) ){ //Realiza o movimento   

              (pacote.jogador[id].pos.posY) ++; //Atualiza o backup de players do server!
              pacote.jogador[id].direcao = 's';

              pacoteInGame.posY = (pacote.jogador[id].pos.posY); //Configurando o pacote para envio
              pacoteInGame.posX = (pacote.jogador[id].pos.posX);
              pacoteInGame.idClient = id;
              pacoteInGame.vida = (pacote.jogador[id].vida);
              pacoteInGame.flag = 0;
              pacoteInGame.direcao = 's';
              broadcast(&pacoteInGame, sizeof(DadosInGame));

            }

            else { // Se encontrou um obstáculo, ele precisa rotacionar a sprite sem tirar do lugar!

              pacote.jogador[id].direcao = 's'; //Atualiza o backup de players do server!

              pacoteInGame.posY = (pacote.jogador[id].pos.posY); //Configurando o pacote para envio
              pacoteInGame.posX = (pacote.jogador[id].pos.posX);
              pacoteInGame.idClient = id;
              pacoteInGame.vida = (pacote.jogador[id].vida);
              pacoteInGame.flag = 0;
              pacoteInGame.direcao = 's';
              broadcast(&pacoteInGame, sizeof(DadosInGame));

            }

          break;

          case 'a':

            if( canMove( movimento , id ) ){     //Realiza o movimento

              (pacote.jogador[id].pos.posX) --; //Atualiza o backup de players do server!
              pacote.jogador[id].direcao = 'a';

              pacoteInGame.posY = (pacote.jogador[id].pos.posY); //Configurando o pacote para envio
              pacoteInGame.posX = (pacote.jogador[id].pos.posX);
              pacoteInGame.idClient = id;
              pacoteInGame.vida = (pacote.jogador[id].vida);
              pacoteInGame.flag = 0;
              pacoteInGame.direcao = 'a';
              broadcast(&pacoteInGame, sizeof(DadosInGame));

            }

            else { // Se encontrou um obstáculo, ele precisa rotacionar a sprite sem tirar do lugar!

              pacote.jogador[id].direcao = 'a'; //Atualiza o backup de players do server!

              pacoteInGame.posY = (pacote.jogador[id].pos.posY); //Configurando o pacote para envio
              pacoteInGame.posX = (pacote.jogador[id].pos.posX);
              pacoteInGame.idClient = id;
              pacoteInGame.vida = (pacote.jogador[id].vida);
              pacoteInGame.flag = 0;
              pacoteInGame.direcao = 'a';
              broadcast(&pacoteInGame, sizeof(DadosInGame));

            }

          break;

          case 'd':

            if( canMove( movimento , id ) ){     //Realiza o movimento

              
              (pacote.jogador[id].pos.posX) ++; //Atualiza o backup de players do server!
              pacote.jogador[id].direcao = 'd';

              pacoteInGame.posY = (pacote.jogador[id].pos.posY); //Configurando o pacote para envio
              pacoteInGame.posX = (pacote.jogador[id].pos.posX);
              pacoteInGame.idClient = id;
              pacoteInGame.vida = (pacote.jogador[id].vida);
              pacoteInGame.flag = 0;
              pacoteInGame.direcao = 'd';
              broadcast(&pacoteInGame, sizeof(DadosInGame));

            }

            else { // Se encontrou um obstáculo, ele precisa rotacionar a sprite sem tirar do lugar!

              pacote.jogador[id].direcao = 'd'; //Atualiza o backup de players do server!

              pacoteInGame.posY = (pacote.jogador[id].pos.posY); //Configurando o pacote para envio
              pacoteInGame.posX = (pacote.jogador[id].pos.posX);
              pacoteInGame.idClient = id;
              pacoteInGame.vida = (pacote.jogador[id].vida);
              pacoteInGame.flag = 0;
              pacoteInGame.direcao = 'd';
              broadcast(&pacoteInGame, sizeof(DadosInGame));

            }

          break;

          case 'k': //Momento que ele esta atacando

            printf("PLAYER [%d] ATACANDO\n", mensagemMov.client_id);

            if(canHit(id)){

              (pacote.jogador[idPlayerHittado].vida)--; //Atualiza o backup de players do server!

              if(pacote.jogador[idPlayerHittado].vida > 0){
                
                pacoteInGame.idClient = idPlayerHittado; //Preparando pacote para enviar!
                pacoteInGame.vida = (pacote.jogador[idPlayerHittado].vida);
                pacoteInGame.flag = 1;
                broadcast(&pacoteInGame, sizeof(DadosInGame));
                printf("Player [%d] esta com [%d] vidas\n", pacoteInGame.idClient, pacoteInGame.vida);


              } else if(pacote.jogador[idPlayerHittado].vida <= 0){

                printf("Player [%d] morreu!\n", idPlayerHittado); 
                qtdJogadoresMortos++;

                pacoteInGame.idClient = idPlayerHittado;  //Preparar um pacote especifico para quem morreu!
                pacoteInGame.vida = 0;
                pacoteInGame.flag = 2;
                sendMsgToClient(&pacoteInGame, sizeof(DadosInGame), idPlayerHittado);

                pacoteInGame.idClient = idPlayerHittado; //Preparando pacote para dizer a todos que ele morreu!
                pacoteInGame.vida = 0;
                pacoteInGame.flag = 3;
                broadcast(&pacoteInGame, sizeof(DadosInGame));

              }
              
            }

          break;

          case '*': //Player saiu do jogo!

            printf("Player [%d] saiu do jogo!\n", mensagemMov.client_id);
            disconnectClient(mensagemMov.client_id);
            qtdJogadores--;

          break;

          }

      } else if (mensagemMov.status == DISCONNECT_MSG) {

        qtdJogadores--;

      }

      if(qtdJogadoresMortos == qtdJogadores - 1){

        for(i = 0; i < pacote.qtdPlayers; i++){

          if(pacote.jogador[i].vida > 0){

            idWinner = i;
            break;
          }

        }

        pacoteInGame.idClient = idWinner;  //Preparar um pacote especifico para quem venceu!
        pacoteInGame.flag = 4;
        sendMsgToClient(&pacoteInGame, sizeof(DadosInGame), idWinner);
        printf("Player [%d] is the WINNER!\n", idWinner);

        comecar = 1;
        InGame = 0;
        qtdJogadores = 0;
        printf("Jogadores desconectados\n");
        printf("Servidor reiniciando...\n");

        for(i = 0; i < pacote.qtdPlayers; i++){

          disconnectClient(i);

        }

      }

      if(qtdJogadores == 0) {

          comecar = 1;
          InGame = 0;
          printf("Jogadores desconectados\n");
          printf("Servidor reiniciando...\n");
      }

    }
  }
}

int canMove(char direcao , int id){

  int **posicoesJogadores = NULL; 
  int i;

  posicoesJogadores = (int **) malloc(2 * sizeof(int*)); // Essa sera a matriz que armazenara a posicao  de todos os jogadores
  posicoesJogadores[0] = (int *) malloc(pacote.qtdPlayers * sizeof(int) ); //Esse sera o vetor da posicao x de todos os jogadores
  posicoesJogadores[1] = (int *) malloc(pacote.qtdPlayers * sizeof(int) ); //Esse sera o vetor da posicao y de todos os jogadores

  for(i = 0 ; i < pacote.qtdPlayers ; i ++){

    int posX = pacote.jogador[i].pos.posX;
    int posY = pacote.jogador[i].pos.posY;

    posicoesJogadores[0][i] = posX; 
    posicoesJogadores[1][i] = posY; 

  }

  switch(direcao){

    case 'w':

      for(i = 0 ; i < pacote.qtdPlayers ; i++){
        
        if( i != id){

          if(pacote.jogador[id].pos.posX == posicoesJogadores[0][i] && pacote.jogador[id].pos.posY - 1 == posicoesJogadores[1][i]){

            free(posicoesJogadores[0]);
            free(posicoesJogadores[1]);
            free(posicoesJogadores);

            return 0;
            break;

          }
        }
      }

      free(posicoesJogadores[0]);
      free(posicoesJogadores[1]);
      free(posicoesJogadores);
      return 1;
      break;

    case 's':

      for(i = 0 ; i < pacote.qtdPlayers ; i++){

        if( i != id){

          if(pacote.jogador[id].pos.posX == posicoesJogadores[0][i] && pacote.jogador[id].pos.posY + 1 == posicoesJogadores[1][i]){

            free(posicoesJogadores[0]);
            free(posicoesJogadores[1]);
            free(posicoesJogadores);

            return 0;
            break;

          }

        }
        
      }

      free(posicoesJogadores[0]);
      free(posicoesJogadores[1]);
      free(posicoesJogadores);
      return 1;
      break;

    case 'a':

      for(i = 0 ; i < pacote.qtdPlayers ; i++){

        if(i != id){

          if(pacote.jogador[id].pos.posX - 1 == posicoesJogadores[0][i] && pacote.jogador[id].pos.posY == posicoesJogadores[1][i]){

            free(posicoesJogadores[0]);
            free(posicoesJogadores[1]);
            free(posicoesJogadores);

            return 0;
            break;

          }

        }
        
      }

      free(posicoesJogadores[0]);
      free(posicoesJogadores[1]);
      free(posicoesJogadores);
      return 1;
      break;

    case 'd':

      for(i = 0 ; i < pacote.qtdPlayers ; i++){

        if(i != id){
          
          if(pacote.jogador[id].pos.posX + 1 == posicoesJogadores[0][i] && pacote.jogador[id].pos.posY == posicoesJogadores[1][i]){

            free(posicoesJogadores[0]);
            free(posicoesJogadores[1]);
            free(posicoesJogadores);
            return 0;
            break;

          }

        }
        
      }

      free(posicoesJogadores[0]);
      free(posicoesJogadores[1]);
      free(posicoesJogadores);
      return 1;
      break;
  }

  return 0;
}

int canHit(int id){

  int **posicoesJogadores = NULL; 
  int i;

  posicoesJogadores = (int **) malloc(2 * sizeof(int*));                   // Essa sera a matriz que armazenara a posicao  de todos os jogadores
  posicoesJogadores[0] = (int *) malloc(pacote.qtdPlayers * sizeof(int) ); //Esse sera o vetor da posicao x de todos os jogadores
  posicoesJogadores[1] = (int *) malloc(pacote.qtdPlayers * sizeof(int) ); //Esse sera o vetor da posicao y de todos os jogadores

  for(i = 0 ; i < pacote.qtdPlayers ; i ++){

    int posX = pacote.jogador[i].pos.posX;
    int posY = pacote.jogador[i].pos.posY;

    posicoesJogadores[0][i] = posX; 
    posicoesJogadores[1][i] = posY; 

  }

  for(i = 0; i < pacote.qtdPlayers; i++){   //Procurar se existe algum jogador para ser atacado!

    if(i != id){

      if(pacote.jogador[id].direcao == 'w'){

        if(pacote.jogador[id].pos.posX == posicoesJogadores[0][i] && pacote.jogador[id].pos.posY - 1 == posicoesJogadores[1][i]){
          
          idPlayerHittado = i;
          free(posicoesJogadores[0]);
          free(posicoesJogadores[1]);
          free(posicoesJogadores);
          printf("Player [%d] ira sofrer o ataque de [%d]\n", idPlayerHittado, id);

          return 1;

        }

      } else if(pacote.jogador[id].direcao == 's'){

        if(pacote.jogador[id].pos.posX == posicoesJogadores[0][i] && pacote.jogador[id].pos.posY + 1 == posicoesJogadores[1][i]){

          idPlayerHittado = i;
          free(posicoesJogadores[0]);
          free(posicoesJogadores[1]);
          free(posicoesJogadores);
          printf("Player [%d] ira sofrer o ataque de [%d]\n", idPlayerHittado, id);

          return 1;

        }

      } else if(pacote.jogador[id].direcao == 'a'){

        if(pacote.jogador[id].pos.posX - 1 == posicoesJogadores[0][i] && pacote.jogador[id].pos.posY == posicoesJogadores[1][i]){

          idPlayerHittado = i;
          free(posicoesJogadores[0]);
          free(posicoesJogadores[1]);
          free(posicoesJogadores);
          printf("Player [%d] ira sofrer o ataque de [%d]\n", idPlayerHittado, id);

          return 1;

        }

      } else if(pacote.jogador[id].direcao == 'd'){

        if(pacote.jogador[id].pos.posX + 1 == posicoesJogadores[0][i] && pacote.jogador[id].pos.posY == posicoesJogadores[1][i]){

          idPlayerHittado = i;
          free(posicoesJogadores[0]);
          free(posicoesJogadores[1]);
          free(posicoesJogadores);
          printf("Player [%d] ira sofrer o ataque de [%d]\n", idPlayerHittado, id);

          return 1;

        }

      }

    }

  }

  free(posicoesJogadores[0]);
  free(posicoesJogadores[1]);
  free(posicoesJogadores);

  return 0;
  
}