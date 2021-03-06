 

 #include "sample.h"
 /*
  浜様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様融
  � Copyright (C) Transcendental Automation, 1993.                             �
  把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳超
  � SAMPLE.C - The main file of project.                                       �
  把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳超
  � This file contains next functions:                                         �
  �                                                                            �
  � void main(void)                                                            �
  � void InitAll(char *s) - Initialize all resources and load file passed as   �
  �                         first argument of prgram or (if nothing was passed �
  �                         to programm) 'sample.txt'.                         �
  �                                                                            �
  � void FreeAll(void)   - Rlease all resources                                �
  把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳超
  � Description of program:                                                    �
  � This program is an interpreter of simple grammar.                          �
  � First program initialize stack of float , vartable ,load compiled grammar  �
  � and so on. Then it launch parsing of the text contained in file passed as  �
  � argument or 'sample.txt'.Then program free all allocated resources.        �
  藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様夕
 
 Requred files:
 
       TABLE.C
 
       COMMANDS.C
 
       SAMPLE.H
 
       SAMPLE.MAK
 
       SAMPLE.GR
 
  */
 
 LRSAF cmd[SAMPLE_n];
 SAMPLE_NPS NTPS;             // nonterminal pointer set
 LR2      *grammar;          // Pointer to compiled grammar
 
 void    InitAll(char *);
 void    FreeAll();
 char    *parse_text;              // text to parse
 
 /*
 ___________________________________________________________________________
  The main function
 ___________________________________________________________________________
 */
 int main(int e,char **s)
  {puts("Copyright (C) Transcendental Automation, 1993.");
   if(s[1]==0)
     puts("Usage : sample [input_file]");
   InitAll(s[1]);
   puts("Processing...");                                                                                                /**/
   lrx_parse(0,0,cmd,(LRX_PT*)&NTPS,grammar,parse_text,STACK_SIZE,0);//launch parsing of text
                                                       //then semantics action.                                                                                                /**/
   FreeAll();
 }
 /*
 ______________________________________________________________________________
  This function initializes all needed resources.
 ______________________________________________________________________________
 */
 void InitAll(char *name)
  {//initialize internal tables.
   InitTable       (); // initializing vartable.
   InitFloatStack  (); // initializing stack of floats.
   InitCmdTable    (); // initializing table of semantic actions.                                                                                               /**/
   lr2_open(&grammar,"sample.lrs"); //open compiled grammar
   parse_text = u_load_ds( name ? name : "sample.txt" );//load file to memory                                                                                                                                     /**/
   printf("Input file : %s\n",name ? name : "sample.txt");
   if(!parse_text)
    {puts("Error : unable to open input file.");
     exit(3452);
    }
   puts("Input text :");
   puts(parse_text);
  }
 
 /*
 ______________________________________________________________________________
  This function releases all allocated resources.
 ______________________________________________________________________________
 */
 
 void  FreeAll(void)                                                                              /**/
  {u_free_ds(parse_text);    // free alocated memory
   lr2_free(grammar);  // release compiled grammar                                                                                 /**/
   FreeTable       (); // free vartable.
   FreeFloatStack  (); // freestack of floats

  }
 

