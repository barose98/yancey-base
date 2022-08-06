#pragma once

#include "YanceyVector.h"
#include "YanceyShape.h"
#include "debug_config.h"
//#include "GameBase.h"

static inline float PX2MKS(int lit){
  float lit_f = float(lit) / 100.0f;
  //  log_i<< lit <<" "<<lit_f <<'\n';
  return  lit_f;
};
static inline int MKS2PX(float lit){
  int ret = round(lit * 100.0f);
  //  log_i<< lit <<" "<<ret <<'\n';
  return ret;
};
