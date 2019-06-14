#include "ACore.h"


bool coreInit(){  //Inicializando os modulos basicos!

    //modules and add-ons initialization
	if (!al_init()) {

        fprintf(stderr, "Falha ao inicializar Allegro.\n");
        return false;
    }

    if (!al_init_image_addon()){

        fprintf(stderr, "Falha ao inicializar add-on allegro_image.\n");
        return false;
    }

    if (!al_init_font_addon()){

        fprintf(stderr, "Falha ao inicializar add-on allegro_font.\n");
        return false;
    }

    if (!al_init_ttf_addon()){

        fprintf(stderr, "Falha ao inicializar add-on allegro_ttf.\n");
        return false;
    }

    if (!al_init_primitives_addon()){

        fprintf(stderr, "Falha ao inicializar add-on allegro_primitives.\n");
        return false;
    }

    eventsQueue = al_create_event_queue();

    if (!eventsQueue) {

        fprintf(stderr, "Falha ao criar fila de eventos.\n");
        return false;
    }

    return true;
}

bool windowInit(int W, int H, char title[]){    //Inicializando a janela!

    //window and event queue creation
    main_window = al_create_display(W, H);

    if (!main_window) {

        fprintf(stderr, "Falha ao criar janela.\n");
        return false;
    }

    al_set_window_title(main_window, "Battle Of Feuds");

    //registra janela na fila de eventos

    al_register_event_source(eventsQueue, al_get_display_event_source(main_window));

    return true;
}



bool inputInit(){ //Inicializando as entradas do teclado!

	/*------------------------------MOUSE--------------------------------*/

	if (!al_install_mouse()){  //Inicializa Mouse

        fprintf(stderr, "Falha ao inicializar o mouse.\n");
        al_destroy_display(main_window);
        return false;
    }

    if (!al_set_system_mouse_cursor(main_window, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT)){ // Atribui o cursor padrão do sistema para ser usado

        fprintf(stderr, "Falha ao atribuir ponteiro do mouse.\n");
        al_destroy_display(main_window);
        return false;
    }

    /*------------------------------KEYBOARD------------------------------*/
    if (!al_install_keyboard() ) {

        fprintf(stderr, "Falha ao inicializar o teclado.\n");
        return false;
    }

    /*------------------------------FILA DE EVENTOS------------------------------*/

    al_register_event_source(eventsQueue, al_get_mouse_event_source());     
    al_register_event_source(eventsQueue, al_get_keyboard_event_source());
    
    return true;
}



void readInput(ALLEGRO_EVENT event, char str[], int limit){ //Lendo as entradas pelo teclado no chat!

    if (event.type == ALLEGRO_EVENT_KEY_CHAR){

        if (strlen(str) <= limit){

            char temp[] = {event.keyboard.unichar, '\0'};
            if (event.keyboard.unichar == ' '){

                strcat(str, temp);
            }
            else if (event.keyboard.unichar >= '!' && event.keyboard.unichar <= '?'){

                strcat(str, temp);
            }
            else if (event.keyboard.unichar >= 'A' && event.keyboard.unichar <= 'Z'){

                strcat(str, temp);
            }
            else if (event.keyboard.unichar >= 'a' && event.keyboard.unichar <= 'z'){

                strcat(str, temp);
            }
        }

        if (event.keyboard.keycode == ALLEGRO_KEY_BACKSPACE && strlen(str) != 0){

            str[strlen(str) - 1] = '\0';
        }
    }
}


//FPS CONTROL (FPS IS DEFINED IN ACORE.H)
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


//FOR DEALLOCATING ALL ALLEGRO STUFF
void allegroEnd(){

    al_destroy_display(main_window);
    al_destroy_event_queue(eventsQueue);
}


bool fontInit(){        //Carregando todas as fontes!

    /*------------------------------FONTE--------------------------------*/

    start = al_load_font("examples/graphicChat/Resources/Fonts/pressStart.ttf", 16, 0);
    if (!start){

        fprintf(stderr, "Falha ao carregar \"examples/graphicChat/Resources/Fonts/pressStart.ttf\".\n");
        return false;
    }

    ubuntu = al_load_font("examples/graphicChat/Resources/Fonts/Ubuntu-R.ttf", 32, 0);

    if (!ubuntu){

        fprintf(stderr, "Falha ao carregar \"Ubuntu-R.ttf\".\n");
        return false;
    }

    fonteHTP = al_load_font("examples/graphicChat/Resources/Fonts/Amita-Regular.ttf", 30, 0);

    if (!fonteHTP){
        
        fprintf(stderr, "Falha ao carregar \"Amita-Regular.ttf.\n");
        return false;
    }

	fonteHTPTitulo = al_load_font("examples/graphicChat/Resources/Fonts/Amita-Bold.ttf", 50, 0);

    if (!fonteHTPTitulo){
        
        fprintf(stderr, "Falha ao carregar \"Amita-Bold.ttf.\n");
        return false;
    }

    return true;
}



