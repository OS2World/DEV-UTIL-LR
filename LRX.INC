/*
______________________________________________________________________________
LR Parse tree navigation macros
Philip R Brenan,  Transcendental Automation,  1992,  800-FOR-PHIL

MACRO    DESCRIPTION
n        Obtain number of a non terminal
loc      Add pointer to current non terminal
one      Return single item below current item, or zero otherwise
zero     Initialize new non terminal pointer set
add      Add pointers to the current non terminal and its singleton dependents
all      Add pointers to the current non terminal and all its dependents up to repetition
zap      Zero and add
up       Move up through parse tree until top, or a non terminal pointer would be overlaid
copy     Initialize new non terminal pointer set by copying existing non terminal pointer set
list_do  Process non terminal sub list
integer  Convert non terminal to integer
string   Convert non terminal to string

KEYS     DESCRIPTION
KEYS     Non terminal set generated during grammar preparation
P        Parse results
PT       Current non terminal
UNTIL    Move up until end or this expression returns true
FROM     Non terminal set to be copied
L        Work Xl *
T        Work Xt *
Pt       Dependent non terminal
______________________________________________________________________________
*/
#ifndef   LRX_INC
#define   LRX_INC

#ifdef    LRX_MAIN
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "m.inc"
#include "lr.inc"
#endif

#ifndef   LR_INC
#include "lr.inc"
#endif
/*
______________________________________________________________________________
Non terminal pointers
______________________________________________________________________________
*/
typedef struct LRX_PT
 {struct LR_PT *l;
  struct LR_P  *p;          // Parse results
  struct LR_PT *key[32];    // Non terminals
 } LRX_PT;

/*
______________________________________________________________________________
Request for services from LRX_REQ.  Fill out this structure and pass to LRX.
______________________________________________________________________________
*/
typedef struct LRX_REQ
 {long    req;                                   // Actions to be performed as per lrx_req_*
  long    rc;                                    // Return code as defined in lrx_req_rc_*
  char   *name;                                  // Name of grammar - only required if you are compiling a grammar
  LR_P   *P;                                     // Parse tree
  LR     *lr;                                    // Grammar compilation results
  LR2    *grammar;                               // Compiled and loaded grammar
  char   *grammar_file;                          // File   containing compiled grammar
  char   *gdl;                                   // String containing source GDL for grammar
  char   *gdl_file;                              // File   containing source GDL for grammar
  char   *text;                                  // Text to be parsed
  char   *text_file;                             // File containing text to be parsed
  void (**pre)();                                // Pointer to Pre commands  <<GRAMMAR>>_cmd.pre  function pointers
  void (**post)();                               // Pointer to Post commands <<GRAMMAR>>_cmd.post function pointers
  void   *nps;                                   // Pointer to Non terminal Pointer Set <<GRAMMAR>>_NPS
  long    stack;                                 // Default parser stack, will be set to 4K unless you set it higher
  void   *sysp;                                  // User parameter to be passed to each pre/post command function invoked
  char    grammar_file_save[256];                // File   containing compiled grammar, saved from compilation
 } LRX_REQ;

#define lrx_req_load_gdl              0x00000001 // Load GDL file
#define lrx_req_compile_gdl           0x00000002 // Compile gdl to create grammar file
#define lrx_req_load_grammar          0x00000004 // Load grammar file
#define lrx_req_load_text             0x00000008 // Load text file
#define lrx_req_parse                 0x00000010 // Perform parse
#define lrx_req_free_parse            0x00000020 // Free parse tree
#define lrx_req_free_grammar          0x00000040 // Free grammar
#define lrx_req_free_gdl              0x00000080 // Free GDL
#define lrx_req_free_text             0x00000100 // Free text
#define lrx_req_free_compile          0x00000200 // Free grammar compilation results
#define lrx_req_strip_comments        0x00000400 // Remove *, -- comment lines from input text
#define lrx_req_print_parse           0x00000800 // Print parse tree to <<GRAMMAR>>.PRS
#define lrx_req_rescan                0x00001000 // Rescan parse tree
#define lrx_req_free_all        \
        lrx_req_free_parse    | \
        lrx_req_free_grammar  | \
        lrx_req_free_gdl      | \
        lrx_req_free_text     | \
        lrx_req_free_compile

#define lrx_req_rc_ok                          0 // Request performed successfully
#define lrx_req_rc_no_grammar         0x00000001 // No grammar supplied
#define lrx_req_rc_no_grammar_file    0x00000002 // No grammar file supplied
#define lrx_req_rc_bad_grammar_file   0x00000004 // Bad grammar file supplied - errors occurred during read
#define lrx_req_rc_no_gdl_file        0x00000008 // No GDL file supplied
#define lrx_req_rc_bad_gdl_file       0x00000010 // Bad GDL file, errors occurred during read
#define lrx_req_rc_no_gdl             0x00000020 // No GDL text supplied
#define lrx_req_rc_no_text_file       0x00000040 // No input text file to be loaded, parsed, freed
#define lrx_req_rc_bad_text_file      0x00000080 // Bad input text file, errors occurred during read
#define lrx_req_rc_no_text            0x00000100 // No input text to be parsed
#define lrx_req_rc_compile_errors     0x00000200 // Compile errors occurred, check <<GRAMMAR>>.LR
#define lrx_req_rc_parse_errors       0x00000400 // Parse errors occurred,   check <<GRAMMAR>>.ERR
#define lrx_req_rc_no_nps             0x00000800 // No NPS supplied, you should include <<GRAMMAR>>.STR
#define lrx_req_rc_no_action          0x00001000 // No action specified
#define lrx_req_rc_no_name            0x00002000 // No grammar name supplied
#define lrx_req_rc_no_parse_to_free   0x00004000 // No parse to free per request
#define lrx_req_rc_no_text_to_free    0x00008000 // No text to free per request
#define lrx_req_rc_no_grammar_to_free 0x00010000 // No compiled grammar to free per request
#define lrx_req_rc_no_gdl_to_free     0x00020000 // No gdl to free per request
#define lrx_req_rc_no_compile_to_free 0x00040000 // No compilation results to free per request
#define lrx_req_rc_no_parse_tree      0x00080000 // No parse tree available for printing

