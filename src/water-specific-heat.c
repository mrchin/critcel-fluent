/**************************************************************/
/*                                                            */
/* 15 MPa Water                                               */
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


DEFINE_SPECIFIC_HEAT(user_water_cp, T, Tref, h, yi)

{

  real cp;
  real TT=T-273.15;  // Conversion from Kelvin to Celsius

  {

/* Units from I2S-LWR Property Database are in degrees Celsius (make sure Fluent is adjusted to global degrees Celsius) */

/* If the temperature is lower than the reactor inlet, use the boundary specific heat */

  if (TT < 292.8)
      cp = 5298.2;

/* If the temperature is higher than the reactor outlet, use the boundary specific heat */

  else if (TT >= 330.19)
      cp = 6966.7;

/* NIST developed linearly-parameterized thermal profile for 15 MPa water in temperature range of interest */

  else
      cp = 0.6998*pow(TT,2) - 397.6*TT + 61740;

  }

  TT=TT+273.15;         // Convert Celsius back to Kelvin
  *h = cp*(TT-Tref);   // Calculate specific heat

  return cp;
}

