
#include <stdlib.h>
#include <unistd.h>
#include <SDL2/SDL.h>

SDL_Renderer *renderer;


#include "pix.c"
#include "loop.c"
#include "audio_in_callback.c"

#include "macros.h"

int main( int argc , char *argv[] ){ 

  SDL_Window *win = 
    SDL_CreateWindow( "sdl2" , 
      SDL_WINDOWPOS_UNDEFINED , SDL_WINDOWPOS_UNDEFINED , 
        WID , HGT , 0 );

  if(!win){
    fprintf(stderr,"!SDL_CreateWindow: %s\n",SDL_GetError());
    exit(1);
  }

  renderer = SDL_CreateRenderer( win , -1 , 0 );

  if(!renderer){
    fprintf(stderr,"!SDL_CreateRenderer: %s\n",SDL_GetError());
    exit(1);
  }

  if(0!=SDL_Init(SDL_INIT_AUDIO)){
    fprintf(stderr,"!SDL_Init: %s\n",SDL_GetError());
    exit(1);
  }


  SDL_AudioSpec want, have;
  SDL_zero(want);
  want.freq     = 11025;
  want.format   = AUDIO_S16;
  want.channels = 1;
  want.samples  = 256;
  want.callback = audio_in_callback;

  SDL_AudioDeviceID dev = SDL_OpenAudioDevice(0,SDL_TRUE,&want,&have,0);
  if(!dev){
    fprintf(stderr,"!SDL_OpenAudioDevice: %s\n",SDL_GetError());
    exit(1);
  }
  
  SDL_PauseAudioDevice(dev,0);  // start audio activity
  loop();
  SDL_CloseAudioDevice(dev);

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(win);
  
  return 0 ;
}


