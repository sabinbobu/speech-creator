
#ifndef CDDSPI_CONCAT2
#define CDDSPI_CONCAT2(x, y)  x ## y
#endif

#ifndef CDDSPI_CONCAT
#define CDDSPI_CONCAT(x, y) CDDSPI_CONCAT2(x, y)
#endif

#ifdef  BEGIN_CDDSPI_MAP
#undef  BEGIN_CDDSPI_MAP
#endif

#ifdef BEGIN_CDDSPI_IFC
#undef BEGIN_CDDSPI_IFC
#endif

#ifdef CDDSPI_IFC
#undef CDDSPI_IFC
#endif

#ifdef END_CDDSPI_IFC
#undef END_CDDSPI_IFC
#endif

#ifdef  BEGIN_CDDSPI_DEV
#undef  BEGIN_CDDSPI_DEV
#endif

#ifdef  CDDSPI_DEV_CFG
#undef  CDDSPI_DEV_CFG
#endif

#ifdef  END_CDDSPI_DEV
#undef  END_CDDSPI_DEV
#endif

#ifdef  BEGIN_CDDSPI_SEQ
#undef  BEGIN_CDDSPI_SEQ
#endif

#ifdef BEGIN_CDDSPI_DEVCYC
#undef BEGIN_CDDSPI_DEVCYC
#endif

#ifdef CDDSPI_DEVCB_CFG
#undef CDDSPI_DEVCB_CFG
#endif

#ifdef END_CDDSPI_DEVCYC
#undef END_CDDSPI_DEVCYC
#endif

#ifdef  END_CDDSPI_SEQ
#undef  END_CDDSPI_SEQ
#endif

#ifdef  END_CDDSPI_MAP
#undef  END_CDDSPI_MAP
#endif

#ifdef CDDSPI_DEVCRC_CFG
#undef CDDSPI_DEVCRC_CFG
#endif