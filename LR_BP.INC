/*
_______________________________________________________________________________
Debug mode of LR parsing.
Serge Kovalyov, March 1993.
_______________________________________________________________________________
*/

#ifndef LR_BP_INC
#define LR_BP_INC

#include "lr.inc"

/*
_______________________________________________________________________________
Types
_______________________________________________________________________________
*/

// Breakpoint state constants

typedef enum
 {bp_default,
  bp_shift_primary,
  bp_reduction_primary,
  bp_reduction_primary_n,
  bp_shift_secondary,
  bp_reduction_secondary,
  bp_reduction_secondary_n
 } LR_BPTS;

// Breakpoint set

typedef struct LR_BP
 {LR2   *lr;                        // Condensed grammar
  char  *text;                      // Text to be parsed
  char  *file;                      // Name of file containing text
  LR_P  *lp;                        // Parse results

  // Array of breakpoints

  long   bpts;                      // Number of breakpoints
  long   bptc;                      // Work breakpoint counter
  struct LR_BPT *bpt_start;         // Start breakpoint handler
  struct LR_BPT *bpt_eof;           // End of text breakpoint handler
  struct LR_BPT *bpt_err;           // Error breakpoint handler
  struct LR_BPT *bpt_set;           // Pointer to an array of breakpoints

  // User semantics

  void (*cmd)();                    // User-defined semantics for all active breakpoints
  void  *user;                      // User-defined pointer (for breakpoint semantics)
 } LR_BP;

// Breakpoint handler

typedef struct LR_BPT
 {LR_BP *bp;                        // Breakpoint set to which this breakpoint belongs

  // User semantics

  LR_PT *pt;                        // Parse tree node on which break occurs
  void (*cmd)();                    // Semantic routine to be executed at a break

  // Break control flags

  unsigned  isactive  : 1;          // Whether the breakpoint is active
  unsigned  stop_here : 1;          // Whether to return control to caller at a break
  unsigned  isstart   : 1;          // Is start breakpoint
  unsigned  iseof     : 1;          // Is end of text break
  unsigned  iserr     : 1;          // Is error break

  // Break context - serves to correctly continue parsing after a break

  char     *C;                      // Text parsed from previous break
  char     *c;                      // Text to be parsed after break
  char     *Cc;                     // Pointer to currently located string
  LR2_S    *S;                      // LR automaton state at which break occurs
  LR_BPTS   state;                  // Breakpoint state
  long      n;                      // Breakpoint reduction counter
 } LR_BPT;

/*
_______________________________________________________________________________
Macros
_______________________________________________________________________________
*/

// Set a field of a breakpoint handler

#define lr_bp_field(_BP, _n, _field, _value)   ((_BP)->bpt_set[_n]._field = (_value))

// Obtain number of a breakpoint

#define lr_bp_n(_BPT)                          ((_BPT) - (_BPT)->bp->bpt_set)

// Scan breakpoint set (work counter is (_BP)->bptc)

#define lr_bp_do(_BP)                          for ((_BP)->bptc = 0; (_BP)->bptc < (_BP)->bpts; (_BP)->bptc++)

// Obtain pointer to predefined breakpoint

#define lr_bp_bpt(_BP, NAME)                   ((_BP)->bpt_##NAME)

// Set/clear breakpoint control fields

#define lr_bp_active_on(_BP, _n)           lr_bp_field(_BP, _n, isactive,   1)
#define lr_bp_active_off(_BP, _n)          lr_bp_field(_BP, _n, isactive,   0)
#define lr_bp_stop_on(_BP, _n)             lr_bp_field(_BP, _n, stop_here,  1)
#define lr_bp_stop_off(_BP, _n)            lr_bp_field(_BP, _n, stop_here,  0)
#define lr_bp_start_on(_BP, _n)            lr_bp_field(_BP, _n, isstart,    1)
#define lr_bp_start_off(_BP, _n)           lr_bp_field(_BP, _n, isstart,    0)
#define lr_bp_eof_on(_BP, _n)              lr_bp_field(_BP, _n, iseof,      1)
#define lr_bp_eof_off(_BP, _n)             lr_bp_field(_BP, _n, iseof,      0)
#define lr_bp_error_on(_BP, _n)            lr_bp_field(_BP, _n, iserr,      1)
#define lr_bp_error_off(_BP, _n)           lr_bp_field(_BP, _n, iserr,      0)

#define lr_bp_switch_on(_BP, _n)           lr_bp_active_on(_BP, _n),  lr_bp_stop_on(_BP, _n)
#define lr_bp_switch_off(_BP, _n)          lr_bp_active_off(_BP, _n), lr_bp_stop_off(_BP, _n)

// Set/clear semantic action
// Note: the prototype for a semantic action is 'void _cmd(LR_BPT *)'

#define lr_bp_command_on(_BP, _n, _cmd)    lr_bp_field(_BP, _n, cmd, (void (*)())(_cmd))
#define lr_bp_command_off(_BP, _n)         lr_bp_command_on(_BP, _n, 0)
#define lr_bp_command_active(_BP, _n, _cmd)    lr_bp_command_on(_BP, _n, _cmd), lr_bp_active_on(_BP, _n)
#define lr_bp_command_start(_BP, _cmd)     lr_bp_bpt(_BP, start)->cmd = (void (*)())(_cmd)
#define lr_bp_command_eof(_BP, _cmd)       lr_bp_bpt(_BP, eof)  ->cmd = (void (*)())(_cmd)
#define lr_bp_command_err(_BP, _cmd)       lr_bp_bpt(_BP, err)  ->cmd = (void (*)())(_cmd)

