#ifndef NDL_DIRECTMEDIA_API_VERSION
# define NDL_DIRECTMEDIA_API_VERSION 1
#endif

#if (NDL_DIRECTMEDIA_API_VERSION == 1)
# include "NDL_directmedia_v1.h"
#elif (NDL_DIRECTMEDIA_API_VERSION == 2)
# include "NDL_directmedia_v2.h"
#else
# error "unknown NDL_DIRECTMEDIA_API_VERSION"
#endif
