
void frame( SDL_Event event ){

//  SDL_SetRenderDrawColor( renderer , 0,0,0 , 255 );
//  SDL_RenderClear( renderer );
        
//  pix( rand()%WID , rand()%HGT, rand()%256 , rand()%256 , rand()%256 );
  pix( event.motion.x , event.motion.y , 255 , 255 , 255 );
}
