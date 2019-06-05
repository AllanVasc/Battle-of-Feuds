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

void ChecaPonteiro(void * ptr, char erro[50]){

	if(ptr == NULL){

		printf("Deu merda em: [%s]\n", erro);
		exit(0);
	}

}

int main(){
	
	ALLEGRO_DISPLAY *janela = NULL;
	ALLEGRO_BITMAP *BackgroundMenu = NULL, *gameName = NULL, *gameIcon = NULL, *HTPwasd = NULL, *HTPJ = NULL, *HTPK = NULL, *HTPReturn = NULL, *botaoPlay = NULL, *botaoHTP = NULL, *botaoExit = NULL, *mapa = NULL;
	ALLEGRO_EVENT_QUEUE *filaEventosMouse = NULL, *filaEventosTimer = NULL; 
	ALLEGRO_EVENT evento;	
	ALLEGRO_FONT *fonteHTP = NULL, *fonteHTPTitulo = NULL;
	ALLEGRO_TIMER *timer = NULL;
	int apertouBotaoPlay = 0, inMenu = 1, InGame = 0, apertouBotaoExit = 0, apertouBotaoHowtoPlay = 0;

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

	ChecaPonteiro(filaEventosMouse, "Erro na fila de eventos Mouse"); 	//Checa erro!
	ChecaPonteiro(filaEventosTimer, "Erro em filaEventosTimer"); 	//Checa erro!

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
					InGame = 1;

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

					al_start_timer(timer);

					while(InGame){
						
        				al_wait_for_event(filaEventosTimer, &evento);
						

						if(evento.type == ALLEGRO_EVENT_TIMER){  //Cada 1/60s sera desenhado um frame!

							al_draw_bitmap(BackgroundMenu, 0, 0, 0);
							al_draw_bitmap(mapa, 0, 0, 0);			
						  	al_draw_bitmap_region(charSprite,colunaSprite*larguraSprite,linhaSprite*alturaSprite,larguraSprite,alturaSprite,posXChar,posYChar,0); //Desenha só uma regiao do sprite!
							al_flip_display();
		
						}
						
						al_wait_for_event(filaEventosMouse, &evento);

						if (evento.type == ALLEGRO_EVENT_KEY_DOWN){		//Movimentação do personagem!

							switch (evento.keyboard.keycode){
								
								case ALLEGRO_KEY_ESCAPE: 	
										InGame = 0;
										printf("Apertasse botão ESC\n");
										break;

								case ALLEGRO_KEY_W :

										if(posYChar - 5 > 0){
											linhaSprite = 1;
											colunaSprite++;
											if(colunaSprite == 4){
												colunaSprite = 0;
											}
											posYChar -= 5 ;
										}
										break;

								case ALLEGRO_KEY_S :

										if(posYChar + 5 < 780 - 50){

											linhaSprite = 0;
											colunaSprite++;
											if(colunaSprite == 4){
												colunaSprite = 0;
											}
											posYChar += 5 ;
										}
										break;

								case ALLEGRO_KEY_A :

										if(posXChar - 5 > 0){

											linhaSprite = 2;
											colunaSprite++;
											if(colunaSprite == 4){
												colunaSprite = 0;
											}
											posXChar -= 5 ;
										}
										break;

								case ALLEGRO_KEY_D :

										if(posXChar + 5 < 940 - 40){

											linhaSprite = 3;
											colunaSprite++;
											if(colunaSprite == 4){
												colunaSprite = 0;
											}
											posXChar += 5 ;
										}
										break;
								
							} 

						}

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
