#include "ACore.h"
#include "client.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MSG_MAX_SIZE 350
#define BUFFER_SIZE (MSG_MAX_SIZE + 100)
#define LOGIN_MAX_SIZE 13
#define HIST_MAX_SIZE 200
#define MAX_CHAT_CLIENTS 6

#define LARGURA 1024
#define ALTURA 768
#define MAX_LOG_SIZE 17


//Variaveis globais

Inicio playersInGame;
Personagem posicoes[MAX_CHAT_CLIENTS];
Personagem pacotePersonagem;
DadosInGame pacoteInGame;
DADOS pacote;
DADOS auxID;
int meuID;

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


///////////Declarações de funções

void printConnectScreen(char str[]);
void printChatLog( char chatLog[][MSG_MAX_SIZE]);
void printLobbyText(char str[]);
void printLoginScreen(char str[]);
void printMap();
enum conn_ret_t tryConnect(char IP[]);
void assertConnection(char IP[], char login[]);
void printSprite();
void printHeart();

int main() {

    int apertouBotaoPlay = 0, inMenu = 1, inGame = 0, apertouBotaoExit = 0, apertouBotaoHowtoPlay = 0, delay = 0, inChat = 0;
    int i,k;
    
    if (!coreInit()) //Inicializando os modulos centrais
        return -1;

    if (!windowInit(LARGURA, ALTURA, "Battle Of Feuds")) //Criando a janela
        return -1;

    
    if (!inputInit()) //Agora inicializamos nosso teclado e mouse, para que a janela responda às entradas deles
        return -1;

    
    if(!fontInit()) //Agora inicializamos nossas fontes
      return -1;

    if(!loadGraphics()) //E por fim todas as imagens que vamos utilizar no programa.
        return -1;

    while (inMenu){

        while(!al_is_event_queue_empty(eventsQueue)){
            
            ALLEGRO_EVENT menuEvent;
            al_wait_for_event(eventsQueue, &menuEvent);

            if (menuEvent.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
			
				if (menuEvent.mouse.x >= 300 &&  // Verificamos se ele está sobre a região do botao play
					menuEvent.mouse.x <= 300 + al_get_bitmap_width(botaoPlay) &&
					menuEvent.mouse.y >= 350 &&
					menuEvent.mouse.y <= 350 + al_get_bitmap_height(botaoPlay) ){

					apertouBotaoPlay = 1;

					printf("Apertasse botão Play\n");

				}else if (menuEvent.mouse.x >= 300 &&  // Verificamos se ele está sobre a região do botao How to play
						  menuEvent.mouse.x <= 300 + al_get_bitmap_width(botaoHTP) &&
						  menuEvent.mouse.y >= 420 &&
						  menuEvent.mouse.y <= 420 + al_get_bitmap_height(botaoHTP) ){

					apertouBotaoHowtoPlay = 1;
					
					
					printf("Apertasse botão How to play\n");

				}else if (menuEvent.mouse.x >= 300 &&  // Verificamos se ele está sobre a região do botao Exit
						  menuEvent.mouse.x <= 300 + al_get_bitmap_width(botaoExit) &&
						  menuEvent.mouse.y >= 480 &&
						  menuEvent.mouse.y <= 480 + al_get_bitmap_height(botaoExit) ){

					inMenu = 0;
					
					printf("Apertasse botão Exit\n");

				}

            }

        }

        if(apertouBotaoPlay == 1){	//Logica do nosso jogo ficara aqui!

            
            char ServerIP[30]={"127.0.0.1"}; //Esse sera o IP do Server!
            int qtdCharIP = 9;
            char chatLog[MAX_LOG_SIZE][MSG_MAX_SIZE] = {{0}}; //para guardar o log do chat
            char lobbyMessage[110]={0}; //mensagem pra ser mandada no lobby
            char loginMsg[BUFFER_SIZE]={0}; //para guardar o login
            int connectScreen = 1;
            int loginScreen = 1;
            int lobby = 1;

            inChat = 1;

            while(inChat){	//Iniciando codigos do nosso chat!

                while(connectScreen){ //Tela para digitar o IP

                    startTimer();

                    while(!al_is_event_queue_empty(eventsQueue)){

                        ALLEGRO_EVENT connectEvent;
                        al_wait_for_event(eventsQueue, &connectEvent);

                        readInput(connectEvent, ServerIP, IP_MAX_SIZE);

                        if (connectEvent.type == ALLEGRO_EVENT_KEY_DOWN){

                            switch(connectEvent.keyboard.keycode){

                                case ALLEGRO_KEY_ENTER:
                                    connectScreen = 0;
                                    break;

                                case ALLEGRO_KEY_ESCAPE:
                                    connectScreen = 0;
                                    loginScreen = 0;
                                    lobby = 0;
                                    apertouBotaoPlay = 0;
                                    break;
                            }
                                
                        }

                    }

                    printConnectScreen(ServerIP);
                    al_flip_display();
                    FPSLimit();
                }

                if(connectScreen == 0 && loginScreen == 0 && lobby == 0){
                    break;
                }

                while(loginScreen){ 	//Tela para ler a entrada do login

                    startTimer();

                    while(!al_is_event_queue_empty(eventsQueue)){

                        ALLEGRO_EVENT loginEvent;
                        al_wait_for_event(eventsQueue, &loginEvent);

                        readInput(loginEvent, loginMsg, LOGIN_MAX_SIZE);

                        if (loginEvent.type == ALLEGRO_EVENT_KEY_DOWN){

                            switch(loginEvent.keyboard.keycode){

                                case ALLEGRO_KEY_ENTER:
                                    loginScreen = false;
                                    break;

                                case ALLEGRO_KEY_ESCAPE:
                                    connectScreen = 0;
                                    loginScreen = 0;
                                    lobby = 0;
                                    apertouBotaoPlay = 0;
                                    break;
                            }
                        }
                    }

                    printLoginScreen(loginMsg);
                    al_flip_display();
                    al_clear_to_color(al_map_rgb(0, 0, 0));
                    FPSLimit();
                }

                if(lobby == 1){
                    
                    //Função para realizar a conexão com o server
                    assertConnection(ServerIP, loginMsg);
                    recvMsgFromServer(&auxID, WAIT_FOR_IT);
                    meuID = auxID.valor;
                    printf("Meu ID eh: [%d]\n", meuID);

                }

                while(lobby){ //Momento das conversas!

                    startTimer();
                    int rec = recvMsgFromServer(&pacote, DONT_WAIT);

                    if(rec != NO_MESSAGE){  //recebe as mensagens do servidor (jogador se conectou, avisos, etc)

                        

                        if(pacote.valor == 1){  //Recebi uma mensagem e vamos printar 

                            for(i = 0; i < MAX_LOG_SIZE - 1; ++i)
                                strcpy(chatLog[i], chatLog[i+1]);
                            
                            strcpy(chatLog[MAX_LOG_SIZE - 1], pacote.mensagem);
                                           
                            pacote.mensagem[0]='\0';

                        }

                        if(pacote.valor == 2){  //Recebi que alguem começou!

                            lobby = 0;
                            inChat = 0;
                            inGame = 1;
                            printf("Outro player começou o jogo!\n");
                            break;
                        }

                    } 

                    while(!al_is_event_queue_empty(eventsQueue)){

                        rec = recvMsgFromServer(&pacote, DONT_WAIT);
                        if(rec != NO_MESSAGE){  //recebe as mensagens do servidor (jogador se conectou, avisos, etc)

                            if(pacote.valor == 1){

                                for(i = 0; i < MAX_LOG_SIZE - 1; ++i)
                                    strcpy(chatLog[i], chatLog[i+1]);
                            
                                strcpy(chatLog[MAX_LOG_SIZE - 1], pacote.mensagem);
                            
                                pacote.mensagem[0]='\0';  

                            }

                            if(pacote.valor == 2){ //Alguem apertou para começar e ira começar

                                lobby = 0;
                                inChat = 0;
                                inGame = 1;
                                printf("Outro player começou o jogo!\n");
                                break;
                            }

                        }

                        ALLEGRO_EVENT lobbyEvent;
                        al_wait_for_event(eventsQueue, &lobbyEvent);
                        readInput(lobbyEvent, lobbyMessage, MSG_MAX_SIZE);

                        if (lobbyEvent.type == ALLEGRO_EVENT_KEY_DOWN){

                            switch(lobbyEvent.keyboard.keycode){

                                case ALLEGRO_KEY_ENTER:

                                    pacote.valor = 1;
                                    strcpy(pacote.mensagem, lobbyMessage);
                                    sendMsgToServer(&pacote, sizeof(DADOS));
                                    lobbyMessage[0] = '\0';
                                    break;

                                case ALLEGRO_KEY_LCTRL:				//Se apertar Left control começa o jogo

                                    pacote.valor = 0;
                                    sendMsgToServer(&pacote, sizeof(DADOS));
                                    printf("Jogo ira começar!\n");
                                    break;
                            }
                        }
                    }

                    printLobbyText(lobbyMessage);
                    printChatLog(chatLog);
                    al_flip_display();
                    al_clear_to_color(al_map_rgb(0, 0, 0));
                    FPSLimit();
                }
            }

            recvMsgFromServer(&playersInGame, WAIT_FOR_IT);    //Recebendo os dados de todos os personagens para iniciar o jogo!
            printf("Dados de todos os jogadores recebidos!\n");
            printf("Quantidade de jogadores: [%d]\n", playersInGame.qtdPlayers);

            while(inGame){  //Momento do jogo!

                startTimer();
                int rec = recvMsgFromServer(&pacoteInGame, DONT_WAIT);

                if(rec != NO_MESSAGE){  //Atualizando a posição dos jogadores!

                    playersInGame.jogador[pacoteInGame.idClient].pos.posX = pacoteInGame.posX;
                    playersInGame.jogador[pacoteInGame.idClient].pos.posY = pacoteInGame.posY;

                }

                while(!al_is_event_queue_empty(eventsQueue)){

                    rec = recvMsgFromServer(&pacoteInGame, DONT_WAIT);

                    if(rec != NO_MESSAGE){  //Atualizando a posição dos jogadores!

                        playersInGame.jogador[pacoteInGame.idClient].pos.posX = pacoteInGame.posX;
                        playersInGame.jogador[pacoteInGame.idClient].pos.posY = pacoteInGame.posY;

                    }

                    ALLEGRO_EVENT inGameEvent;
                    al_wait_for_event(eventsQueue, &inGameEvent);

                    if (inGameEvent.type == ALLEGRO_EVENT_KEY_DOWN){

                        char mov;

                        switch(inGameEvent.keyboard.keycode){

                            case ALLEGRO_KEY_W:

                                if(map[(playersInGame.jogador[meuID].pos.posY) - 1][playersInGame.jogador[meuID].pos.posX] > 0 && (playersInGame.jogador[meuID].pos.posY) - 1 >= 0){

                                    mov = 'w';
                                    //Falta mudar as sprites!
                                    sendMsgToServer(&mov, sizeof(char));
                                    printf("Mandei comando: [%c]\n", mov);
                                }

                                break;

                            case ALLEGRO_KEY_S:

                                if(map[(playersInGame.jogador[meuID].pos.posY) + 1][playersInGame.jogador[meuID].pos.posX] > 0 && (playersInGame.jogador[meuID].pos.posY) + 1 < 32 ){

                                    mov = 's';  
                                    //Falta mudar as sprites!
                                    sendMsgToServer(&mov, sizeof(char));
                                    printf("Mandei comando: [%c]\n", mov);
                                }                              

                                break;

                            case ALLEGRO_KEY_A:

                                if(map[playersInGame.jogador[meuID].pos.posY][playersInGame.jogador[meuID].pos.posX -1] > 0 && (playersInGame.jogador[meuID].pos.posX) - 1 >= 0){

                                    mov = 'a';  
                                    //Falta mudar as sprites!
                                    sendMsgToServer(&mov, sizeof(char));
                                    printf("Mandei comando: [%c]\n", mov);
                                }
                                
                                break;

                            case ALLEGRO_KEY_D:

                                if(map[playersInGame.jogador[meuID].pos.posY][playersInGame.jogador[meuID].pos.posX + 1] > 0 && (playersInGame.jogador[meuID].pos.posX) + 1 < 32){

                                    mov = 'd';  
                                    //Falta mudar as sprites!
                                    sendMsgToServer(&mov, sizeof(char));
                                    printf("Mandei comando: [%c]\n", mov);
                                }
                                
                                break;
                        }
                    }
                }

                printMap();
                printSprite();
                printHeart();
                FPSLimit();	
                //inGame = 0; //Ira ficar preso, ajeitar quando botar a vida!	  
            } 
        }

        if(apertouBotaoHowtoPlay == 1){			//Tela How to play vai ficar aqui

            while(apertouBotaoHowtoPlay == 1){

                al_draw_bitmap(BackgroundMenu, 0, 0, 0); 	//Desenha as imagens
                al_draw_text(fonteHTPTitulo, al_map_rgb(255, 0, 0), 380, 100, ALLEGRO_ALIGN_LEFT, "How to play");
                al_draw_bitmap(HTPwasd, 200, 200, 0);
                al_draw_text(fonteHTP, al_map_rgb(255, 255, 0), 450, 300, ALLEGRO_ALIGN_LEFT, "Movimentaçao do personagem");
                al_draw_bitmap(HTPJ, 200, 310, 0);
                al_draw_text(fonteHTP, al_map_rgb(255, 255, 0), 450, 360, ALLEGRO_ALIGN_LEFT, "Ataque fraco");
                al_draw_bitmap(HTPK, 200, 370, 0);
                al_draw_text(fonteHTP, al_map_rgb(255, 255, 0), 450, 420, ALLEGRO_ALIGN_LEFT, "Ataque forte");
                al_draw_bitmap(HTPReturn, 300, 550, 0);
                al_flip_display(); //atualiza tela
                
                while(!al_is_event_queue_empty(eventsQueue)){

                    ALLEGRO_EVENT howToPlayEvent;
                    al_wait_for_event(eventsQueue, &howToPlayEvent);

                    if (howToPlayEvent.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
    
                        if (howToPlayEvent.mouse.x >= 300 &&  //Verificamos se ele está sobre a região do botao voltar
                            howToPlayEvent.mouse.x <= 300 + al_get_bitmap_width(HTPReturn) &&
                            howToPlayEvent.mouse.y >= 550 &&
                            howToPlayEvent.mouse.y <= 550 + al_get_bitmap_height(HTPReturn) ){

                            apertouBotaoHowtoPlay = 0;

                            printf("Apertasse botão voltar\n");
                        }
                    }

                    if(howToPlayEvent.keyboard.keycode == ALLEGRO_KEY_ESCAPE){

                        apertouBotaoHowtoPlay = 0;
                        printf("Saindo tela howtoplay!\n");

                    }
                }
            }
        }

            al_draw_bitmap(BackgroundMenu, 0, 0, 0); //Desenha as imagens
            al_draw_bitmap(gameIcon, 450, 70, 0);
            al_draw_bitmap(gameName, 200, 220, 0);
            al_draw_bitmap(botaoPlay, 300, 350, 0);
            al_draw_bitmap(botaoHTP, 300, 420, 0);
            al_draw_bitmap(botaoExit, 300, 480, 0);
            al_flip_display(); //atualiza tela

        }

  allegroEnd();
  return 0;
}

