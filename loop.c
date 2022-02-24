
#include "frame.c"

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>


void eat()
{
  struct LR { short l,r; } lr;
  fcntl(0,F_SETFL,fcntl(0,F_GETFL)|O_NONBLOCK);
  while(1)
  {
    if(read(0,&lr,sizeof(lr))<=0)return;
    // fai robe
    static int x=0;
    pix( x , HGT/2-lr.l*(HGT/2)/32768.0, 256,256,256 );
    pix( x , HGT/2-lr.r*(HGT/2)/32768.0, 256,0,0 );
    x++;
    x%=WID;
  }
}


void loop(){
    
    while(1){

        eat();
        
        SDL_Event event;
        while( SDL_PollEvent(&event)){
            switch( event.type ){
                case SDL_KEYDOWN:
//                    printf( "Il tasto %s e' stato premuto!\n",
//                           SDL_GetKeyName(event.key.keysym.sym));
//                    switch( event.key.keysym.sym ){
//                      case SDLK_1 :
//                        printf( "1\n" );
//                      break;
//                    }
                    break;
                case SDL_KEYUP:
                    break;
                case SDL_MOUSEMOTION:
//                    printf("Il Mouse e' stato mosso da %d,%d "
//                               "a(%d,%d)\n", 
//                           event.motion.xrel, event.motion.yrel,
//                           event.motion.x , event.motion.y );
                    break;
                case SDL_MOUSEBUTTONDOWN:
//                    printf(
//                        "Il pulsante %d del Mouse e' stato "
//                        "premuto a(%d,%d)\n",
//                        event.button.button, 
//                        event.button.x, 
//                        event.button.y );
                    break;
                case SDL_MOUSEBUTTONUP:
                    break;
                case SDL_QUIT:
//                    printf( "SDL_QUIT\n" );
                    return;
            }
        }

        frame( event );

        SDL_RenderPresent(renderer);
        SDL_Delay(1);
    }
}    




