// Os arquivos de cabeçalho
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

//Atributos importantes
#define LARGURA_TELA 940
#define ALTURA_TELA 780
#define FPS 60.0

//AtributosChat

#define MSG_MAX_SIZE 350
#define BUFFER_SIZE (MSG_MAX_SIZE + 100)
#define LOGIN_MAX_SIZE 13
#define HIST_MAX_SIZE 200
#define MAX_LOG_SIZE 17
#define IP_MAX_SIZE 100

void ChecaPonteiro(void * ptr, char erro[50]){

	if(ptr == NULL){

		printf("Deu merda em: [%s]\n", erro);
		exit(0);
	}

}

// Funções para controle da quantidade de frames por segundo
void startTimer();
double getTimer();
void FPSLimit();
double startingTime;
void readInput(ALLEGRO_EVENT event, char str[], int limit);

int main(){
	
	ALLEGRO_DISPLAY *janela = NULL;
	ALLEGRO_BITMAP *BackgroundMenu = NULL, *gameName = NULL, *gameIcon = NULL, *HTPwasd = NULL, *HTPJ = NULL, *HTPK = NULL, *HTPReturn = NULL, *botaoPlay = NULL, *botaoHTP = NULL, *botaoExit = NULL, *mapa = NULL;
	ALLEGRO_EVENT_QUEUE *filaEventosMouse = NULL, *filaEventosTimer = NULL; 
	ALLEGRO_EVENT evento;	
	ALLEGRO_FONT *fonteHTP = NULL, *fonteHTPTitulo = NULL;
	ALLEGRO_TIMER *timer = NULL;
	int apertouBotaoPlay = 0, inMenu = 1, inGame = 0, apertouBotaoExit = 0, apertouBotaoHowtoPlay = 0, delay = 0;

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

				if(apertouBotaoPlay == 1){			//Logica do nosso jogo ficara aqui!

					//Esse sera o IP do Server!
					char ServerIP[30]={"127.0.0.1"};
					int qtdCharIP = 9;
					//para guardar o log do chat
					char chatLog[MAX_LOG_SIZE][MSG_MAX_SIZE] = {{0}};
					//mensagem pra ser mandada no lobby
					char lobbyMessage[110]={0}; 
					//para guardar o login
					char loginMsg[BUFFER_SIZE]={0};
					int connectScreen = 1;
					int loginScreen = 1;
					int lobby = 1;

					
					connectScreen = 1;
					inChat = 1;
					filaEventosChat = al_create_event_queue();	//Reiniciando fila de Eventos!
					al_register_event_source(filaEventosChat, al_get_mouse_event_source());	//Fontes dos eventos!
					al_register_event_source(filaEventosChat, al_get_keyboard_event_source());

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
							
							al_draw_bitmap(BackgroundMenu,0,0,0);	//Printar as informações na tela!

    						al_draw_text(fonteHTPTitulo, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, 30, ALLEGRO_ALIGN_CENTRE, "Digite o IP do server:");

    						if (strlen(ServerIP) > 0){

        						al_draw_text(fonteHTP, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, (ALTURA_TELA - al_get_font_ascent(fonteHTP)) / 2, ALLEGRO_ALIGN_CENTRE, ServerIP);
    						}else{

        						al_draw_text(fonteHTP, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, (ALTURA_TELA - al_get_font_ascent(fonteHTP)) / 2, ALLEGRO_ALIGN_CENTRE, "0.0.0.0");
    						}	

							al_flip_display();
							FPSLimit();
						}

						while(loginScreen){ //Tela para printar o login!

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

							al_draw_bitmap(BackgroundMenu,0,0,0);	//Printar as informações na tela!

							al_draw_text(fonteHTPTitulo, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, 30, ALLEGRO_ALIGN_CENTRE, "Digite o Login desejado: ");

							if (strlen(loginMsg) > 0){

								al_draw_text(fonteHTP, al_map_rgb(255, 255, 255), LARGURA_TELA / 2,
											(ALTURA_TELA - al_get_font_ascent(fonteHTP)) / 2,
											ALLEGRO_ALIGN_CENTRE, loginMsg);
							}
							
							else{

								al_draw_text(fonteHTP, al_map_rgb(255, 255, 255), LARGURA_TELA / 2,
											(ALTURA_TELA - al_get_font_ascent(fonteHTP)) / 2,
											ALLEGRO_ALIGN_CENTRE, "<login>");
							}

							//printLoginScreen(loginMsg);
							al_flip_display();
							al_clear_to_color(al_map_rgb(0, 0, 0));
							FPSLimit();
						}

						connectScreen = 0;
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

//FOR READING KEYBOARD INPUT WITH MAX SIZE = LIMIT AND SAVING AT STR[]
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




/* se não pegar Read INPUT

case ALLEGRO_KEY_0:

			if(qtdCharIP < 29){
				ServerIP[qtdCharIP] = '0';
				qtdCharIP++;
				ServerIP[qtdCharIP]= '\0';
				break;

			}
			
		case ALLEGRO_KEY_1:

			if(qtdCharIP < 29){
				ServerIP[qtdCharIP]= '1';
				qtdCharIP++;
				ServerIP[qtdCharIP]= '\0';
				break;
				
			}
			
		case ALLEGRO_KEY_2:
			if(qtdCharIP < 29){

				ServerIP[qtdCharIP]= '2';
				qtdCharIP++;
				ServerIP[qtdCharIP]= '\0';
				break;
				
			}
			
		case ALLEGRO_KEY_3:
			if(qtdCharIP < 29){

				ServerIP[qtdCharIP]= '3';
				qtdCharIP++;
				ServerIP[qtdCharIP]= '\0';
				break;
		
			}
			
		case ALLEGRO_KEY_4:
			if(qtdCharIP < 29){
				ServerIP[qtdCharIP]= '4';
				qtdCharIP++;
				ServerIP[qtdCharIP]= '\0';
				break;

			}
			
		case ALLEGRO_KEY_5:
			if(qtdCharIP < 29){

				ServerIP[qtdCharIP]= '5';
				qtdCharIP++;
				ServerIP[qtdCharIP]= '\0';
				break;
				
			}
			
		case ALLEGRO_KEY_6:
			if(qtdCharIP < 29){

				ServerIP[qtdCharIP]= '6';
				qtdCharIP++;
				ServerIP[qtdCharIP]= '\0';
				break;
				
			}
			
		case ALLEGRO_KEY_7:
			if(qtdCharIP < 29){
				ServerIP[qtdCharIP]= '7';
				qtdCharIP++;
				ServerIP[qtdCharIP]= '\0';
				break;
				
			}
			
		case ALLEGRO_KEY_8:
			if(qtdCharIP < 29){

				ServerIP[qtdCharIP]= '8';
				qtdCharIP++;
				ServerIP[qtdCharIP]= '\0';
				break;
				
			}
			
		case ALLEGRO_KEY_9:
			if(qtdCharIP < 29){

				ServerIP[qtdCharIP] = '9';
				qtdCharIP++;
				ServerIP[qtdCharIP]= '\0';
				break;
			}
			
		case ALLEGRO_KEY_FULLSTOP:
			if(qtdCharIP < 29){

				ServerIP[qtdCharIP] = '.';
				qtdCharIP++;
				ServerIP[qtdCharIP]= '\0';
				break;
				
			}

		case ALLEGRO_KEY_BACKSPACE:

			if(qtdCharIP != 0){
				qtdCharIP--;
				ServerIP[qtdCharIP]= '\0';
			}

			break;
	}
	}

	*/
