/* Sparc64 gmp-mparam.h -- Compiler/machine parameter header file.

Copyright 1991, 1993, 1994, 1999, 2000 Free Software Foundation, Inc.

This file is part of the GNU MP Library.

The GNU MP Library is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or (at your
option) any later version.

The GNU MP Library is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
License for more details.

You should have received a copy of the GNU Lesser General Public License
along with the GNU MP Library; see the file COPYING.LIB.  If not, write to
the Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
MA 02111-1307, USA. */

#define BITS_PER_MP_LIMB 64
#define BYTES_PER_MP_LIMB 8
#define BITS_PER_LONGINT 64
#define BITS_PER_INT 32
#define BITS_PER_SHORTINT 16
#define BITS_PER_CHAR 8

/* Tell the toom3 multiply implementation to call low-level mpn
   functions instead of open-coding operations in C.  */
#ifndef USE_MORE_MPN
#define USE_MORE_MPN 1
#endif


/* Run on sun workshop cc. */
/* Generated by tuneup.c, 2000-10-02. */

#ifndef KARATSUBA_MUL_THRESHOLD
#define KARATSUBA_MUL_THRESHOLD     12
#endif
#ifndef TOOM3_MUL_THRESHOLD
#define TOOM3_MUL_THRESHOLD        114
#endif

#ifndef KARATSUBA_SQR_THRESHOLD
#define KARATSUBA_SQR_THRESHOLD     26
#endif
#ifndef TOOM3_SQR_THRESHOLD
#define TOOM3_SQR_THRESHOLD        102
#endif

#ifndef DC_THRESHOLD
#define DC_THRESHOLD                27
#endif

#ifndef FIB_THRESHOLD
#define FIB_THRESHOLD              107
#endif

#ifndef POWM_THRESHOLD
#define POWM_THRESHOLD              47
#endif

#ifndef GCD_ACCEL_THRESHOLD
#define GCD_ACCEL_THRESHOLD          4
#endif
#ifndef GCDEXT_THRESHOLD
#define GCDEXT_THRESHOLD           199
#endif

#ifndef FFT_MUL_TABLE
#define FFT_MUL_TABLE  { 304, 608, 1344, 2304, 7168, 20480, 49152, 0 }
#endif
#ifndef FFT_MODF_MUL_THRESHOLD
#define FFT_MODF_MUL_THRESHOLD     320
#endif
#ifndef FFT_MUL_THRESHOLD
#define FFT_MUL_THRESHOLD         1664
#endif

#ifndef FFT_SQR_TABLE
#define FFT_SQR_TABLE  { 304, 608, 1344, 2816, 7168, 20480, 49152, 0 }
#endif
#ifndef FFT_MODF_SQR_THRESHOLD
#define FFT_MODF_SQR_THRESHOLD     320
#endif
#ifndef FFT_SQR_THRESHOLD
#define FFT_SQR_THRESHOLD         1664
#endif