#define lrx_cmd(NAME) void NAME(LRX_REQ *REQ, LR_PT *PT) // Defines a semantuic action procedure
#define lrx_default_stack                           4096 // Default stack size

/*
______________________________________________________________________________
External macros
______________________________________________________________________________
*/
#define lr_do(_P, _L, _pt) x_vector_do((_P)->V, _L, _pt)

/*
______________________________________________________________________________
N
______________________________________________________________________________
*/
#define lrx_n(_PT) ((_PT)->rc->nt->nts)
/*
______________________________________________________________________________
LOC
______________________________________________________________________________
*/
#define lrx_loc(_KEYS, _PT)                                       \
 {if (_PT)                                                        \
   {LRX_PT *_q = (void *)&(_KEYS);                                \
                                                                  \
    _q->key[lrx_n(_PT)] = (_PT);                                  \
   }                                                              \
 }
/*
______________________________________________________________________________
ONE
______________________________________________________________________________
*/
#define lrx_one(_PT) (((_PT) && (_PT)->PL.f && (_PT)->PL.f == (_PT)->PL.l) ? (LR_PT *)(_PT)->PL.f->d : (LR_PT *)0)
/*
______________________________________________________________________________
ZERO
______________________________________________________________________________
*/
#define lrx_zero(_KEYS, _P)                                          \
  (memset((_KEYS).key, 0, (_P)->lr->NTS * sizeof(LR_PT *)),            \
  (_KEYS).p = (_P))
/*
______________________________________________________________________________
ADD
______________________________________________________________________________
*/
#define lrx_add(_KEYS, _PT) lrx_Add(&(_KEYS), _PT)
/*
______________________________________________________________________________
ALL
______________________________________________________________________________
*/
#define lrx_all(_KEYS, _PT)  \
 {lrx_add(_KEYS, _PT);       \
  lrx_All(&(_KEYS), _PT);    \
 }
/*
______________________________________________________________________________
ZAP
______________________________________________________________________________
*/
#define lrx_zap(_KEYS, _P, _PT)                                      \
  lrx_zero((_KEYS), _P);                                             \
  lrx_add ((_KEYS), _PT);
/*
______________________________________________________________________________
UP
______________________________________________________________________________
*/
#define lrx_up(_KEYS, _PT, _UNTIL)                                   \
if (_PT)                                                             \
 {XL      *_l;                                                       \
  LR_PT   *_p = _PT;                                                 \
  LR_PT *(*_q)[32];                                                  \
                                                                     \
  for(_q = (void *)&(_KEYS).key; _l = _p->Pl.u;)                     \
   {_p = _l->d;                                                      \
   (*_q)[lrx_n(_p)] = _p;                                            \
    if (_UNTIL) break;                                               \
   }                                                                 \
 }
/*
______________________________________________________________________________
COPY
______________________________________________________________________________
*/
#define lrx_copy(_KEYS, _FROM)                                             \
  (memcpy((_KEYS).key, (_FROM).key, (_FROM).p->lr->NTS * sizeof(LR_PT *)), \
  (_KEYS).p = (_FROM).p)
/*
______________________________________________________________________________
LIST_DO
______________________________________________________________________________
*/
#define lrx_list_do(_PT, _L, _pt)                                    \
  x_list_do(&(_PT)->PL, _L, _pt)
/*
______________________________________________________________________________
Integer
______________________________________________________________________________
*/
#define lrx_integer(_pt) atol(_pt->t)
/*
__________________________________________________________________________________________________
String
__________________________________________________________________________________________________
*/
#define lrx_string(M, PT) u_strip_quote1(m_alloc_str(M, PT->t))
/*
______________________________________________________________________________
Procedures
______________________________________________________________________________
*/
void  lrx_parse        (LR_P **p,       void (**cmd)(), void (**cmd2)(), LRX_PT *PT, LR2 *grammar, char *text, long stack, void *sysp);
void  __lrx_parse_scan (LR_P  *P,       void (**cmd)(), void (**cmd2)(), LRX_PT *PT, void *sysp);
void  lrx_parse_scan   (LRX_REQ *r);
void  lrx_Add          (void *KEYS,     struct LR_PT  *PT);
void  lrx_All          (void *KEYS,     struct LR_PT  *PT);

char *lrx_concat       (struct M    *m, struct LR_PT  *p);
void  lrx_concat2      (char **c,       struct LR_PT  *p);
char *lrx_concat_space (struct M    *m, struct LR_PT  *p);
void  lrx_concat_space2(char **c,       struct LR_PT  *p);
long  lrx_req          (LRX_REQ *r);
#endif