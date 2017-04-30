/*
 * SDL_Plotter.h
 *
 *  Created on: Jun 13, 2016
 *      Author: booth
 */

#ifndef SDL_PLOTTER_H_
#define SDL_PLOTTER_H_

//OSX Library
//#include <SDL2/SDL.h>
//#include <SDL2_mixer/SDL_mixer.h>
//#include <SDL2/SDL_thread.h>

//Windows Library
#include <SDL.h>
#include <SDL_mixer.h>

#include <string.h>
#include <iostream>
#include <string>
#include <string.h>
#include <map>
using namespace std;

const char UP_ARROW    = 1;
const char DOWN_ARROW  = 2;
const char LEFT_ARROW  = 3;
const char RIGHT_ARROW = 4;
const int RED_SHIFT   = 65536;
const int GREEN_SHIFT = 256;
const int BLUE_SHIFT  = 1;
const int ALPHA_SHIFT = 16777216;
const int WHITE = 255;
const int MAX_THREAD = 100;

#define MUS_PATH "scratch.wav"

//sample threaded sound function
static int Sound(void *data);

struct param{
	bool play;
	bool running;
	bool pause;
	SDL_Thread*  threadID;
	SDL_cond *cond;
	SDL_mutex *mut;
	string name;

	param(){
		play = false;
		running = false;
		pause = false;
	}
};

class SDL_Plotter{
private:
	SDL_Texture * texture;
	SDL_Renderer * renderer;
	SDL_Window * window;

	bool leftMouseButtonDown;
    Uint32 * pixels;
    const Uint8* currentKeyStates;

    int row, col;
    bool quit;
    SDL_Event event;

    //Sound Stuff
    bool SOUND;
    int soundCount;
    map<string, param> soundMap;

public:



