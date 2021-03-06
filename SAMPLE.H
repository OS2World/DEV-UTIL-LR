 

 #ifndef __SAMPLE_H
 #define __SAMPLE_H
 /*
  浜様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様融
  � Copyright (C) Transcendental Automation, 1993.                           �
  把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳超
  � SAMPLE.H                                                                 �
  把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳超
  � This file is used by all modules and contains all necessary definitions  �
  � and declarations                                                         �
  藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様夕
 */
 #include <io.h>
 #include <lrx.inc>
 #include <process.h>
 #include "sample.str"
 
 #define STACK_SIZE 1000                       // size of stack of automaton.
 
 typedef void(*LRSAF)(void*,SAMPLE_NPS*,LR_PT*);// type of semantic action.
 
 extern LRSAF cmd[SAMPLE_n]; //table of semantic action(LRSAF - LR Semantic Action Function).
 void  InitCmdTable();       //initialization of this table
 
 extern SAMPLE_NPS NTPS;      // nonterminal pointer set
 extern LR2      *grammar;   // Pointer to compiled grammar
 
 void    InitTable (void);   // see table.c for more information about these
 float   LookUp    (char*);  // functions.
 void    SetItem   (char*,float);
 void    FreeTable (void);
 
 void    InitFloatStack  (void);
 void    pushFloat		(float);
 float   popFloat		(void);
 void    FreeFloatStack  (void);
 
 #endif
   

