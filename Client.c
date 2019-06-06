// Os arquivos de cabeçalho
#include <stdio.h>
#include <ctype.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

//Includes utilizado nas funções do server
#include <termios.h>
#include <poll.h>
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

//Atributos importantes
#define LARGURA_TELA 940
#define ALTURA_TELA 780
#define FPS 60.0

//Configurações do chat

#define MSG_MAX_SIZE 350
#define BUFFER_SIZE (MSG_MAX_SIZE + 100)
#define LOGIN_MAX_SIZE 13
#define HIST_MAX_SIZE 200
#define MAX_LOG_SIZE 17
#define IP_MAX_SIZE 100
#define READ_CONN_TIMEOUT 6
#define NO_KEY_PRESSED '\0'
#define NO_MESSAGE -1
#define SERVER_DISCONNECTED -2
#define WAIT_FOR_IT 1
#define DONT_WAIT 2
#define PORT 9005
#define SELECT_TIMEOUT 300

//Structs para o envio do servidor
enum conn_msg_t {
  SUCCESSFUL_CONNECTION,
  TOO_MANY_CLIENTS,
  CONNECTIONS_CLOSED
};

enum conn_ret_t {
  SERVER_UP,
  SERVER_DOWN,
  SERVER_FULL,
  SERVER_CLOSED,
  SERVER_TIMEOUT
};

typedef struct DADOS{

    char mensagem[100];
    int valor;

}DADOS;

//////////Variaveis globais!
int network_socket;
fd_set sock_fd_set;
DADOS pacote;
double startingTime;

//////////DECLARAÇÕES PREVIAS DAS FUNÇÕES
void startTimer();
double getTimer();
void FPSLimit();
void readInput(ALLEGRO_EVENT event, char str[], int limit);
void ChecaPonteiro(void * ptr, char erro[50]);
void assertConnection(char IP[], char login[], ALLEGRO_DISPLAY *janela, ALLEGRO_EVENT_QUEUE *filaEventosChat,ALLEGRO_BITMAP *BackgroundMenu,ALLEGRO_FONT *fonteHTPTitulo,ALLEGRO_FONT *fonteHTP);
enum conn_ret_t tryConnect(char IP[]);
int sendMsgToServer(void *msg, int size);
enum conn_ret_t connectToServer(const char *server_IP);
int recvMsgFromServer(void *msg, int option);
void closeConnection();
void printLoginScreen(char str[], ALLEGRO_BITMAP * BackgroundMenu, ALLEGRO_FONT * fonteHTPTitulo, ALLEGRO_FONT * fonteHTP );
void printConnectScreen(char str[],ALLEGRO_BITMAP * BackgroundMenu, ALLEGRO_FONT * fonteHTPTitulo, ALLEGRO_FONT * fonteHTP);
void printLobbyText(char str[], ALLEGRO_BITMAP * BackgroundMenu,ALLEGRO_FONT * fonteHTPTitulo, ALLEGRO_FONT * fonteHTP);
void printChatLog( char chatLog[][MSG_MAX_SIZE], ALLEGRO_FONT * fonteHTP );

