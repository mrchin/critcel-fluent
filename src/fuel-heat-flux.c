/**************************************************************/
/*                                                            */
/* U3Si2 Nuclear Fuel                                         */
/*                                                            */
/* User-Defined Functions for wall heat flux                  */
/*                                                            */
/* Units are in W/m^2                                         */
/*                                                            */
/* FLUENT 15.0                                                */
/*                                                            */
/* Author: Michael Chin                                       */
/*   Date: February 2014                                      */
/*                                                            */
/**************************************************************/

#include "udf.h"
#define PI 3.141592654

DEFINE_PROFILE(u3si2_heat_flux, thread, position)
{
   real r[3]; /* this will hold the position vector */
   real x;
   face_t f;

   begin_f_loop(f, thread)
   {
     F_CENTROID(r,f,thread);
     x = r[0];   // Units of x are in meters
	 /* Units from I2S-LWR Property Database are in degrees Celsius (make sure Fluent is adjusted to global degrees Celsius) */
     F_PROFILE(f, thread, position) = 0.0002*pow(x,4) - 2E-14*pow(x,3) - 51.75*pow(x,2) + 4E-9*x + 1E6;
   }
   end_f_loop(f, thread)
}