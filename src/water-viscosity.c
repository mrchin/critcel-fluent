/**************************************************************/
/*                                                            */
/* 15 MPa Water                                               */
/*                                                            */
/* User-Defined Functions for temperature-dependent viscosity */
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


DEFINE_PROPERTY(user_water_vis, cell, thread)

{

  real temp, mu;

  temp = C_T(cell, thread);

  {

/* Units from I2S-LWR Property Database are in degrees Celsius (make sure Fluent is adjusted to global degrees Celsius) */

/* If the temperature is lower than the reactor inlet, use the boundary viscosity */

  if (temp < 292.8)
      mu = 0.000091331;

/* If the temperature is higher than the reactor outlet, use the boundary viscosity */

  else if (temp >= 330.19)
      mu = 0.000076069;

/* NIST developed linearly-parameterized thermal profile for 15 MPa water in temperature range of interest */

  else
      mu = -4E-07*temp + 0.0002;

  }
  return mu;
}