int main(){
	
	ALLEGRO_DISPLAY *janela = NULL;
	ALLEGRO_BITMAP *BackgroundMenu = NULL, *gameName = NULL, *gameIcon = NULL, *HTPwasd = NULL, *HTPJ = NULL, *HTPK = NULL, *HTPReturn = NULL, *botaoPlay = NULL, *botaoHTP = NULL, *botaoExit = NULL, *mapa = NULL;
	ALLEGRO_EVENT_QUEUE *filaEventosMouse = NULL, *filaEventosTimer = NULL; 
	ALLEGRO_EVENT evento;	
	ALLEGRO_FONT *fonteHTP = NULL, *fonteHTPTitulo = NULL;
	ALLEGRO_TIMER *timer = NULL;
	int apertouBotaoPlay = 0, inMenu = 1, inGame = 0, apertouBotaoExit = 0, apertouBotaoHowtoPlay = 0, delay = 0, i;

	//Variaveis do chat! 
	ALLEGRO_EVENT_QUEUE *filaEventosChat = NULL;
	int inChat = 0;

	ALLEGRO_BITMAP *charSprite = NULL;		//Variaveis do personagem!
	float larguraSprite = 42, alturaSprite = 52.5 ;
	int posXChar = 400, posYChar = 400;
	int linhaSprite = 0, colunaSprite = 0;

	al_init();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_mouse();
	al_install_keyboard();

	janela = al_create_display(LARGURA_TELA, ALTURA_TELA); //cria display em janela
	al_set_window_title(janela, "Battle Of Feuds"); 	// Configura o título da janela
	al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);	// Atribui o cursor padrão do sistema para ser usado

	ChecaPonteiro(janela, "Erro na janela"); 	//Checa erro!

	BackgroundMenu = al_load_bitmap("BackgroundMenu.png"); 	//carrega imagem
	gameName = al_load_bitmap("BattleOfFeudsName.png");
	gameIcon = al_load_bitmap("BattleOfFeudsIcon.png");
	botaoPlay = al_load_bitmap("StartGameButton01.png");
	botaoHTP = al_load_bitmap("HowToPlayButton01.png");
	botaoExit = al_load_bitmap("ExitButton01.png");
	HTPwasd = al_load_bitmap("HTPwasd.png");
	HTPJ = al_load_bitmap("HTPJ.png");
	HTPK = al_load_bitmap("HTPK.png");
	HTPReturn = al_load_bitmap("HTPReturn.png");
	mapa = al_load_bitmap("PreviewMap.png");
	charSprite = al_load_bitmap("PreviewSprite.png");

	ChecaPonteiro(BackgroundMenu, "Erro no BackgroundMenu"); 			//Checa erro!
	ChecaPonteiro(gameName, "Erro no gamename"); 						//Checa erro!
	ChecaPonteiro(gameIcon, "Erro no gameIcon"); 						//Checa erro!
	ChecaPonteiro(botaoPlay, "Erro no botaoplay"); 						//Checa erro!
	ChecaPonteiro(botaoHTP, "Erro no botaoHTP"); 						//Checa erro!
	ChecaPonteiro(botaoExit, "Erro no botaoExit"); 						//Checa erro!
	ChecaPonteiro(HTPwasd, "Erro no HTPwasd"); 							//Checa erro!
	ChecaPonteiro(HTPJ, "Erro no HTPJ"); 								//Checa erro!
	ChecaPonteiro(HTPK, "Erro no HTPK"); 								//Checa erro!
	ChecaPonteiro(HTPReturn, "Erro no HTPReturn"); 						//Checa erro!
	ChecaPonteiro(mapa, "Erro no mapa"); 								//Checa erro!
	ChecaPonteiro(charSprite, "Erro no charSprite"); 					//Checa erro!

	fonteHTP = al_load_font("Amita-Regular.ttf", 30, 0);
	fonteHTPTitulo = al_load_font("Amita-Bold.ttf", 50, 0);

	ChecaPonteiro(fonteHTP, "Erro no fonteHTP");
	ChecaPonteiro(fonteHTPTitulo, "Erro no fonteHTPTitulo");

	timer = al_create_timer(1.0 / FPS); 		//Criado o temporizador do time

	ChecaPonteiro(timer, "Erro no timer");   							//Checa erro!

	filaEventosMouse = al_create_event_queue(); //Cria as filas de eventos!
	filaEventosTimer = al_create_event_queue();
	filaEventosChat = al_create_event_queue();

	ChecaPonteiro(filaEventosMouse, "Erro na fila de eventos Mouse"); 	//Checa erro!
	ChecaPonteiro(filaEventosTimer, "Erro em filaEventosTimer"); 	//Checa erro! 
	ChecaPonteiro(filaEventosChat, "Erro em filaEventosChat"); 	//Checa erro!

	al_register_event_source(filaEventosMouse, al_get_mouse_event_source());	//Fontes dos eventos!
	al_register_event_source(filaEventosMouse, al_get_keyboard_event_source());
	al_register_event_source(filaEventosTimer, al_get_timer_event_source(timer));

	

	al_draw_bitmap(BackgroundMenu, 0, 0, 0); //Desenha as imagens
	al_draw_bitmap(gameIcon, 450, 70, 0);
	al_draw_bitmap(gameName, 200, 220, 0);
	al_draw_bitmap(botaoPlay, 300, 350, 0);
	al_draw_bitmap(botaoHTP, 300, 420, 0);
	al_draw_bitmap(botaoExit, 300, 480, 0);
	al_flip_display(); 						//atualiza tela
	
	printf("Jogo iniciado com sucesso\n");

	while (inMenu){

		al_wait_for_event(filaEventosMouse, &evento);

			if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
			
				if (evento.mouse.x >= 300 &&  // Verificamos se ele está sobre a região do botao play
					evento.mouse.x <= 300 + al_get_bitmap_width(botaoPlay) &&
					evento.mouse.y >= 350 &&
					evento.mouse.y <= 350 + al_get_bitmap_height(botaoPlay) ){

					apertouBotaoPlay = 1;
					inGame = 1;

					printf("Apertasse botão Play\n");

				}else if (evento.mouse.x >= 300 &&  // Verificamos se ele está sobre a região do botao How to play
						  evento.mouse.x <= 300 + al_get_bitmap_width(botaoHTP) &&
						  evento.mouse.y >= 420 &&
						  evento.mouse.y <= 420 + al_get_bitmap_height(botaoHTP) ){

					apertouBotaoHowtoPlay = 1;
					
					
					printf("Apertasse botão How to play\n");

				}else if (evento.mouse.x >= 300 &&  // Verificamos se ele está sobre a região do botao Exit
						  evento.mouse.x <= 300 + al_get_bitmap_width(botaoExit) &&
						  evento.mouse.y >= 480 &&
						  evento.mouse.y <= 480 + al_get_bitmap_height(botaoExit) ){

					inMenu = 0;
					
					printf("Apertasse botão Exit\n");

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

					filaEventosChat = al_create_event_queue();	//Reiniciando fila de Eventos!
					al_register_event_source(filaEventosChat, al_get_mouse_event_source());	//Fontes dos eventos!
					al_register_event_source(filaEventosChat, al_get_keyboard_event_source());
					al_register_event_source(filaEventosChat, al_get_display_event_source(janela));

					while(inChat){	//Iniciando codigos do nosso chat!

						while(connectScreen){ //Tela para digitar o IP

							startTimer();

							while(!al_is_event_queue_empty(filaEventosChat)){

								ALLEGRO_EVENT connectEvent;
								al_wait_for_event(filaEventosChat, &connectEvent);

								readInput(connectEvent, ServerIP, IP_MAX_SIZE);

								if (connectEvent.type == ALLEGRO_EVENT_KEY_DOWN){

									switch(connectEvent.keyboard.keycode){

										case ALLEGRO_KEY_ENTER:
											connectScreen = 0;
											break;
									}
										
								}

							}

							printConnectScreen(ServerIP,BackgroundMenu,fonteHTPTitulo,fonteHTP);
							al_flip_display();
							FPSLimit();
						}

						while(loginScreen){ 	//Tela para ler a entrada do login

							startTimer();

							while(!al_is_event_queue_empty(filaEventosChat)){

								ALLEGRO_EVENT loginEvent;
								al_wait_for_event(filaEventosChat, &loginEvent);

								readInput(loginEvent, loginMsg, LOGIN_MAX_SIZE);

								if (loginEvent.type == ALLEGRO_EVENT_KEY_DOWN){

									switch(loginEvent.keyboard.keycode){

										case ALLEGRO_KEY_ENTER:
											loginScreen = false;
											break;
									}
								}
							}

							printLoginScreen(loginMsg,BackgroundMenu,fonteHTPTitulo,fonteHTP);
							al_flip_display();
							al_clear_to_color(al_map_rgb(0, 0, 0));
							FPSLimit();
						}

						//Função para realizar a conexão com o server
    					assertConnection(ServerIP, loginMsg,janela, filaEventosChat,BackgroundMenu,fonteHTPTitulo,fonteHTP);

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

							while(!al_is_event_queue_empty(filaEventosChat)){

								ALLEGRO_EVENT lobbyEvent;
								al_wait_for_event(filaEventosChat, &lobbyEvent);
								readInput(lobbyEvent, lobbyMessage, MSG_MAX_SIZE);

								if (lobbyEvent.type == ALLEGRO_EVENT_KEY_DOWN){

									switch(lobbyEvent.keyboard.keycode){

										case ALLEGRO_KEY_ENTER:
											strcpy(pacote.mensagem, lobbyMessage);
											sendMsgToServer(&pacote, sizeof(DADOS));
											lobbyMessage[0]='\0';
											break;
									}
								}

								if(lobbyEvent.type == ALLEGRO_EVENT_KEY_DOWN){ //Se apertar LeftShifht começa o jogo

									switch(lobbyEvent.keyboard.keycode){
										case ALLEGRO_KEY_LCTRL:
											printf("Jogo ira começar!\n");
											lobby = 0;
									}
								}
							}

							printLobbyText(lobbyMessage,BackgroundMenu, fonteHTPTitulo, fonteHTP);
							printChatLog(chatLog, fonteHTP);
							al_flip_display();
							al_clear_to_color(al_map_rgb(0, 0, 0));
							FPSLimit();
						}

						inChat = 0;
					}

					al_start_timer(timer);
					al_destroy_event_queue(filaEventosMouse); 
					al_destroy_event_queue(filaEventosChat);

					while(inGame){

						startTimer();			  

						al_draw_bitmap(BackgroundMenu, 0, 0, 0);
						al_draw_bitmap(mapa, 0, 0, 0);			
						al_draw_bitmap_region(charSprite,colunaSprite*larguraSprite,linhaSprite*alturaSprite,larguraSprite,alturaSprite,posXChar,posYChar,0); //Desenha só uma regiao do sprite!
						al_flip_display();

						if(colunaSprite%2 != 0 && delay > 15){
							colunaSprite++;
							if(colunaSprite == 4){
								colunaSprite = 0;
							}
							al_draw_bitmap(BackgroundMenu, 0, 0, 0);
							al_draw_bitmap(mapa, 0, 0, 0);			
							al_draw_bitmap_region(charSprite,colunaSprite*larguraSprite,linhaSprite*alturaSprite,larguraSprite,alturaSprite,posXChar,posYChar,0); //Desenha só uma regiao do sprite!
							al_flip_display();


						}

						// A verificação das teclas acontece sem o uso de eventos para reduzir o lag
						ALLEGRO_KEYBOARD_STATE keyState;
						al_get_keyboard_state(&keyState);

						if ( al_key_down(&keyState, ALLEGRO_KEY_ESCAPE) && delay > 10 ){		

							ALLEGRO_KEY_ESCAPE: 	
							inGame = 0;
							apertouBotaoPlay = 0;
							printf("Apertasse botão ESC\n");

						} else if ( al_key_down(&keyState, ALLEGRO_KEY_W) && delay > 10 ){
							
							if(posYChar - 5 > 0){
								linhaSprite = 1;
								colunaSprite++;
								if(colunaSprite == 4){
									colunaSprite = 0;
								}
								posYChar -= 5;
							}
							delay = 0;

						}else if ( al_key_down(&keyState, ALLEGRO_KEY_S) && delay > 10 ){	

							if(posYChar + 5 < 780 - 50){

								linhaSprite = 0;
								colunaSprite++;
								if(colunaSprite == 4){
									colunaSprite = 0;
								}
								posYChar += 5 ;
							}
							delay = 0;

						}else if ( al_key_down(&keyState, ALLEGRO_KEY_A) && delay > 10 ){	

							if(posXChar - 5 > 0){

								linhaSprite = 2;
								colunaSprite++;
								if(colunaSprite == 4){
									colunaSprite = 0;
								}
								posXChar -= 5 ;
							}
							delay = 0;

						}else if ( al_key_down(&keyState, ALLEGRO_KEY_D) && delay > 10 ){	

							if(posXChar + 5 < 940 - 40){

								linhaSprite = 3;
								colunaSprite++;
								if(colunaSprite == 4){
									colunaSprite = 0;
								}
								posXChar += 5 ;
							}
							delay = 0;

						}else if ( al_key_down(&keyState, ALLEGRO_KEY_J) && delay > 10 ){	
							
							printf("Ataque fraco!\n");
							delay = 0;

						}else if ( al_key_down(&keyState, ALLEGRO_KEY_K) && delay > 10 ){	
							
							printf("Ataque forte!\n");
							delay = 0;
						}

					delay++;
					FPSLimit();

					} 

					filaEventosMouse = al_create_event_queue();	//Reiniciando fila de Eventos!
					al_register_event_source(filaEventosMouse, al_get_mouse_event_source());	
					al_register_event_source(filaEventosMouse, al_get_keyboard_event_source());
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

						al_wait_for_event(filaEventosMouse, &evento);

						if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
			
							if (evento.mouse.x >= 300 &&  //Verificamos se ele está sobre a região do botao voltar
								evento.mouse.x <= 300 + al_get_bitmap_width(HTPReturn) &&
								evento.mouse.y >= 550 &&
								evento.mouse.y <= 550 + al_get_bitmap_height(HTPReturn) ){

								apertouBotaoHowtoPlay = 0;

								printf("Apertasse botão voltar\n");
							}
						}

						if (evento.type == ALLEGRO_EVENT_KEY_DOWN){

							if(evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE){

								apertouBotaoHowtoPlay = 0;
								printf("Apertasse botão ESC\n");

							}

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

	//destroi janela e fila de eventos ao fim
	al_destroy_display(janela);
	al_destroy_bitmap(BackgroundMenu);
	al_destroy_bitmap(gameName);
	al_destroy_bitmap(gameIcon);
	al_destroy_bitmap(botaoPlay);
	al_destroy_bitmap(botaoHTP);
	al_destroy_bitmap(botaoExit);
	al_destroy_bitmap(HTPwasd);
	al_destroy_bitmap(HTPJ);
	al_destroy_bitmap(HTPK);
	al_destroy_bitmap(HTPReturn);
	al_destroy_bitmap(mapa);
    al_destroy_timer(timer);
	al_destroy_event_queue(filaEventosMouse);
	al_destroy_event_queue(filaEventosTimer);
	return 0;
}

