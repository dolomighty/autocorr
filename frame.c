

#include "snapshot.h"
#include "autocorr.c"
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



  // l'idea come sempre è di minimizzare i calcoli
  // l'autocorrelazione viene calcolata in un certo range di lag
  // poi si cerca la prima gola intorno allo 0
  // partendo da lag 0

#define SR 11025

  static int min_lag;
  static int max_lag;
  static int notch_lag = 0;

  if(notch_lag==0)
  {
    min_lag = SR/600;
    max_lag = SR/60;
  }

  float acor[SR/60]={0};
  float avg = autocorr( acor, max_lag , min_lag , snap );

  if(avg<0.1)
  {
    notch_lag=0;    
  }
  else  
  {
    // troviamo il minimo assoluto intorno a 0
    int cand_min=10;
    for(int i=min_lag;i<max_lag;i++)
    {
      if(cand_min<acor[i])continue; // cerchiamo il minimo
      if(acor[i]>0.1)continue;  // tra 0 e ...
      cand_min=acor[i];
      notch_lag=i;
    }
    min_lag=notch_lag-5;
    max_lag=notch_lag+5;
  }


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

  SDL_SetRenderDrawColor( renderer , 255,0,0 , 255 );

  SDL_Rect rectangle;
  rectangle.x = min_lag;
  rectangle.y = HGT*3/4;
  rectangle.w = 1;
  rectangle.h = HGT*1/4;
  SDL_RenderFillRect(renderer,&rectangle);
  rectangle.x = max_lag;
  SDL_RenderFillRect(renderer,&rectangle);
}


