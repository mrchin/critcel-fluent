/**************************************************************/
/*                                                            */
/* 15 MPa Water                                               */
/*                                                            */
/* User-Defined Functions for temperature-dependent specific  */
/* heat at constant pressure                                  */
/*                                                            */
/* Units are in Pa-s                                          */
/*                                                            */
/* FLUENT 14.5.7                                              */
/*                                                            */
/* Author: Michael Chin                                       */
/*   Date: December 2013                                      */
/*                                                            */
/**************************************************************/



#include "udf.h"


DEFINE_PROPERTY(user_water_cp, cell, thread)

{

  real temp, cp;

  temp = C_T(cell, thread);

  {

/* If the temperature is lower than the reactor inlet, use the boundary specific heat */

  if (temp < 292.8)
      cp = 5298.2;

/* If the temperature is higher than the reactor outlet, use the boundary specific heat */

  else if (temp >= 330.19)
      cp = 6966.7;

/* NIST developed linearly-parameterized thermal profile for 15 MPa water in temperature range of interest */

  else
      cp = 0.6998*pow(temp,2) - 397.6*temp + 61740;

  }
  return cp;
}

