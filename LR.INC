/*
______________________________________________________________________________
LR parser generator data structures
Philip R Brenan,  Transcendental Automation,  1992,  800-FOR-PHIL
______________________________________________________________________________
*/
#ifndef LR_INC
#define LR_INC

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "x.inc"
#include "m.inc"
#include "void.inc"
#include "u.inc"
#include "lr_mess.inc"

/*
______________________________________________________________________________
Constants
______________________________________________________________________________
*/
#define lr_chars              256 // Number of characters in the alphabet being parsed
#define lr_chars_1            257 // Above + 1
#define lr_max_key            257 // Maximum keyword length
#define lr_chars_on           '1' // Present
#define lr_chars_off          '2' // Absent
#define lr_reductions          2  // Number of reduction levels

#define lr_reduction_primary    0 // Primary reductions
#define lr_reduction_secondary  1 // Secondary reductions

#define lr_reduce_normal        0 // Normal reduction
#define lr_reduce_string        1 // String reduction
#define lr_reduce_substr        2 // String component

#define lr_repeat_normal        0 // No repetition
#define lr_repeat_start         1 // Start repetition
#define lr_repeat_continue      2 // Continue repetition

#define lr_width_nt            16 // Width of a non terminal name
#define lr_width_state          8 // Width of state number

#define lr_save_count           1 // More than one area in condensed version
#define lr_save_file            2 // Unable to open save file

#define lr_print_states       999 // Maximum number of states to be printed
#define lr_print_width         10 // Step size in parse tree width
#define lr_print_width1       220 // Maximum tree width in printing parse tree
#define lr_print_width2        16 // Maximum width of leaf in printing of parse tree

#define lr_char_horiz         196 // Horizontal line
#define lr_char_vert          179 // Vertical line
#define lr_char_cont          195 // T from left side
#define lr_char_end           192 // Lower left corner

#define lr_file_code       ".CC"  // Suffix for code file
#define lr_file_error      ".ERR" // Suffix for errors file
#define lr_file_grammar    ".GR"  // Suffix for source grammar
#define lr_file_n          ".N"   // Suffix for non terminal count file
#define lr_file_print      ".LR"  // Suffix for grammar listing file
#define lr_file_parse      ".PRS" // Suffix for parse   listing file
#define lr_file_save       ".LRS" // Suffix for condensed grammar save file
#define lr_file_struct     ".STR" // Suffix for struct files
#define lr_file_text       ".TXT" // Suffix for text input files

#define lr_struct_suffix   "_NPS" // LR_PT * structure suffix
#define lr_struct_width       32  // LR_PT * structure name width

