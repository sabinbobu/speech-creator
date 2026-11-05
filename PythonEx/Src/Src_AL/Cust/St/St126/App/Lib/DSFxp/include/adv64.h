/**
 * @file       $RCSfile: adv64.h $
 * @brief      This file contains advanced functions and macros for 64bit arithmetic.
 * @author     Klaus Goebel, Dagmar Andoleit
 * @copyright  (c) 2017, dSPACE GmbH, Paderborn, Germany
 * @version    $Revision: 1.7 $ $Date: 2017/07/27 14:25:32CEST $
 */

/* Note:
 *   This file functions and macros in this file are implemented in ANSI-C Code,
 *   but they are target dependent! The functions are using complex data types
 *   containing structs, unions and arrays, so the handling of some pointers
 *   depends on the "Endian" of the target.
 * - C-macros are characterized by a leading "C__".
 *   Ansi-C-functions are characterized by a leading "F__".
 * - The macro/function-name represents the implemented operation(s):
 *  (C__|F__) + output_type + OPERATION + input_type [+ input_type] [+ _SAT]
 * - Note: The target's endian must be defined in the "tl_types.h" file.
 *
 ***** TYPEDEFS *****
 *   UInt64s             64bit data type containing a two 32bit values (struct)
 *   Int64s              64bit data type containing a two 32bit values (struct)
 *
 ***** BASE FUNCTIONS *****
 *   negate();           negate a 64bit value
 *
 ***** MUL *****
 *   F__U64sMULU32U32(); multiply two 32bit values with a 64bit result (internal use)
 *   F__I64sMULI32U32(); multiply two 32bit values with a 64bit result (internal use)
 *   F__I64sMULU32I32(); multiply two 32bit values with a 64bit result (internal use)
 *   F__I64sMULI32I32(); multiply two 32bit values with a 64bit result (internal use)
 *
 ***** DIV *****
 *   div3by2();          divide a 3-digit value by a 2-digit value (internal use)
 *
 *   F__U64sDIVU64sU16();divide a 64bit value by a 16bit value (internal use)
 *   F__U32DIVU64sU16(); divide a 64bit value by a 16bit value (internal use)
 *
 *   F__U64sDIVU64sU32();divide a 64bit value by a 32 bit value (internal use)
 *   F__I64sDIVI64sU32();divide a 64bit value by a 32 bit value (internal use)
 *   F__I64sDIVU64sI32();divide a 64bit value by a 32 bit value (internal use)
 *   F__I64sDIVI64sI32();divide a 64bit value by a 32 bit value (internal use)
 *   F__U32DIVU64sU32(); divide a 64bit value by a 32 bit value (internal use)
 *   F__I32DIVI64sU32(); divide a 64bit value by a 32 bit value (internal use)
 *   F__I32DIVU64sI32(); divide a 64bit value by a 32 bit value (internal use)
 *   F__I32DIVI64sI32(); divide a 64bit value by a 32 bit value (internal use)
 */


#ifndef DSFXP_ADV64_H
#define DSFXP_ADV64_H


/* Definition of basic type */
#ifdef LITTLE_ENDIAN    /* Target with little-endian architecture */

typedef struct
{
    UInt32 lo;
    Int32 hi;
} Int64s;

typedef struct
{
    UInt32 lo;
    UInt32 hi;
} UInt64s;

#else
    #ifdef BIG_ENDIAN  /* Target with big-endian architecture */

	typedef struct
	{
		Int32 hi;
		UInt32 lo;
	} Int64s;

	typedef struct
	{
		UInt32 hi;
		UInt32 lo;
	} UInt64s;

	#else

		#error "The definition LITTLE_ENDIAN or BIG_ENDIAN is not define! Please check the file tllimits.h and set the endian."

	#endif
#endif


/* negate a UInt64s */
void negate(UInt64s *x);


/* divide three digits by two (used by multiword division) */
UInt16 div3by2(UInt16 u[3], UInt32 v);

/* divide a UInt64s by an UInt16 */
UInt64s F__U64sDIVU64sU16(const UInt64s *u, UInt16 a);

/* divide a UInt64s by an UInt16 */
UInt32 F__U32DIVU64sU16(const UInt64s *u, UInt16 a);

/* divide unsigned UInt64s by UInt32 */
UInt64s F__U64sDIVU64sU32(const UInt64s *U, UInt32 v);

/* mixed division of Int64s by UInt32 */
Int64s F__I64sDIVI64sU32(const Int64s *u, UInt32 a);

/* mixed division of UInt64s by Int32 */
Int64s F__I64sDIVU64sI32(const UInt64s *u, Int32 v);

/* signed division of Int64s by Int32 */
Int64s F__I64sDIVI64sI32(const Int64s *u, Int32 v);

/* divide unsigned UInt64s by UInt32 */
UInt32 F__U32DIVU64sU32(const UInt64s *U, UInt32 v);

/* mixed division of Int64s by UInt32 */
Int32 F__I32DIVI64sU32(const Int64s *u, UInt32 a);

/* mixed division of UInt64s by Int32 */
Int32 F__I32DIVU64sI32(const UInt64s *u, Int32 v);

/* signed division of Int64s by Int32 */
Int32 F__I32DIVI64sI32(const Int64s *u, Int32 v);


#endif /* #ifndef DSFXP_ADV64_H */
