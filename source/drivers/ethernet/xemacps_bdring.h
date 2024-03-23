/******************************************************************************
* Copyright (C) 2010 - 2022 Xilinx, Inc.  All rights reserved.
* Copyright (C) 2022 - 2023 Advanced Micro Devices, Inc. All rights reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/

/*****************************************************************************/
/**
*
* @file xemacps_bdring.h
* @addtogroup emacps Overview
* @{
*
* The Xiline EmacPs Buffer Descriptor ring driver. This is part of EmacPs
* DMA functionalities.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date     Changes
* ----- ---- -------- -------------------------------------------------------
* 1.00a wsy  01/10/10 First release
* 2.1   srt  07/15/14 Add support for Zynq Ultrascale Mp architecture.
* 3.0   kvn  02/13/15 Modified code for MISRA-C:2012 compliance.
* 3.6   rb   09/08/17 HwCnt variable (in XEmacPs_BdRing structure) is
*		      changed to volatile.
*
* </pre>
*
******************************************************************************/

#ifndef XEMACPS_BDRING_H	/* prevent curcular inclusions */
#define XEMACPS_BDRING_H	/* by using protection macros */

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


/**************************** Type Definitions *******************************/

/** This is an internal structure used to maintain the DMA list */
typedef struct {
	uint64_t PhysBaseAddr;/**< Physical address of 1st BD in list */
	uint64_t BaseBdAddr;	 /**< Virtual address of 1st BD in list */
	uint64_t HighBdAddr;	 /**< Virtual address of last BD in the list */
	uint32_t Length;	 /**< Total size of ring in bytes */
	uint32_t RunState;	 /**< Flag to indicate DMA is started */
	uint32_t Separation;	 /**< Number of bytes between the starting address
                                  of adjacent BDs */
	XEmacPs_Bd *FreeHead;
			     /**< First BD in the free group */
	XEmacPs_Bd *PreHead;/**< First BD in the pre-work group */
	XEmacPs_Bd *HwHead; /**< First BD in the work group */
	XEmacPs_Bd *HwTail; /**< Last BD in the work group */
	XEmacPs_Bd *PostHead;
			     /**< First BD in the post-work group */
	XEmacPs_Bd *BdaRestart;
			     /**< BDA to load when channel is started */

	volatile uint32_t HwCnt;    /**< Number of BDs in work group */
	uint32_t PreCnt;     /**< Number of BDs in pre-work group */
	uint32_t FreeCnt;    /**< Number of allocatable BDs in the free group */
	uint32_t PostCnt;    /**< Number of BDs in post-work group */
	uint32_t AllCnt;     /**< Total Number of BDs for channel */
} XEmacPs_BdRing;


/***************** Macros (Inline Functions) Definitions *********************/

/*****************************************************************************/
/**
* Use this macro at initialization time to determine how many BDs will fit
* in a BD list within the given memory constraints.
*
* The results of this macro can be provided to XEmacPs_BdRingCreate().
*
* @param Alignment specifies what byte alignment the BDs must fall on and
*        must be a power of 2 to get an accurate calculation (32, 64, 128,...)
* @param Bytes is the number of bytes to be used to store BDs.
*
* @return Number of BDs that can fit in the given memory area
*
* @note
* C-style signature:
*    uint32_t XEmacPs_BdRingCntCalc(uint32_t Alignment, uint32_t Bytes)
*
******************************************************************************/
#define XEmacPs_BdRingCntCalc(Alignment, Bytes)                    \
    (uint32_t)((Bytes) / (sizeof(XEmacPs_Bd)))

/*****************************************************************************/
/**
* Use this macro at initialization time to determine how many bytes of memory
* is required to contain a given number of BDs at a given alignment.
*
* @param Alignment specifies what byte alignment the BDs must fall on. This
*        parameter must be a power of 2 to get an accurate calculation (32, 64,
*        128,...)
* @param NumBd is the number of BDs to calculate memory size requirements for
*
* @return The number of bytes of memory required to create a BD list with the
*         given memory constraints.
*
* @note
* C-style signature:
*    uint32_t XEmacPs_BdRingMemCalc(uint32_t Alignment, uint32_t NumBd)
*
******************************************************************************/
#define XEmacPs_BdRingMemCalc(Alignment, NumBd)                    \
    (uint32_t)(sizeof(XEmacPs_Bd) * (NumBd))