    SDL_Plotter(int r=480, int c=640, bool WITH_SOUND = true){
    	row = r;
    	col = c;
    	leftMouseButtonDown = false;
    	quit = false;
    	SOUND = WITH_SOUND;

    	SDL_Init(SDL_INIT_AUDIO);

        window   = SDL_CreateWindow("SDL2 Pixel Drawing",
        		                     SDL_WINDOWPOS_UNDEFINED,
        		                     SDL_WINDOWPOS_UNDEFINED, col, row, 0);

        renderer = SDL_CreateRenderer(window, -1, 0);

        texture  = SDL_CreateTexture(renderer,
        		                     SDL_PIXELFORMAT_ARGB8888,
        		                     SDL_TEXTUREACCESS_STATIC, col, row);

        pixels   = new Uint32[col * row];

        memset(pixels, WHITE, col * row * sizeof(Uint32));

        //SOUND Thread Pool
        Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );
        soundCount = 0;

      }


    ~SDL_Plotter(){
        delete[] pixels;
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();

    }

    void update(){
        SDL_UpdateTexture(texture, NULL, pixels, col * sizeof(Uint32));
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    bool getQuit(){
    	return quit;
    }

    bool kbhit(){
    	bool flag = false;
    	if(SDL_PollEvent(&event)){
    		if(event.type == SDL_KEYDOWN){
    			flag = true;
    		}
    		if( event.type == SDL_QUIT )
			{
				quit = true;
			}
    	}
    	return flag;
    }

    char getKey(){

    	char key = '\0';


		currentKeyStates = SDL_GetKeyboardState( NULL );
		if(currentKeyStates[SDL_SCANCODE_A]) key = 'A';
		if(currentKeyStates[SDL_SCANCODE_B]) key = 'B';
		if(currentKeyStates[SDL_SCANCODE_C]) key = 'C';
		if(currentKeyStates[SDL_SCANCODE_D]) key = 'D';
		if(currentKeyStates[SDL_SCANCODE_E]) key = 'E';
		if(currentKeyStates[SDL_SCANCODE_F]) key = 'F';
		if(currentKeyStates[SDL_SCANCODE_G]) key = 'G';
		if(currentKeyStates[SDL_SCANCODE_H]) key = 'H';
		if(currentKeyStates[SDL_SCANCODE_I]) key = 'I';
		if(currentKeyStates[SDL_SCANCODE_J]) key = 'J';
		if(currentKeyStates[SDL_SCANCODE_K]) key = 'K';
		if(currentKeyStates[SDL_SCANCODE_L]) key = 'L';
		if(currentKeyStates[SDL_SCANCODE_M]) key = 'M';
		if(currentKeyStates[SDL_SCANCODE_N]) key = 'N';
		if(currentKeyStates[SDL_SCANCODE_O]) key = 'O';
		if(currentKeyStates[SDL_SCANCODE_P]) key = 'P';
		if(currentKeyStates[SDL_SCANCODE_Q]) key = 'Q';
		if(currentKeyStates[SDL_SCANCODE_R]) key = 'R';
		if(currentKeyStates[SDL_SCANCODE_S]) key = 'S';
		if(currentKeyStates[SDL_SCANCODE_T]) key = 'T';
		if(currentKeyStates[SDL_SCANCODE_U]) key = 'U';
		if(currentKeyStates[SDL_SCANCODE_V]) key = 'V';
		if(currentKeyStates[SDL_SCANCODE_W]) key = 'W';
		if(currentKeyStates[SDL_SCANCODE_X]) key = 'X';
		if(currentKeyStates[SDL_SCANCODE_Y]) key = 'Y';
		if(currentKeyStates[SDL_SCANCODE_Z]) key = 'Z';
		if(currentKeyStates[SDL_SCANCODE_1]) key = '1';
		if(currentKeyStates[SDL_SCANCODE_2]) key = '2';
		if(currentKeyStates[SDL_SCANCODE_3]) key = '3';
		if(currentKeyStates[SDL_SCANCODE_4]) key = '4';
		if(currentKeyStates[SDL_SCANCODE_5]) key = '5';
		if(currentKeyStates[SDL_SCANCODE_6]) key = '6';
		if(currentKeyStates[SDL_SCANCODE_7]) key = '7';
		if(currentKeyStates[SDL_SCANCODE_8]) key = '8';
		if(currentKeyStates[SDL_SCANCODE_9]) key = '9';
		if(currentKeyStates[SDL_SCANCODE_0]) key = '0';
		if(currentKeyStates[SDL_SCANCODE_SPACE]) key = ' ';
		if(currentKeyStates[SDL_SCANCODE_DOWN])  key = DOWN_ARROW;
		if(currentKeyStates[SDL_SCANCODE_UP])    key = UP_ARROW;
		if(currentKeyStates[SDL_SCANCODE_LEFT])  key = LEFT_ARROW;
		if(currentKeyStates[SDL_SCANCODE_RIGHT]) key = RIGHT_ARROW;
		if(currentKeyStates[SDL_SCANCODE_RETURN]) key = SDL_SCANCODE_RETURN;
		if(currentKeyStates[SDL_SCANCODE_ESCAPE]) quit = true;

    	return key;
    }

    void plotPixel(int x, int y, int r, int g, int b){
    	pixels[y * col + x] = RED_SHIFT*r + GREEN_SHIFT*g + BLUE_SHIFT*b;
    }

    void clear(){
    	memset(pixels, WHITE, col * row * sizeof(Uint32));
    }

    int getRow(){
    	return row;
    }

    int getCol(){
    	return col;
    }

    void initSound(string sound){
    	//int  *threadReturnValue;

		if(!soundMap[sound].running){
				param* p = &soundMap[sound];
				p->name = sound;
				p->cond = SDL_CreateCond();
				p->mut = SDL_CreateMutex();

				p->threadID = SDL_CreateThread( Sound, sound.c_str(), (void*)p );
				//p->threadID = SDL_CreateThread( Sound, "SoundThread", (void*)p );
				//SDL_DetachThread(p->threadID);
		}
    }

    void setQuit(bool flag){
    	this->quit = flag;
    }

    void playSound(string sound){
    	if(soundMap[sound].running){
    		SDL_CondSignal(soundMap[sound].cond);
    	}
    }

    void quitSound(string sound){
    	soundMap[sound].running = false;
    	SDL_CondSignal(soundMap[sound].cond);
    }

    void Sleep(int ms){
    	SDL_Delay(ms);
    }
};



//Threaded Function

static int Sound(void *data){
	param *p = (param*)data;
	p->running = true;
	Mix_Chunk *gScratch = NULL;
	gScratch = Mix_LoadWAV( p->name.c_str() );


	while(p->running){
		SDL_mutexP( p->mut );
		  SDL_CondWait(p->cond, p->mut);
		  Mix_PlayChannel( -1, gScratch, 0 );
		  p->play = false;
		SDL_mutexV(p->mut);
	}

	Mix_FreeChunk( gScratch );
	p->running = false;
	return 0;
}



#endif /* SDL_PLOTTER_H_ */