//========================================================FUNCTIONS========================================================\\

void ChecaPonteiro(void * ptr, char erro[50]){

	if(ptr == NULL){

		printf("Deu merda em: [%s]\n", erro);
		exit(0);
	}

}

void startTimer(){
    startingTime = al_get_time();
}

double getTimer(){
    return al_get_time() - startingTime;
}

void FPSLimit(){
	if (getTimer() < 1.0/FPS) {
        al_rest((1.0 / FPS) - getTimer());
    }
}

//Função para ler as entradas do teclado de maneira otimizada
void readInput(ALLEGRO_EVENT event, char str[], int limit){

    if (event.type == ALLEGRO_EVENT_KEY_CHAR)
    {
        if (strlen(str) <= limit)
        {
            char temp[] = {event.keyboard.unichar, '\0'};
            if (event.keyboard.unichar == ' ')
            {
                strcat(str, temp);
            }
            else if (event.keyboard.unichar >= '!' &&
                     event.keyboard.unichar <= '?')
            {
                strcat(str, temp);
            }
            else if (event.keyboard.unichar >= 'A' &&
                     event.keyboard.unichar <= 'Z')
            {
                strcat(str, temp);
            }
            else if (event.keyboard.unichar >= 'a' &&
                     event.keyboard.unichar <= 'z')
            {
                strcat(str, temp);
            }
        }

        if (event.keyboard.keycode == ALLEGRO_KEY_BACKSPACE && strlen(str) != 0)
        {
            str[strlen(str) - 1] = '\0';
        }
    }
}

