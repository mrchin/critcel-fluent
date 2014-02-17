/**************************************************************/
/*                                                            */
/* APMT ODS Stainless Steel                                   */
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


DEFINE_PROPERTY(user_apmt_k, cell, thread)

{

  real temp, k;

  temp = C_T(cell, thread);

  {

/* Units from I2S-LWR Property Database are in degrees Celsius (make sure Fluent is adjusted to global degrees Celsius) */

/* If the temperature is lower than the reactor inlet, use the boundary thermal conductivity */

  if (temp <= 0)
      k = 10.318;

/* If the temperature is higher than the reactor outlet, use the boundary thermal conductivity */

  else if (temp >= 1200.)
      k = 29.5216;

/* I2S-LWR Reference thermal profile for APMT ODS steel in temperature range of interest */

  else
      k = 10.318 + 1.6003E-02*temp;

  }
  return k;
}