bool loadGraphics(){    //Carregando todos os graficos!

    BackgroundMenu = al_load_bitmap("examples/graphicChat/Resources/Tilesets/BackgroundMenu.png"); 	

    if (!BackgroundMenu){

        fprintf(stderr, "Falha carregando BackgroundMenu.png\n");
        return false;
    }

	gameName = al_load_bitmap("examples/graphicChat/Resources/Tilesets/BattleOfFeudsName.png");

    if (!gameName){

        fprintf(stderr, "Falha carregando BattleOfFeudsName.png\n");
        return false;
    }

	gameIcon = al_load_bitmap("examples/graphicChat/Resources/Tilesets/BattleOfFeudsIcon.png");

    if (!gameIcon){

        fprintf(stderr, "Falha carregando BattleOfFeudsIcon.png\n");
        return false;
    }

	botaoPlay = al_load_bitmap("examples/graphicChat/Resources/Tilesets/StartGameButton01.png");

    if (!gameIcon){

        fprintf(stderr, "Falha carregando StartGameButton01.png\n");
        return false;
    }

	botaoHTP = al_load_bitmap("examples/graphicChat/Resources/Tilesets/HowToPlayButton01.png");

    if (!botaoHTP){

        fprintf(stderr, "Falha carregando HowToPlayButton01.png\n");
        return false;
    }

	botaoExit = al_load_bitmap("examples/graphicChat/Resources/Tilesets/ExitButton01.png");

    if (!botaoExit){

        fprintf(stderr, "Falha carBackgroundMenuregando ExitButton01.png");
        return false;
    }

	HTPwasd = al_load_bitmap("examples/graphicChat/Resources/Tilesets/HTPwasd.png");

    if (!HTPwasd){

        fprintf(stderr, "Falha carregando HTPwasd.png");
        return false;
    }

	HTPJ = al_load_bitmap("examples/graphicChat/Resources/Tilesets/HTPJ.png");

    if (!HTPJ){

        fprintf(stderr, "Falha carregando HTPJ.png");
        return false;
    }

	HTPK = al_load_bitmap("examples/graphicChat/Resources/Tilesets/HTPK.png");

    if (!HTPK){

        fprintf(stderr, "Falha carregando HTPK.png\n");
        return false;
    }

	HTPReturn = al_load_bitmap("examples/graphicChat/Resources/Tilesets/HTPReturn.png");

    if (!HTPReturn){

        fprintf(stderr, "Falha carregando HTPReturn.png\n");
        return false;
    }

	charSprite = al_load_bitmap("examples/graphicChat/Resources/Tilesets/PreviewSprite.png");

    if (!charSprite){

        fprintf(stderr, "Falha carregando charSprite.png\n");
        return false;
    }

	texturaMapa = al_load_bitmap("examples/graphicChat/Resources/Tilesets/imagemTexturas.png");

    if (!texturaMapa){

        fprintf(stderr, "Falha carregando texturaMapa.png\n");
        return false;
    }

    detalhesDoChao = al_load_bitmap("examples/graphicChat/Resources/Tilesets/detalhesDoChao.png");

    if (!detalhesDoChao){

        fprintf(stderr, "Falha carregando detalhesDoChao.png\n");
        return false;
    }

	heart = al_load_bitmap("examples/graphicChat/Resources/Tilesets/FullHeart.png");

    if (!heart){

        fprintf(stderr, "Falha carregando FullHeart.png");
        return false;

    }

    // Carrega a imagem
    
    grama = al_load_bitmap("examples/graphicChat/Resources/Tilesets/detalhesDoChao.png");

    if (!grama){

        fprintf(stderr, "Falha carregando detalhesDoChao.png");
        return false;

    }

    pedra = al_load_bitmap("examples/graphicChat/Resources/Tilesets/pedraChao.png");

    if (!pedra){

        fprintf(stderr, "Falha carregando pedraChao.png");
        return false;

    }

    cerca = al_load_bitmap("examples/graphicChat/Resources/Tilesets/cerca.png");

    if (!cerca){

        fprintf(stderr, "Falha carregando cerca.png");
        return false;

    }

    //obstaculo;
    obstaculos = al_load_bitmap("examples/graphicChat/Resources/Tilesets/obstaculos.png");

    if (!obstaculos){

        fprintf(stderr, "Falha carregando obstaculos.png");
        return false;

    }

    objetos = al_load_bitmap("examples/graphicChat/Resources/Tilesets/objetos.png"); 

    if (!objetos){

        fprintf(stderr, "Falha carregando objetos.png");
        return false;

    }

    skeletonButton = al_load_bitmap("examples/graphicChat/Resources/Tilesets/SkeletonButton.png");

    if (!skeletonButton){

        fprintf(stderr, "Falha carregando skeletonButton.png\n");
        return false;
    }

    ripperButton = al_load_bitmap("examples/graphicChat/Resources/Tilesets/RipperButton.png");
    
    if (!ripperButton){

        fprintf(stderr, "Falha carregando ripperButton.png\n");
        return false;
    }

    //Carregando as sprites

    Sprite_Skeleton0 = al_load_bitmap("examples/graphicChat/Resources/Tilesets/Sprite_Skeleton0.png"); 
    
    if (!Sprite_Skeleton0){

        fprintf(stderr, "Falha carregando Sprite_Skeleton0.png");
        return false;

    }

    Sprite_Ripper01 = al_load_bitmap("examples/graphicChat/Resources/Tilesets/Sprite_Ripper01.png");

    if (!Sprite_Ripper01){

        fprintf(stderr, "Falha carregando Sprite_Ripper01.png");
        return false;

    }

    return true;
}