

volatile float max_rms=0;
volatile char req_new_rms=1;


void audio_in_callback( void *userdata , Uint8 *stream , int len_bytes ){
  short *frame = (short*)stream;
  int len_frames = len_bytes / sizeof(*frame);

  static char prev_req_new_rms=0;
  if(prev_req_new_rms!=req_new_rms){
    prev_req_new_rms=req_new_rms;
    max_rms=0;
  }

  for (; len_frames > 0; len_frames-- , frame++ ){
    float rms = *frame/32768.0;
    rms *= rms;
    if(max_rms<rms)max_rms=rms;
  }
}

