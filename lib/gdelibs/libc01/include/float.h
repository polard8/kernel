
//credits.
//Copyright (C) 2002-2011 Michael Ringgaard.
 
//All rights reserved. 
	
#ifndef FLOAT_H
#define FLOAT_H 1

//
// Limits for float
//

#define FLT_RADIX      2
#define FLT_ROUNDS     1
#define FLT_DIG        6
#define FLT_EPSILON    1.192092896e-07F
#define FLT_MANT_DIG   24
#define FLT_MAX        3.402823466e+38F
#define FLT_MAX_10_EXP 38
#define FLT_MAX_EXP    128
#define FLT_MIN        1.175494351e-38F
#define FLT_MIN_10_EXP (-37)
#define FLT_MIN_EXP    (-125)

//
// Limits for double
//

#define DBL_DIG        15
#define DBL_EPSILON    2.2204460492503131e-016
#define DBL_MANT_DIG   53
#define DBL_MAX        1.7976931348623158e+308
#define DBL_MAX_10_EXP 308
#define DBL_MAX_EXP    1024
#define DBL_MIN        2.2250738585072014e-308
#define DBL_MIN_10_EXP (-307)
#define DBL_MIN_EXP    (-1021)

//
// Floating point classes for _fpclass()
//

#define _FPCLASS_SNAN   0x0001  // Signaling NaN
#define _FPCLASS_QNAN   0x0002  // Quiet NaN
#define _FPCLASS_NINF   0x0004  // Negative infinity
#define _FPCLASS_NN     0x0008  // Negative normal
#define _FPCLASS_ND     0x0010  // Negative denormal
#define _FPCLASS_NZ     0x0020  // -0
#define _FPCLASS_PZ     0x0040  // +0
#define _FPCLASS_PD     0x0080  // Positive denormal
#define _FPCLASS_PN     0x0100  // Positive normal
#define _FPCLASS_PINF 0x0200 // Positive infinity





#endif  /* float.h*/