//========================================================FUNCTIONS========================================================

enum conn_ret_t tryConnect(char IP[]) {

  char server_ip[30];
  return connectToServer(IP);

}

void assertConnection(char IP[], char login[]) {

    puts("Chat sendo inicializado...");

    int connectScreen = 1;

    enum conn_ret_t ans = tryConnect(IP);

    while (ans != SERVER_UP){

        if (ans == SERVER_DOWN) {

			puts("Server is down!");
			al_show_native_message_box(main_window, "Battle Of Feuds", "O servidor esta inativo!", "Tente novamente", NULL, ALLEGRO_MESSAGEBOX_WARN);

		} else if (ans == SERVER_FULL) {

			puts("Server is full!");
			al_show_native_message_box(main_window, "Battle Of Feuds", "O servidor esta cheio!", "Tente novamente", NULL, ALLEGRO_MESSAGEBOX_WARN);

		} else if (ans == SERVER_CLOSED) {

			puts("Server is closed for new connections!");
			al_show_native_message_box(main_window, "Battle Of Feuds", "O servidor nao permite novas conexoes!", "Tente novamente", NULL, ALLEGRO_MESSAGEBOX_WARN);

		} else {

			puts("Server didn't respond to connection!");
			al_show_native_message_box(main_window, "Battle Of Feuds", "O servidor nao respondeu!", "Tente novamente", NULL, ALLEGRO_MESSAGEBOX_WARN);

		}

        while(connectScreen){ //Tela para digitar o IP novamente!

			startTimer();

			while(!al_is_event_queue_empty(eventsQueue)){

				ALLEGRO_EVENT connectEvent;
				al_wait_for_event(eventsQueue, &connectEvent);

				readInput(connectEvent, IP, IP_MAX_SIZE);

				if (connectEvent.type == ALLEGRO_EVENT_KEY_DOWN){

					switch(connectEvent.keyboard.keycode){

						case ALLEGRO_KEY_ENTER:
							connectScreen = 0;
							break;
					}
						
				}

			}

			printConnectScreen(IP);
			al_flip_display();
			FPSLimit();
		}

	printf("Tentando novamente a conexao!\n");
  
    ans = tryConnect(IP);
	connectScreen = 1;
    }
    
    int len = (int)strlen(login);
    sendMsgToServer(login, len + 1);

}