//Função responsavel para realizar a conexão com o servidor!
void assertConnection(char IP[], char login[], ALLEGRO_DISPLAY *janela, ALLEGRO_EVENT_QUEUE *filaEventosChat,ALLEGRO_BITMAP *BackgroundMenu,ALLEGRO_FONT *fonteHTPTitulo,ALLEGRO_FONT *fonteHTP) {

 	puts("Chat sendo inicializado...");

  	enum conn_ret_t ans = tryConnect(IP);
	int connectScreen = 1;

  	while (ans != SERVER_UP){

		if (ans == SERVER_DOWN) {

			puts("Server is down!");
			al_show_native_message_box(janela, "Battle Of Feuds", "O servidor esta inativo!", "Tente novamente", NULL, ALLEGRO_MESSAGEBOX_WARN);

		} else if (ans == SERVER_FULL) {

			puts("Server is full!");
			al_show_native_message_box(janela, "Battle Of Feuds", "O servidor esta cheio!", "Tente novamente", NULL, ALLEGRO_MESSAGEBOX_WARN);

		} else if (ans == SERVER_CLOSED) {

			puts("Server is closed for new connections!");
			al_show_native_message_box(janela, "Battle Of Feuds", "O servidor nao permite novas conexoes!", "Tente novamente", NULL, ALLEGRO_MESSAGEBOX_WARN);

		} else {

			puts("Server didn't respond to connection!");
			al_show_native_message_box(janela, "Battle Of Feuds", "O servidor nao respondeu!", "Tente novamente", NULL, ALLEGRO_MESSAGEBOX_WARN);

		}

		while(connectScreen){ //Tela para digitar o IP novamente!

			startTimer();

			while(!al_is_event_queue_empty(filaEventosChat)){

				ALLEGRO_EVENT connectEvent;
				al_wait_for_event(filaEventosChat, &connectEvent);

				readInput(connectEvent, IP, IP_MAX_SIZE);

				if (connectEvent.type == ALLEGRO_EVENT_KEY_DOWN){

					switch(connectEvent.keyboard.keycode){

						case ALLEGRO_KEY_ENTER:
							connectScreen = 0;
							break;
					}
						
				}

			}

			printConnectScreen(IP,BackgroundMenu,fonteHTPTitulo,fonteHTP);
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

enum conn_ret_t tryConnect(char IP[]) {

  char server_ip[30];
  return connectToServer(IP);

}

int sendMsgToServer(void *msg, int size) {
	
  ssize_t size_ret = send(network_socket, &size, sizeof(int), MSG_NOSIGNAL);

  if (size_ret <= 0) {

    return SERVER_DISCONNECTED;
  }

  ssize_t total_size = 0;

  while (total_size < (ssize_t) size) {

    ssize_t msg_ret =
        send(network_socket, msg + total_size, (size_t)size, MSG_NOSIGNAL);
    if (msg_ret <= 0) {
      return SERVER_DISCONNECTED;
    }
    total_size += msg_ret;

  }
  return (int)total_size;
}

enum conn_ret_t connectToServer(const char *server_IP) {

  // create a socket for the client
  network_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (network_socket == -1) {
    perror("Could not create socket");
    exit(EXIT_FAILURE);
  }
  // making struct for server adress
  struct sockaddr_in server_address;
  memset(&server_address, 0, sizeof(server_address));  // clear struct
  server_address.sin_family = AF_INET;                 // set family
  server_address.sin_port = htons(PORT);               // working port
  if (server_IP == NULL) {  // if no IP sent, connect to localhost
    server_address.sin_addr.s_addr = INADDR_ANY;
  } else {
    server_address.sin_addr.s_addr = inet_addr(server_IP);
  }

  // Connect to server now
  int connection_status =
      connect(network_socket, (struct sockaddr *)&server_address,
              sizeof(server_address));
  enum conn_msg_t server_response = SUCCESSFUL_CONNECTION;

  FD_ZERO(&sock_fd_set);
  FD_SET(network_socket, &sock_fd_set);
  
  if (connection_status == 0) {
    // read server_response
    ssize_t conn_ans = recvMsgFromServer(&server_response, DONT_WAIT);
    unsigned int i = 0;
    while (i < READ_CONN_TIMEOUT && conn_ans == NO_MESSAGE) {
      i++;
      sleep(i);
      conn_ans = recvMsgFromServer(&server_response, DONT_WAIT);
    }
    if (conn_ans == SERVER_DISCONNECTED) {
      closeConnection();
      return SERVER_DOWN;
    } else if (conn_ans == NO_MESSAGE) {
      closeConnection();
      return SERVER_TIMEOUT;
    }
  } else if (connection_status == -1) {
    closeConnection();
    return SERVER_DOWN;
  }

  if (server_response == TOO_MANY_CLIENTS) {
    closeConnection();
    return SERVER_FULL;
  } else if (server_response == CONNECTIONS_CLOSED) {
    closeConnection();
    return SERVER_CLOSED;
  }

  FD_ZERO(&sock_fd_set);
  FD_SET(network_socket, &sock_fd_set);
  return SERVER_UP;
}

int recvMsgFromServer(void *msg, int option) {

  if (option == DONT_WAIT) {

    struct timeval timeout = {0, SELECT_TIMEOUT};
    fd_set readfds = sock_fd_set;
    int sel_ret = select(FD_SETSIZE, &readfds, NULL, NULL, &timeout);
    if (sel_ret < 0) {
      perror("select");
      exit(EXIT_FAILURE);
    }
    if (sel_ret == 0 || !FD_ISSET(network_socket, &readfds)) {  // timeout
      return NO_MESSAGE;
    }
  }
  int size;
  // get message size
  ssize_t size_ret = read(network_socket, &size, sizeof(int));

  if (size_ret <= 0) {
    return SERVER_DISCONNECTED;
  }

  // get message content
  ssize_t total_size = 0;
  while (total_size < (ssize_t) size) {
    ssize_t msg_ret = read(network_socket, msg + total_size, (size_t)size);
    if (msg_ret <= 0) {
      return SERVER_DISCONNECTED;
    }
    total_size += msg_ret;
  }
  return (int)total_size ;
}

void closeConnection() {
  shutdown(network_socket, 3);
  close(network_socket);
}

////////////Funções para printar o chat!

void printConnectScreen(char str[], ALLEGRO_BITMAP * BackgroundMenu, ALLEGRO_FONT * fonteHTPTitulo, ALLEGRO_FONT * fonteHTP ){

    al_draw_bitmap(BackgroundMenu,0,0,0);

    al_draw_text(fonteHTPTitulo, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, 30, ALLEGRO_ALIGN_CENTRE, "Digite o IP do server:");

    if (strlen(str) > 0){

        al_draw_text(fonteHTP, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, (ALTURA_TELA - al_get_font_ascent(fonteHTP)) / 2, ALLEGRO_ALIGN_CENTRE, str);

    }
	else{

        al_draw_text(fonteHTP, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, (ALTURA_TELA - al_get_font_ascent(fonteHTP)) / 2, ALLEGRO_ALIGN_CENTRE, "0.0.0.0");
    }
}

void printLoginScreen(char str[], ALLEGRO_BITMAP * BackgroundMenu, ALLEGRO_FONT * fonteHTPTitulo, ALLEGRO_FONT * fonteHTP ){

    al_draw_bitmap(BackgroundMenu,0,0,0);

    al_draw_text(fonteHTPTitulo, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, 30, ALLEGRO_ALIGN_CENTRE, "Digite o Login desejado: ");

    if (strlen(str) > 0){

        al_draw_text(fonteHTP, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, (ALTURA_TELA - al_get_font_ascent(fonteHTP)) / 2,ALLEGRO_ALIGN_CENTRE, str);
    }
    else
    {
        al_draw_text(fonteHTP, al_map_rgb(255, 255, 255), LARGURA_TELA / 2,(ALTURA_TELA - al_get_font_ascent(fonteHTP)) / 2, ALLEGRO_ALIGN_CENTRE, "<login>");
    }
}

void printLobbyText(char str[], ALLEGRO_BITMAP * BackgroundMenu,ALLEGRO_FONT * fonteHTPTitulo, ALLEGRO_FONT * fonteHTP){

    al_draw_bitmap(BackgroundMenu,0,0,0);

    al_draw_text(fonteHTPTitulo, al_map_rgb(255, 255, 255), 20, 30, ALLEGRO_ALIGN_LEFT, "Preparing to battle... Left Ctrl to start...");

    if (strlen(str) > 0){

        al_draw_text(fonteHTP, al_map_rgb(255, 255, 255), 20, (ALTURA_TELA - al_get_font_ascent(fonteHTP)) - 20, ALLEGRO_ALIGN_LEFT, str);
    }
    else{

        al_draw_text(fonteHTP, al_map_rgb(255, 255, 255), 20,(ALTURA_TELA - al_get_font_ascent(fonteHTP)) - 20, ALLEGRO_ALIGN_LEFT, "Type anything to chat...");
    }
}

void printChatLog( char chatLog[][MSG_MAX_SIZE], ALLEGRO_FONT * fonteHTP ){

    int i;
    int initialY = 100;
    int spacing = al_get_font_ascent(fonteHTP)+5;
    
    for(i = 0; i < MAX_LOG_SIZE; ++i){

        al_draw_text(fonteHTP, al_map_rgb(255, 255, 255), 40, initialY + (i*spacing), ALLEGRO_ALIGN_LEFT, chatLog[i]);
    }
}
