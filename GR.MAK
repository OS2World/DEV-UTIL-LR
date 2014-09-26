#-----------------------------------------------------------------------------
# GR.MAK - Make file to make grammars
#
# Serge Kovalyov, February 1993
#-----------------------------------------------------------------------------

#-----------------------------------------------------------------------------
#                  PART 1 - define grammar and text
#
#            Edit this part when choosing another grammar
#-----------------------------------------------------------------------------


# Grammar name - if absents, no make at all

GR = C:\LR\LR_SQL
# Text name - if commented out by #, then only compile grammar

#TEXT = C:\LR\LR_SQL.TXT

#-----------------------------------------------------------------------------
#                  PART 2 - path to LRP compiler/parser
#
#                     Edit this part when installing LRP
#-----------------------------------------------------------------------------

LRP_DIR = C:\LR


#-----------------------------------------------------------------------------
#            PART 3 - invoke makefile to make grammar and/or parse text
#
#                    Do not edit this part
#-----------------------------------------------------------------------------

!CMDSWITCHES +S
!IFDEF LRP_DIR
!INCLUDE <$(LRP_DIR)\GRP.MAK>
!ELSE
ERR:
        echo Fatal error U1050: failed to find path to LRP compiler/parser
!ENDIF