void printConnectScreen(char str[]){

    al_draw_bitmap(BackgroundMenu,0,0,0);

    al_draw_text(fonteHTPTitulo, al_map_rgb(255, 255, 255), WIDTH / 2, 30, ALLEGRO_ALIGN_CENTRE, "Digite o IP do server:");

    if (strlen(str) > 0){

        al_draw_text(fonteHTPTitulo, al_map_rgb(255, 255, 255), WIDTH / 2,
                     (HEIGHT - al_get_font_ascent(fonteHTPTitulo)) / 2,
                     ALLEGRO_ALIGN_CENTRE, str);
    }

    else{

        al_draw_text(fonteHTPTitulo, al_map_rgb(255, 255, 255), WIDTH / 2,
                     (HEIGHT - al_get_font_ascent(fonteHTPTitulo)) / 2,
                     ALLEGRO_ALIGN_CENTRE, "0.0.0.0");
    }
}


void printChatLog( char chatLog[][MSG_MAX_SIZE]){

    int i;
    int initialY = 100;
    int spacing = al_get_font_ascent(fonteHTP)+5;
    
    for(i = 0; i < MAX_LOG_SIZE; ++i){

        al_draw_text(fonteHTP, al_map_rgb(255, 255, 255), 40, initialY + (i*spacing), ALLEGRO_ALIGN_LEFT, chatLog[i]);
    }

}

