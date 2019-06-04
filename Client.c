// Os arquivos de cabeçalho
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>

// Atributos da tela
#define LARGURA_TELA 640
#define ALTURA_TELA 480

void error_msg(char *text){
	al_show_native_message_box(NULL,"ERRO",
		"Ocorreu o seguinte erro e o programa sera finalizado:",
		text,NULL,ALLEGRO_MESSAGEBOX_ERROR);
}

int main(){
	ALLEGRO_DISPLAY *janela = NULL;
	ALLEGRO_BITMAP *menu = NULL;

	ALLEGRO_EVENT_QUEUE *fila_eventos = NULL; //declara a fila de eventos


	if (!al_init()){        //Inicialização da biblioteca Allegro
		error_msg("Falha ao inicializar a Allegro");
		return -1;
	}


	if (!al_init_image_addon()){    //tenta iniciar o módulo de imagens
		error_msg("Falha ao inicializar add-on allegro_image");
		return -1;
	}


	janela = al_create_display(LARGURA_TELA, ALTURA_TELA); //cria display em janela

	if (!janela){ //caso al_create_display retorne NULL, encerra programa
		error_msg("Falha ao criar janela");
		return -1;
	}


	menu = al_load_bitmap("Menu.png"); //carrega imagem

	if (!menu){       //caso al_load_bitmap retorne NULL, encerra programa
		error_msg("Falha ao carregar o arquivo de imagem");
		al_destroy_display(janela);
		return -1;
	}


	fila_eventos = al_create_event_queue(); //cria fila de eventos

	if (!fila_eventos){ //caso al_create_event_queue retorne NULL, destroi a janela e encerra o programa
		error_msg("Falha ao criar fila de eventos");
		al_destroy_display(janela);
		return -1;
	}


	al_register_event_source(fila_eventos, al_get_display_event_source(janela)); //registra eventos da janela em fila_eventos


	al_draw_bitmap(menu, 0, 0, 0); //desenha imagem no display ativo em X:0 Y:0


	al_flip_display(); //atualiza tela

	while (1){

		ALLEGRO_EVENT evento; //declara vriavel que recebe evento e timeout

		al_wait_for_event(fila_eventos, &evento); //espero por um evento da fila, e guarda em evento


		if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) { //se teve eventos e foi um evento de fechar janela, encerra repetição

			int resp = al_show_native_message_box(janela,"Fechar","Deseja sair do programa?","",NULL,ALLEGRO_MESSAGEBOX_YES_NO);
			if (resp) break;

		}

		al_draw_bitmap(menu, 0, 0, 0);
		al_flip_display();
	}

	//destroi janela e fila de eventos ao fim
	al_destroy_display(janela);
	al_destroy_event_queue(fila_eventos);

	return 0;
}
