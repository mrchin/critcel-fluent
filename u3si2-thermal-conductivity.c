/**************************************************************/
/*                                                            */
/* U3Si2 Nuclear Fuel                                         */
/*                                                            */
/* User-Defined Functions for temperature-dependent thermal   */
/* conductivity                                               */
/*                                                            */
/* Units are in W/m-K                                         */
/*                                                            */
/* FLUENT 14.5.7                                              */
/*                                                            */
/* Author: Michael Chin                                       */
/*   Date: December 2013                                      */
/*                                                            */
/**************************************************************/



#include "udf.h"


DEFINE_PROPERTY(user_u3si2_k, cell, thread)

{

  real temp, k;

  temp = C_T(cell, thread);

  {

/* If the temperature is lower than the reactor inlet, use the boundary thermal conductivity */

  if (temp <= 0.0)
      k = 7.98;

/* If the temperature is higher than the reactor outlet, use the boundary thermal conductivity */

  else if (temp >= 1200.)
      k = 14.1;

/* I2S-LWR Reference value for U3Si2 in temperature range of interest, low correlation */

  else
      k = 7.98 + 5.1E-03*temp;

  }
  return k;
}

