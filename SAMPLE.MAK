 #ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
 #บ Copyright (C)  Transcendental Automation ,1993.                          บ
 #วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
 #บ SAMPLE.MAK                                                               บ
 #วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
 #บ This makefile create program 'sample.exe' which is an example of         บ
 #บ usage of LR. Sample.exe is a simple interpreter. The syntax of input     บ
 #บ language of it is discribed in file sample.gr.                           บ
 #ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
 
LRDIR = .

CC=ICC -c -Ss -I$(LRDIR)
LINK=LINK386 /W /PM:VIO /NOE
LRP=$(LRDIR)\LRP.EXE
 
SAMPLE.EXE : SAMPLE.OBJ TABLE.OBJ COMMANDS.OBJ
         $(LINK) SAMPLE.OBJ+TABLE.OBJ+COMMANDS.OBJ, SAMPLE.EXE, NUL, $(LRDIR)\LRX.LIB;
 
SAMPLE.OBJ : SAMPLE.C SAMPLE.H SAMPLE.STR
         $(CC)  SAMPLE.C
 
TABLE.OBJ : TABLE.C SAMPLE.H
         $(CC)  TABLE.C
 
COMMANDS.OBJ : COMMANDS.C SAMPLE.H SAMPLE.STR
         $(CC) COMMANDS.C
 
SAMPLE.STR : SAMPLE.GR
         $(LRP) SAMPLE.GR
