#include <stdio.h>
#include <stdlib.h>
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_primitives.h"
 
int main(){

   ALLEGRO_DISPLAY *janela = NULL;
   ALLEGRO_BITMAP *menu = NULL;
   ALLEGRO_DISPLAY_MODE   disp_data;
   ALLEGRO_EVENT_QUEUE *filaEventos = NULL;

   al_init(); 
   al_init_image_addon();
   al_init_primitives_addon();

   al_get_display_mode(al_get_num_display_modes() - 1, &disp_data);

   al_set_new_display_flags(ALLEGRO_FULLSCREEN);

   janela = al_create_display(1600,900);
   menu = al_load_bitmap("Menu.png");
   filaEventos = al_create_event_queue();                                          //Criando a fila de eventos para a tela janela
   al_register_event_source(filaEventos, al_get_display_event_source(janela)); 
   al_draw_bitmap(menu, 0, 0, 0);
   al_flip_display();

   while (1){
		
		ALLEGRO_EVENT evento;   //declara variavel que recebe evento e timeout
		
		al_wait_for_event(filaEventos, &evento);  //espero por um evento da fila, e guarda em evento
 
		
		if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {       //se teve eventos e foi um evento de fechar janela, encerra repetição

				break;
		}
 
		al_draw_bitmap(menu, 0, 0, 0);
		al_flip_display();
	}

   al_rest(10);

   al_destroy_display(janela);
   al_destroy_event_queue(filaEventos);

    return 0;
}