void printLobbyText(char str[]){

    al_draw_bitmap(BackgroundMenu,0,0,0);

    al_draw_text(fonteHTPTitulo, al_map_rgb(255, 255, 255), 20, 30, ALLEGRO_ALIGN_LEFT, "Preparing to battle... Left Ctrl to start...");

    if (strlen(str) > 0){

        al_draw_text(fonteHTP, al_map_rgb(255, 255, 255), 20,
                     (HEIGHT - al_get_font_ascent(fonteHTP)) - 20,
                     ALLEGRO_ALIGN_LEFT, str);
    }
    else{

        al_draw_text(fonteHTP, al_map_rgb(255, 255, 255), 20,
                     (HEIGHT - al_get_font_ascent(fonteHTP)) - 20,
                     ALLEGRO_ALIGN_LEFT, "type anything to chat...");
    }

}

void printLoginScreen(char str[]){

    al_draw_bitmap(BackgroundMenu,0,0,0);

    al_draw_text(fonteHTPTitulo, al_map_rgb(255, 255, 255), WIDTH / 2, 30, ALLEGRO_ALIGN_CENTRE, "Digite o Login desejado: ");

    if (strlen(str) > 0) {
        al_draw_text(fonteHTP, al_map_rgb(255, 255, 255), WIDTH / 2,
                     (HEIGHT - al_get_font_ascent(fonteHTP)) / 2,
                     ALLEGRO_ALIGN_CENTRE, str);
    }

    else {

        al_draw_text(fonteHTP, al_map_rgb(255, 255, 255), WIDTH / 2,
                     (HEIGHT - al_get_font_ascent(fonteHTP)) / 2,
                     ALLEGRO_ALIGN_CENTRE, "<login>");
    }
}

