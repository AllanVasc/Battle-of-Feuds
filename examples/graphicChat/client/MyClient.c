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

#define LARGURA 1024
#define ALTURA 768
#define MAX_LOG_SIZE 17

void printConnectScreen(char str[]);
void printChatLog( char chatLog[][MSG_MAX_SIZE]);
void printLobbyText(char str[]);
void printLoginScreen(char str[]);

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

int main() {

    int apertouBotaoPlay = 0, inMenu = 1, inGame = 0, apertouBotaoExit = 0, apertouBotaoHowtoPlay = 0, delay = 0, i, inChat = 0;

	
    //Variaveis do personagem!
	ALLEGRO_BITMAP *charSprite = NULL;		
	float larguraSprite = 42, alturaSprite = 52.5 ;
	int posXChar = 400, posYChar = 400;
	int linhaSprite = 0, colunaSprite = 0;

	int espacamentoHeart = 32;
    
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
 
    //Criamos uma nova estrutura que será enviada e recebida do servidor.
    DADOS pacote;

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

                }

                while(lobby){ //Momento das conversas!

                    startTimer();

                    int rec = recvMsgFromServer(&pacote, DONT_WAIT);

                    
                    if(rec != NO_MESSAGE){  //recebe as mensagens do servidor (jogador se conectou, avisos, etc)

                        //printf("RECEIVED: %s\n", pacote.mensagem);

                        for(i = 0; i < MAX_LOG_SIZE - 1; ++i)
                            strcpy(chatLog[i], chatLog[i+1]);
                            
                        strcpy(chatLog[MAX_LOG_SIZE - 1], pacote.mensagem);
                            
                        pacote.mensagem[0]='\0';

                    }

                    while(!al_is_event_queue_empty(eventsQueue)){

                        ALLEGRO_EVENT lobbyEvent;
                        al_wait_for_event(eventsQueue, &lobbyEvent);
                        readInput(lobbyEvent, lobbyMessage, MSG_MAX_SIZE);

                        if (lobbyEvent.type == ALLEGRO_EVENT_KEY_DOWN){

                            switch(lobbyEvent.keyboard.keycode){

                                case ALLEGRO_KEY_ENTER:
                                    strcpy(pacote.mensagem, lobbyMessage);
                                    sendMsgToServer(&pacote, sizeof(DADOS));
                                    lobbyMessage[0]='\0';
                                    break;

                                case ALLEGRO_KEY_LCTRL:				//Se apertar Left control começa o jogo

                                    printf("Jogo ira começar!\n");
                                    lobby = 0;
                                    inChat = 0;
                                    inGame = 1;
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


            while(inGame){  //Momento do jogo!    //MUDAR TUDO!!!!

                startTimer();	
                FPSLimit();
                al_draw_bitmap(BackgroundMenu,0, 0, 0);
                al_draw_text(fonteHTPTitulo, al_map_rgb(255, 255, 255), WIDTH / 2, (HEIGHT - al_get_font_ascent(fonteHTPTitulo)) / 2,ALLEGRO_ALIGN_CENTRE, "Em desenvolvimento...");
                al_flip_display();
                al_rest(10);	
                inGame = 0;	  

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