#define lr_file_chars         257 // Maximum file length name
#define lr_comment_width      80  // Comment width
/*
______________________________________________________________________________
Structures with forward references
______________________________________________________________________________
*/
struct LR_SPACE;
/*
______________________________________________________________________________
Structures
______________________________________________________________________________
*/
typedef struct LR
 {
#define lr_LR                                                             \
  char   *name;               /* Name of grammar                        */\
  char   *title;              /* Short description of grammar           */\
  M      *mc;                 /* Memory for condensed version of parser */\
  long    STATES;             /* Number of states                       */\
  long    NTS;                /* Number of non terminals                */\
  long    ACTIONS;            /* Number of actions                      */

  lr_LR
  M             *m;           // Memory used by this parse
  struct  LR2   *lr2;         // Condensed version
  struct  LR_S  *start_state; // Start state in the LR(0) automaton
  struct  LR_S  *end_state;   // End   state in the LR(0) automaton
  char          *path;        // Path used for file names
  char          *save_file;   // File to which condensed version was saved
  char          *print_file;  // File to which LR automaton was printed
  char          *struct_file; // File to which LR structures were written
  char          *struct_file_n; // Other file
  char          *code_file;   // Code file
  VOID_PARSE *vp;             // Parse of void language representation of grammar
  VOID_ITEM  *rules;          // Rules      keyword
  VOID_ITEM  *zero;           // Zero       keyword
  VOID_ITEM  *optional;       // Optional   keyword
  VOID_ITEM  *repeat;         // Repeat     keyword
  VOID_ITEM  *choice;         // Choice     keyword
  VOID_ITEM  *ignore;         // Ignore     keyword
  struct VOID_ITEM  *secondary;      // Secondary  keyword
  struct VOID_ITEM  *string;         // String     keyword
  struct VOID_ITEM  *describe;       // Describe   keyword
  struct VOID_ITEM  *save;           // Save       keyword
  struct VOID_ITEM  *print;          // Print      keyword
  struct VOID_ITEM  *printf;         // Print file keyword
  struct VOID_ITEM  *structs;        // Struct     keyword
  struct VOID_ITEM  *code;           // Code       keyword
  char   *grammar;            // Void language representation of grammar

  XT      NT;                 // Non terminals LR_NT
  XL      LR_R;               // Rules
  XL      LR_RC;              // Rule components
  XL      STATE;              // States
  XL      LR_A;               // Actions
  XL      LR_At;              // Terminal Actions

  long    RS, RCS;            // Number of rules, rule components (rule components only)
  XT      T;                  // Terminals
  long    eS;                 // Number of states removed
  long    eA;                 // Number of actions removed
  long    eAt;                // Number of terminal actions removed
  long    ISTATES;            // Number of identified states
  long    ACTIONS_NT;         // Number of non terminal actions
  long    ACTIONS_T;          // Number of terminal actions
  long    nBUNDLES;           // Number of bundles
  struct  LR_NT *start_nt;    // Start non terminal (first one under RULES keyword)

  XT      BUNDLES;            // States by bundle
  struct LR_CONDENSE_COUNT    // Number of duplicates in condensed version
   {long NTs, ts[lr_reductions], REACTIONs;
   } CC;
  struct LR_CONDENSE_SAVE     // Storage occupied by duplicates in condensed version
   {long NTs, ts[lr_reductions], REACTIONs;
   } CS;

  long    reuses;             // Size of following area
  long   *reuse;              // Non terminal reuse check

  struct  LR_ERRORS           // Errors
   {long  info, severe;       // Number of informational and severe errors detected
    long  name;               // Name keyword missing
    long  title;              // Title keyword missing
    long  rules;              // Rules keyword missing
    long  start_symbol;       // Start symbol missing
    long  parse;              // Parse errors occurred
    long  save;               // Save  errors occurred
    long  terminals;          // Number of invalid terminal specifications (not CHOICE, NOT, MIXED, or SEQUENCE)
    long  non_terminals;      // Number of invalid non terminal specifications (not ZERO, REPEAT, CHOICE, OPTIONAL, SECONDARY)
    long  sec_nts;            // Number of secondary non terminals without terminal RHS
    long  rc_sec_nts;         // Number of rule components specifying secondary for a non terminal whose RHS is non terminal
    long  lhss;               // Number of undefined LHS used on the RHS
    long  rhss;               // Number of defined LHS not used on the RHS
    long  nt_options;         // Invalid non terminal options
    long  optionals;          // Optional non terminals without definitions
    long  secondarys;         // Secondary non terminals without definitions
    long  strings;            // String non terminals without definitions
    long  repeats;            // Repeatable non terminals without definitions
    long  choices;            // Choosable non terminals without definitions
    long  sub_choices;        // First choice non terminal with more than one non termional in each rule
    long  ignores;            // Ignorable non terminals without definitions
    long  zeros;              // Zero non terminals without definitions
    long  str_strs;           // Number of string over string reductions
    long  substr_strs;        // Number of string under substring reductions
    long  normal_substrs;     // Number of substrings under normal reductions
    long  start_substr;       // Start non terminal is a substring reduction
    long  dup_rule_names;     // Number of non unique rule names
    long  zero_productions;   // Number of zero productions
    long  reduces;            // Number of reduce conflicts
    long  mixeds;             // Number of non terminals which mix terminals and non terminals in the same rule
    long  reuses;             // Number of rule components which use a non terminal more than once on the RHS of a rule
    long  no_shift_reduces;   // Number of states containing neither shift nor reduce

    struct LR_ERRORS_RS       // Reduce-shift conflict details
     {long   count;           // Number of reduce-shift conflicts
     } reduce_shift;

    struct LR_ERRORS_OVERLAP  // Terminal symbol overlap detected
     {long   count;           // Number of errors detected
     } overlap;

    struct LR_ERRORS_SECOND   // Secondary, Non secondary conflict
     {long   count;           // Number of errors detected
     } second_conflict;

    struct LR_ERRORS_IGNORE   // Ignore, Not ignore conflict
     {long   count;           // Number of errors detected
     } ignore_conflict;

    struct LR_ERRORS_ND       // Non deterministic state
     {long   count;           // Number of errors detected
     } non_deter;

    struct LR_ERRORS_FINAL    // Unable to locate final state
     {long   count;           // Number of errors detected
     } final;

    struct LR_ERRORS_DOUBLED  // Same non terminal transfer to different states
     {long   count;           // Number of errors detected
     } doubled;
   } errors;
  XL              * ERROR;    // Error list
  struct LR_ERROR *PERROR;    // Last error
 } LR;

