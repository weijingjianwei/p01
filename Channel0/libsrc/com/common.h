/* -------------------------------------------------------------------- */
/* Copyright(c) 2009 Renesas Electronics Corporation                    */
/* -------------------------------------------------------------------- */
/* File name: Common header file for CubeSuite+                         */
/* Version:   0.01                                                      */
/* Date:      2013/01/18                                                */
/* Author:    A.Kondo                                                   */
/* -------------------------------------------------------------------- */

/* -------------------------------------------------------------------- */
/* History                                                              */
/*   V0.01: 2013.01.18  1st creation.                                   */
/* -------------------------------------------------------------------- */
#ifndef H_COMMON
#define H_COMMON

/* -------------------------------------------------------------------- */
/* Type definition                                                      */
/* -------------------------------------------------------------------- */
typedef signed char     s1;
typedef signed short    s2;
typedef signed long     s4;
typedef unsigned char   u1;
typedef unsigned short  u2;
typedef unsigned long   u4;
typedef float           f4;

/* -------------------------------------------------------------------- */
/* Macro definition                                                     */
/* -------------------------------------------------------------------- */
/* Maximum and minimum value */
#define s1gMIN  ((s1)0x80)
#define s1gMAX  ((s1)0x7f)
#define u1gMAX  ((u1)0xff)
#define s2gMIN  ((s2)0x8000)
#define s2gMAX  ((s2)0x7fff)
#define u2gMAX  ((u2)0xffff)
#define s4gMIN  ((s4)0x80000000)
#define s4gMAX  ((s4)0x7fffffff)
#define u4gMAX  ((u4)0xffffffff)

/* Return value of function */
#define ON      1
#define OFF     0
#define OK      0
#define ERROR   (-1)
#define TRUE    1
#define FALSE   0

#endif /* H_COMMON */

/* End of file */
