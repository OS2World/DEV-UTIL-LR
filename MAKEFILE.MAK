 

 #-----------------------------------------------------------------------------
 # MAKEFILE - Make file to make grammars
 #
 # Copyright (C) Transendental Automation, 1993.
 #
 # Type 'make.exe' or 'nmake.exe' to use it or use another tools that can work
 # with make files ( for example IBM WorkFrame/2 ).
 # See notes below for understanding of work of this make file.
 # We hope there is all that you need for compiling your grammars and parsing
 # your text no more no less.
 #-----------------------------------------------------------------------------
 
 
 #-----------------------------------------------------------------------------
 #                  PART 1 - define grammar and text
 #
 #            Edit this part when choosing another grammar
 #-----------------------------------------------------------------------------
 
 
 #-----------------------------------------------------------------------------
 # Grammar name - if absents, no make at all.
 #
 # This name will be used as name + '.' + extension of input and
 # output files. So,in this case, the GDL file is 'sample.gr'
 # compiled grammar will be named as 'sample.lrs' and parse results
 # will be named as 'sample.prs', this name also will be used in
 # names of structures and constants in 'sample.str' and 'sample.n'
 # files
 #-----------------------------------------------------------------------------
 
 GR = sample
 
 #-----------------------------------------------------------------------------
 # Text name - if commented out by #, then only compile grammar
 # You can also set it with any name of file that you want to parse.
 # For example :
 # TEXT = ASD.YYT
 #-----------------------------------------------------------------------------
 
 TEXT = $(GR).txt
 
 #-----------------------------------------------------------------------------
 #                  PART 2 - path to LRP compiler/parser
 #
 #                     Edit this part when installing LRP
 # Here must be full path without '\' at end where is placed program 'lrp.exe'
 # that is used to compile grammar and parse input files .
 #-----------------------------------------------------------------------------
 
 LRP_DIR = .
 
 #-----------------------------------------------------------------------------
 #            PART 3 - making grammar and/or parse text
 #
 #                    Do not edit this part
 #-----------------------------------------------------------------------------
 
 !CMDSWITCHES +S
 !IFDEF LRP_DIR
 
 úSUFFIXES: .gr .lrs .prs
 
 {.}.gr.lrs:
         $(LRP_DIR)\LRP.EXE $*.gr
 
 !IFDEF GR
 
 !IFDEF TEXT
 $(GR).prs:      $(GR).lrs $(TEXT)
         $(LRP_DIR)\LRP.EXE $**
 !ENDIF
 
 $(GR).lrs:      $(GR).gr
 
 
 !ENDIF
 
 !ELSE
 ERR:
         echo Fatal error U1050: failed to find path to LRP compiler/parser
 !ENDIF
   

