/**************************************************************/
/*                                                            */
/* 15 MPa Water                                               */
/*                                                            */
/* User-Defined Functions for temperature-dependent density   */
/*                                                            */
/* Units are in kg/m3                                         */
/*                                                            */
/* FLUENT 14.5.7                                              */
/*                                                            */
/* Author: Michael Chin                                       */
/*   Date: December 2013                                      */
/*                                                            */
/**************************************************************/



#include "udf.h"


DEFINE_PROPERTY(user_water_den, cell, thread)

{

  real temp, rho;

  temp = C_T(cell, thread);



/* If the temperature is lower than the reactor inlet, use the boundary density */

  if (temp <= 292.8 )
      rho = 740.89;

/* If the temperature is higher than the reactor outlet, use the boundary density */

  else if (temp >= 330.19 )
      rho = 651;

/* NIST developed quadratically-parameterized thermal profile for 15 MPa water in temperature range of interest */

  else
      rho = -0.0155*pow(temp,2) + 7.2415*temp - 53.942;

  return rho;
}

