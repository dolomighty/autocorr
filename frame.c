

#include "snapshot.h"
#include "macros.h"



float lerp( float a , float b , float x ){ return a+(b-a)*x; }






void autocorr( float *out , int out_len , int lag_start , float *in ){
  // naive impl. O(n²)
  // non è propriamente autocorrelazione
  // nel senso che cosi calcolata l'autocorr massima = 0
  // in letteratura dovrebbe essere +1 ... ma chissene
  // per i miei scopi è indifferente
  for(int lag=lag_start;lag<out_len;lag++){
    float sqdiff = 0;
    for(int i=0;i<out_len;i++){
      float diff = in[i]-in[i+lag];
      sqdiff += diff*diff;
    }
//    out[lag] = sqdiff/(out_len-lag_start);  // scalatura "giusta" ... gole pessime
//    sqdiff=sqrt(sqdiff);  // sarebbe più corretto, ma farlo genera gole meno accentuate
    out[lag] = sqdiff/(1+sqdiff);  // scalatura quasi-log (reinhard) aiuta nel delineare le gole
  }
}





void frame( SDL_Event event ){

//  pix( rand()%WID , rand()%HGT, rand()%256 , rand()%256 , rand()%256 );
//  pix( event.motion.x , event.motion.y , 255 , 255 , 255 );

  SDL_SetRenderDrawColor( renderer , 0,0,0 , 255 );
  SDL_RenderClear(renderer);

  SDL_SetRenderDrawColor( renderer , 255,255,255 , 255 );

  float snap[WID];
  snapshot_rd(snap,COUNT(snap));

  float acor[WID/2]={};  // min Hz (=max lag)
  autocorr( acor , COUNT(acor) , 0 , snap );
//  autocorr(acor, COUNT(acor) , SR/1000 , snap);
//  //                           ^^^max Hz (=min lag)

  for(int x=0;x<WID;x++)
  {
    float v = snap[x];
    if(v<0)v=-v;

    SDL_Rect rectangle;
    rectangle.x = x;
    rectangle.y = lerp(HGT/4,0,v);
    rectangle.w = 1;
    rectangle.h = lerp(0,HGT/2,v);
    SDL_RenderFillRect(renderer,&rectangle);

    if(x>=COUNT(acor))continue;
    v = acor[x];
    rectangle.y = lerp(HGT,HGT/2,v);
    rectangle.h = lerp(0,HGT/2,v);
    SDL_RenderFillRect(renderer,&rectangle);
  }
}