// Feed the brekpoint set by semantics; _CMDS is an array of semantic actions (its type is 'void (**)()')

#define lr_bp_feed(_BP, _CMDS)             lr_bp_do(_BP) lr_bp_command_on(_BP,     (_BP)->bptc, (void (**)())_CMDS+(_BP)->bptc)
#define lr_bp_feed_active(_BP, _CMDS)      lr_bp_do(_BP) lr_bp_command_active(_BP, (_BP)->bptc, (void (**)())_CMDS+(_BP)->bptc)

// Register a global breakpoint semantic action

#define lr_bp_register_command(_BP, _cmd)  {(_BP)->cmd = (void (*)())(_cmd);                  \
                                            lr_bp_do(_BP) lr_bp_active_on(_BP, (_BP)->bptc);  \
                                           }

// Go parsing from a break to specified breakpoint

#define lr_bp_go(_BPT_START, _n)           while(((_BPT_START) = lr_bp_next(_BPT_START)) && lr_bp_n(_BPT_START) != (_n) && !(_BPT_START)->iseof && !(_BPT_START)->iserr)

/*
_______________________________________________________________________________
Function prototypes
_______________________________________________________________________________
*/

/*
_______________________________________________________________________________
Initialize new breakpoint set by condensed grammar file
Argument:   grammar2 - name of file containing condensed grammar
Return:     pointer to new breakpoint set
            0 if file not found
_______________________________________________________________________________
*/

LR_BP *lr_bp_init(char *grammar2);

/*
_______________________________________________________________________________
Create new breakpoint set correspondent to a condensed grammar
Argument:   lr - condensed LR grammar (parse table)
Return:     pointer to new breakpoint set
Note:       by default, no breakpoint has a semantics; predefined breakpoints
            bpt_start, bpt_eof and bpt_err are active; bpt_eof and bpt_err
            are stop breakpoints
_______________________________________________________________________________
*/

LR_BP *lr_bp_create(LR2 *lr);

/*
_______________________________________________________________________________
Start parsing for a given text; stop on first active stop breakpoint
Arguments:  bp    - pointer to breakpoint set
            text  - null terminated charcter string of text to be parsed
Return:     pointer to first breakpoint encountered
Note:       if there were the results of previous parsing (field bp->lp is
            nonzero), the function at first releases them
_______________________________________________________________________________
*/

LR_BPT *lr_bp_start(LR_BP *bp, char *text);

/*
_______________________________________________________________________________
Perform a single reduction considering breakpoint(s)
Arguments:  bp    - pointer to breakpoint set
            S     - address of pointer to current LR state
            C     - pointer to text at which reduction starts
            c     - pointer to text at which reduction stops
            sc    - text parsed from the previous break
            s     - breakpoint state
            n     - breakpoint reduction counter
Return:     pointer to encountered breakpoint
            0 if reduction doesn't lead to break (correspondent breakpoint is
            inactive)
_______________________________________________________________________________
*/

LR_BPT *lr_bp_reduce(LR_BP *bp, LR2_S **S, char **C, char **c, char *sc, LR_BPTS s, long n);

/*
_______________________________________________________________________________
Go parsing from a breakpoint until next break
Argument:   bpt   - pointer to start breakpoint
Return:     pointer to next breakpoint encountered
_______________________________________________________________________________
*/

LR_BPT *lr_bp_next(LR_BPT *bpt);

/*
_______________________________________________________________________________
Free a breakpoint set
Argument:   bp    - pointer to breakpoint set
Return:     nothing
_______________________________________________________________________________
*/

void lr_bp_free(LR_BP *bp);

/*
_______________________________________________________________________________
Default error breakpoint semantics - print parse errors to GRAMMAR.ERR file
Argument:   bpt   - pointer to error breakpoint handler
Return:     nothing
Note:       this routine is recommended to be used in run-time semantics,
            e.g.:
                    lr_bp_command_err(bp, lr_bp_error);
_______________________________________________________________________________
*/

void lr_bp_error(LR_BPT *bpt);

/*
______________________________________________________________________________
Perform LR parse (override combination lr2_open()+lr_parse_open())
Arguments:  grammar2    - .LRS file with condensed grammar
            text        - text to be parsed
            file        - name of file containing text
Return:     pointer to parse results
            0 if condensed grammar was not found
______________________________________________________________________________
*/

LR_P *lr_bp_parse_open(char *grammar2, char *text, char *file);

/*
______________________________________________________________________________
Perform LR parse with run-time semantics
Arguments:  p           - address of pointer to parse results
            cmd         - array of run-time semantic fuctions
            lr          - condensed grammar
            text        - text to be parsed
            sysp        - pointer used to pass arguments to run-time semantics
Return:     nothing
______________________________________________________________________________
*/

void lr_bp_parse(LR_P **p, void (**cmd)(), LR2 *lr, char *text, void *sysp);

#endif
