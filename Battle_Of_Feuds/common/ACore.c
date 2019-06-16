#include "ACore.h"


bool coreInit(){  //Inicializando os modulos basicos!

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

    if(!al_install_audio()){

        fprintf(stderr, "Falha ao inicializar add-on al_install_audio.\n");
        return -1;
    }

   if(!al_init_acodec_addon()) {

        fprintf(stderr, "Falha ao inicializar add-on al_init_acodec!\n");
        return -1;
    }

    eventsQueue = al_create_event_queue();

    if (!eventsQueue) {

        fprintf(stderr, "Falha ao criar fila de eventos.\n");
        return false;
    }

    return true;
}


bool windowInit(int W, int H, char title[]){ //Inicializando a janela principal da allegro!

    main_window = al_create_display(W, H);

    if (!main_window) {

        fprintf(stderr, "Falha ao criar janela.\n");
        return false;
    }

    al_set_window_title(main_window, "Battle Of Feuds");

    al_register_event_source(eventsQueue, al_get_display_event_source(main_window));    //registra janela na fila de eventos

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


//Funções que realizando o controle do FPS
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


//Desalocar todos os ponteiros usados na Allegro
void allegroEnd(){

    al_destroy_display(main_window);
    al_destroy_event_queue(eventsQueue);

    al_destroy_bitmap(BackgroundMenu); //BITMAPS!
    al_destroy_bitmap(gameName);
    al_destroy_bitmap(gameIcon);
    al_destroy_bitmap(HTPwasd);
    al_destroy_bitmap(HTPK);
    al_destroy_bitmap(HTPReturn);
    al_destroy_bitmap(botaoPlay);
    al_destroy_bitmap(botaoHTP);
    al_destroy_bitmap(botaoExit);
    al_destroy_bitmap(skeletonButton);
    al_destroy_bitmap(ripperButton);
    al_destroy_bitmap(deathKnightButton);
    al_destroy_bitmap(ogreButton);
    al_destroy_bitmap(goblinButton);
    al_destroy_bitmap(skeleton05Button);
    al_destroy_bitmap(texturaMapa);
    al_destroy_bitmap(detalhesDoChao);
    al_destroy_bitmap(grama);
    al_destroy_bitmap(pedra);
    al_destroy_bitmap(cerca);
    al_destroy_bitmap(obstaculos);
    al_destroy_bitmap(objetos);

    al_destroy_bitmap(Sprite_Skeleton0);    //SPRITES
    al_destroy_bitmap(Sprite_Ripper01);
    al_destroy_bitmap(Sprite_DeathKnight02);
    al_destroy_bitmap(Sprite_Ogre03);
    al_destroy_bitmap(Sprite_Goblin04);
    al_destroy_bitmap(Sprite_Skeleton05);
    al_destroy_bitmap(heart);

    al_destroy_audio_stream(menuGameSong);  // SOUNDS
    al_destroy_audio_stream(deathSong);
    al_destroy_audio_stream(victorySong);
    al_destroy_audio_stream(conflictSong);

    al_destroy_font(ubuntu);    //FONTS 
    al_destroy_font(start);
    al_destroy_font(fonteHTP);
    al_destroy_font(fonteHTPTitulo);

}


bool fontInit(){    //Inicializando todas as fontes usadas

    /*------------------------------FONTE--------------------------------*/

    start = al_load_font("Battle_Of_Feuds/Resources/Fonts/pressStart.ttf", 16, 0);

    if (!start){

        fprintf(stderr, "Falha ao carregar \"examples/graphicChat/Resources/Fonts/pressStart.ttf\".\n");
        return false;
    }

    ubuntu = al_load_font("Battle_Of_Feuds/Resources/Fonts/Ubuntu-R.ttf", 32, 0);

    if (!ubuntu){

        fprintf(stderr, "Falha ao carregar \"Ubuntu-R.ttf\".\n");
        return false;
    }

    fonteHTP = al_load_font("Battle_Of_Feuds/Resources/Fonts/Amita-Regular.ttf", 30, 0);

    if (!fonteHTP){
        
        fprintf(stderr, "Falha ao carregar \"Amita-Regular.ttf.\n");
        return false;
    }

	fonteHTPTitulo = al_load_font("Battle_Of_Feuds/Resources/Fonts/Amita-Bold.ttf", 50, 0);

    if (!fonteHTPTitulo){
        
        fprintf(stderr, "Falha ao carregar \"Amita-Bold.ttf.\n");
        return false;
    }

    return true;
}



bool loadGraphics(){    //Carregando todos os graficos utilizados


    /*------------------------------Buttons && Background--------------------------------*/

    BackgroundMenu = al_load_bitmap("Battle_Of_Feuds/Resources/Tilesets/BackgroundMenu.png"); 	

    if (!BackgroundMenu){

        fprintf(stderr, "Falha carregando BackgroundMenu.png\n");
        return false;
    }

	gameName = al_load_bitmap("Battle_Of_Feuds/Resources/Tilesets/BattleOfFeudsName.png");

    if (!gameName){

        fprintf(stderr, "Falha carregando BattleOfFeudsName.png\n");
        return false;
    }

	gameIcon = al_load_bitmap("Battle_Of_Feuds/Resources/Tilesets/BattleOfFeudsIcon.png");

    if (!gameIcon){

        fprintf(stderr, "Falha carregando BattleOfFeudsIcon.png\n");
        return false;
    }

	botaoPlay = al_load_bitmap("Battle_Of_Feuds/Resources/Tilesets/StartGameButton.png");

    if (!gameIcon){

        fprintf(stderr, "Falha carregando StartGameButton01.png\n");
        return false;
    }

	botaoHTP = al_load_bitmap("Battle_Of_Feuds/Resources/Tilesets/HowToPlayButton.png");

    if (!botaoHTP){

        fprintf(stderr, "Falha carregando HowToPlayButton01.png\n");
        return false;
    }

	botaoExit = al_load_bitmap("Battle_Of_Feuds/Resources/Tilesets/ExitButton.png");

    if (!botaoExit){

        fprintf(stderr, "Falha carBackgroundMenuregando ExitButton01.png");
        return false;
    }

	HTPwasd = al_load_bitmap("Battle_Of_Feuds/Resources/Tilesets/HTPwasd.png");

    if (!HTPwasd){

        fprintf(stderr, "Falha carregando HTPwasd.png");
        return false;
    }

	HTPK = al_load_bitmap("Battle_Of_Feuds/Resources/Tilesets/HTPK.png");

    if (!HTPK){

        fprintf(stderr, "Falha carregando HTPK.png\n");
        return false;
    }

	HTPReturn = al_load_bitmap("Battle_Of_Feuds/Resources/Tilesets/HTPReturn.png");

    if (!HTPReturn){

        fprintf(stderr, "Falha carregando HTPReturn.png\n");
        return false;
    }

	heart = al_load_bitmap("Battle_Of_Feuds/Resources/Tilesets/FullHeart.png");

    if (!heart){

        fprintf(stderr, "Falha carregando FullHeart.png");
        return false;

    }

    skeletonButton = al_load_bitmap("Battle_Of_Feuds/Resources/Tilesets/SkeletonButton.png");

    if (!skeletonButton){

        fprintf(stderr, "Falha carregando skeletonButton.png\n");
        return false;
    }

    ripperButton = al_load_bitmap("Battle_Of_Feuds/Resources/Tilesets/RipperButton.png");
    
    if (!ripperButton){

        fprintf(stderr, "Falha carregando ripperButton.png\n");
        return false;
    }

    deathKnightButton = al_load_bitmap("Battle_Of_Feuds/Resources/Tilesets/DeathKnightButton.png");
    
    if (!deathKnightButton){

        fprintf(stderr, "Falha carregando ripperButton.png\n");
        return false;
    }

    ogreButton = al_load_bitmap("Battle_Of_Feuds/Resources/Tilesets/OgreButton.png");
    
    if (!ogreButton){

        fprintf(stderr, "Falha carregando ogre.png\n");
        return false;
    }

    goblinButton = al_load_bitmap("Battle_Of_Feuds/Resources/Tilesets/GoblinButton.png");
    
    if (!goblinButton){

        fprintf(stderr, "Falha carregando goblinButton.png\n");
        return false;
    }

    
    skeleton05Button = al_load_bitmap("Battle_Of_Feuds/Resources/Tilesets/Skeleton05Button.png");

    if (!skeleton05Button){

        fprintf(stderr, "Falha carregando Skeleton05Button.png\n");
        return false;
    }

    /*------------------------------------Mapa------------------------------------*/

    texturaMapa = al_load_bitmap("Battle_Of_Feuds/Resources/Tilesets/imagemTexturas.png");

    if (!texturaMapa){

        fprintf(stderr, "Falha carregando texturaMapa.png\n");
        return false;
    }

    detalhesDoChao = al_load_bitmap("Battle_Of_Feuds/Resources/Tilesets/detalhesDoChao.png");

    if (!detalhesDoChao){

        fprintf(stderr, "Falha carregando detalhesDoChao.png\n");
        return false;
    }
    
    grama = al_load_bitmap("Battle_Of_Feuds/Resources/Tilesets/detalhesDoChao.png");

    if (!grama){

        fprintf(stderr, "Falha carregando detalhesDoChao.png");
        return false;

    }

    pedra = al_load_bitmap("Battle_Of_Feuds/Resources/Tilesets/pedraChao.png");

    if (!pedra){

        fprintf(stderr, "Falha carregando pedraChao.png");
        return false;

    }

    cerca = al_load_bitmap("Battle_Of_Feuds/Resources/Tilesets/cerca.png");

    if (!cerca){

        fprintf(stderr, "Falha carregando cerca.png");
        return false;

    }

    obstaculos = al_load_bitmap("Battle_Of_Feuds/Resources/Tilesets/obstaculos.png");

    if (!obstaculos){

        fprintf(stderr, "Falha carregando obstaculos.png");
        return false;

    }

    objetos = al_load_bitmap("Battle_Of_Feuds/Resources/Tilesets/objetos.png"); 

    if (!objetos){

        fprintf(stderr, "Falha carregando objetos.png");
        return false;

    }
    
    /*------------------------------------Sprites------------------------------------*/

    Sprite_Skeleton0 = al_load_bitmap("Battle_Of_Feuds/Resources/Tilesets/Sprite_Skeleton0.png"); 
    
    if (!Sprite_Skeleton0){

        fprintf(stderr, "Falha carregando Sprite_Skeleton0.png");
        return false;

    }

    Sprite_Ripper01 = al_load_bitmap("Battle_Of_Feuds/Resources/Tilesets/Sprite_Ripper01.png");

    if (!Sprite_Ripper01){

        fprintf(stderr, "Falha carregando Sprite_Ripper01.png");
        return false;

    }

    Sprite_DeathKnight02 = al_load_bitmap("Battle_Of_Feuds/Resources/Tilesets/Sprite_DeathKnight02.png");

    if (!Sprite_DeathKnight02){

        fprintf(stderr, "Falha carregando Sprite_DeathKnight02.png");
        return false;

    }

    Sprite_Ogre03 = al_load_bitmap("Battle_Of_Feuds/Resources/Tilesets/Sprite_Ogre03.png");

    if (!Sprite_Ogre03){

        fprintf(stderr, "Falha carregando Sprite_ogre03.png");
        return false;

    }

    Sprite_Goblin04 = al_load_bitmap("Battle_Of_Feuds/Resources/Tilesets/Sprite_Goblin04.png");

    if (!Sprite_Goblin04){

        fprintf(stderr, "Falha carregando Sprite_Goblin04.png");
        return false;

    }
    
    Sprite_Skeleton05 = al_load_bitmap("Battle_Of_Feuds/Resources/Tilesets/Sprite_Skeleton05.png"); 
    
    if (!Sprite_Skeleton05){

        fprintf(stderr, "Falha carregando Sprite_Skeleton05.png");
        return false;

    }

    /*------------------------------------Songs------------------------------------*/

    menuGameSong = al_load_audio_stream("Battle_Of_Feuds/Resources/Tilesets/menuSong.ogg", 4, 1024);

    if (!menuGameSong){

        fprintf(stderr, "Falha carregando menuGameSong.ogg");
        return false;

    }

    conflictSong = al_load_audio_stream("Battle_Of_Feuds/Resources/Tilesets/conflictSong.ogg", 4, 1024);

    if (!conflictSong){

        fprintf(stderr, "Falha carregando conflictSong.ogg");
        return false;

    }

    deathSong = al_load_audio_stream("Battle_Of_Feuds/Resources/Tilesets/deathSong.ogg", 4, 1024);

    if (!deathSong){

        fprintf(stderr, "Falha carregando deathSong.ogg");
        return false;

    }

    victorySong = al_load_audio_stream("Battle_Of_Feuds/Resources/Tilesets/victorySong.ogg", 4, 1024);
    
    if (!victorySong){

        fprintf(stderr, "Falha carregando victorySong.ogg");
        return false;

    }

    return true;
}