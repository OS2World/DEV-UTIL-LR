#-----------------------------------------------------------------------------
# GRP.MAK - Make file to make grammars (uses macros defined somewhere else)
#
# Serge Kovalyov, March 1993
#-----------------------------------------------------------------------------

!IFDEF LRP_DIR

.SUFFIXES:

.SUFFIXES: .gr .lrs .prs

{.}.gr.lrs:
        $(LRP_DIR)\LRP.EXE $*.gr

!IFDEF GR

!IFDEF TEXT
$(GR).prs:      $(GR).lrs $(TEXT)
        $(LRP_DIR)\LRP.EXE $**
!ENDIF

$(GR).lrs:      $(GR).gr

!ENDIF

!ENDIF