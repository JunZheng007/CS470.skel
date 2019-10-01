#include "IP.h"
using namespace IP;

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW_contrast:
//
// Apply contrast enhancement to I1. Output is in I2.
// Stretch intensity difference from reference value (128) by multiplying
// difference by "contrast" and adding it back to 128. Shift result by
// adding "brightness" value.
//
void
HW_contrast(ImagePtr I1, double brightness, double contrast, ImagePtr I2)
{
	// copy image header (width, height) of input image I1 to output image I2
	IP_copyImageHeader(I1, I2);

	// init vars for width, height, and total number of pixels
	int w = I1->width();
	int h = I1->height();
	int total = w * h;

	// init lookup table and useful variables
	int i, lut[MXGRAY];
	int reference = 128;
	double result;
	
	for (i = 0; i < MXGRAY; ++i) {
	
		// Stretches the intensity difference from reference value, then adding the reference value and brightness value
		result = ((i - reference) * contrast) + reference + brightness;
		
		// Save the int result
		lut[i] = round(result);
	}

	// The same code to evaluate output image as giving in the threshold file:
	// declarations for image channel pointers and datatype
	ChannelPtr<uchar> p1, p2, endd;
	int type;

	// visit all image channels and evaluate output image
	for (int ch = 0; IP_getChannel(I1, ch, p1, type); ch++) {	// get input  pointer for channel ch
		IP_getChannel(I2, ch, p2, type);		// get output pointer for channel ch
		for (i = 0; i < total; i++) *p2++ = lut[*p1++];	// use lut[] to eval output
	}
}