typedef struct  LR_ERROR      // Errors
 {Xl        *error;           // Error list entry
  long      line_number;      // Error line number
  VOID_ITEM *terminal;        // Invalid terminal specification
  VOID_ITEM *non_terminal;    // Invalid non terminal specification
  struct LR_RC *sec_nt;       // Secondary non terminal without terminal RHS
  struct LR_RC *rc_sec_nt;    // Rule components specifying secondary for a non terminal whose RHS is non terminal
  char *lhs;                  // Number of undefined LHS used on the RHS
  char *rhs;                  // Number of defined LHS not used on the RHS
  char *nt_option;            // Invalid non terminal options
  char *optional;             // Optional non terminals without definitions
  char *secondary;            // Secondary non terminals without definitions
  char *string;               // String non terminals without definitions
  char *repeat;               // Repeatable non terminals without definitions
  char *choice;               // Choosable non terminals without definitions
  char *sub_choice;           // First choice non terminal with more than one non termional in each rule
  char *ignore;               // Ignorable non terminals without definitions
  char *zero;                 // Zero non terminals without definitions
  struct LR_RC *str_str;      // Number of string over string reductions
  struct LR_RC *substr_str;   // Number of string under substring reductions
  struct LR_RC *normal_substr;// Number of substrings under normal reductions
  struct LR_R  *dup_rule_name;// Number of non unique rule names
  struct LR_R  *zero_production;// Nunmer of zero productions
  struct LR_S  *reduce1;      // State at which reduce/reduce conflict occurs
  struct LR_R  *reduce2;      // First conflicting reduce-reduce rules
  struct LR_RC *mixed;        // Number of non terminals which mix terminals and non terminals in the same rule
  struct LR_RC *reuse;        // Number of rule components which use a non terminal more than once on the RHS of a rule
  struct LR_S  *no_shift_reduce;// State containing neither shift nor reduce

  struct LR_ERROR_RS          // Reduce-shift conflict details
   {struct LR_S *state;       // State with first reduce-shift conflict
    struct LR_A *action;      // Action causing first reduce-shift conflict
    char  *text;              // Text which caused the reduce-shift conflict
   } reduce_shift;

  struct LR_ERROR_OVERLAP     // Terminal symbol overlap detected
   {struct LR_RC *rc;         // Rule component causing overlap
    struct LR_S  *s;          // State affected by overlap
   } overlap;

  struct LR_ERROR_SECOND      // Secondary, Non secondary conflict
   {struct LR_RC *on, *off;   // Rule component causing conflict
   } second_conflict;

  struct LR_ERROR_IGNORE      // Ignore, Not ignore conflict
   {struct LR_RC *on, *off;   // Rule components causing conflict
   } ignore_conflict;

  struct LR_ERROR_ND          // Non deterministic state
   {struct LR_RC *rc;         // Rule component causing non determinism
    struct LR_S  *from;       // State at which non determinism was detected
    struct LR_A  *action;     // Existing action
   } non_deter;

  struct LR_ERROR_FINAL       // Unable to locate final state
   {struct LR_RC *rc;         // Rule component causing non determinism
    struct LR_S  *from;       // State at which non determinism was detected
   } final;

  struct LR_ERROR_DOUBLED     // Same non terminal transfer to different states
   {struct LR_A *action1;     // First  action exiting state with doubled non terminal
    struct LR_A *action2;     // Second action exiting state with doubled non terminal
   } doubled;
 } LR_ERROR;

