hsvimage
========

HSV images in gnu octave

This is code for an .oct file to process HSV images. It's not well tested yet, however it does the job.

Compile by:

$ mkoctfile hsvimage.cc

Then use it:

$ octave
octave:1> image(hsvimage(exp(linspace(-1,0.9,100)'.+(linspace(0,2*pi,100)*J))))

There are three input modes:

hsvimage(A) with A being a complex matrix
hsvimage(A) with A being a three dimensional real array with third dimension 3 containing H, S and V values
hsvimage(H,S,V) with three two dimensional real matrices

The return value will be a three dimensional real array of R, G and B values.

There is some error processing.
