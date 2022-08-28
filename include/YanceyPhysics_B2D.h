#pragma once

#include "YanceyVector.h"
#include "YanceyShape.h"
#include "debug_config.h"
//#include "GameBase.h"

#define MKS_FACT 100.0f

static inline Yancey_Vector PX2MKS(Yancey_Vector pix, Yancey_Vector wind_mks )
{
  Yancey_Vector ret = { pix.x / MKS_FACT , wind_mks.y - (pix.y / MKS_FACT) };
  return  ret;
};

static inline Yancey_Vector MKS2PX(Yancey_Vector mks , Yancey_Vector wind_mks)
{
  Yancey_Vector ret = { mks.x * MKS_FACT , (wind_mks.y - mks.y) * MKS_FACT };
  return ret;
};

static inline Yancey_Vector MKS2PX(float w , float h)
{
  return { w * MKS_FACT , h * MKS_FACT };
}
static inline Yancey_Vector PX2MKS(int w , int h)
{
  return { float(w) / MKS_FACT , float(h) / MKS_FACT };
};

