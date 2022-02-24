

#include "snapshot.h"


void audio_in_callback( void *userdata , Uint8 *stream , int len_bytes ){
  short *frame = (short*)stream;
  int len_frames = len_bytes / sizeof(*frame);
  for (; len_frames > 0; len_frames-- , frame++ ){
    snapshot_wr(*frame/32768.0);
  }
}




//void autocorr( float *out , int out_len ){
//  float buf[out_len*2];
//  snapshot_rd(buf,COUNT(out));
//  // naive impl. O(n²)
//  for(int lag=0;lag<out_len;lag++){
//    float sqdiff = 0;
//    for(int i=0;i<out_len;i++){
//      float xc = buf[i]-buf[i+lag];
//      sqdiff += xc*xc;
//    }
//    *out++ = sqdiff;
//  }
//}


