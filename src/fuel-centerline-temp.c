/**************************************************************/
/*                                                            */
/* U3Si2 Nuclear Fuel                                         */
/*                                                            */
/* User-Defined Functions for sinusoidal temperature profile  */
/*                                                            */
/* Units are in Kelvin                                        */
/*                                                            */
/* FLUENT 14.5.7 version                                      */
/*                                                            */
/* Author: Michael Chin                                       */
/*   Date: December 2013                                      */
/*                                                            */
/**************************************************************/

#include "udf.h"
#define PI 3.141592654

DEFINE_PROFILE(temperature_profile, thread, position)
{
   real r[3]; /* this will hold the position vector */
   real x;
   face_t f;

   begin_f_loop(f, thread)
   {
     F_CENTROID(r,f,thread);
     x = r[0];
     F_PROFILE(f, thread, position) = 11.305*pow(x,6) - 123.63*pow(x,5) + 479.14*pow(x,4) - 757.26*pow(x,3) + 182.75*pow(x,2) + 754.53*x + 292.05;
   }
   end_f_loop(f, thread)
}