void printMap(){

    int i,k;
    
    for(i = 0; i < 24; i++){ // Essa parte agora printa o map.

        for(int k = 0; k < 32; k++){

            if(map[i][k] == 6){
                            al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
                            al_draw_bitmap_region(pedra, 22*32, 34*32, 32, 32, k*32, i*32, 0); // piso de pedra 1,2
				}
				if(map[i][k] == 7){
                            al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
							al_draw_bitmap_region(pedra, 23*32, 34*32, 32, 32, k*32, i*32, 0); // piso de pedra 1,3
				}
				if(map[i][k] == 8){
                            al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
                            al_draw_bitmap_region(pedra, 21*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,1
				}
                if(map[i][k] == 9){
                            al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
							al_draw_bitmap_region(pedra, 23*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,3
				}
                if(map[i][k] == 10){
                            al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
                            al_draw_bitmap_region(pedra, 21*32, 36*32, 32, 32, k*32, i*32, 0); // piso de pedra 3,1
				}
				if(map[i][k] == 11){
                            al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
							al_draw_bitmap_region(pedra, 22*32, 36*32, 32, 32, k*32, i*32, 0); // piso de pedra 3,2
				}
				if(map[i][k] == 12){
                            al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
                            al_draw_bitmap_region(pedra, 23*32, 36*32, 32, 32, k*32, i*32, 0); // piso de pedra 3,3
				}
                if(map[i][k] == 13){
                            al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
							al_draw_bitmap_region(pedra, 22*32, 32*32, 32, 32, k*32, i*32, 0); // piso de pedra encaixe 1,1
				}
				if(map[i][k] == 14){
                            al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
							al_draw_bitmap_region(pedra, 22*32, 33*32, 32, 32, k*32, i*32, 0); // piso de pedra encaixe 2,1
                }
				if(map[i][k] == 15){
                            al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
                            al_draw_bitmap_region(pedra, 23*32, 33*32, 32, 32, k*32, i*32, 0); // piso de pedra encaixe 2,2
				}

				if(map[i][k] == 16){
                            al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
							al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
				}
		     	if(map[i][k] == 17){

		           	        al_draw_bitmap_region(grama, 0*32, 11*32, 32, 32, k*32, i*32, 0); // fundo padrao esquerda
				}
				if(map[i][k] == 18){

							al_draw_bitmap_region(grama, 1*32, 11*32, 32, 32, k*32, i*32, 0); // fundo padrao meio
				}
				if(map[i][k] == 19){

						    al_draw_bitmap_region(grama, 2*32, 11*32, 32, 32, k*32, i*32, 0); // fundo padrao direita
				}
				if(map[i][k] == 20){

							al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0); // fundo padrao liso
				}
                    //CERCA <0 (nao pode passar por cima)
                if(map[i][k] == -1){
                            al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
                            al_draw_bitmap_region(cerca, 0*32, 1*32, 32, 32, k*32, i*32, 0); // lado baixo
                            al_draw_bitmap_region(cerca, 0*32, 0*32, 32, 32, k*32, i*32, 0); // frente esq
				}
                if(map[i][k] == -2){
                            al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
                            al_draw_bitmap_region(cerca, 1*32, 0*32, 32, 32, k*32, i*32, 0); // frente meio
                }
                if(map[i][k] == -3){
                            al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
                            al_draw_bitmap_region(cerca, 0*32, 1*32, 32, 32, k*32, i*32, 0); // lado baixo
                            al_draw_bitmap_region(cerca, 2*32, 0*32, 32, 32, k*32, i*32, 0); // frente dir
                          
				}
                if(map[i][k] == -4){
                            al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
                            al_draw_bitmap_region(cerca, 0*32, 0*32, 32, 32, k*32, i*32, 0); // frente esq
                            al_draw_bitmap_region(cerca, 2*32, 1*32, 32, 32, k*32, i*32, 0); // lado cima
				}
                if(map[i][k] == -5){
                            al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
                            al_draw_bitmap_region(cerca, 1*32, 1*32, 32, 32, k*32, i*32, 0); // lado meio
				}
                if(map[i][k] == -6){
                            al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
                            al_draw_bitmap_region(cerca, 2*32, 0*32, 32, 32, k*32, i*32, 0); // frente dir
                            al_draw_bitmap_region(cerca, 2*32, 1*32, 32, 32, k*32, i*32, 0); // lado cima
				}

                //arco e flecha
                
                if(map[i][k] == -7){
                            	al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 4*32, 47*32, 32, 32, k*32, i*32, 0);
				}
                if(map[i][k] == -8){
                            	al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2;
                            al_draw_bitmap_region(obstaculos, 5*32, 47*32, 32, 32, k*32, i*32, 0);
				}
                if(map[i][k] == -9){
                           	al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 4*32, 48*32, 32, 32, k*32, i*32, 0);
				}
                if(map[i][k] == -10){
                           	al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 5*32, 48*32, 32, 32, k*32, i*32, 0);
				}
                if(map[i][k] == -11){
                            	al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 2*32, 48*32, 32, 32, k*32, i*32, 0);
				}
                if(map[i][k] == -12){
                            	al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 2*32, 49*32, 32, 32, k*32, i*32, 0);
				}
                if(map[i][k] == -13){
                            	al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 3*32, 49*32, 32, 32, k*32, i*32, 0);
				}

                //arvore com relogio

                if(map[i][k] == -14){
                            al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
                            al_draw_bitmap_region(obstaculos, 14*32, 9*32, 32, 32, k*32, i*32, 0);
				}
                if(map[i][k] == -15){
                            al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
                            al_draw_bitmap_region(obstaculos, 15*32, 9*32, 32, 32, k*32, i*32, 0);
				}
                if(map[i][k] == -16){
                            al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
                            al_draw_bitmap_region(obstaculos, 14*32, 10*32, 32, 32, k*32, i*32, 0);
				}
                if(map[i][k] == -17){
                            al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
                            al_draw_bitmap_region(obstaculos, 15*32, 10*32, 32, 32, k*32, i*32, 0);
				}
                if(map[i][k] == -18){
                             al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
                            al_draw_bitmap_region(obstaculos, 14*32, 11*32, 32, 32, k*32, i*32, 0);
				}
                if(map[i][k] == -19){
                             al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
                            al_draw_bitmap_region(obstaculos, 15*32, 11*32, 32, 32, k*32, i*32, 0);
				}
                if(map[i][k] == -20){
                             al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
                            al_draw_bitmap_region(obstaculos, 14*32, 12*32, 32, 32, k*32, i*32, 0);
				}
                if(map[i][k] == -21){
                             al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
                            al_draw_bitmap_region(obstaculos, 15*32, 12*32, 32, 32, k*32, i*32, 0);
				}
                
                
                //guilhotina
              
                if(map[i][k] == -22){ //cima guilhotina esq fora do palco
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 2*32, 44*32, 32, 32, k*32, i*32, 0);
				}
                if(map[i][k] == -23){ //cima guilhotina dir fora do palco
                           al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 3*32, 44*32, 32, 32, k*32, i*32, 0); //guilho
				}
                if(map[i][k] == -24){ // cima esq palco
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 2*32, 41*32, 32, 32, k*32, i*32, 0); //palco
                         
				}
                if(map[i][k] == -25){ //cima meio palco e meio esq guilho
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                           al_draw_bitmap_region(obstaculos, 3*32, 41*32, 32, 32, k*32, i*32, 0); //palco
                            al_draw_bitmap_region(obstaculos, 2*32, 45*32, 32, 32, k*32, i*32, 0); //guilho
				}
                if(map[i][k] == -26){ //cima dir palco e meio dir gilho
                             al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 4*32, 41*32, 32, 32, k*32, i*32, 0); //palco
                            al_draw_bitmap_region(obstaculos, 3*32, 45*32, 32, 32, k*32, i*32, 0); //guilho
				}
                if(map[i][k] == -27){ //meio esq palco 
                             al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 2*32, 42*32, 32, 32, k*32, i*32, 0); //palco
                            
				}
                if(map[i][k] == -28){ //meio meio palco e baixo esq guilho
                             al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 3*32, 42*32, 32, 32, k*32, i*32, 0); //palco
                            al_draw_bitmap_region(obstaculos, 2*32, 46*32, 32, 32, k*32, i*32, 0); //guilho
				}
                if(map[i][k] == -29){ //meio dir palco e baixo dir guilho
                             al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                           al_draw_bitmap_region(obstaculos, 4*32, 42*32, 32, 32, k*32, i*32, 0); //palco
                            al_draw_bitmap_region(obstaculos, 3*32, 46*32, 32, 32, k*32, i*32, 0); //guilho
				}
                if(map[i][k] == -30){ //baixo esq palco
                             al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 2*32, 43*32, 32, 32, k*32, i*32, 0);
				}
                  if(map[i][k] == -31){ //baixo meio palco
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 3*32, 43*32, 32, 32, k*32, i*32, 0);
				}
                if(map[i][k] == -32){ //baixo dir palco
                           al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 4*32, 43*32, 32, 32, k*32, i*32, 0);
				}

                // barraquinha peq

                 if(map[i][k] == -33){ //toldo cima
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); 
                            al_draw_bitmap_region(obstaculos, 5*32, 25*32, 32, 32, k*32, i*32, 0);
				}
                if(map[i][k] == -34){ //toldo meio
                           al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 5*32, 26*32, 32, 32, k*32, i*32, 0); 
				}
                if(map[i][k] == -35){ //toldo baixo e barraca cima
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 5*32, 28*32, 32, 32, k*32, i*32, 0); 
                            al_draw_bitmap_region(obstaculos, 5*32, 27*32, 32, 32, k*32, i*32, 0); 
                         
				}
                if(map[i][k] == -36){ //barraca baixo
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 5*32, 29*32, 32, 32, k*32, i*32, 0); 
                            
				}

                // barraca grande

                if(map[i][k] == -37){ //toldo cima esq
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 6*32, 25*32, 32, 32, k*32, i*32, 0);
				}
                if(map[i][k] == -38){ //toldo cima dir
                             al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 7*32, 25*32, 32, 32, k*32, i*32, 0); 
                            
				}
                if(map[i][k] == -39){ //toldo meio esq
                             al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 6*32, 26*32, 32, 32, k*32, i*32, 0); 
				}
                if(map[i][k] == -40){ //toldo meio dir
                             al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 7*32, 26*32, 32, 32, k*32, i*32, 0);
				}
                if(map[i][k] == -41){ //toldo baixo esq e barraca cima esq
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 6*32, 28*32, 32, 32, k*32, i*32, 0); //barraca
                            al_draw_bitmap_region(obstaculos, 6*32, 27*32, 32, 32, k*32, i*32, 0); //toldo
				}
                if(map[i][k] == -42){ //toldo baixo dir e barraca cima dir
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 7*32, 28*32, 32, 32, k*32, i*32, 0); 
                            al_draw_bitmap_region(obstaculos, 7*32, 27*32, 32, 32, k*32, i*32, 0); 
				}
                if(map[i][k] == -43){ //barraca baixo esq
                           al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 6*32, 29*32, 32, 32, k*32, i*32, 0);
				}
                if(map[i][k] == -44){ //barraca baixo dir
                           al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 7*32, 29*32, 32, 32, k*32, i*32, 0);
				}
               

                    // agua
                if(map[i][k] == -45){
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 415, 576, 32, 32, k*32, i*32, 0);
				}
                if(map[i][k] == -46){
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 447, 576, 32, 32, k*32, i*32, 0 );
				}
                if(map[i][k] == -47){
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 479, 576, 32, 32, k*32, i*32, 0 );
				}
                
                // cemiterio
                if(map[i][k] == -48){
                            al_draw_bitmap_region(grama, 0*32, 11*32, 32, 32, k*32, i*32, 0); 
                            al_draw_bitmap_region(obstaculos, 2*32, 2*32, 32, 32, k*32, i*32, 0);
				}
                if(map[i][k] == -49){
                            al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
                            al_draw_bitmap_region(obstaculos, 3*32, 4*32, 32, 32, k*32, i*32, 0 );
				}
                if(map[i][k] == -50){
                            al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
                            al_draw_bitmap_region(obstaculos, 4*32, 3*32, 32, 32, k*32, i*32, 0 );
				}

                // fonte
                if(map[i][k] == -51){
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 0*32, 18*32, 32, 32, k*32, i*32, 0);
				}
                if(map[i][k] == -52){
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 1*32, 18*32, 32, 32, k*32, i*32, 0 );
				}
                if(map[i][k] == -53){
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 0*32, 19*32, 32, 32, k*32, i*32, 0 );
				}
                if(map[i][k] == -54){
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 1*32, 19*32, 32, 32, k*32, i*32, 0 );
				}

                // poço
                if(map[i][k] == -55){
                            al_draw_bitmap_region(grama, 0*32, 11*32, 32, 32, k*32, i*32, 0); 
                            al_draw_bitmap_region(obstaculos, 14*32, 13*32, 32, 32, k*32, i*32, 0);
				}
                if(map[i][k] == -56){
                            al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
                            al_draw_bitmap_region(obstaculos, 15*32, 13*32, 32, 32, k*32, i*32, 0 );
				}
                if(map[i][k] == -57){
                            al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
                            al_draw_bitmap_region(obstaculos, 14*32, 14*32, 32, 32, k*32, i*32, 0 );
				}
                if(map[i][k] == -58){
                            al_draw_bitmap_region(grama, 0*32, 11*32, 32, 32, k*32, i*32, 0); 
                            al_draw_bitmap_region(obstaculos, 15*32, 14*32, 32, 32, k*32, i*32, 0);
				}
                if(map[i][k] == -59){
                            al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
                            al_draw_bitmap_region(obstaculos, 14*32, 15*32, 32, 32, k*32, i*32, 0 );
				}
                if(map[i][k] == -60){
                            al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
                            al_draw_bitmap_region(obstaculos, 15*32, 15*32, 32, 32, k*32, i*32, 0 );
				}

                //sacas e saquinhos
                if(map[i][k] == -61){ //sacas 1,1
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(objetos, 9*32, 8*32, 32, 32, k*32, i*32, 0 );
				}
                if(map[i][k] == -62){ //sacas 1,2
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(objetos, 10*32, 8*32, 32, 32, k*32, i*32, 0 );
				}
                if(map[i][k] == -63){ //sacas 2,1
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(objetos, 9*32, 9*32, 32, 32, k*32, i*32, 0 );
				}
                if(map[i][k] == -64){ //sacas 2,2
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(objetos, 10*32, 9*32, 32, 32, k*32, i*32, 0 );
				}
                if(map[i][k] == -65){ //saquinho 1
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(objetos, 7*32, 10*32, 32, 32, k*32, i*32, 0 );
				}
                if(map[i][k] == -66){ //saquinho 2
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(objetos, 8*32, 10*32, 32, 32, k*32, i*32, 0 );
				}

                 // barraquinha com produtos

                 if(map[i][k] == -67){ //toldo cima esq
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); 
                            al_draw_bitmap_region(objetos, 12*32, 0*32, 32, 32, k*32, i*32, 0);
				}
                if(map[i][k] == -68){ //toldo meio esq
                           al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(objetos, 13*32, 0*32, 32, 32, k*32, i*32, 0); 
				}
                if(map[i][k] == -69){ //toldo meio dir
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(objetos, 14*32, 0*32, 32, 32, k*32, i*32, 0);                          
				}
                if(map[i][k] == -70){ //toldo dir
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(objetos, 15*32, 0*32, 32, 32, k*32, i*32, 0);                
                }
                if(map[i][k] == -71){ //meio esq
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(objetos, 12*32, 1*32, 32, 32, k*32, i*32, 0);
				}
                if(map[i][k] == -72){ //meio meio esq
                             al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(objetos, 13*32, 1*32, 32, 32, k*32, i*32, 0);             
				}
                if(map[i][k] == -73){ //meio meio dir
                             al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(objetos, 14*32, 1*32, 32, 32, k*32, i*32, 0); 
				}
                if(map[i][k] == -74){ //meio dir
                             al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(objetos, 15*32, 1*32, 32, 32, k*32, i*32, 0);
				}
                if(map[i][k] == -75){ //barraca baixo esq
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(objetos, 12*32, 2*32, 32, 32, k*32, i*32, 0); //barraca                          
				}
                if(map[i][k] == -76){ //barraca baixo meio esq
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(objetos, 13*32, 2*32, 32, 32, k*32, i*32, 0);  
				}
                if(map[i][k] == -77){ //barraca baixo meio dir
                           al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(objetos, 14*32, 2*32, 32, 32, k*32, i*32, 0);
				}
                if(map[i][k] == -78){ //barraca baixo dir
                           al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(objetos, 15*32, 2*32, 32, 32, k*32, i*32, 0);
				}

                //lenha e corte
                 if(map[i][k] == -79){ //lenha 1,1
                            al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
                            al_draw_bitmap_region(objetos, 7*32, 11*32, 32, 32, k*32, i*32, 0 );
				}
                if(map[i][k] == -80){ //lenha 1,2
                            al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
                            al_draw_bitmap_region(objetos, 8*32, 11*32, 32, 32, k*32, i*32, 0 );
				}
                if(map[i][k] == -81){ //lenha 2,1
                            al_draw_bitmap_region(grama, 0*32, 11*32, 32, 32, k*32, i*32, 0); 
                            al_draw_bitmap_region(objetos, 7*32, 12*32, 32, 32, k*32, i*32, 0);
				}
                if(map[i][k] == -82){ //lenha 2,2
                            al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
                            al_draw_bitmap_region(objetos, 8*32, 12*32, 32, 32, k*32, i*32, 0 );
				}
                if(map[i][k] == -83){ //corte
                            al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
                            al_draw_bitmap_region(objetos, 15*32, 3*32, 32, 32, k*32, i*32, 0 );
				}

                //forca

               
                if(map[i][k] == -84){ //toldo baixo esq e barraca cima esq
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 0*32, 1423, 32, 32, k*32, i*32, 0); //barraca
                            
				}
                if(map[i][k] == -85){ //toldo baixo dir e barraca cima dir
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 1*32, 1423, 32, 32, k*32, i*32, 0); 
                           
				}
                if(map[i][k] == -86){ //barraca baixo esq
                           al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 0*32, 1455, 32, 32, k*32, i*32, 0);
				}
                if(map[i][k] == -87){ //barraca baixo esq
                           al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 1*32, 1455, 32, 32, k*32, i*32, 0);
				}

                // mesinha
                if(map[i][k] == -88){ //banco cima cima esq
                             al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                             al_draw_bitmap_region(obstaculos, 6*32, 35*32, 32, 32, k*32, i*32, 0); 
				}
                if(map[i][k] == -89){ // banco cima cima dir
                             al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                             al_draw_bitmap_region(obstaculos, 7*32, 35*32, 32, 32, k*32, i*32, 0);
				}
                if(map[i][k] == -90){ //banco cima baixo esq e mesa esq
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 6*32, 36*32, 32, 32, k*32, i*32, 0);  // banco                    
				}
                if(map[i][k] == -91){ //banco cima baixo dir e mesa dir
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 7*32, 36*32, 32, 32, k*32, i*32, 0); 
                            
				}
                if(map[i][k] == -92){ //banco baixo esq
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 6*32, 34*32, 32, 32, k*32, i*32, 0);
				}
                if(map[i][k] == -93){ //banco baixo dir
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 7*32, 34*32, 32, 32, k*32, i*32, 0);
				}
                if(map[i][k] == -94){ //banco baixo dir
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 8*32, 34*32, 32, 32, k*32, i*32, 0);  // mesa 
				}
                if(map[i][k] == -95){ //banco baixo dir
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 9*32, 34*32, 32, 32, k*32, i*32, 0); 
				}
		}
	}
}

