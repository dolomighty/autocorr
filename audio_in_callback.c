

#include "snapshot.h"


void audio_in_callback( void *userdata , Uint8 *stream , int len_bytes ){
  short *frame = (short*)stream;
  int len_frames = len_bytes / sizeof(*frame);
  for (; len_frames > 0; len_frames-- , frame++ ){
    snapshot_wr(*frame/32768.0);
  }
}