/****************************************************************************/
/**
* Return the total number of BDs allocated by this channel with
* XEmacPs_BdRingCreate().
*
* @param  RingPtr is the DMA channel to operate on.
*
* @return The total number of BDs allocated for this channel.
*
* @note
* C-style signature:
*    uint32_t XEmacPs_BdRingGetCnt(XEmacPs_BdRing* RingPtr)
*
*****************************************************************************/
#define XEmacPs_BdRingGetCnt(RingPtr) ((RingPtr)->AllCnt)

/****************************************************************************/
/**
* Return the number of BDs allocatable with XEmacPs_BdRingAlloc() for pre-
* processing.
*
* @param  RingPtr is the DMA channel to operate on.
*
* @return The number of BDs currently allocatable.
*
* @note
* C-style signature:
*    uint32_t XEmacPs_BdRingGetFreeCnt(XEmacPs_BdRing* RingPtr)
*
*****************************************************************************/
#define XEmacPs_BdRingGetFreeCnt(RingPtr)   ((RingPtr)->FreeCnt)

/****************************************************************************/
/**
* Return the next BD from BdPtr in a list.
*
* @param  RingPtr is the DMA channel to operate on.
* @param  BdPtr is the BD to operate on.
*
* @return The next BD in the list relative to the BdPtr parameter.
*
* @note
* C-style signature:
*    XEmacPs_Bd *XEmacPs_BdRingNext(XEmacPs_BdRing* RingPtr,
*                                      XEmacPs_Bd *BdPtr)
*
*****************************************************************************/
#define XEmacPs_BdRingNext(RingPtr, BdPtr)                           \
    (((uint64_t)((void *)(BdPtr)) >= (RingPtr)->HighBdAddr) ?                     \
    (XEmacPs_Bd*)((void*)(RingPtr)->BaseBdAddr) :                              \
    (XEmacPs_Bd*)((uint64_t)((void *)(BdPtr)) + (RingPtr)->Separation))

/****************************************************************************/
/**
* Return the previous BD from BdPtr in the list.
*
* @param  RingPtr is the DMA channel to operate on.
* @param  BdPtr is the BD to operate on
*
* @return The previous BD in the list relative to the BdPtr parameter.
*
* @note
* C-style signature:
*    XEmacPs_Bd *XEmacPs_BdRingPrev(XEmacPs_BdRing* RingPtr,
*                                      XEmacPs_Bd *BdPtr)
*
*****************************************************************************/
#define XEmacPs_BdRingPrev(RingPtr, BdPtr)                           \
    (((uint64_t)(BdPtr) <= (RingPtr)->BaseBdAddr) ?                     \
    (XEmacPs_Bd*)(RingPtr)->HighBdAddr :                              \
    (XEmacPs_Bd*)((uint64_t)(BdPtr) - (RingPtr)->Separation))

/************************** Function Prototypes ******************************/

/*
 * Scatter gather DMA related functions in xemacps_bdring.c
 */
long XEmacPs_BdRingCreate(XEmacPs_BdRing * RingPtr, uint64_t PhysAddr,
			  uint64_t VirtAddr, uint32_t Alignment, uint32_t BdCount);
long XEmacPs_BdRingClone(XEmacPs_BdRing * RingPtr, XEmacPs_Bd * SrcBdPtr,
			 uint8_t Direction);
long XEmacPs_BdRingAlloc(XEmacPs_BdRing * RingPtr, uint32_t NumBd,
			 XEmacPs_Bd ** BdSetPtr);
long XEmacPs_BdRingUnAlloc(XEmacPs_BdRing * RingPtr, uint32_t NumBd,
			   XEmacPs_Bd * BdSetPtr);
long XEmacPs_BdRingToHw(XEmacPs_BdRing * RingPtr, uint32_t NumBd,
			XEmacPs_Bd * BdSetPtr);
long XEmacPs_BdRingFree(XEmacPs_BdRing * RingPtr, uint32_t NumBd,
			XEmacPs_Bd * BdSetPtr);
uint32_t XEmacPs_BdRingFromHwTx(XEmacPs_BdRing * RingPtr, uint32_t BdLimit,
				 XEmacPs_Bd ** BdSetPtr);
uint32_t XEmacPs_BdRingFromHwRx(XEmacPs_BdRing * RingPtr, uint32_t BdLimit,
				 XEmacPs_Bd ** BdSetPtr);
long XEmacPs_BdRingCheck(XEmacPs_BdRing * RingPtr, uint8_t Direction);

void XEmacPs_BdRingPtrReset(XEmacPs_BdRing * RingPtr, void *virtaddrloc);

#ifdef __cplusplus
}
#endif


#endif /* end of protection macros */
/** @} */