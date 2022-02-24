



float autocorr( float *out , int out_len , int lag_start , float *in ){
  // naive impl. O(n²)
  // non è propriamente autocorrelazione
  // nel senso che cosi calcolata l'autocorr massima = 0
  // in letteratura dovrebbe essere +1 ... ma chissene
  // per i miei scopi è indifferente
  float avg=0;
  for(int lag=lag_start;lag<out_len;lag++){
    float sqdiff = 0;
    for(int i=0;i<out_len;i++){
      float diff = in[i]-in[i+lag];
      sqdiff += diff*diff;
    }
//    out[lag] = sqdiff/(out_len-lag_start);  // scalatura "giusta" ... gole pessime
//    sqdiff=sqrt(sqdiff);  // sarebbe più corretto, ma farlo genera gole meno accentuate
    out[lag] = sqdiff/(1+sqdiff);  // scalatura quasi-log (reinhard) aiuta nel delineare le gole
    avg += out[lag];
  }
  return avg / (out_len-lag_start);
}



