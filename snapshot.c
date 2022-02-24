

#define COUNT(ARR) (sizeof(ARR)/sizeof(ARR[0]))

#include <string.h>
#include <stdio.h>

float snapshot_buffer[2048]={0};
float *snapshot_wr_ptr = &snapshot_buffer[0];



void snapshot_wr( float v ) // HEADER
{
  *snapshot_wr_ptr=v;
  snapshot_wr_ptr++;
  if(snapshot_wr_ptr >= &snapshot_buffer[COUNT(snapshot_buffer)]) snapshot_wr_ptr = &snapshot_buffer[0];
}


void snapshot_rd( float *dst , int samples ) // HEADER
{
  float *src = snapshot_wr_ptr-samples;
  if( src < &snapshot_buffer[0]){
    //   xxxxxx................... snapshot_buffer (x=invalid)
    //   ^src     ^snapshot_wr_ptr
    //   |--------| samples
    int sams = &snapshot_buffer[0]-src;
    //   xxxxxx................... snapshot_buffer
    //   ^src     ^snapshot_wr_ptr
    //   |----| sams
    src += COUNT(snapshot_buffer);
    //   .............111111 snapshot_buffer
    //      ^wr       ^src
    //                |----| sams
    memcpy(dst,src,sams*sizeof(*dst));
    //   .............111111 snapshot_buffer
    //      ^wr       ^src
    //                |----| sams
    //                111111.... dst buffer
    //                ^dst
    src=&snapshot_buffer[0];
    samples-=sams;
    dst+=sams;
    //   2222.........111111 snapshot_buffer
    //   ^s ^wr       
    //   |--| samples
    //                111111.... dst buffer
    //                      ^dst
  }
  memcpy(dst,src,samples*sizeof(*dst));
  // 1111112222 dst buffer
}




/*

int main()
{
  snapshot_wr(1);
  snapshot_wr(2);
  snapshot_wr(3);
  snapshot_wr(4);
  snapshot_wr(5);
  snapshot_wr(6);
  snapshot_wr(7);

  {
    float snap[4]={0};
    snapshot_rd(snap,COUNT(snap));
    for(int i=0;i<COUNT(snap);i++) fprintf(stderr,"%.0f ",snap[i]);
    fprintf(stderr,"\n");
    // OK
  }

  {
    float snap[10]={0};
    snapshot_rd(snap,COUNT(snap));
    for(int i=0;i<COUNT(snap);i++) fprintf(stderr,"%.0f ",snap[i]);
    fprintf(stderr,"\n");
    // OK
  }

  return 0;
}



/*


gcc -o main snapshot.c && ./main


*/

