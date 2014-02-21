/**************************************************************/
/*                                                            */
/* 15 MPa Water                                               */
/*                                                            */
/* User-Defined Functions for temperature-dependent thermal   */
/* conductivity                                               */
/*                                                            */
/* Units are in W/m-K                                         */
/*                                                            */
/* FLUENT 15.0                                                */
/*                                                            */
/* Author: Michael Chin                                       */
/*   Date: December 2013                                      */
/*                                                            */
/**************************************************************/



#include "udf.h"


DEFINE_PROPERTY(user_water_k, cell, thread)

{

  real temp, tempCel, k;

  temp = C_T(cell, thread);

  {

/* Units from I2S-LWR Property Database are in degrees Celsius (make sure Fluent is adjusted to global degrees Celsius) */

  tempCel = temp - 273.15;  // Conversion from Kelvin to Celsius

/* If the temperature is lower than the reactor inlet, use the boundary thermal conductivity */

  if (tempCel < 292.8)
      k = 0.57554;

/* If the temperature is higher than the reactor outlet, use the boundary thermal conductivity */

  else if (tempCel >= 330.19)
      k = 0.49755;

/* NIST developed linearly-parameterized thermal profile for 15 MPa water in temperature range of interest */

  else
      k = -9E-06*pow(tempCel,2) + 0.0036*tempCel + 0.3112;

  }
  return k;
}

