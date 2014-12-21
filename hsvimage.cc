

#include <octave/oct.h>
#include "check_arguments.cc"
#include "write_to_image.cc"

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

  if (mode==0) {
    error("Illegal arguments");
    return retval;
  }

  int width=args(0).columns();
  int height=args(0).rows();

  dim_vector dv(height,width,3);

  NDArray image(dv);

  ComplexMatrix c0;

  Matrix m0;
  Matrix m1;
  Matrix m2;

  NDArray a0;

  if (mode==1) {
    m0=args(0).matrix_value();
    m1=args(1).matrix_value();
    m2=args(2).matrix_value();
  }
  if (mode==2) {
    c0=args(0).complex_matrix_value();
  }

  if (mode==3) {
    a0=args(0).array_value();
  }

  float H,S,V;

  for (int i=0;i<height;i++) {
    for (int j=0;j<width;j++) {
      if (mode==1) {
	H = ((octave_value)m0(i,j)).scalar_value();
	S = ((octave_value)m1(i,j)).scalar_value();
	V = ((octave_value)m2(i,j)).scalar_value();

      }
      if (mode==2) {
	H = 0.5*(1+((arg(c0(i,j)))*(M_1_PI)));

	// Sometimes this is a tad below 0 or above 1

	if (H<=0) {
	  H=0;
	}
	if (H>1) {
	  H=1;
	}
	float A=abs(c0(i,j));
	if (A<1) {
	  S = 1;
	  V = A;
	} else if (A<2) {
	  S = 2-A;
	  V = 1;
	} else {
	  S = 0;
	  V = 1;
	}
      }
      if (mode==3) {
	H = ((octave_value)a0(i,j,0)).scalar_value();
	S = ((octave_value)a0(i,j,1)).scalar_value();
	V = ((octave_value)a0(i,j,2)).scalar_value();
      }
      setHSV(image,i,j,H,S,V);
    }
  }
  
  retval(0)=image;

  return retval;
}
