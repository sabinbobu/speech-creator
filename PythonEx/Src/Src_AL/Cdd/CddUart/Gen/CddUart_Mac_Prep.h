/* Do not create header for this file ! */

#ifndef CDDUART_CONCAT2
#define CDDUART_CONCAT2(x, y)  x ## y
#endif

#ifndef CDDUART_CONCAT
#define CDDUART_CONCAT(x, y) CDDUART_CONCAT2(x, y)
#endif

#ifdef  BEGIN_CDDUART_MAP
#undef  BEGIN_CDDUART_MAP
#endif

#ifdef BEGIN_CDDUART_IFC
#undef BEGIN_CDDUART_IFC
#endif

#ifdef CDDUART_IFC
#undef CDDUART_IFC
#endif

#ifdef END_CDDUART_IFC
#undef END_CDDUART_IFC
#endif

#ifdef  BEGIN_CDDUART_DEV
#undef  BEGIN_CDDUART_DEV
#endif

#ifdef  CDDUART_DEV_CFG
#undef  CDDUART_DEV_CFG
#endif

#ifdef  END_CDDUART_DEV
#undef  END_CDDUART_DEV
#endif

#ifdef  BEGIN_CDDUART_SEQ
#undef  BEGIN_CDDUART_SEQ
#endif

#ifdef BEGIN_CDDUART_DEVCYC
#undef BEGIN_CDDUART_DEVCYC
#endif

#ifdef CDDUART_DEVCB_CFG
#undef CDDUART_DEVCB_CFG
#endif

#ifdef END_CDDUART_DEVCYC
#undef END_CDDUART_DEVCYC
#endif

#ifdef  END_CDDUART_SEQ
#undef  END_CDDUART_SEQ
#endif

#ifdef  END_CDDUART_MAP
#undef  END_CDDUART_MAP
#endif

//#ifdef CDDUART_DEVCRC_CFG
//#undef CDDUART_DEVCRC_CFG
//#endif