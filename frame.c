

#include "snapshot.h"
#include "macros.h"



float lerp( float a , float b , float x ){ return a+(b-a)*x; }



void frame( SDL_Event event ){

//  pix( rand()%WID , rand()%HGT, rand()%256 , rand()%256 , rand()%256 );
//  pix( event.motion.x , event.motion.y , 255 , 255 , 255 );


  SDL_SetRenderDrawColor( renderer , 0,0,0 , 255 );
  SDL_RenderClear(renderer);

  SDL_SetRenderDrawColor( renderer , 255,255,255 , 255 );

  float snap[WID];
  snapshot_rd(snap,COUNT(snap));

  for(int x=0;x<WID;x++)
  {
    float v = snap[x];
    if(v<0)v=-v;
    SDL_Rect rectangle;
    rectangle.x = x;
    rectangle.y = lerp(HGT/2,0,v);
    rectangle.w = 1;
    rectangle.h = lerp(0,HGT,v);
    SDL_RenderFillRect(renderer,&rectangle);
  }
}


