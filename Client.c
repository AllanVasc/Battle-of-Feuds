// Os arquivos de cabeçalho
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>

// Atributos da tela
#define LARGURA_TELA 940
#define ALTURA_TELA 780

void TelaMenu();

int main(){
	
	ALLEGRO_DISPLAY *janela = NULL;
	ALLEGRO_BITMAP *menu = NULL, *gameName = NULL, *botaoPlay = 0;

	ALLEGRO_EVENT_QUEUE *fila_eventos = NULL; //declara a fila de eventos

	al_init();
	al_init_image_addon();
	al_install_mouse(); 

	janela = al_create_display(LARGURA_TELA, ALTURA_TELA); //cria display em janela
	al_set_window_title(janela, "Battle Of Feuds"); 	// Configura o título da janela
	al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);	// Atribui o cursor padrão do sistema para ser usado

	if (!janela){ //caso al_create_display retorne NULL, encerra programa
		printf("Falha ao criar janela");
		return -1;
	}

	menu = al_load_bitmap("Menu.png"); //carrega imagem
	gameName = al_load_bitmap("BattleLogo.png");

	if (!menu){       //caso al_load_bitmap retorne NULL, encerra programa
		printf("Falha ao carregar o arquivo de imagem");
		al_destroy_display(janela);
		return -1;
	}


	fila_eventos = al_create_event_queue(); //cria fila de eventos

	if (!fila_eventos){ //caso al_create_event_queue retorne NULL, destroi a janela e encerra o programa
		printf("Falha ao criar fila de eventos");
		al_destroy_display(janela);
		return -1;
	}

	al_register_event_source(fila_eventos, al_get_display_event_source(janela)); //registra eventos da janela em fila_eventos
	al_register_event_source(fila_eventos, al_get_mouse_event_source());
	al_draw_bitmap(menu, 0, 0, 0); //desenha imagem no display ativo em X:0 Y:0
	al_draw_bitmap(gameName, 200, 100, 0);
	botaoPlay = al_create_bitmap(LARGURA_TELA / 2, ALTURA_TELA / 2);
	al_flip_display(); //atualiza tela

	int noBotaoPlay = 0;

	while (1){

		while (!al_is_event_queue_empty(fila_eventos)){

		    ALLEGRO_EVENT evento;	//declara vriavel que recebe evento e timeout
            al_wait_for_event(fila_eventos, &evento);

				if (evento.type == ALLEGRO_EVENT_MOUSE_AXES){
                // Verificamos se ele está sobre a região do botao play
                if (evento.mouse.x >= LARGURA_TELA / 2 - al_get_bitmap_width(botaoPlay) / 2 &&
                	evento.mouse.x <= LARGURA_TELA / 2 + al_get_bitmap_width(botaoPlay) / 2 &&
                	evento.mouse.y >= ALTURA_TELA / 2 - al_get_bitmap_height(botaoPlay) / 2 &&
                	evento.mouse.y <= ALTURA_TELA / 2 + al_get_bitmap_height(botaoPlay) / 2){

                    noBotaoPlay = 1;
                }
                else{
                    noBotaoPlay = 0;
                }
            }
		}

		al_draw_bitmap(menu, 0, 0, 0);
		al_draw_bitmap(gameName, 200, 100, 0);

		al_set_target_bitmap(botaoPlay);
        if (!noBotaoPlay){
            al_clear_to_color(al_map_rgb(255, 255, 255));
        }
        else{
            al_clear_to_color(al_map_rgb(0, 255, 0));
        }
		
		al_set_target_bitmap(al_get_backbuffer(janela));
		al_draw_bitmap(botaoPlay, LARGURA_TELA / 2 - al_get_bitmap_width(botaoPlay) / 2,
        			   ALTURA_TELA / 2 - al_get_bitmap_height(botaoPlay) / 2, 0);
					   
		al_flip_display();
	}

	//destroi janela e fila de eventos ao fim
	al_destroy_display(janela);
	al_destroy_event_queue(fila_eventos);

	return 0;
}