typedef struct LR2            // Condensed LR parser definition
 {lr_LR
  char   *(*separator)(struct LR_SPACE *p, char *c);// Procedure to move over white space
  struct  LR2_S  *start_state;      // Start state in the LR(0) automaton
  struct  LR2_S  *end_state;        // End   state in the LR(0) automaton
  long    Ss, As, Ats, Rs, RCs, NTs;// Objects count by vector
  struct  LR2_S  *S;                // States  vector
  struct  LR2_A  *A;                // Actions vector
  struct  LR2_At *At;               // Terminal actions vector
  struct  LR2_R  *R;                // Rules vector
  struct  LR2_RC *RC;               // Rule components vector
  struct  LR2_NT *NT;               // Non terminals vector
 } LR2;

typedef struct LR_NT        // Non terminal
 {
#define lr_NT                                                \
  char   *name;             /* Non terminal symbol name    */\
  char   *describe;         /* Description of non terminal */\
  long    nts;              /* Non terminal number         */\
  long    reduce_action;    /* lr_reduce_* constants       */

  lr_NT
  Xt      nt;               // Non terminal tree from LR
  XL      R;                // Rules of which this non terminal is the LHS
  long    refs;             // Number of references to this rule

  unsigned zero      : 1;   // Repeat zero or more times
  unsigned repeat    : 1;   // Repeat one or more times
  unsigned choice    : 1;   // Choose one or more
  unsigned optional  : 1;   // Optional non terminal
  unsigned ignore    : 1;   // Do not index this non terminal in the parse tree
  unsigned secondary : 1;   // Secondary non terminal
  unsigned string    : 1;   // String options
  unsigned write     : 1;   // Writable NT

  struct  LR_NT *set_substr;// Non terminal which set this non terminal to substring reduction
  long    rc_nts, rc_ts;    // Number of rule component non terminals and terminals
  XT      rule;             // Rule names tree
  long    line_number;      // Source line number
 } LR_NT;

typedef    struct LR2_NT    // Condensed non terminal description
 {lr_NT
 } LR2_NT;

typedef    struct LR_T  // Terminal symbol
 {char    *value;       // Possible character values of this terminal symbol
  struct   LR_TS  *ts;  // Terminal symbol from which it was derived
  long     position;    // Position within terminal symbol (SEQUENCE option)
 } LR_T;


typedef    struct LR_TS // Terminal symbol text
 {unsigned sequence : 1;
  unsigned choice   : 1;
  unsigned not      : 1;
  unsigned mixed    : 1;
  char    *value;       // Text associated with this terminal symbol
  VOID_ITEM *v;         // Void language item from which it was derived
 } LR_TS;

