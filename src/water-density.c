/**************************************************************/
/*                                                            */
/* 15 MPa Water                                               */
/*                                                            */
/* User-Defined Functions for temperature-dependent density   */
/*                                                            */
/* Units are in kg/m3                                         */
/*                                                            */
/* FLUENT 15.0                                                */
/*                                                            */
/* Author: Michael Chin                                       */
/*   Date: December 2013                                      */
/*                                                            */
/**************************************************************/



#include "udf.h"


DEFINE_PROPERTY(user_water_den, cell, thread)

{

  real temp, tempCel, rho;

  temp = C_T(cell, thread);

/* Units from I2S-LWR Property Database are in degrees Celsius (make sure Fluent is adjusted to global degrees Celsius) */

  tempCel = temp - 273.15;  // Conversion from Kelvin to Celsius

/* If the temperature is lower than the reactor inlet, use the boundary density */

  if (tempCel <= 292.8 )
      rho = 740.89;

/* If the temperature is higher than the reactor outlet, use the boundary density */

  else if (tempCel >= 330.19 )
      rho = 651;

/* NIST developed quadratically-parameterized thermal profile for 15 MPa water in temperature range of interest */

  else
      rho = -0.0155*pow(tempCel,2) + 7.2415*tempCel - 53.942;

  return rho;
}

