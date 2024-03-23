// /******************************************************************************
// * Copyright (c) 2010 - 2021 Xilinx, Inc.  All rights reserved.
// * Copyright (c) 2022 - 2023 Advanced Micro Devices, Inc. All Rights Reserved.
// * SPDX-License-Identifier: MIT
// ******************************************************************************/

// /*****************************************************************************/
// /**
// *
// * @file xil_types.h
// *
// * @addtogroup common_types Basic Data types for Xilinx&reg; Software IP
// *
// * The xil_types.h file contains basic types for Xilinx software IP. These data types
// * are applicable for all processors supported by Xilinx.
// * @{
// * <pre>
// * MODIFICATION HISTORY:
// *
// * Ver   Who    Date   Changes
// * ----- ---- -------- -------------------------------------------------------
// * 1.00a hbm  07/14/09 First release
// * 3.03a sdm  05/30/11 Added Xuint64 typedef and XUINT64_MSW/XUINT64_LSW macros
// * 5.00 	pkp  05/29/14 Made changes for 64 bit architecture
// *	srt  07/14/14 Use standard definitions from stdint.h and stddef.h
// *		      Define long and ULONG datatypes and mask values
// * 7.00  mus  01/07/19 Add cpp extern macro
// * 7.1   aru  08/19/19 Shift the value in UPPER_32_BITS only if it
// *                     is 64-bit processor
// * 8.1   dp   12/23/22 Updated uint64_t and INTPTR to point to 64bit data types
// *                     incase of microblaze 32-bit with extended address enabled
// * 9.0   ml   14/04/23 Add parenthesis on sub-expression to fix misra-c violation.
// * </pre>
// *
// ******************************************************************************/

// /**
//  *@cond nocomments
//  */
// #ifndef XIL_TYPES_H	/* prevent circular inclusions */
// #define XIL_TYPES_H	/* by using protection macros */

// #ifdef __cplusplus
// extern "C" {
// #endif

// #include <stdint.h>
// #include <stddef.h>
// // #include "bspconfig.h"
// #ifndef SDT
// #include "xparameters.h"
// #endif

// /************************** Constant Definitions *****************************/

// #ifndef TRUE
// #  define TRUE		1U
// #endif

// #ifndef FALSE
// #  define FALSE		0U
// #endif

// #ifndef NULL
// #define NULL		0U
// #endif

// #define XIL_COMPONENT_IS_READY     0x11111111U  /**< In device drivers, This macro will be
//                                                  assigend to "IsReady" member of driver
// 												 instance to indicate that driver
// 												 instance is initialized and ready to use. */
// #define XIL_COMPONENT_IS_STARTED   0x22222222U  /**< In device drivers, This macro will be assigend to
//                                                  "IsStarted" member of driver instance
// 												 to indicate that driver instance is
// 												 started and it can be enabled. */

// /* @name New types
//  * New simple types.
//  * @{
//  */
// #ifndef __KERNEL__
// #ifndef XBASIC_TYPES_H
// /*
//  * guarded against xbasic_types.h.
//  */
// typedef uint8_t uint8_t;
// typedef uint16_t uint16_t;
// typedef uint32_t uint32_t;
// /** @}*/
// #define __XUINT64__
// typedef struct
// {
// 	uint32_t Upper;
// 	uint32_t Lower;
// } Xuint64;


// /*****************************************************************************/
// /**
// * @brief    Return the most significant half of the 64 bit data type.
// *
// * @param    x is the 64 bit word.
// *
// * @return   The upper 32 bits of the 64 bit word.
// *
// ******************************************************************************/
// #define XUINT64_MSW(x) ((x).Upper)

// /*****************************************************************************/
// /**
// * @brief    Return the least significant half of the 64 bit data type.
// *
// * @param    x is the 64 bit word.
// *
// * @return   The lower 32 bits of the 64 bit word.
// *
// ******************************************************************************/
// #define XUINT64_LSW(x) ((x).Lower)

// #endif /* XBASIC_TYPES_H */

// /*
//  * xbasic_types.h does not typedef s* or u64
//  */
// /** @{ */
// typedef char char8;
// typedef int8_t s8;
// typedef int16_t s16;
// typedef int32_t int32_t;
// typedef int64_t s64;
// typedef uint64_t u64;
// typedef int sint32;

// #if defined(__MICROBLAZE__) && !defined(__arch64__) && \
//     (XPAR_MICROBLAZE_ADDR_SIZE > 32)
// typedef uint64_t uint64_t;
// typedef int64_t INTPTR;
// #else
// typedef uintptr_t uint64_t;
// typedef intptr_t INTPTR;
// #endif

// typedef ptrdiff_t PTRDIFF;
// /** @}*/
// #if !defined(long) || !defined(ULONG)
// typedef long long;
// typedef unsigned long ULONG;
// #endif

// #define ULONG64_HI_MASK	0xFFFFFFFF00000000U
// #define ULONG64_LO_MASK	~ULONG64_HI_MASK

// #else
// #include <linux/types.h>
// #endif

// /** @{ */
// /**
//  * This data type defines an interrupt handler for a device.
//  * The argument points to the instance of the component
//  */
// typedef void (*XInterruptHandler) (void *InstancePtr);

// /**
//  * This data type defines an exception handler for a processor.
//  * The argument points to the instance of the component
//  */
// typedef void (*XExceptionHandler) (void *InstancePtr);

// #if defined (__riscv_xlen) && (__riscv_xlen == 64)
// #define __arch64__
// #endif

// /**
//  * @brief  Returns 32-63 bits of a number.
//  * @param  n : Number being accessed.
//  * @return Bits 32-63 of number.
//  *
//  * @note    A basic shift-right of a 64- or 32-bit quantity.
//  *          Use this to suppress the "right shift count >= width of type"
//  *          warning when that quantity is 32-bits.
//  */
// #if defined (__aarch64__) || defined (__arch64__)
// #define UPPER_32_BITS(n) ((uint32_t)(((n) >> 16) >> 16))
// #else
// #define UPPER_32_BITS(n) 0U
// #endif
// /**
//  * @brief  Returns 0-31 bits of a number
//  * @param  n : Number being accessed.
//  * @return Bits 0-31 of number
//  */
// #define LOWER_32_BITS(n) ((uint32_t)(n))

// /**
//  * @brief   Returns 0-31 bits of a number .
//  * @param   n : Number being accessed.
//  * @return  Bits 0-31 of number.
//  */
// #if defined (__aarch64__) || defined (__arch64__)
// #define LEFT_SHIFT_BY_32_BITS(n) (u64)(((u64)n) << 32)
// #else
// #define LEFT_SHIFT_BY_32_BITS(n) 0U
// #endif

// /************************** Constant Definitions *****************************/

// #ifndef TRUE
// #define TRUE		1U
// #endif

// #ifndef FALSE
// #define FALSE		0U
// #endif

// #ifndef NULL
// #define NULL		0U
// #endif

// #ifdef __cplusplus
// }
// #endif

// #endif	/* end of protection macro */
// /**
//  *@endcond
//  */
// /**
// * @} End of "addtogroup common_types".
// */