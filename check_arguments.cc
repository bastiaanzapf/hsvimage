
int check_arguments(octave_value_list args) {
  if (args(0).is_real_matrix()) {
    if (args.length()!=3) {
      if (args.length()==1) {
	return 3;
      }
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
