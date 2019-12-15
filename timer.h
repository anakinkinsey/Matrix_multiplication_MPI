/**
 * 473 Final Project
 * Anakin Kinsey & Cory Rothenberger
 * 10/27/2019
 * Fall 2019
**/
#ifndef _TIMER_H_
#define _TIMER_H_

#include <sys/time.h>

/* The argument now should be a double (not a pointer to a double) */
#define GET_TIME(now) { \
   struct timeval t; \
   gettimeofday(&t, NULL); \
   now = t.tv_sec + t.tv_usec/1000000.0; \
}

#endif