typedef    struct LR_R  // Rule
 {
#define lr_R                                   \
  char    *rule_name;   /* Rule name         */\
  long     nt;          /* Non terminal count*/

  lr_R
  Xl       lr_r;        // Rules in LR
  long     rs;          // Rule number
  long     t;           // Terminal count
  XL       RC;          // Rule components
  Xl       r;           // Rule list
  long     line_number; // Source line number
 } LR_R;

typedef    struct LR2_R // Condensed rule
 {lr_R
 } LR2_R;

typedef    struct LR_RC // Rule component
 {
#define lr_RC                                                      \
  unsigned choice:1;    /* Local version of non terminal options */\
  unsigned ignore:1;    /* Local version of non terminal options */

  lr_RC
  unsigned zero:1;      // Local version of non terminal options
  unsigned repeat:1;    // Local version of non terminal options
  unsigned optional:1;  // Local version of non terminal options
  unsigned secondary:1; // Local version of non terminal options
  LR_NT   *nt;          // Non terminal symbol
  Xl       lr_rc;       // Rule components in LR
  long     rcs;         // Rule component number
  LR_T    *t;           // Terminal symbol
  struct   LR_A *action;// Action associated with this rule component
  Xl       rc;          // Rule component list
  long     line_number;      // Source line number
 } LR_RC;


typedef    struct LR2_RC    // Condensed Rule component
 {lr_RC
  LR2_NT  *nt;              // Non terminal symbol
 } LR2_RC;

typedef    struct LR_S      // State in the LR(0) automaton
 {
#define lr_S                                            \
  long     states;           /* State number          */\
  LR_R    *reduce;           /* Reduce by this rule   */

  lr_S
  XT      *NT;               /* Non terminal actions  */
  XT      *t[lr_reductions]; /* Terminal actions tree */
  XT      *REACTION;         /* Reduction actions     */
  Xl       state;            // States list
  XT       BUNDLE;           // Bundle elements from this state by rule component number
  char    *expanded;         // Non terminals already expanded
  struct   LR_S *identify;   // First state with same bundle
  XV      *rc_expanded;      // Vector of expanded rule components
  unsigned complete:1;       // Expansion of this state has been completed
  unsigned required:1;       // State can be reached from start state
  unsigned error:1;          // State needs to be printed to help resolve errors
 } LR_S;

typedef    struct LR2_S      // Condensed state
 {lr_S
  XV      *NT;               /* Non terminal actions  */
  XV      *t[lr_reductions]; /* Terminal actions tree */
  XV      *REACTION;         /* Reduction actions     */
 } LR2_S;

typedef    struct LR_A       // Action from a state
 {
#define lr_A                                                           \
  char    *k;           /* Reduction state number - key              */\
  unsigned push:1;      /* Number of pushes after a reduction        */\
  unsigned repeat:2;    /* Repeat status                             */

  lr_A
  unsigned required:1;  // Action can be reached from start state
  LR_RC   *rc;          // Rule component used to create this action
  LR_S    *to;          // To state
  Xl       lr_a;        // Actions in LR
  LR_S    *from;        // From states
  Xt       action;      // Non terminal action tree in LR_S
  long     actions;     // Action number
 } LR_A;

typedef    struct LR2_A // Condensed action
 {lr_A
  LR2_RC  *rc;          // Rule component used to create this action
  LR2_S   *to;          // To state
 } LR2_A;

typedef    struct LR_At // Terminal action
 {
#define lr_At                                                          \
  char    *k;           /* Transition character                      */

  lr_At
  LR_S    *to;          // To state
  LR_A    *action;      // Action
  Xl       lr_at;       // Actions in LR
  Xt       t;           // Transition index
  unsigned required:1;  // Terminal action required
 } LR_At;

typedef    struct LR2_At// Condensed terminal action
 {lr_At
  LR2_S   *to;          // To state
 } LR2_At;

typedef    struct LR_B  // Rule component bundle.
 {LR_A    *action;      // Action generated by this bundle element
  LR_A    *reduce;      // Action used to reduce this bundle element
  LR_RC   *rc;          // Rule component generating this bundle element
  Xt       bundle;      // State bundle element, keyed by associated rule component number
  struct   LR_B *n, *p; // Next and previous bundle elements
 } LR_B;

