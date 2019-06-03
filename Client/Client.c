#include <stdio.h>
#include <stdlib.h>
#include "allegro5/allegro.h"
 #include "allegro5/allegro_image.h"       // Inclui o cabeçalho do add-on para uso de imagens

 
int main(){

    ALLEGRO_DISPLAY *janela = NULL;         // Variável representando a janela principal
    ALLEGRO_BITMAP *imagem = NULL;          // Variável representando a imagem

al_init();                                  // Inicializa a Allegro

al_init_image_addon();                      // Inicializa o add-on para utilização de imagens

    janela = al_create_display(640, 480);   // Configura a janela

    imagem = al_load_bitmap("hu3.bmp");     // Carrega a imagem
    
    al_draw_bitmap(imagem, 0, 0, 0);        // Desenha a imagem na tela
 
    al_flip_display();                      // Atualiza a tela

    al_rest(10.0);                           // Segura a execução por 10 segundos

    al_destroy_display(janela);              // Finaliza a janela
 
    return 0;
}