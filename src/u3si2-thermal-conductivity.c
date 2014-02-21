/**************************************************************/
/*                                                            */
/* U3Si2 Nuclear Fuel                                         */
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


DEFINE_PROPERTY(user_u3si2_k, cell, thread)

{

  real temp, tempCel, k;

  temp = C_T(cell, thread);

  {

/* Units from I2S-LWR Property Database are in degrees Celsius (make sure Fluent is adjusted to global degrees Celsius) */

  tempCel = temp - 273.15;  // Conversion from Kelvin to Celsius

/* If the temperature is lower than the reactor inlet, use the boundary thermal conductivity */

  if (tempCel <= 0.0)
      k = 7.98;

/* If the temperature is higher than the reactor outlet, use the boundary thermal conductivity */

  else if (tempCel >= 1200.)
      k = 14.1;

/* I2S-LWR Reference value for U3Si2 in temperature range of interest, low correlation */

  else
      k = 7.98 + 5.1E-03*tempCel;

  }
  return k;
}

