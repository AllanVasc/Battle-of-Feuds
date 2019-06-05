// Os arquivos de cabeçalho
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

// Atributos da tela
#define LARGURA_TELA 940
#define ALTURA_TELA 780

void ChecaPonteiro(void * ptr, char erro[50]){

	if(ptr == NULL){

		printf("Deu merda em: [%s]\n", erro);
		exit(0);
	}

}

int main(){
	
	ALLEGRO_DISPLAY *janela = NULL;
	ALLEGRO_BITMAP *BackgroundMenu = NULL, *gameName = NULL, *gameIcon = NULL, *HTPwasd = NULL, *HTPJ = NULL, *HTPK = NULL, *HTPReturn = NULL, *botaoPlay = NULL, *botaoHTP = NULL, *botaoExit = NULL, *mapa = NULL;
	ALLEGRO_EVENT_QUEUE *filaEventosMouse = NULL; //declara a fila de eventos
	ALLEGRO_EVENT evento;	//declara variavel que recebe evento e timeout
	ALLEGRO_FONT *fonteHTP = NULL, *fonteHTPTitulo = NULL;
	int apertouBotaoPlay = 0, inMenu = 1, InGame = 0, apertouBotaoExit = 0, apertouBotaoHowtoPlay = 0;

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

	fonteHTP = al_load_font("Amita-Regular.ttf", 30, 0);
	fonteHTPTitulo = al_load_font("Amita-Bold.ttf", 50, 0);

	ChecaPonteiro(fonteHTP, "Erro no fonteHTP");
	ChecaPonteiro(fonteHTPTitulo, "Erro no fonteHTPTitulo");

	filaEventosMouse = al_create_event_queue(); //cria fila de eventos

	ChecaPonteiro(filaEventosMouse, "Erro na fila de eventos Mouse"); 	//Checa erro!

	al_register_event_source(filaEventosMouse, al_get_mouse_event_source());	//Fontes dos eventos!
	al_register_event_source(filaEventosMouse, al_get_keyboard_event_source());

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

					while(InGame){

						al_draw_bitmap(BackgroundMenu, 0, 0, 0);
						al_draw_bitmap(mapa, 0, 0, 0);
						al_flip_display();

						al_wait_for_event(filaEventosMouse, &evento);

						if (evento.type == ALLEGRO_EVENT_KEY_DOWN){

							if(evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE){

								InGame = 0;
								printf("Apertasse botão ESC\n");

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
	al_destroy_event_queue(filaEventosMouse);

	return 0;
}
