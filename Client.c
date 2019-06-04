// Os arquivos de cabeçalho
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>

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
	ALLEGRO_BITMAP *menu = NULL, *gameName = NULL, *botaoPlay = NULL, *botaoHTP = NULL, *botaoExit = NULL;
	ALLEGRO_EVENT_QUEUE *filaEventosMouse = NULL; //declara a fila de eventos
	int apertouBotaoPlay = 0, inMenu = 1, apertouBotaoExit = 0, apertouBotaoHowtoPlay = 0;

	al_init();
	al_init_image_addon();
	al_install_mouse(); 

	janela = al_create_display(LARGURA_TELA, ALTURA_TELA); //cria display em janela
	al_set_window_title(janela, "Battle Of Feuds"); 	// Configura o título da janela
	al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);	// Atribui o cursor padrão do sistema para ser usado

	ChecaPonteiro(janela, "Erro na janela"); 	//Checa erro!

	menu = al_load_bitmap("Menu.png"); //carrega imagem
	gameName = al_load_bitmap("BattleLogo.png");
	botaoPlay = al_load_bitmap("StartGameButton00.png");
	botaoHTP = al_load_bitmap("HowToPlayButton.png");
	botaoExit = al_load_bitmap("ExitButton.png");

	ChecaPonteiro(menu, "Erro no menu"); 			//Checa erro!
	ChecaPonteiro(gameName, "Erro no gamename"); 	//Checa erro!
	ChecaPonteiro(botaoPlay, "Erro no botaoplay"); 	//Checa erro!
	ChecaPonteiro(botaoHTP, "Erro no botaoHTP"); 	//Checa erro!
	ChecaPonteiro(botaoExit, "Erro no botaoExit"); 	//Checa erro!

	filaEventosMouse = al_create_event_queue(); //cria fila de eventos

	ChecaPonteiro(filaEventosMouse, "Erro na fila de eventos Mouse"); 	//Checa erro!

	al_register_event_source(filaEventosMouse, al_get_mouse_event_source());
	al_draw_bitmap(menu, 0, 0, 0); //desenha imagem no display ativo em X:0 Y:0
	al_draw_bitmap(gameName, 200, 20, 0);
	al_draw_bitmap(botaoPlay, 500, 300, 0);
	al_draw_bitmap(botaoHTP, 500, 350, 0);
	al_draw_bitmap(botaoExit, 500, 400, 0);
	al_flip_display(); //atualiza tela

	while (inMenu){

		ALLEGRO_EVENT eventoMouse;	//declara variavel que recebe evento e timeout

		al_wait_for_event(filaEventosMouse, &eventoMouse);

			if (eventoMouse.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
			
				if (eventoMouse.mouse.x >= 500 &&  // Verificamos se ele está sobre a região do botao play
					eventoMouse.mouse.x <= 500 + al_get_bitmap_width(botaoPlay) &&
					eventoMouse.mouse.y >= 300 &&
					eventoMouse.mouse.y <= 300 + al_get_bitmap_height(botaoPlay) ){

					apertouBotaoPlay = 1;

					printf("Apertasse botão Play\n");

				}else if (eventoMouse.mouse.x >= 500 &&  // Verificamos se ele está sobre a região do botao How to play
						eventoMouse.mouse.x <= 500 + al_get_bitmap_width(botaoHTP) &&
						eventoMouse.mouse.y >= 350 &&
						eventoMouse.mouse.y <= 350 + al_get_bitmap_height(botaoHTP) ){

					apertouBotaoHowtoPlay = 1;
					
					printf("Apertasse botão How to play\n");

				}else if (eventoMouse.mouse.x >= 500 &&  // Verificamos se ele está sobre a região do botao Exit
						eventoMouse.mouse.x <= 500 + al_get_bitmap_width(botaoExit) &&
						eventoMouse.mouse.y >= 400 &&
						eventoMouse.mouse.y <= 400 + al_get_bitmap_height(botaoExit) ){

					inMenu = 0;
					
					printf("Apertasse botão Exit\n");

				}

				if(apertouBotaoPlay == 1){			//Logica do nosso jogo ficara aqui!



				}

				if(apertouBotaoHowtoPlay == 1){			//Tela How to play vai ficar aqui


					
				}
			
			}

		al_draw_bitmap(menu, 0, 0, 0); //desenha imagem no display ativo em X:0 Y:0
		al_draw_bitmap(gameName, 200, 20, 0);
		al_draw_bitmap(botaoPlay, 500, 300, 0);
		al_draw_bitmap(botaoHTP, 500, 350, 0);
		al_draw_bitmap(botaoExit, 500, 400, 0);
		al_flip_display();

	}

	//destroi janela e fila de eventos ao fim
	al_destroy_display(janela);
	al_destroy_event_queue(filaEventosMouse);

	return 0;
}
