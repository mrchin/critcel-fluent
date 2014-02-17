/**************************************************************/
/*                                                            */
/* U3Si2 Nuclear Fuel                                         */
/*                                                            */
/* User-Defined Functions for temperature-dependent specific  */
/* heat at constant pressure                                  */
/*                                                            */
/* Units are in Pa-s                                          */
/*                                                            */
/* FLUENT 15.0                                                */
/*                                                            */
/* Author: Michael Chin                                       */
/*   Date: December 2013                                      */
/*                                                            */
/**************************************************************/



#include "udf.h"


DEFINE_SPECIFIC_HEAT(user_u3si2_cp, T, Tref, h, yi)

{

  real cp;

  {

/* Units from I2S-LWR Property Database are in degrees Celsius (make sure Fluent is adjusted to global degrees Celsius) */

/* If the temperature is lower than the reactor inlet, use the boundary specific heat */

  if (T <= 25 )
      cp = 202;

/* If the temperature is higher than the reactor outlet, use the boundary specific heat */

  else if (T >= 2000.)
      cp = 407;

/* I2S-LWR Reference for U3Si2 in temperature range of interest */

  else
      cp = 199 + 0.104*T;

   }

  *h = cp*(T-Tref);   // Calculate specific heat

  return cp;
}

