#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MSG_MAX_SIZE 350
#define BUFFER_SIZE (MSG_MAX_SIZE + 100)
#define LOGIN_MAX_SIZE 13
#define MAX_CHAT_CLIENTS 3

int main(){

    char client_names[MAX_CHAT_CLIENTS][LOGIN_MAX_SIZE];
    char str_buffer[BUFFER_SIZE];
    char aux_buffer[BUFFER_SIZE];
    serverInit(MAX_CHAT_CLIENTS);
    puts("Servidor está funcionando!\n");

    return 0;
}
