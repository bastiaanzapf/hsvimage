

#include <octave/oct.h>

int check_arguments(octave_value_list args) {
  if (args(0).is_real_matrix()) {
    if (args.length()!=3) {
      error("hsvimage(A,B,C): first parameter is real, so exactly three parameters are required");
      return 0;
    }
    if (!args(1).is_real_matrix() ||
	!args(2).is_real_matrix()) {
      error("hsvimage(A,B,C): all arguments must be real matrices");
      return 0;
    }
    return 1;
  }

  if (args(0).is_complex_matrix()) {
    if (args.length()!=1) {
      error("hsvimage(A): first parameter is complex, so exactly one parameter is required");
      return 0;
    }
    return 2;
  }

  if (args(0).is_real_matrix()) {
    dim_vector dims=args(0).dims();
    if (dims(3)!=3) {
      error("hsvimage(A): first parameter is real and there are no other parameters, so A should have a third dimension of 3");
      return 0;
    }
    return 3;
  }

  error("hsvimage: illegal arguments");      
  
  return 0;
}

void setRGB(NDArray &x, int i, int j, double a, double b, double c) {
  x(i,j,0)=a;
  x(i,j,1)=b;
  x(i,j,2)=c;
}

void setHSV(NDArray &x,int i, int j,double H, double S, double V) {
  int h_i=(int)(6*H);
  float f=(6*H)-h_i;
  float p=0;
  float q=V*(1-f);
  float t=V*f;
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

DEFUN_DLD (hsvimage, args, ,
"Display an image from hsv data.\n"
"\n"
"If called with one argument, and it is a complex matrix, the argument of "
"every entry is used as a hue value, saturation is set to 1 and the "
"absolute value is used as the luminance and bound at 1.\n"
"\n"
"If called with one argument, and it is a three dimensional matrix, or "
"if called with three arguments, these values are mapped to hue, saturation "
"and luminance.\n"
"\n"
"The resulting image is shown.\n"
)
{

  int arguments=args.length();
  octave_value_list retval;

  int mode=check_arguments(args);

  int width=args(0).columns();
  int height=args(0).rows();

  dim_vector dv(height,width,3);

  NDArray image(dv);

  ComplexMatrix arg0=args(0).complex_matrix_value();

  for (int i=0;i<height;i++) {
    for (int j=0;j<width;j++) {
      //      if (mode==1)
      Complex arg0_ = ((octave_value)arg0(i,j)).complex_value();

      float H=0.5+(arg(arg0(i,j)))*(M_1_PI);
      float S=1;
      float V=abs(arg0(i,j));

      setHSV(image,i,j,H,S,V);
    }
  }
  
  retval(0)=image;

  return retval;
}
