/**************************************************************/
/*                                                            */
/* APMT ODS Stainless Steel                                   */
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


DEFINE_SPECIFIC_HEAT(user_apmt_cp, T, Tref, h, yi)

{

  real cp;

  {

/* Units from I2S-LWR Property Database are in degrees Celsius (make sure Fluent is adjusted to global degrees Celsius) */

/* If the temperature is lower than the reactor inlet, use the boundary specific heat */

  if (T <= 0.0 )
      cp = 464.2;

/* If the temperature is higher than the reactor outlet, use the boundary specific heat */

  else if (T >= 1200.)
      cp = 700.90096;

/* I2S-LWR Reference for APMT ODS Steel in temperature range of interest */

  else
      cp = 2.5532E-07*pow(T,3) - 6.8145E-04*pow(T,2) + 6.4698E-01*T + 464.62;

   }

  *h = cp*(T-Tref);   // Calculate specific heat

  return cp;
}

