

#include <octave/oct.h>

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

  int mode=0;

  if (args(0).is_real_matrix()) {
    if (args.length()!=3) {
      error("hsvimage(A,B,C): first parameter is real, so exactly three parameters are required");
      return retval;
    }
    if (!args(1).is_real_matrix() ||
	!args(2).is_real_matrix()) {
      error("hsvimage(A,B,C): all arguments must be real matrices");
      return retval;
    }
    mode=1;
  }

  if (mode==0 && args(0).is_complex_matrix()) {
    if (args.length()!=1) {
      error("hsvimage(A): first parameter is complex, so exactly one parameter is required");
      return retval;
    }
    mode=2;
  }

  if (mode==0 && args(0).is_real_matrix()) {
    dim_vector dims=args(0).dims();
    if (dims(3)!=3) {
      error("hsvimage(A): first parameter is real and there are no other parameters, so A should have a third dimension of 3");
      return retval;
    }
    mode=3;
  }

  if (mode == 0) {
    error("hsvimage: illegal arguments");      
    return retval;

  }

  int width=args(0).columns();
  int height=args(0).rows();

  dim_vector dv(width,height,3);

  NDArray image(dv);

  ComplexMatrix arg0=args(0).complex_matrix_value();

  for (int i=0;i<width;i++) {
    for (int j=0;j<height;j++) {
      //      if (mode==1)
      Complex arg0_ = ((octave_value)arg0(i,j)).complex_value();
      float H=arg(arg0(i,j));
      int h_i=(int)(3+(3*H)*(M_1_PI));
      float f=(3+(3*H)*(M_1_PI))-h_i;
      octave_stdout << h_i << "\n";
      float V=abs(arg0(i,j));
      float p=0;
      float q=V*(1-f);
      float t=V*f;
      if ( h_i==0 || h_i==6 ){
	image(i,j,0)=V;
	image(i,j,1)=t;
	image(i,j,2)=p;
      } else if (h_i==1) {
	image(i,j,0)=q;
	image(i,j,1)=V;
	image(i,j,2)=p;	
      } else if (h_i==2) {
	image(i,j,0)=p;
	image(i,j,1)=V;
	image(i,j,2)=t;	
      } else if (h_i==3) {
	image(i,j,0)=p;
	image(i,j,1)=q;
	image(i,j,2)=V;	
      } else if (h_i==4) {
	image(i,j,0)=t;
	image(i,j,1)=p;
	image(i,j,2)=V;	
      } else if (h_i==5) {
	image(i,j,0)=V;
	image(i,j,1)=p;
	image(i,j,2)=q;	
      }
    }
  }

  retval(0)=image;

  return retval;
}
