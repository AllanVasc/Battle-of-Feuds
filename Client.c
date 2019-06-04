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

		printf("Deu merda na linha: [%s]\n", erro);
		exit(0);
	}

}

int main(){
	
	ALLEGRO_DISPLAY *janela = NULL;
	ALLEGRO_BITMAP *menu = NULL, *gameName = NULL, *botaoPlay = 0;
	ALLEGRO_EVENT_QUEUE *filaEventosMouse = NULL; //declara a fila de eventos
	int apertouBotaoPlay = 0, inMenu = 1;

	al_init();
	al_init_image_addon();
	al_install_mouse(); 

	janela = al_create_display(LARGURA_TELA, ALTURA_TELA); //cria display em janela
	al_set_window_title(janela, "Battle Of Feuds"); 	// Configura o título da janela
	al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);	// Atribui o cursor padrão do sistema para ser usado

	ChecaPonteiro(janela, "Erro na janela"); 	//Checa erro!

	menu = al_load_bitmap("Menu.png"); //carrega imagem
	gameName = al_load_bitmap("BattleLogo.png");
	botaoPlay = al_load_bitmap("StartButton00.png");

	ChecaPonteiro(menu, "Erro no menu"); 	//Checa erro!
	ChecaPonteiro(gameName, "Erro no gamename"); 	//Checa erro!
	ChecaPonteiro(botaoPlay, "Erro no botaoplay"); 	//Checa erro!

	filaEventosMouse = al_create_event_queue(); //cria fila de eventos

	ChecaPonteiro(filaEventosMouse, "Erro na fila de eventos Mouse"); 	//Checa erro!

	al_register_event_source(filaEventosMouse, al_get_mouse_event_source());
	al_draw_bitmap(menu, 0, 0, 0); //desenha imagem no display ativo em X:0 Y:0
	al_draw_bitmap(gameName, 200, 100, 0);
	al_flip_display(); //atualiza tela

	while (1){

		while (inMenu){

		    ALLEGRO_EVENT eventoMouse;	//declara variavel que recebe evento e timeout

            al_wait_for_event(filaEventosMouse, &eventoMouse);
			printf("%d\n", eventoMouse.type);

				if (eventoMouse.type == ALLEGRO_EVENT_MOUSE_AXES){
                
                if (eventoMouse.mouse.x >= LARGURA_TELA / 2 - al_get_bitmap_width(botaoPlay) / 2 &&  // Verificamos se ele está sobre a região do botao play
                	eventoMouse.mouse.x <= LARGURA_TELA / 2 + al_get_bitmap_width(botaoPlay) / 2 &&
                	eventoMouse.mouse.y >= ALTURA_TELA / 2 - al_get_bitmap_height(botaoPlay) / 2 &&
                	eventoMouse.mouse.y <= ALTURA_TELA / 2 + al_get_bitmap_height(botaoPlay) / 2){

						while (!al_is_event_queue_empty(filaEventosMouse)){

							if(eventoMouse.type == ALLEGRO_EVENT_MOUSE_AXES){

								apertouBotaoPlay = 1;
								printf("Apertasse puto\n");
							}

							else{
							//printf("to aq");
                    		apertouBotaoPlay = 0;
                			}

						}        
                }
                
            }

			al_draw_bitmap(menu, 0, 0, 0);
			al_draw_bitmap(gameName, 200, 100, 0);
			al_set_target_bitmap(botaoPlay);
			if (!apertouBotaoPlay){
            botaoPlay = al_load_bitmap("StartButton00.png");
        	}
        	else{
            botaoPlay = al_load_bitmap("StartButton2.jpg");
        	}
			al_set_target_bitmap(al_get_backbuffer(janela));
			al_draw_bitmap(botaoPlay, LARGURA_TELA / 2 - al_get_bitmap_width(botaoPlay) / 2,
        			   		ALTURA_TELA / 2 - al_get_bitmap_height(botaoPlay) / 2, 0);
					   
			al_flip_display();

		}

	}

	//destroi janela e fila de eventos ao fim
	al_destroy_display(janela);
	al_destroy_event_queue(filaEventosMouse);

	return 0;
}
