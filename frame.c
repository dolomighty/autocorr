

extern volatile float max_rms;
extern volatile char req_new_rms;


void frame( SDL_Event event ){

//  pix( rand()%WID , rand()%HGT, rand()%256 , rand()%256 , rand()%256 );
//  pix( event.motion.x , event.motion.y , 255 , 255 , 255 );

  SDL_Rect rectangle;

//  SDL_SetRenderDrawColor( renderer , 0,0,0 , 255 );
//  SDL_RenderClear(renderer);

  SDL_SetRenderDrawColor( renderer , 255,255,255 , 255 );
  rectangle.x = 0;
  rectangle.y = 0;
  rectangle.w = max_rms*WID;
  rectangle.h = HGT;
  SDL_RenderFillRect(renderer, &rectangle);

  SDL_SetRenderDrawColor( renderer , 0,0,0 , 255 );
  rectangle.x = rectangle.w;
  rectangle.w = WID-rectangle.x;
  SDL_RenderFillRect(renderer, &rectangle);

  req_new_rms++;
}
