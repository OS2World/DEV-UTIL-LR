/*
______________________________________________________________________________
Utilities
Philip R Brenan, Transcendental Automation, 1992, 800-FOR-PHIL
______________________________________________________________________________
*/
#ifndef U_INC
#define U_INC
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
______________________________________________________________________________
Constants
______________________________________________________________________________
*/
#define u_comment_char '*' // Comment marker if column 1
/*
______________________________________________________________________________
Utility routines
______________________________________________________________________________
*/
void  u_edit_ds       (char *ds);
char *u_load_ds       (char *ds);
void u_free_ds        (char *ds);
char *u_strip_comments(char *ds);

void  u_test(void);
/*
______________________________________________________________________________
Zero a structure
______________________________________________________________________________
*/
#define u_zero(p) (memset(&p, 0, sizeof(p)))
/*
______________________________________________________________________________
Add to non null pointer
______________________________________________________________________________
*/
#define u_ptr_add(p, i) (p ? (p = (void *)((char *)p + (i))) : 0)
/*
______________________________________________________________________________
Create string of specified width, padded with blanks or truncated
______________________________________________________________________________
*/
#define u_str_fix(t, s)  \
 (memset (t, ' ', sizeof t), \
  strncpy(t, s, strlen(s) < sizeof t ? strlen(s) : sizeof(t)), \
  t[sizeof t - 1] = 0, \
  t \
 )

#endif