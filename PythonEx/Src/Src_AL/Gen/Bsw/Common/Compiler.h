#ifndef COMPILER_2019_06_06_H_
  #define COMPILER_2019_06_06_H_

  /* AUTOMATIC used for the declaration of local pointers */
  #define AUTOMATIC

  /* INLINE define for abstraction of the keyword inline */
  #define INLINE __inline

  /* LOCAL_INLINE define for abstraction of the keyword inline for functions with static scope */
  #define LOCAL_INLINE static inline

  #define STATIC    static
  #define TYPEDEF   typedef

  #define CRC_CODE
  #define CRC_APPL_DATA
  #define CRC_LOCAL static

  #define FUNC(rettype, memclass) rettype                                  /* PRQA S 3410 */ /* Architecture */
  #define FUNC_P2CONST(rettype, ptrclass, memclass) const rettype*         /* PRQA S 3410 */ /* Architecture */
  #define FUNC_P2VAR(rettype, ptrclass, memclass) rettype*                 /* PRQA S 3410 */ /* Architecture */
  #define P2VAR(ptrtype, memclass, ptrclass) ptrtype*                      /* PRQA S 3410 */ /* Architecture */
  #define P2CONST(ptrtype, memclass, ptrclass) const ptrtype*              /* PRQA S 3410 */ /* Architecture */
  #define CONSTP2VAR(ptrtype, memclass, ptrclass) ptrtype* const           /* PRQA S 3410 */ /* Architecture */
  #define CONSTP2CONST(ptrtype, memclass, ptrclass) const ptrtype* const   /* PRQA S 3410 */ /* Architecture */
  #define P2FUNC(rettype, ptrclass, fctname) rettype (*fctname)            /* PRQA S 3410 */ /* Architecture */
  #define CONSTP2FUNC(rettype, ptrclass, fctname) rettype (*const fctname) /* PRQA S 3410 */ /* Architecture */
  #if !defined(CONST)
  #define CONST(type, memclass) const type                                 /* PRQA S 3410 */ /* Architecture */
  #endif
  #define VAR(vartype, memclass) vartype                                   /* PRQA S 3410 */ /* Architecture */

#endif // COMPILER_2019_06_06_H_
