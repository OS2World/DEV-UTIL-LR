/*
_____________________________________________________________
Memory allocation structures
Philip R Brenan,  Transcendental Automation,  1993,  800-FOR-PHIL
_____________________________________________________________
*/
#ifndef M_INC
#define M_INC

#ifdef M_MAIN
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INCL_DOSMEMMGR
#include <os2.h>
#endif

#ifndef   X_INC
#include "x.inc"
#endif
/*
_____________________________________________________________
Memory allocation constants
_____________________________________________________________
*/
#define m_put_count          1 // More than one area in condensed version
#define m_put_file           2 // Unable to open save file for writing
#define m_get_file           3 // Unable to open save file for reading
#define m_size long int        // Integer large enough to hold maximum memory amount
#define m_page_size       4096 // Page size
/*
_____________________________________________________________
Memory allocation structures
_____________________________________________________________
*/
typedef struct M                       // Memory chain
 {XL        x;                         // Memory list
  m_size    size;                      // Size of allocation - sizeof(m)
  struct m *last;                      // Current area
  m_size    alloc_used;                // Used memory (including control areas)
  m_size    alloc_bytes;               // Allocated bytes (including control areas)
  m_size    alloc_areas;               // Allocated areas
  m_size    allocs;                    // Number of user allocations
 } M;

typedef struct m                       // Memory area
 {Xl     x;                            // Memory list
  m_size size;                         // Size of usable area
  m_size alloc;                        // Amount allocated for this area (include control blocks)
  void  *at;                           // Next allocation
 } m;
/*
_____________________________________________________________
Memory management macros
_____________________________________________________________
*/
#define m_alloc_str(m, s)     strcpy (m_alloc(m, strlen(s) + 1), s)
#define m_alloc_strn(m, s, n) strncpy(m_alloc(m, n + 1),         s, n + 1)
#define m_alloc_struct(S, s, size) {M *m = m_open(sizeof(S) + (size)); s = m_alloc(m, sizeof(S)); s->m = m;}
/*
_____________________________________________________________
Memory procedure declarations
_____________________________________________________________
*/
M    *m_open (       m_size size);
void *m_alloc(M  *p, m_size size);
void  m_close(M  *p);
int   m_put  (M  *p, void *u,  char *ds);
int   m_get  (M **p, void **u, char *ds);

void  m_test (void);

void *m_alloc_area(m_size size);
void  m_free_area (void  *at);

#endif
