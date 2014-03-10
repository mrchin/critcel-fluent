/**************************************************************/
/*                                                            */
/* Helium Gap Conductivity                                    */
/*                                                            */
/* User-Defined Functions for temperature-dependent thermal   */
/* conductivity                                               */
/*                                                            */
/* Units are in W/m-K                                         */
/*                                                            */
/* FLUENT 15.0                                                */
/*                                                            */
/* Author: Michael Chin                                       */
/*   Date: March 2014                                         */
/*                                                            */
/**************************************************************/



#include "udf.h"
#define PI 3.141592654

DEFINE_PROPERTY(dat_gap_k, cell, thread)

{

  real temp, tempCel, k;

  temp = C_T(cell, thread);

  {

/* Units from I2S-LWR Property Database are in degrees Celsius (make sure Fluent is adjusted to global degrees Celsius) */

  tempCel = temp - 273.15;  // Conversion from Kelvin to Celsius

/* If the temperature is lower than the reactor inlet, use the boundary thermal conductivity */

  if (tempCel <= 292.8)
      k = 0.406755439;

/* If the temperature is higher than the reactor outlet, use the boundary thermal conductivity */

  else if (tempCel >= 330.2)
      k = 0.696240582;

/* I2S-LWR Reference value for U3Si2 in temperature range of interest, low correlation */

  else
      k = 3E-10*pow(tempCel,5) - 9E-7*pow(tempCel,4) + 0.0011*pow(tempCel,3) - 0.6998*pow(tempCel,2) + 220.58*tempCel - 27743.0;

  }
  return k;
}