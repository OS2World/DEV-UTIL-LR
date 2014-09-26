
/*
______________________________________________________________________________
Example LR processing
Philip R Brenan, Transcendental Automation, 1993, CompuServe 71022,3620
______________________________________________________________________________
*/
#include "lrx.inc"           //01 Include this file in all parsing programs
#include "lr_sql.str"        //02 Generated declarations for SQL
#include "lr_sql.cc"         //03 Generated load procedures for SQL

lrx_cmd(lr_sql_print);       //04 Generic print routine for any non terminal
lrx_cmd(lr_sql_ts_options);  //05 Print routine for create tablespace options
/*
_______________________________________________________________________________
Parse the sql in LR_SQL.SQL and print each non terminal
_______________________________________________________________________________
*/
int main(void)               //06 Main procedure
 {LRX_REQ    r;              //07 Request structure to lrx_req
  LR_SQL_cmd cmd;            //08 Procedures to implement non terminals for SQL
  LR_SQL_NPS nps;            //09 Non terminal work area for SQL
  int        i, j;           //10 Counters

  r.pre  = cmd.pre;          //11 Initialize pointer to pre commands for SQL
  r.post = 0;                //12 No post commands
  r.nps  = &amp.nps;            //13 Initialize pointer to Non terminal Pointer Set work area for SQL
/*
_______________________________________________________________________________
Load print routine into each non terminal's pre command - must initialize each
semantic routine pointer, or set to zero.  r.post will be zero and hence ignored.
_______________________________________________________________________________
*/
  for(i = 0; i < LR_SQL_n; ++i)           //14 For each non terminal in SQL
   {cmd.pre[i] = lr_sql_print;            //15 Set print routine as semantic action
   }
  cmd.pre[LR_SQL_CREATE_TS_OPTIONS_n] = lr_sql_ts_options;
                                          //16 Load semantic action for specific non terminal
/*
_______________________________________________________________________________
Request parse of the sql in LR_SQL.SQL and print each non terminal
_______________________________________________________________________________
*/
  r.text_file    = "lr_sql.sql";          //17 Name the input filer
  r.grammar_file = "lr_sql.lrs";          //18 Name grammar file
  r.req          = lrx_req_load_grammar | //19 Load grammar
                   lrx_req_load_text    | //20 Load text
                   lrx_req_parse        | //21 Parse text with grammar
                   lrx_req_print_parse  | //22 Print parse tree
                   lrx_req_free_all;      //23 Free all parse resources
/*
_______________________________________________________________________________
Perform parse and exit
_______________________________________________________________________________
*/
  lrx_req(&amp.r);                           //24 Perform requests
 }
/*
_______________________________________________________________________________
Generic Semantic action
REQ - request list
PT  - Non terminal pointer
_______________________________________________________________________________
*/
lrx_cmd(lr_sql_print)                     //25 Generic print
 {printf("%s", PT->k);                    //26 Print non terminal name
  if (PT->t)                              //27 If non terminal has a value
    printf(" = %s", PT->t);               //28 Print associated value
  printf("\n");                           //29 New line
 }
/*
_______________________________________________________________________________
Put a non terminal - lrx_concat concatenates all the text under the given
non terminal
_______________________________________________________________________________
*/
void lr_sql_put(LR_PT *pt)                  //30 Put a non terminal
 {char   c[256];                            //31 Character buffer

  if (pt) printf("%s ", lrx_concat(c, pt)); //32 Print non terminal if present
 }
/*
_______________________________________________________________________________
CREATE_TS_OPTIONS semantic action.
Get addressability to non terminals beneath current non terminal, and print them

REQ - request list - from main procedure
PT  - Non terminal pointer
_______________________________________________________________________________
*/
lrx_cmd(lr_sql_ts_options)                   //33 Process CREATE_TS_OPTIONS non terminal
 {LR_SQL_NT_CREATE_TS_OPTIONS a;             //34 Pointers to this non terminal's immediate decendents

  LR_SQL_LOAD_NT_CREATE_TS_OPTIONS(&amp.a, PT); //35 Get addressability to non terminals dependents

  lr_sql_put(a.FREEPAGE);                    //36 Print FREEPAGE
  lr_sql_put(a.PCTFREE);                     //37 Print PCTFREE
  lr_sql_put(a.BUFFERPOOL3);                 //38 Print BUFFERPOOL
  lr_sql_put(a.LOCKSIZE);                    //39 Print LOCKSIZE
  lr_sql_put(a.CLOSE);                       //40 Print CLOSE
  printf("\n");                              //41 New line
 }


