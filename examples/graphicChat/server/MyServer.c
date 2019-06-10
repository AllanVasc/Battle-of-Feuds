#include "ACore.h"
#include "server.h"
#include <stdio.h>
#include <string.h>

#define MSG_MAX_SIZE 350
#define BUFFER_SIZE (MSG_MAX_SIZE + 100)
#define LOGIN_MAX_SIZE 13
#define MAX_CHAT_CLIENTS 3

int mapaJogo[24][32] = { 	  {1 , 3 , 3 , 3 , 3 , 2 , 3 , 1 , 2 , 2 , 3 , 3 , 2 , 1 , 3 , 3 , 2 , 1 , 2 , -1, 2 , 2 , 1 , 3 , 3 , 3 , 1 , 2 , 3 , 3 , 3 , 2},
                        	  {2 , 2 , -1, 3 , 2 , 1 , 2 , -2, 2 , 2 , -1, 3 , 3 , 3 , 2 , 1 , 2 , 3 , 3 , 2 , 2 , 3 , 2 , -3, 3 , 2 , -1, 3 , 2 , 3 , 2 , 3},
                            {3 , 2 , 3 , 2 , 1 , 4 , 5 , 5, 5 , 5 , 6 , 2 , 2 , -2, 3 , 2 , 3 , 2 , 3 , 3 , 3 , 3 , 2 , 1 , 2 , 2 , 3 , 2 , 2 , 2 , -2, 2},
                            {3 , 3 , 2 , 2 , 3 , 7 , 8 , 8 , 8 , 8 , 9 , 3 , 2 , -3, 3 , 2 , 2 , 2 , -2, 2 , 3 , 3 , 3 , 3 , 3 , 2 , 2 , 2 , 3 , 2 , -3, 1},
                            {2 , 1 , 2 , 3 , -1, 7 , 8 , 8 , 8 , 8 , 9 , 2 , 3 , 2 , 3 , 3 , -1, 3 , 3 , 3 , 2 , -1, 2 , 2 , 2 , 3 , 2 , -3, 2 , 3 , 3 , 3},
                            {-2, 3 , 3 , 3 , 3 , 7 , 8 , 8 , 8 , 8 , 9 , 2 , 1 , 2 , 3 , 3 , 3 , 2 , 2 , 2 , 3 , 3 , 3 , 2 , 3 , 1 , 2 , 2 , 2 , -1, 2 , 3},
                            {-3, 3 , 2 , 2 , 2 , 7 , 8 , 8 , 8 , 8 , 9 , 3 , 2 , 3 , 3 , 2 , 2 , 2 , -1, 2 , 2 , 1 , 2 , 3 , -1, 3 , 3 , 1 , 2 , 3 , 3 , 3},
                            {3 , 2 , 2 , 2 , 1 , 10, 11, 11, 11, 11, 12, 3 , 3 , 2 , -1, 2 , 1 , 3 , 2 , 3 , 3 , 4 , 5 , 5 , 5 , 5 , 6 , -2, 3 , 3 , 1 , 2}, 
                            {2 , 3 , 3 , 3 , 3 , 2 , 3 , 2 , 2 , 2 , 3 , 3 , 2 , 3 , 3 , 3 , -3, 2 , 2 , 2 , 2 , 7 , 8 , 8 , 8 , 8 , 9 , -3, 3 , 3 , 3 , 2},
                            {2 , 2 , 2 , 3 , 2 , 3 , 2 , 1 , 2 , 2 , -1, 3 , 2 , 3 , 2 , 2 , 2 , 3 , 3 , 3 , 1 , 7 , 8 , 8 , 8 , 8 , 9 , 3 , 3 , 3 , 2 , 3},
                            {3 , -1, 3 , 2 , -2, 2 , 3 , 2 , -1, 3 , 2 , 2 , 3 , 2 , 3 , 3 , 3 , 2 , 3 , 2 , 3 , 7 , 8 , 8 , 8 , 8 , 9 , 1 , 2 , 2 , 3 , -2},
                            {3 , 3 , 2 , 2 , -3, 3 , 3 , 3 , 2 , 2 , 3 , -3, 2 , 1 , 3 , 2 , 2 , 2 , 1 , 2 , 3 , 7 , 8 , 8 , 8 , 8 , 9 , 2 , 3 , 2 , 2 , -3},
                            {2 , 2 , 2 , 3 , 2 , 2 , 2 , 2 , 3 , 2 , 2 , 2 , 3 , -1, 2 , 3 , 1 , 3 , 3 , 3 , 2 , 10, 11, 11, 11, 11, 12, 3 , 2 , 3 , 3 , 3},
                            {2 , 3 , 3 , 3 , 1 , 3 , 3 , -1, 2 , 2 , 3 , 2 , 2 , 2 , 3 , 3 , 3 , -1, 2 , 2 , 3 , -1, 3 , 2 , 3 , 1 , 2 , 2 , 2 , 1 , 2 , 3},
                            {1 , 3 , 2 , -1, 2 , 2 , 2 , 2 , 3 , 3 , 2 , 1 , 2 , 3 , 3 , 2 , 2 , 2 , 3 , 2 , 2 , 3 , 2 , 2 , 3 , 3 , 2 , 3 , 2 , 3 , 3 , 3},
                            {3 , 2 , 2 , 2 , 3 , 3 , 3 , 3 , 2 , 3 , 3 , 4 , 5 , 5 , 5 , 5 , 6 , 3 , 2 , 3 , 3 , 2 , 3 , 2 , 2 , 2 , 2 , 2 , 3 , 3 , 1 , 2}, 
                            {3 , 3 , 3 , 3 , 3 , 2 , 3 , 2 , 2 , -3, 3 , 7 , 8 , 8 , 8 , 8 , 9 , 1 , 2 , -1, 2 , 2 , 1 , 3 , 3 , 3 , -1, 2 , 3 , -1, 3 , 2},
                            {2 , 2 , 2 , 3 , 2 , -2, 2 , 1 , 3 , 2 , -1, 7 , 8 , 8 , 8 , 8 , 9 , 3 , 3 , 2 , 2 , 3 , 2 , -3, 3 , 2 , 3 , 3 , 3 , 3 , 2 , 3},
                            {3 , -1, 3 , 3, 3 , -3, 2 , 3 , 2 , 3 , 3 , 7 , 8 , 8 , 8 , 8 , 9 , 2 , 3 , 2 , 3 , 3 , 2 , 1 , 2 , 2 , 3 , 3 , 2 , 2 , 3 , 2},
                            {3 , 3 , 2 , 2 , 1 , 3 , 2 , 3 , 2 , 3 , 3 , 7 , 8 , 8 , 8 , 8 , 9 , -1, 2 , 2 , 3 , -1, 3 , 3 , 3 , 2 , 3 , 2 , 3 , 2 , 2 , 1},
                            {2 , 2 , 2 , -1, 2 , 2 , 3 , 2 , 3 , 3 , 2 , 10, 11, 11, 11, 11, 12, 3 , 3 , 3 , 3 , 3 , 2 , 3 , 2 , 3 , 2 , 3 , -3, 3 , 3 , -2},
                            {2 , 3 , 3 , 3 , 3 , 3 , 3 , 3 , 2 , 2 , 3 , 2 , 1 , 2 , -1, 3 , 3 , 2 , 2 , 2 , 3 , 2 , 3 , 2 , 3 , -1, 2 , 2 , 2 , 1 , 2 , -3},
                            {1 , 3 , 2 , 2 , 2 , 2 , 2 , 2 , -1, 2 , 2 , 3 , 2 , 3 , 3 , 2 , 2 , 2 , 1 , 2 , -2, 3 , 2 , 2 , 3 , 3 , 2 , 2 , 2 , 3 , 3 , 3},
                            {3 , 2 , 2 , 2 , -3, 3 , 3 , 1 , 2 , 2 , 3 , 3 , 3 , 2 , 3 , 2 , 1 , 3 , 2 , 3 , -3, 2 , 1 , 2 , -1, 2 , 2 , 1 , 3 , 3 , 1 , 2}, 

                         };

