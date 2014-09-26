 

 /*
  ษอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ Copyright (C) Transcendental Automation, 1993.                            บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ COMMANDS.C                                                                บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ This module contains the function that initializes semantic actions' tableบ
  บ and functions which define this semantic actions.All semantics action     บ
  บ work in the time of postfix traversal.                                    บ
  ศอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
 */
 #include "sample.h"
 #include <stdio.h>
 
 void ASSIGN_func     (void*,SAMPLE_NPS*,LR_PT*);
 void DIV_func        (void*,SAMPLE_NPS*,LR_PT*);
 void MUL_func        (void*,SAMPLE_NPS*,LR_PT*);
 void ADD_func        (void*,SAMPLE_NPS*,LR_PT*);
 void SUB_func        (void*,SAMPLE_NPS*,LR_PT*);
 void NEG_func        (void*,SAMPLE_NPS*,LR_PT*);
 void FLOAT_func      (void*,SAMPLE_NPS*,LR_PT*);
 void IDENTIFIER_func (void*,SAMPLE_NPS*,LR_PT*);
 /*
 _____________________________________________________________________________
  Initialize table of semantic actions
 _____________________________________________________________________________
 */
 void InitCmdTable()
  {int i;
   for(i=0;i<SAMPLE_n;i++) cmd [i] = 0;
   cmd[SAMPLE_ASSIGN_n]        = ASSIGN_func;
   cmd[SAMPLE_DIV_n]           = DIV_func;
   cmd[SAMPLE_MUL_n]           = MUL_func;
   cmd[SAMPLE_ADD_n]           = ADD_func;
   cmd[SAMPLE_SUB_n]           = SUB_func;
   cmd[SAMPLE_NEG_n]           = NEG_func;
   cmd[SAMPLE_FLOAT_n]         = FLOAT_func;
   cmd[SAMPLE_IDENTIFIER_n]    = IDENTIFIER_func;
  }
 
 /*
 ______________________________________________________________________________
  The function realize semantics of assign
 _____________________________________________________________________________
 */
 static void ASSIGN_func     (void* sysp, SAMPLE_NPS* NPS, LR_PT* pt)
  {LR_PT* zt = pt->PL.f->d;      // the RHS of rule ASSIGN contain 3 nonterminals
                                 // so the first son always exists.
                                 // 'pt->PL.f->d' means pointer to first son.
 
   if(zt->t && lrx_n(zt) == SAMPLE_IDENTIFIER_n) //test if first son is identifier
    {SetItem(zt->t,popFloat()); // the top of stack is value of expression
     popFloat();                // the top of stack is value of identifier before
                                // calculation.
    }
  }
 
 /*
 ______________________________________________________________________________
  The function realize semantics of division.
 _____________________________________________________________________________
 */
 static void DIV_func        (void* sysp, SAMPLE_NPS* NPS, LR_PT* pt)
  {float a = popFloat();
   if(a==0)
    {puts("Divide by zero.");
     exit(4);
    }
   pushFloat(popFloat()/a);
  }
 
 /*
 ______________________________________________________________________________
  The function realize semantics of multiplication
 _____________________________________________________________________________
 */
 static void MUL_func        (void* sysp, SAMPLE_NPS* NPS, LR_PT* pt)
  {pushFloat( popFloat() * popFloat() );
  }
 
 /*
 ______________________________________________________________________________
  The function realize semantics of addition
 _____________________________________________________________________________
 */
 static void ADD_func        (void* sysp, SAMPLE_NPS* NPS, LR_PT* pt)
  {pushFloat( popFloat() + popFloat() );
  }
 
 /*
 ______________________________________________________________________________
  The function realize semantics of subtraction
 _____________________________________________________________________________
 */
 static void SUB_func        (void* sysp, SAMPLE_NPS* NPS, LR_PT* pt)
  {pushFloat( - popFloat() + popFloat() );
  }
 
 /*
 ______________________________________________________________________________
  The function realize semantics of negation
 _____________________________________________________________________________
 */
 static void NEG_func        (void* sysp, SAMPLE_NPS* NPS, LR_PT* pt)
  {pushFloat( - popFloat());
  }
 
 /*
 ______________________________________________________________________________
  The function realize semantics of constant
 _____________________________________________________________________________
 */
 static void FLOAT_func      (void* sysp, SAMPLE_NPS* NPS, LR_PT* pt)
  {pushFloat(atof(pt->t));
  }
 
 /*
 ______________________________________________________________________________
  The function realize semantics of identifier
 _____________________________________________________________________________
 */
 static void IDENTIFIER_func (void* sysp, SAMPLE_NPS* NPS, LR_PT* pt)
  {pushFloat(LookUp(pt->t));
  }
   

