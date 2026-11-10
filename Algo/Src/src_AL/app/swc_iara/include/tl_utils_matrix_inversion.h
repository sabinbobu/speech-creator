#ifndef TL_UTILS_MATRIX_H
#define TL_UTILS_MATRIX_H

#ifdef VECU_CODE
   /* TL VECU Autosar */
   #ifdef TL_TYPES_DEFINED_IN_RTE_TYPE
      #include "Rte_Type.h"
   #else
      /* TL VECU Standard and SystemDesk */
      #include "IARA_TL_Types.h"
   #endif
#else
   #ifndef RTE_TYPE_H
      #include "IARA_TL_Types.h"
   #endif
#endif

#ifndef FLT_EPSILON
  #define FLT_EPSILON 1e-5f
#endif

#define C__ABS(X)\
    (((X) >= 0.F) ? (X) : -(X))   

#define C__SWAP(type, a, b)\
{\
	type temp;\
	temp = a;\
	a = b;\
	b = temp;\
}\


#define C__MATRIX2POINTER(dim, matrix, pMatrix) \
{\
	UInt8 i;\
    for(i = 0; i < dim; i++)\
	{\
	    pMatrix[i] = matrix[i];\
	}\
}

#define C__MATINVGAUSS_F32(dim, A, AInv)\
{\
	Float32 * ppA[dim];\
    Float32 * ppLU[dim];\
    Float32 * ppAInv[dim];\
	Float32 LU[dim][dim];\
	Float32 vTemp[dim];\
	UInt32 vP[dim];\
	C__MATRIX2POINTER (dim, LU, ppLU);\
	C__MATRIX2POINTER (dim, AInv, ppAInv);\
	C__MATRIX2POINTER (dim, A, ppA);\
	F__MATINVGAUSS_F32(dim, (const Float32 **) ppA, ppLU, vP, vTemp, ppAInv);\
}

#define C__I8MATINVGAUSS_F32(dim, A, AInv, retVal)\
{\
    Float32 * ppA[dim];\
    Float32 * ppLU[dim];\
    Float32 * ppAInv[dim];\
	Float32 LU[dim][dim];\
	Float32 vTemp[dim];\
	UInt32 vP[dim];\
	C__MATRIX2POINTER (dim, LU, ppLU);\
	C__MATRIX2POINTER (dim, AInv, ppAInv);\
	C__MATRIX2POINTER (dim, A, ppA);\
	retVal = F__MATINVGAUSS_F32(dim, (const Float32 **) ppA, ppLU, vP, vTemp, ppAInv);\
}


extern Int8 F__MATINVGAUSS_F32(Int32 n, const Float32 * A[], Float32 * LU[], UInt32 vP[], Float32 vTemp[], Float32 * AInv[]);
extern Int8 F__LUGAUSSPIV_F32 (Int32 n, const Float32 * A[], Float32 * LU[], UInt32 vP[], Float32 vD[]);
extern void F__LUSOLVE_F32(Int32 n, const Float32 * LR[], const UInt32 vP[], const Float32 b[], Float32 x[]);

#endif /* TL_UTILS_MATRIX_H */
