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
Inicio pacote;


///////Funções

int puderIr();

int main() {

  char client_names[MAX_CHAT_CLIENTS][LOGIN_MAX_SIZE];
  char str_buffer[BUFFER_SIZE], aux_buffer[BUFFER_SIZE];
  serverInit(MAX_CHAT_CLIENTS);
  puts("Server is running!!");

  int comecar = 1;
  int InGame = 0 ;

  while(1){

    while (comecar) {   //Momento do chat e da configuração dos personagens!

      int id = acceptConnection();

      if (id != NO_CONNECTION){

        recvMsgFromClient(client_names[id], id, WAIT_FOR_IT);
        strcpy(str_buffer, client_names[id]);
        strcat(str_buffer, " connected to chat");
        broadcast(str_buffer, (int)strlen(str_buffer) + 1);
        printf("%s connected id = %d\n", client_names[id], id);

        qtdJogadores++;                     //Configurando o personagem!  
        pacote.jogador[id].qualPers = id;
        pacote.jogador[id].direcao = 's';
        pacote.jogador[id].vida = 5;
        pacote.jogador[id].pos.posX = 0 + id;
        pacote.jogador[id].pos.posY = 0 + id;   //O cliente precisa saber do id DELE, falta codar isso!

      }

      struct msg_ret_t msg_ret = recvMsg(&aux);

      if (msg_ret.status == MESSAGE_OK) {

        if(aux.valor == 1){

          sprintf(aux.mensagem, "%s-%d: %s", client_names[msg_ret.client_id],msg_ret.client_id, aux);
          broadcast(&aux, sizeof(DADOS));

        }

        else if(aux.valor == 0){

          aux.valor = 2;
          broadcast(&aux, sizeof(DADOS));
          comecar = 0;
          InGame = 1;
          break;

        }

      } else if (msg_ret.status == DISCONNECT_MSG) {

        sprintf(str_buffer, "%s disconnected", client_names[msg_ret.client_id]);
        printf("%s disconnected, id = %d is free\n",client_names[msg_ret.client_id], msg_ret.client_id);
        broadcast(str_buffer, (int)strlen(str_buffer) + 1);

      }
    }


    pacote.players = qtdJogadores;      //Envio de todos os jogadores para todos os clients!
    broadcast(&pacote, sizeof(Inicio));
    printf("Dados de todos os personagens enviados...Jogo ira começar...\n");
    printf("Jogo ira começar...\n");

    while(InGame){  //Enquanto o jogo estiver rolando!

      struct msg_ret_t mensagemMov = recvMsg(&movimento); //Recebendo qual movimento foi feito

      if(mensagemMov.status == MESSAGE_OK){

        int id = mensagemMov.client_id;

        switch (movimento){

          case 'w':
          pacote.jogador[id].pos.posY --;

          if(!puderIr()){     //Falta programar essa função!

            pacote.jogador[id].pos.posY ++;

          }

          else {
            //mudar a posicao do que ela saiu
          // map[pacote.jogador[id].pos.posY][pacote.jogador[id].pos.posX] = id do personagem
            broadcast(&pacote, sizeof(Inicio));
          }
          break;

        }
      }
    }

    comecar = 1;
  }
}

int puderIr(){





  return 0;
}