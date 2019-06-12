
// Inclui o cabeçalho da bibilioteca Allegro 5
#include <allegro5/allegro.h>
 
// Inclui o cabeçalho do add-on para uso de imagens
#include <allegro5/allegro_image.h>
#include <stdio.h>
 

#define ALTURATELA 768
#define LARGURATELA 1024


int main(void)
{
    // Variável representando a janela principal
    ALLEGRO_DISPLAY *janela = NULL;
 
    // Variável representando a imagem 

   
    ALLEGRO_BITMAP *grama = NULL;
    ALLEGRO_BITMAP *pedra = NULL;
    ALLEGRO_BITMAP *cerca = NULL;
    ALLEGRO_BITMAP *obstaculos = NULL;
    ALLEGRO_BITMAP *objetos = NULL;
 

 
    // Inicializa a Allegro
    al_init();
 
    // Inicializa o add-on para utilização de imagens
    al_init_image_addon();

	int mapa[24][32] = { {1 , 4 , 3 , 4 , 2 , 4 , 2 , 4 , 2 , 4 , 2 , 4 , 4 , 4 , 2 , 4 , 4 , -5, 4 , 4 , 1 , 4 , 4 , 2 , 4 , 4 , 4 , 2 , 4 , 4 , 2 , 2},
                         {4 , 3 , 4 , 1 , 3 , 4 , 1 , 3 , -5, 4 , 2 , 4 , 6 , 6 , 6 , 6 , 6 , -1, -2, -6, 4 , 4 , 2 , 4 , 4 , 2 , 4 , 4 ,-55,-56, 4 , 4},
                         {2 , 2 , 4 , 2 , -4, -2, -2, -2, -3, 17, 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 16, -1, -2, -2, 2 , 4 , 4 , 4 , 2 , 1 ,-57,-58, 4 , 3},
                         {2 , 1 , 2 , 3 , -5, 4 , 1 , 6 , 6 , 9 , 9 , 9 , 9 ,-33,-37,-38, 9 , 9 , 9 , 9 , 6 , 6 , 4 , 2 , -5, 1 , 2 , 4 ,-59,-60, 2 , 4},
                         {1 , 1 , -4, -2, -3, 2 , 17,-22,-23, 9 , 9 , 9 , 9 ,-34,-39,-40,-61,-62, 9 , 9 , 9 , 9 , 16, 4 , -1, -2, -2, -6, 2 , 4 , 4 , 2},
                         {4 , 4 , -5, 1 , 4 , 5 ,-24,-25,-26, 9 , 9 , 9 , 9 ,-35,-41,-42,-63,-64, 9 , 9 , 9 , 9 , 9 , 16, 4 , 4 , 4 , -5, 2 ,-83,-79,-80},
                         {2 , -4, -3, 4 , 5 , 9 ,-27,-28,-29, 9 , 9 , 9 , 9 ,-36,-43,-44,-65, 9 , 9 , 9 , 9 , 9 , 9 , 9 , 6 , 4 , 1 , -5, 4 ,-83,-81,-82},
                         {4 , -5, 3 , 8 , 9 , 9 ,-30,-31,-32, 9 , 9 , 9 , 9 , 9 , 9 ,-66, 9 , 9 , 9 , 9 ,-67,-68,-69,-70, 9 , 10, 4 , -5, 4 , 2 , 4 , 4},
                         {1 , -5, 4 , 8 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 ,-71,-72,-73,-74, 9 , 10, 1 , -5, 2 , 4 , 4 , 3},
                         {4 , -5, 4 , 8 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 ,-88,-89, 9 ,-88,-89, 9 ,-75,-76,-77,-78, 9 , 10, 4 , -5, 4 , 3 , 4 , 1},
                         {2 , -1, -6, 8 , 9 , 9 , 9 ,-84,-85, 9 , 9 , 9 , 9 , 9 ,-90,-91, 9 ,-90,-91, 9 , 9 , 9 , 9 , 9 , 9 , 10, 2 , 4 , 1 , 4 , 1 , 2},
                         {4 , 2 , 4 , 8 , 9 , 9 , 9 ,-86,-87, 9 , 9 , 9 , 9 , 9 ,-94,-95, 9 ,-94,-95, 9 , 9 , 9 , 9 , 9 , 9 , 10, 2 , 4 , 4 , 1 , 4 , 4},
                         {2 , 1 , 4 , 8 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 ,-92,-93, 9 ,-92,-93, 9 , 9 , 9 , 9 , 9 , 9 , 10, 4 , -5, 4 , 2 , 1 , 4},   
                         {4 , 2 , 2 , 8 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 14, -4, -2, -3, 3 , 1 , 4 , 2},
                         {4 , -4, -3, 17, 9 , 9 , 9 ,-22,-23, 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 10, -5, 4 , 4 , 4 , 2 , 4 , 4},
                         {2 , -5, 8 , 9 , 9 , 9 ,-24,-25,-26, 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 10, -5, 4 , 3 ,-14,-15, 1 , 4},
                         {4 , -5, 8 , 9 , 9 , 9 ,-27,-28,-29, 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 14, 4 , 2 , -5, 2 , 4 ,-16,-17, 2 , 1},
                         {4 , -5, 8 , 9 , 9 , 9 ,-30,-31,-32, 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 4 , -4, -2, -3, 1 , 1 ,-18,-19, 4 , 4},
                         {6 , 17, 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 ,-51,-52 , 9 , 9 , 14, 4 , -5, 4 , 2 , 4 ,-50,-20,-21, 4 , 4},
                         {9 , 9 , 9 , -7, -8,-13, 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 ,-53,-54, 9 , 14, 4 , 4 , 1 , 2 , 4 , 4 , 3 , 2 , 4 ,-48, 4},
                         {9 , 9 , 9 , -9,-10,-11, 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 13, 2 , -4, -2, 4 ,-49, 4 ,-48, 4 , 4 , 4 , 4 , 2},
                         {12, 12, 9 , 9 , 9 ,-12, 9 , 12, 12, 12, 12, 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 4 , 1 , -5, 4 , 2 , 4 , 4 , 1 , 2 , 4 ,-49, 4 , 3},
                         {2 , 4 , 11, 12, 12, 12, 13, -2, -2, -2, -6, 12, 12, 9 , 9 , 9 , 9 , 9 , 13, 4 , 2 , -5, 1 , 4 , 3 ,-50, 4 , 4 ,-48, 3 , 1 ,-50},
                         {4 , 2 , 4 , 4 , 4 , 4 , 2 , 4 , 4 , 2 , -1, -2, -2, 8 , 9 , 9 , 9 , 9 , 10, -2, -2, -3, 4 , 4 , 2 , 4 , 4 , 4 , 1 , 4 , 4 , 4}  };
                            
    int i,k;
 
    // Configura a janela
    janela = al_create_display(LARGURATELA, ALTURATELA);
 
    // Carrega a imagem
    
    grama = al_load_bitmap("detalhesDoChao.png");
    pedra = al_load_bitmap("pedraChao.png");
    cerca = al_load_bitmap("cerca.png");

    //obstaculo;
    obstaculos = al_load_bitmap("obstaculos.png");
    objetos = al_load_bitmap("objetos.png"); 
    




	for(i = 0; i < 24; i++){

	       	for(k = 0; k < 32; k++){
		       
		     	if(mapa[i][k] == 1){

		           	        al_draw_bitmap_region(grama, 0*32, 11*32, 32, 32, k*32, i*32, 0); // fundo padrao esquerda
				}
				if(mapa[i][k] == 2){

							al_draw_bitmap_region(grama, 1*32, 11*32, 32, 32, k*32, i*32, 0); // fundo padrao meio
				}
				if(mapa[i][k] == 3){

						    al_draw_bitmap_region(grama, 2*32, 11*32, 32, 32, k*32, i*32, 0); // fundo padrao direita
				}
				if(mapa[i][k] == 4){

							al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0); // fundo padrao liso
				}
                if(mapa[i][k] == 5){
                            al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
							al_draw_bitmap_region(pedra, 21*32, 34*32, 32, 32, k*32, i*32, 0); // piso de pedra 1,1
				}
                if(mapa[i][k] == 6){
                            al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
                            al_draw_bitmap_region(pedra, 22*32, 34*32, 32, 32, k*32, i*32, 0); // piso de pedra 1,2
				}
				if(mapa[i][k] == 7){
                            al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
							al_draw_bitmap_region(pedra, 23*32, 34*32, 32, 32, k*32, i*32, 0); // piso de pedra 1,3
				}
				if(mapa[i][k] == 8){
                            al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
                            al_draw_bitmap_region(pedra, 21*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,1
				}
				if(mapa[i][k] == 9){
                            al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
							al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
				}
                if(mapa[i][k] == 10){
                            al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
							al_draw_bitmap_region(pedra, 23*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,3
				}
                if(mapa[i][k] == 11){
                            al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
                            al_draw_bitmap_region(pedra, 21*32, 36*32, 32, 32, k*32, i*32, 0); // piso de pedra 3,1
				}
				if(mapa[i][k] == 12){
                            al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
							al_draw_bitmap_region(pedra, 22*32, 36*32, 32, 32, k*32, i*32, 0); // piso de pedra 3,2
				}
				if(mapa[i][k] == 13){
                            al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
                            al_draw_bitmap_region(pedra, 23*32, 36*32, 32, 32, k*32, i*32, 0); // piso de pedra 3,3
				}
                if(mapa[i][k] == 14){
                            al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
							al_draw_bitmap_region(pedra, 22*32, 32*32, 32, 32, k*32, i*32, 0); // piso de pedra encaixe 1,1
				}
                if(mapa[i][k] == 15){
                            al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
                            al_draw_bitmap_region(pedra, 23*32, 32*32, 32, 32, k*32, i*32, 0); // piso de pedra encaixe 1,2
                }
				if(mapa[i][k] == 16){
                            al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
							al_draw_bitmap_region(pedra, 22*32, 33*32, 32, 32, k*32, i*32, 0); // piso de pedra encaixe 2,1
                }
				if(mapa[i][k] == 17){
                            al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
                            al_draw_bitmap_region(pedra, 23*32, 33*32, 32, 32, k*32, i*32, 0); // piso de pedra encaixe 2,2
				}

                    //CERCA <0 (nao pode passar por cima)
                if(mapa[i][k] == -1){
                            al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
                            al_draw_bitmap_region(cerca, 0*32, 1*32, 32, 32, k*32, i*32, 0); // lado baixo
                            al_draw_bitmap_region(cerca, 0*32, 0*32, 32, 32, k*32, i*32, 0); // frente esq
				}
                if(mapa[i][k] == -2){
                            al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
                            al_draw_bitmap_region(cerca, 1*32, 0*32, 32, 32, k*32, i*32, 0); // frente meio
                }
                if(mapa[i][k] == -3){
                            al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
                            al_draw_bitmap_region(cerca, 0*32, 1*32, 32, 32, k*32, i*32, 0); // lado baixo
                            al_draw_bitmap_region(cerca, 2*32, 0*32, 32, 32, k*32, i*32, 0); // frente dir
                          
				}
                if(mapa[i][k] == -4){
                            al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
                            al_draw_bitmap_region(cerca, 0*32, 0*32, 32, 32, k*32, i*32, 0); // frente esq
                            al_draw_bitmap_region(cerca, 2*32, 1*32, 32, 32, k*32, i*32, 0); // lado cima
				}
                if(mapa[i][k] == -5){
                            al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
                            al_draw_bitmap_region(cerca, 1*32, 1*32, 32, 32, k*32, i*32, 0); // lado meio
				}
                if(mapa[i][k] == -6){
                            al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
                            al_draw_bitmap_region(cerca, 2*32, 0*32, 32, 32, k*32, i*32, 0); // frente dir
                            al_draw_bitmap_region(cerca, 2*32, 1*32, 32, 32, k*32, i*32, 0); // lado cima
				}

                //arco e flecha
                
                if(mapa[i][k] == -7){
                            	al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 4*32, 47*32, 32, 32, k*32, i*32, 0);
				}
                if(mapa[i][k] == -8){
                            	al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2;
                            al_draw_bitmap_region(obstaculos, 5*32, 47*32, 32, 32, k*32, i*32, 0);
				}
                if(mapa[i][k] == -9){
                           	al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 4*32, 48*32, 32, 32, k*32, i*32, 0);
				}
                if(mapa[i][k] == -10){
                           	al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 5*32, 48*32, 32, 32, k*32, i*32, 0);
				}
                if(mapa[i][k] == -11){
                            	al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 2*32, 48*32, 32, 32, k*32, i*32, 0);
				}
                if(mapa[i][k] == -12){
                            	al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 2*32, 49*32, 32, 32, k*32, i*32, 0);
				}
                if(mapa[i][k] == -13){
                            	al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 3*32, 49*32, 32, 32, k*32, i*32, 0);
				}

                //arvore com relogio

                if(mapa[i][k] == -14){
                            al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
                            al_draw_bitmap_region(obstaculos, 14*32, 9*32, 32, 32, k*32, i*32, 0);
				}
                if(mapa[i][k] == -15){
                            al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
                            al_draw_bitmap_region(obstaculos, 15*32, 9*32, 32, 32, k*32, i*32, 0);
				}
                if(mapa[i][k] == -16){
                            al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
                            al_draw_bitmap_region(obstaculos, 14*32, 10*32, 32, 32, k*32, i*32, 0);
				}
                if(mapa[i][k] == -17){
                            al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
                            al_draw_bitmap_region(obstaculos, 15*32, 10*32, 32, 32, k*32, i*32, 0);
				}
                if(mapa[i][k] == -18){
                             al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
                            al_draw_bitmap_region(obstaculos, 14*32, 11*32, 32, 32, k*32, i*32, 0);
				}
                if(mapa[i][k] == -19){
                             al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
                            al_draw_bitmap_region(obstaculos, 15*32, 11*32, 32, 32, k*32, i*32, 0);
				}
                if(mapa[i][k] == -20){
                             al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
                            al_draw_bitmap_region(obstaculos, 14*32, 12*32, 32, 32, k*32, i*32, 0);
				}
                if(mapa[i][k] == -21){
                             al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
                            al_draw_bitmap_region(obstaculos, 15*32, 12*32, 32, 32, k*32, i*32, 0);
				}
                
                
                //guilhotina
              
                if(mapa[i][k] == -22){ //cima guilhotina esq fora do palco
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 2*32, 44*32, 32, 32, k*32, i*32, 0);
				}
                if(mapa[i][k] == -23){ //cima guilhotina dir fora do palco
                           al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 3*32, 44*32, 32, 32, k*32, i*32, 0); //guilho
				}
                if(mapa[i][k] == -24){ // cima esq palco
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 2*32, 41*32, 32, 32, k*32, i*32, 0); //palco
                         
				}
                if(mapa[i][k] == -25){ //cima meio palco e meio esq guilho
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                           al_draw_bitmap_region(obstaculos, 3*32, 41*32, 32, 32, k*32, i*32, 0); //palco
                            al_draw_bitmap_region(obstaculos, 2*32, 45*32, 32, 32, k*32, i*32, 0); //guilho
				}
                if(mapa[i][k] == -26){ //cima dir palco e meio dir gilho
                             al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 4*32, 41*32, 32, 32, k*32, i*32, 0); //palco
                            al_draw_bitmap_region(obstaculos, 3*32, 45*32, 32, 32, k*32, i*32, 0); //guilho
				}
                if(mapa[i][k] == -27){ //meio esq palco 
                             al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 2*32, 42*32, 32, 32, k*32, i*32, 0); //palco
                            
				}
                if(mapa[i][k] == -28){ //meio meio palco e baixo esq guilho
                             al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 3*32, 42*32, 32, 32, k*32, i*32, 0); //palco
                            al_draw_bitmap_region(obstaculos, 2*32, 46*32, 32, 32, k*32, i*32, 0); //guilho
				}
                if(mapa[i][k] == -29){ //meio dir palco e baixo dir guilho
                             al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                           al_draw_bitmap_region(obstaculos, 4*32, 42*32, 32, 32, k*32, i*32, 0); //palco
                            al_draw_bitmap_region(obstaculos, 3*32, 46*32, 32, 32, k*32, i*32, 0); //guilho
				}
                if(mapa[i][k] == -30){ //baixo esq palco
                             al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 2*32, 43*32, 32, 32, k*32, i*32, 0);
				}
                  if(mapa[i][k] == -31){ //baixo meio palco
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 3*32, 43*32, 32, 32, k*32, i*32, 0);
				}
                if(mapa[i][k] == -32){ //baixo dir palco
                           al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 4*32, 43*32, 32, 32, k*32, i*32, 0);
				}

                // barraquinha peq

                 if(mapa[i][k] == -33){ //toldo cima
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); 
                            al_draw_bitmap_region(obstaculos, 5*32, 25*32, 32, 32, k*32, i*32, 0);
				}
                if(mapa[i][k] == -34){ //toldo meio
                           al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 5*32, 26*32, 32, 32, k*32, i*32, 0); 
				}
                if(mapa[i][k] == -35){ //toldo baixo e barraca cima
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 5*32, 28*32, 32, 32, k*32, i*32, 0); 
                            al_draw_bitmap_region(obstaculos, 5*32, 27*32, 32, 32, k*32, i*32, 0); 
                         
				}
                if(mapa[i][k] == -36){ //barraca baixo
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 5*32, 29*32, 32, 32, k*32, i*32, 0); 
                            
				}

                // barraca grande

                if(mapa[i][k] == -37){ //toldo cima esq
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 6*32, 25*32, 32, 32, k*32, i*32, 0);
				}
                if(mapa[i][k] == -38){ //toldo cima dir
                             al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 7*32, 25*32, 32, 32, k*32, i*32, 0); 
                            
				}
                if(mapa[i][k] == -39){ //toldo meio esq
                             al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 6*32, 26*32, 32, 32, k*32, i*32, 0); 
				}
                if(mapa[i][k] == -40){ //toldo meio dir
                             al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 7*32, 26*32, 32, 32, k*32, i*32, 0);
				}
                if(mapa[i][k] == -41){ //toldo baixo esq e barraca cima esq
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 6*32, 28*32, 32, 32, k*32, i*32, 0); //barraca
                            al_draw_bitmap_region(obstaculos, 6*32, 27*32, 32, 32, k*32, i*32, 0); //toldo
				}
                if(mapa[i][k] == -42){ //toldo baixo dir e barraca cima dir
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 7*32, 28*32, 32, 32, k*32, i*32, 0); 
                            al_draw_bitmap_region(obstaculos, 7*32, 27*32, 32, 32, k*32, i*32, 0); 
				}
                if(mapa[i][k] == -43){ //barraca baixo esq
                           al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 6*32, 29*32, 32, 32, k*32, i*32, 0);
				}
                if(mapa[i][k] == -44){ //barraca baixo dir
                           al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 7*32, 29*32, 32, 32, k*32, i*32, 0);
				}
               

                    // agua
                if(mapa[i][k] == -45){
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 415, 576, 32, 32, k*32, i*32, 0);
				}
                if(mapa[i][k] == -46){
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 447, 576, 32, 32, k*32, i*32, 0 );
				}
                if(mapa[i][k] == -47){
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 479, 576, 32, 32, k*32, i*32, 0 );
				}
                
                // cemiterio
                if(mapa[i][k] == -48){
                            al_draw_bitmap_region(grama, 0*32, 11*32, 32, 32, k*32, i*32, 0); 
                            al_draw_bitmap_region(obstaculos, 2*32, 2*32, 32, 32, k*32, i*32, 0);
				}
                if(mapa[i][k] == -49){
                            al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
                            al_draw_bitmap_region(obstaculos, 3*32, 4*32, 32, 32, k*32, i*32, 0 );
				}
                if(mapa[i][k] == -50){
                            al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
                            al_draw_bitmap_region(obstaculos, 4*32, 3*32, 32, 32, k*32, i*32, 0 );
				}

                // fonte
                if(mapa[i][k] == -51){
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 0*32, 18*32, 32, 32, k*32, i*32, 0);
				}
                if(mapa[i][k] == -52){
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 1*32, 18*32, 32, 32, k*32, i*32, 0 );
				}
                if(mapa[i][k] == -53){
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 0*32, 19*32, 32, 32, k*32, i*32, 0 );
				}
                if(mapa[i][k] == -54){
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 1*32, 19*32, 32, 32, k*32, i*32, 0 );
				}

                // poço
                if(mapa[i][k] == -55){
                            al_draw_bitmap_region(grama, 0*32, 11*32, 32, 32, k*32, i*32, 0); 
                            al_draw_bitmap_region(obstaculos, 14*32, 13*32, 32, 32, k*32, i*32, 0);
				}
                if(mapa[i][k] == -56){
                            al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
                            al_draw_bitmap_region(obstaculos, 15*32, 13*32, 32, 32, k*32, i*32, 0 );
				}
                if(mapa[i][k] == -57){
                            al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
                            al_draw_bitmap_region(obstaculos, 14*32, 14*32, 32, 32, k*32, i*32, 0 );
				}
                if(mapa[i][k] == -58){
                            al_draw_bitmap_region(grama, 0*32, 11*32, 32, 32, k*32, i*32, 0); 
                            al_draw_bitmap_region(obstaculos, 15*32, 14*32, 32, 32, k*32, i*32, 0);
				}
                if(mapa[i][k] == -59){
                            al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
                            al_draw_bitmap_region(obstaculos, 14*32, 15*32, 32, 32, k*32, i*32, 0 );
				}
                if(mapa[i][k] == -60){
                            al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
                            al_draw_bitmap_region(obstaculos, 15*32, 15*32, 32, 32, k*32, i*32, 0 );
				}

                //sacas e saquinhos
                if(mapa[i][k] == -61){ //sacas 1,1
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(objetos, 9*32, 8*32, 32, 32, k*32, i*32, 0 );
				}
                if(mapa[i][k] == -62){ //sacas 1,2
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(objetos, 10*32, 8*32, 32, 32, k*32, i*32, 0 );
				}
                if(mapa[i][k] == -63){ //sacas 2,1
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(objetos, 9*32, 9*32, 32, 32, k*32, i*32, 0 );
				}
                if(mapa[i][k] == -64){ //sacas 2,2
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(objetos, 10*32, 9*32, 32, 32, k*32, i*32, 0 );
				}
                if(mapa[i][k] == -65){ //saquinho 1
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(objetos, 7*32, 10*32, 32, 32, k*32, i*32, 0 );
				}
                if(mapa[i][k] == -66){ //saquinho 2
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(objetos, 8*32, 10*32, 32, 32, k*32, i*32, 0 );
				}

                 // barraquinha com produtos

                 if(mapa[i][k] == -67){ //toldo cima esq
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); 
                            al_draw_bitmap_region(objetos, 12*32, 0*32, 32, 32, k*32, i*32, 0);
				}
                if(mapa[i][k] == -68){ //toldo meio esq
                           al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(objetos, 13*32, 0*32, 32, 32, k*32, i*32, 0); 
				}
                if(mapa[i][k] == -69){ //toldo meio dir
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(objetos, 14*32, 0*32, 32, 32, k*32, i*32, 0);                          
				}
                if(mapa[i][k] == -70){ //toldo dir
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(objetos, 15*32, 0*32, 32, 32, k*32, i*32, 0);                
                }
                if(mapa[i][k] == -71){ //meio esq
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(objetos, 12*32, 1*32, 32, 32, k*32, i*32, 0);
				}
                if(mapa[i][k] == -72){ //meio meio esq
                             al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(objetos, 13*32, 1*32, 32, 32, k*32, i*32, 0);             
				}
                if(mapa[i][k] == -73){ //meio meio dir
                             al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(objetos, 14*32, 1*32, 32, 32, k*32, i*32, 0); 
				}
                if(mapa[i][k] == -74){ //meio dir
                             al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(objetos, 15*32, 1*32, 32, 32, k*32, i*32, 0);
				}
                if(mapa[i][k] == -75){ //barraca baixo esq
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(objetos, 12*32, 2*32, 32, 32, k*32, i*32, 0); //barraca                          
				}
                if(mapa[i][k] == -76){ //barraca baixo meio esq
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(objetos, 13*32, 2*32, 32, 32, k*32, i*32, 0);  
				}
                if(mapa[i][k] == -77){ //barraca baixo meio dir
                           al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(objetos, 14*32, 2*32, 32, 32, k*32, i*32, 0);
				}
                if(mapa[i][k] == -78){ //barraca baixo dir
                           al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(objetos, 15*32, 2*32, 32, 32, k*32, i*32, 0);
				}

                //lenha e corte
                 if(mapa[i][k] == -79){ //lenha 1,1
                            al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
                            al_draw_bitmap_region(objetos, 7*32, 11*32, 32, 32, k*32, i*32, 0 );
				}
                if(mapa[i][k] == -80){ //lenha 1,2
                            al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
                            al_draw_bitmap_region(objetos, 8*32, 11*32, 32, 32, k*32, i*32, 0 );
				}
                if(mapa[i][k] == -81){ //lenha 2,1
                            al_draw_bitmap_region(grama, 0*32, 11*32, 32, 32, k*32, i*32, 0); 
                            al_draw_bitmap_region(objetos, 7*32, 12*32, 32, 32, k*32, i*32, 0);
				}
                if(mapa[i][k] == -82){ //lenha 2,2
                            al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
                            al_draw_bitmap_region(objetos, 8*32, 12*32, 32, 32, k*32, i*32, 0 );
				}
                if(mapa[i][k] == -83){ //corte
                            al_draw_bitmap_region(grama, 1*32, 9*32, 32, 32, k*32, i*32, 0);
                            al_draw_bitmap_region(objetos, 15*32, 3*32, 32, 32, k*32, i*32, 0 );
				}

                //forca

               
                if(mapa[i][k] == -84){ //toldo baixo esq e barraca cima esq
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 0*32, 1423, 32, 32, k*32, i*32, 0); //barraca
                            
				}
                if(mapa[i][k] == -85){ //toldo baixo dir e barraca cima dir
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 1*32, 1423, 32, 32, k*32, i*32, 0); 
                           
				}
                if(mapa[i][k] == -86){ //barraca baixo esq
                           al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 0*32, 1455, 32, 32, k*32, i*32, 0);
				}
                if(mapa[i][k] == -87){ //barraca baixo esq
                           al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 1*32, 1455, 32, 32, k*32, i*32, 0);
				}

                // mesinha
                if(mapa[i][k] == -88){ //banco cima cima esq
                             al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                             al_draw_bitmap_region(obstaculos, 6*32, 35*32, 32, 32, k*32, i*32, 0); 
				}
                if(mapa[i][k] == -89){ // banco cima cima dir
                             al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                             al_draw_bitmap_region(obstaculos, 7*32, 35*32, 32, 32, k*32, i*32, 0);
				}
                if(mapa[i][k] == -90){ //banco cima baixo esq e mesa esq
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 6*32, 36*32, 32, 32, k*32, i*32, 0);  // banco                    
				}
                if(mapa[i][k] == -91){ //banco cima baixo dir e mesa dir
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 7*32, 36*32, 32, 32, k*32, i*32, 0); 
                            
				}
                if(mapa[i][k] == -92){ //banco baixo esq
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 6*32, 34*32, 32, 32, k*32, i*32, 0);
				}
                if(mapa[i][k] == -93){ //banco baixo dir
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 7*32, 34*32, 32, 32, k*32, i*32, 0);
				}
                if(mapa[i][k] == -94){ //banco baixo dir
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 8*32, 34*32, 32, 32, k*32, i*32, 0);  // mesa 
				}
                if(mapa[i][k] == -95){ //banco baixo dir
                            al_draw_bitmap_region(pedra, 22*32, 35*32, 32, 32, k*32, i*32, 0); // piso de pedra 2,2
                            al_draw_bitmap_region(obstaculos, 9*32, 34*32, 32, 32, k*32, i*32, 0); 
				}
               

		}
	}
 
 
    // Atualiza a tela
    al_flip_display();
 
    // Segura a execução por 10 segundos
    al_rest(40.0);
 
    // Finaliza a janela
    al_destroy_display(janela);
 
    return 0;
}

    