void printSprite(){

    int i,k;
    //Variaveis do personagem!
	ALLEGRO_BITMAP *charSprite = NULL;		
	float larguraSprite = 42, alturaSprite = 52.5 ;
	int posXChar = 400, posYChar = 400;
	int linhaSprite = 0, colunaSprite = 0;

    charSprite = al_load_bitmap("examples/graphicChat/Resources/Tilesets/PreviewSprite.png");

    for(i = 0 ; i < playersInGame.qtdPlayers ; i++){

        int x = playersInGame.jogador[i].pos.posX;
        int y = playersInGame.jogador[i].pos.posY;

        al_draw_bitmap_region(charSprite, 0 , 0 ,larguraSprite, alturaSprite , x*32 , y*32 , 0);
    }

    al_flip_display();

}

void printHeart(){

    int i, espacamentoHeart = 32;

    for(i = 0; i < playersInGame.jogador[meuID].vida; i++){

        al_draw_bitmap(heart, i*espacamentoHeart, 0 , 0);

    }

}




/*

for(i = 0 ; i < playersInGame.qtdPlayers ; i++){

    int x = playersInGame.jogador[i].pos.posX;
    int y = playersInGame.jogador[i].pos.posY;
    posicoes[i] = playersInGame.jogador[i];
    map[y][x] = playersInGame.jogador[i].qualPers; //Atribuindo o id do jogador nessa posição!

}

*/