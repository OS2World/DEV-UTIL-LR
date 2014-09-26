 

 #include "sample.h"
 #include <malloc.h>
 /*
  ÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»
  º Copyright (C) Transcendental Automation, 1993.                             º
  ÇÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¶
  º TABLE.C                                                                    º
  º This file contains sourse code of functions:                               º
  ÇÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¶
  º Work with table of variables                                               º
  º      void    InitTable (void)    - initialize vartable.                    º
  º      float   LookUp    (char* nm) - search in vartable variable with name  º
  º                                     'nm' if not found create new variabe inº
  º                                     vartable and set it with zero.         º
  º                                                                            º
  º      void    AddItem   (char*t,float f) - add new var named 'nm'to vartableº
  º                                           and set it with 'f'.             º
  º      void    SetItem   (char* t,float f) - set var named 'nm' with 'f'.    º
  º      void    FreeTable (void)            - free resources allocated by     º
  º                                            vartable                        º
  ÇÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¶
  º Work with stack of floats                                                  º
  º      void    pushFloat       (float f) - put 'f' to stack                  º
  º      float   popFloat        (void)    - get 'f' from stack                º
  º      void    FreeFloatStack  ()        - free stack                        º
  º      void    InitFloatStack  ()        - initialize stack                  º
  ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼
  */
 /*
 _____________________________________________________________________________
  VARTABLE SECTION
 _____________________________________________________________________________
 */
 /*
 _____________________________________________________________________________
  The structure 'VarTableItem' represents element of vartable.
 _____________________________________________________________________________
 */
 
 struct VarTableItem
  {char* name;                   // the name of variable
   float val;                    // the value of variable
   struct VarTableItem *next;    // pointer to next variable
  };
 
 static struct VarTableItem* FList; //pointer to the first variable in the table.
 
 /*
 ______________________________________________________________________________
  Initialize vartable
 ______________________________________________________________________________
  */
 void    InitTable (void)
  {FList = 0;
  }
 
 void    AddItem   (char*t,float f);
 /*
 _____________________________________________________________________________
  Look up variable in the vartable and return its value if found or
  add variable with value 0 to vartable and return 0.
 _____________________________________________________________________________
 */
 float   LookUp    (char* nm)
  {struct VarTableItem *cur;
   cur = FList;
   while ( cur && stricmp(cur->name,nm) )
     cur = cur -> next;
 
   if ( cur == 0)
    {AddItem(nm,0);
     return 0;
    }
   else
    return cur->val;
  }
 /*
 _____________________________________________________________________________
  Add item to vartable.
 _____________________________________________________________________________
 */
 void    AddItem   (char*t,float f)
  {struct VarTableItem *cur = malloc(sizeof(struct VarTableItem));
   cur->next   = FList;
   cur->name   = strdup(t);
   strupr(cur->name);
   cur->val    = f;
   FList = cur;
  }
 /*
 _____________________________________________________________________________
  Set item named 't' with f
 _____________________________________________________________________________
 */
 void    SetItem   (char* t,float f)
  {struct VarTableItem *cur = FList;
   while ( cur && stricmp(cur->name,t) )   cur = cur -> next;
   if ( cur == 0)
     AddItem(t,f);
   else
     cur->val = f;
  }
 /*
 _____________________________________________________________________________
  Release memory allocated by vartable and print results of calculations
 _____________________________________________________________________________
 */
 void    FreeTable (void)
  {struct VarTableItem *cur = FList ,*x;
   puts("Calculations has been finished.");
   puts("Results:");
   puts("Name         Value.");
   while ( cur )
    {x=cur;
     cur = cur -> next;
     printf("%-12.12s %g\n",x->name,x->val);
     free (x);
    }
   FList = 0;
  }
 
 /*
 _____________________________________________________________________________
  FLOAT STACK SECTION
 _____________________________________________________________________________
 */
 
 /*
 _____________________________________________________________________________
  The structure represent a item of float stack.
 _____________________________________________________________________________
 */
 
 static struct FLOAT_EL
  {float val;             // value of the item
   struct FLOAT_EL *next; // pointer to the next item
  } *FStack;              // pointer to the top of the stack
 
 /*
 ______________________________________________________________________________
  Initialize the stack of floats
 ______________________________________________________________________________
 */
 void    InitFloatStack  ()
  {FStack = 0;
  }
 /*
 ______________________________________________________________________________
  Push float 'f' to the stack.
 ______________________________________________________________________________
 */
 void    pushFloat       (float f)
  {struct FLOAT_EL *cur = malloc(sizeof(struct FLOAT_EL));
   cur->next   = FStack;
   cur->val    = f;
   FStack      = cur;
  }
 
 /*
 ______________________________________________________________________________
  Pop float from the stack.
 ______________________________________________________________________________
 */
 float   popFloat        (void)
  {if(FStack)
    {struct FLOAT_EL *cur;
     float r;
     r=FStack->val;
     cur = FStack->next;
     free(FStack);
     FStack = cur;
     return r;
    }
   puts("\'popFloat\':The Stack is empty");
   exit(666);
   return 0;
  }
 /*
 _____________________________________________________________________________
  if the stack is not empty free it.
 _____________________________________________________________________________
 */
 void    FreeFloatStack   ()
  {struct FLOAT_EL *cur = FStack ,*x;
   while ( cur )
    {x=cur;
     cur = cur -> next;
     free (x);
    }
   FStack = 0;
  }
   

