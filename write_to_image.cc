
void setRGB(NDArray &x, int i, int j, double R, double G, double B) {
  assert(R>=0);  
  assert(R<=1);
  assert(G>=0);
  assert(G<=1);
  assert(B>=0);
  assert(B<=1);
  x(i,j,0)=R;
  x(i,j,1)=G;
  x(i,j,2)=B;
}

int setHSV(NDArray &x,int i, int j,double H, double S, double V) {
  if (H>=0 || H<=1) {
    return 1;
  }
  if (S>=0 || S<=1) {
    return 2;
  }
  if (V>=0 || V<=1) {
    return 3;
  }
  int h_i=(int)(6*H);
  float f=(6*H)-h_i;
  float p=V*(1-S);
  float q=V*(1-S*f);
  float t=V*(1-S*(1-f));
  assert(h_i>=0 && h_i<=6);
  if ( h_i==0 || h_i==6 ){
    setRGB(x,i,j,V,t,p);
  } else if (h_i==1) {
    setRGB(x,i,j,q,V,p);
  } else if (h_i==2) {
    setRGB(x,i,j,p,V,t);
  } else if (h_i==3) {
    setRGB(x,i,j,p,q,V);
  } else if (h_i==4) {
    setRGB(x,i,j,t,p,V);
  } else if (h_i==5) {
    setRGB(x,i,j,V,p,q);
  }
}