int main() {

  char client_names[MAX_CHAT_CLIENTS][LOGIN_MAX_SIZE];
  char str_buffer[BUFFER_SIZE], aux_buffer[BUFFER_SIZE];
  serverInit(MAX_CHAT_CLIENTS);

  puts("Servidor esta rodando!\n");

  while (1) {

    int id = acceptConnection();

    if (id != NO_CONNECTION) {

      recvMsgFromClient(client_names[id], id, WAIT_FOR_IT);
      strcpy(str_buffer, client_names[id]);
      strcat(str_buffer, " connected to chat");
      broadcast(str_buffer, (int)strlen(str_buffer) + 1);
      printf("%s connected id = %d\n", client_names[id], id);

    }

    struct msg_ret_t msg_ret = recvMsg(aux_buffer);

    if (msg_ret.status == MESSAGE_OK) {

      sprintf(str_buffer, "%s-%d: %s", client_names[msg_ret.client_id], msg_ret.client_id, aux_buffer);
      broadcast(str_buffer, (int)strlen(str_buffer) + 1);

    } else if (msg_ret.status == DISCONNECT_MSG) {

      sprintf(str_buffer, "%s disconnected", client_names[msg_ret.client_id]);
      printf("%s disconnected, id = %d is free\n",
             client_names[msg_ret.client_id], msg_ret.client_id);
      broadcast(str_buffer, (int)strlen(str_buffer) + 1);

    }
  }
}