typedef struct LR_PT    // Parse tree element
 {char   *t;            // Terminal text
  long    chars, lines; // Amount of spacing between items
  LR2_RC *rc;           // Rule component used to perform reduction
  char   *k;            // Key - parse tree node name
  Xl      Pl;           // Arrival order
  XL      PL;           // Arrival order list
 } LR_PT;

typedef struct LR_PS    // Parse stack element
 {LR2_S  *state;        // State
  LR_PT  *pt;           // Parse tree element
  char   *c;            // Character at which this parse stack entry was created
 } LR_PS;

typedef struct LR_SPACE // Spacing between items
 {long  chars, lines;   // Intervening characters and new lines
 } LR_SPACE;

typedef struct LR_P     // Parse results
 {LR2    *lr;           // LR parser definition
  LR_PT  *parse_tree;   // Parse tree
  M      *m;            // Memory used by the parse
  XT      T;            // Terminals found in the parsed text
  char   *text;         // Text to be parsed
  char   *path;         // Path to be used for file names
  char   *parse;        // File on which parse were printed
  char   *error;        // File on which errors were printed
  long    stack_size;   // Stack size
  long    pts;          // Number of parse tree elements
  LR_SPACE  space;      // Recorded space
  LR_SPACE  space2;     // Unrecorded space
  LR_PS (*stack)[];     // Parse stack
  M      *sm;           // Memory for stack
  LR_PS  *base,         // Base of stack
         *current,      // Current position in stack
         *top;          // Top of stack
  long    errors;       // Error count
  LR2_S  *error_state;  // State in which error was detected
  char   *error_text;   // Position in text at which error was detected
  XT      EXPECTED;     // Expected non terminals at error
  char   *next;         // Next characters
  XV     *V;            // Linearized access to parse tree
 } LR_P;

typedef struct LR_RCN   // Parse results
 {LR_RC  *rc;           // Rule component
  struct LR_RCN *next;  // Next rule component in this chain
  long   in;            // In circuit
 } LR_RCN;
/*
______________________________________________________________________________
Procedures
______________________________________________________________________________
*/
void   lr2_free             (LR2  *lr);
int    lr2_open             (LR2 **lr, char *ds);
LR2   *lr_condense          (LR   *lr);
void   lr_expected          (LR_P *p);
void   lr_free              (LR   *lr);
XV    *lr_linearize_tree    (LR_P *P);
long   lr_locate_string     (LR_P *p,  LR2_S **S, char  **C,   long r);
void   lr_open              (char *NAME, char *grammar, LR **Lr);
void   lr_parse_free        (LR_P *p);
void   lr_parse_open        (LR_P **P, LR2  *lr,  char  *text, char *path, long stack_size);
void   lr_print             (LR   *lr);
void   lr_print_error_text  (FILE *f,  char *c, char *e);
void   lr_print_parse       (LR_P *p);
void   lr_print_parse_tree  (LR_P *p,  LR_PT *pt, FILE *f);
void   lr_print_stack       (LR_P *p);
void   lr_print_state       (LR   *lr, LR_S  *S,  FILE *f);
void   lr_print_terminals   (          LR_PT *P,  FILE *f);
void   lr_reduce            (LR_P *p,  LR2_S **s, char **Sc, char **c);
long   lr_reduce_search     (LR_P *p,  LR2_S *S,  char  *C,  long   i);
void   lr_reduce_state      (LR   *lr, LR_S  *S,  LR_A  *A,  LR_S  *C, LR_S *c, char *text, long l);
int    lr_reduct            (void);
void   lr_relocate          (LR2  *lr, long r);
char  *lr_separator         (LR_SPACE *p, char *c);
void   lr_test              (char *g, char *t);

#endif