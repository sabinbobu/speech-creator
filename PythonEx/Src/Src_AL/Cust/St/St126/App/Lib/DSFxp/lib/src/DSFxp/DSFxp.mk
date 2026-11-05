# =============================================================================
#
#  FILE:
#    DSFxp.mk
#
#  DESCRIPTION:
#    Makefile to build the target's object library DSFxp.lib 
#
#    usage: dsmake -f DSFxp.mk 
#         [VERBOSE=ON]                  (enter verbose mode of make utility)
#         [-a]                          (rebuild all)
#         MCU=<string>                  directory name of the controller
#         COMPILER=<string>             directory name of the target compiler
#         COMP_ROOT=<string>            compiler's root directory
#         LIBNAME=<string>              name of library
#         DSFXP_SRC_PATH=<string>       directory name of the source code
#         DSFXP_LIB_PATH                directory name of the library (destination)
#
#  Copyright (c) 2013 dSPACE GmbH, Germany
#
#  $Revision: 1.2 $
# =============================================================================

# -----------------------------------------------------------------------------
# Evaluate VERBOSE mode
# -----------------------------------------------------------------------------

%ifdef VERBOSEFLAG
    .DEBUG_PRINT
    .DEBUG_RUN
    %exec dsmake.exe -V
    %exec dsmake.exe -V >CON
    %echo Running in VERBOSE mode for $(MAKEFILE) >CON
    %echo Please wait ... >CON
    %echo >CON
%else
    NL = >nul
%endif


# -----------------------------------------------------------------------------
# Define the start rule of the makefile
# -----------------------------------------------------------------------------

make_main : start_check $(LIBNAME).lib make_success;
clean     : cleanup make_success;

# -----------------------------------------------------------------------------
# Specifications for the hardware and software
# -----------------------------------------------------------------------------

# -----------------------------------------------------------------------------
# Specify additional flags
# -----------------------------------------------------------------------------
.OPTIONS : TargetQuoted
.OPTIONS : MacroQuoted
.NOLIBRARY :

# -----------------------------------------------------------------------------
# Tool definitions
# -----------------------------------------------------------------------------

# Compiler specific tools -----------------------------------------------------
CC = "$(COMP_ROOT)\ccrh850.exe"  # compiler
AS = "$(COMP_ROOT)\ccrh850.exe"  # assembler
AR = "$(COMP_ROOT)\ax.exe"      # library tool

# Environment settings for the compiler ---------------------------------------
%setenv TMPDIR = .
%setenv path = $(COMP_ROOT);$(path)

# -----------------------------------------------------------------------------
#  Compiler options
# -----------------------------------------------------------------------------

# Include directories ---------------------------------------------------------
COMP_INCLUDES = #No Need Of Compiler Includes Path


TL_INCLUDES   =     . \
                    "$(DSFXP_LIB_PATH)\Include" \
                    "$(DSFXP_LIB_PATH)" \
                    "$(DSFXP_SRC_PATH)\generic" \
                    "$(DSFXP_SRC_PATH)\$(MCU)\$(COMPILER)" 
                    
%include ..\target.common.mk
             
# Compiler options ------------------------------------------------------------
CC_OPTS =   $(CC_COMMON_OPTS) \
            -stderr=$(*,B).err                      # redirect error messages and warnings \
            -o "$(DSFXP_LIB_PATH)\DSFxp\$(*,B).o"   # specifies the output object file \
            -DTL_FRAME                              # compile sources for target simulation \
            $(LOG_DEF)                              # macro definition for data logging 

# Assembler options -----------------------------------------------------------
AS_OPTS =   $(AS_COMMON_OPTS) \
            -o "$(DSFXP_LIB_PATH)\DSFxp\$(*,B).o"    # specifies the output object file

# Librarian options ---------------------------------------------------
AR_OPTS  =          -rcv "$(DSFXP_LIB_PATH)\DSFxp\$(LIBNAME).lib"       # create an archive with symbol index and insert files



# =============================================================================
# Include library source file list(s)
# =============================================================================
SRCFILES_PATH=
SRC_DSFXP=
SRC_DSFXP_C=
SRC_DSFXP_A=

%include "$(DSFXP_SRC_PATH)\Generic\DSFxp\Src_DSFxp.mk"
%if "$(LIBNAME)" == "DSFxp_C"
   %include "$(DSFXP_SRC_PATH)\$(MCU)\$(COMPILER)\DSFxp_C\Src_DSFxp_C.mk"
%endif
%if "$(LIBNAME)" == "DSFxp_A"
   %include "$(DSFXP_SRC_PATH)\$(MCU)\$(COMPILER)\DSFxp_C\Src_DSFxp_C.mk"
   %include "$(DSFXP_SRC_PATH)\$(MCU)\$(COMPILER)\DSFxp_A\Src_DSFxp_A.mk"
%endif

# -----------------------------------------------------------------------------
#  Library specific definitions
# -----------------------------------------------------------------------------

# Source files for the library ------------------------------------------------
%foreach SRC in $(SRC_DSFXP)
    %set SRC_DSFXP_FILES1 += "$(DSFXP_SRC_PATH)\generic\DSFxp\$(SRC,F)"
%end
%foreach SRC in $(SRC_DSFXP_C)
    %set SRC_DSFXP_FILES2 += "$(DSFXP_SRC_PATH)\$(MCU)\$(COMPILER)\DSFxp_C\$(SRC,F)"
%end
%foreach SRC in $(SRC_DSFXP_A)
    %set SRC_DSFXP_FILES3 += "$(DSFXP_SRC_PATH)\$(MCU)\$(COMPILER)\DSFxp_A\$(SRC,F)"
%end
%do make_abort

SRC_DSFXP_FILES = \
	$(SRC_DSFXP_FILES1) \
	$(SRC_DSFXP_FILES2) \
	$(SRC_DSFXP_FILES3) \

   


# Assembly files for library --------------------------------------------------
ASM_FILES =                       # none
                
# -----------------------------------------------------------------------------
# Response files
# -----------------------------------------------------------------------------


# =============================================================================
# Don't change anything below this line ... !
# =============================================================================

# -----------------------------------------------------------------------------
#  Auxiliary variables
# -----------------------------------------------------------------------------

%foreach INC in $(COMP_INCLUDES) 
  %set INC_PATH += -I$(INC)
%end
%foreach INC in $(TL_INCLUDES) 
  %set INC_PATH += -I$(INC)
%end

# All object files ------------------------------------------------------------
OBJ_FILES =         $(ASM_FILES:.s=.o) \
                    $(SRC_DSFXP_FILES:.c=.o)
                    

# search path for header files included by the library ------------------------
.PATH.h = $(TL_INCLUDES)


# =============================================================================
#  Rules
# =============================================================================

# -----------------------------------------------------------------------------
# Library tool rule
# -----------------------------------------------------------------------------

$(LIBNAME).lib : $(OBJ_FILES)
    %echo ARCHIVING OBJECT FILE(S) ...

    %if %exist( "$(DSFXP_LIB_PATH)\DSFxp\ld.dld" ) 
      del "$(DSFXP_LIB_PATH)\DSFxp\ld.dld"
    %endif    
    # Object and Library files
    %foreach OBJ in $(OBJ_FILES)
      %echo $(DSFXP_LIB_PATH)\DSFxp\$(OBJ,F) >> "$(DSFXP_LIB_PATH)\DSFxp\ld.dld"
    %end
    --$(AR) $(AR_OPTS) "@$(DSFXP_LIB_PATH)\DSFxp\ld.dld"
    %if $(status) > 1
        %echo
        %echo ARCHIVING FAILED
        %do make_abort
    %endif
    
    %echo MOVING LIBRARY TO $(DSFXP_LIB_PATH)\$(LIBNAME).lib
    %if %exist( "$(DSFXP_LIB_PATH)\$(LIBNAME).lib" )
        del "$(DSFXP_LIB_PATH)\$(LIBNAME).lib"
    %endif
    copy "$(DSFXP_LIB_PATH)\DSFxp\$(LIBNAME).lib" "$(DSFXP_LIB_PATH)\$(LIBNAME).lib" $(NL)
 
    # Removing temporary files
    %if %exist("$(DSFXP_LIB_PATH)\DSFxp\$(LIBNAME).lib")
        del "$(DSFXP_LIB_PATH)\DSFxp\$(LIBNAME).lib"
    %endif
    %if %exist( "$(DSFXP_LIB_PATH)\DSFxp\ld.dld" ) 
      del "$(DSFXP_LIB_PATH)\DSFxp\ld.dld"
    %endif
    %foreach OBJ in $(OBJ_FILES)
       del "$(DSFXP_LIB_PATH)\DSFxp\$(OBJ,F)"
    %end
    %echo ARCHIVING FINISHED
       
# -----------------------------------------------------------------------------
# Rules for the Library
# -----------------------------------------------------------------------------

compile_library_src $(SRC_DSFXP_FILES,%.c=%.o) : $(SRC_DSFXP_FILES)
    %echo COMPILING $*.c
    # Removing temporary files
    %if %exist($(*,B).err)
      del $(*,B).err
    %endif
    --$(CC) $*.c $(CC_OPTS)

    %if $(status) != 0 
      %echo
      %echo COMPILING FAILED. See $(*,B).err for details
      @--type $(*,B).err
      %do make_abort
    %endif

    # Removing temporary files
    %if %exist("$(DSFXP_LIB_PATH)\DSFxp\$(*,B).s") 
        del "$(DSFXP_LIB_PATH)\DSFxp\$(*,B).s"
    %endif
    %if %exist("$(DSFXP_LIB_PATH)\DSFxp\$(*,B).lst") 
        del "$(DSFXP_LIB_PATH)\DSFxp\$(*,B).lst"
    %endif
    %if %exist("$(DSFXP_LIB_PATH)\DSFxp\$(*,B).d") 
        del "$(DSFXP_LIB_PATH)\DSFxp\$(*,B).d"
    %endif    
    %if %exist($(*,B).err) 
        del $(*,B).err
    %endif

assemble_library_asm $(ASM_FILES,%.s=%.o) : $(ASM_FILES)
    %echo ASSEMBLING $*.s
    --$(AS) $(AS_OPTS) $*.s 
    %if $(status) != 0 
        %echo
        %echo ASSEMBLING FAILED. See $(*,B).lst for details
        %do make_abort
    %endif
    # Removing temporary files
    %if %exist($(*,B).lst) 
        del $(*,B).lst
    %endif
    %if %exist($(*,B).err) 
        del $(*,B).err
    %endif


# -----------------------------------------------------------------------------
# Clean up rule
# -----------------------------------------------------------------------------

cleanup :
    %echo CLEANING LIBRARY DIRECTORY ...
    %foreach SRC in $(SRC_DSFXP_FILES)
        %if %exist($(SRC,B).s) 
            del $(SRC,B).s
        %endif
        %if %exist($(SRC,B).lst) 
            del $(SRC,B).lst
        %endif
        %if %exist($(SRC,B).err) 
            del $(SRC,B).err
        %endif
        %if %exist($(SRC,B).o) 
            del $(SRC,B).o
        %endif
    %end
    %foreach ASM in $(ASM_FILES)
        %if %exist($(ASM,B).lst) 
            del $(ASM,B).lst
        %endif
        %if %exist($(ASM,B).err) 
            del $(ASM,B).err
        %endif
        %if %exist($(ASM,B).o) 
            del $(ASM,B).o
        %endif
    %end
    %if %exist($(DSFXP_LIB_PATH)\$(LIBNAME).lib)
        del $($(DSFXP_LIB_PATH)\$(LIBNAME).lib
    %endif
    %if %exist($(LIBNAME).lib)
        del $(LIBNAME).lib
    %endif
    %echo CLEANING SUCCESSFUL

# -----------------------------------------------------------------------------
# Start rule (messages and checks)
# -----------------------------------------------------------------------------

start_check :
    %echo Compiler location           : $(COMP_ROOT)
    %echo Target source directory     : $(DSFXP_SRC_PATH)\generic
    %echo Current working directory   : $(CWD)
    %echo Current library             : $(LIBNAME)
    %echo ---------------------------------------------------------------------

    %if !%exist($(CC)) 
        %echo ERROR: The compiler executeable 
        %echo        $(CC,F)
        %echo        does not exist in directory
        %echo        $(CC,D)
        %echo        Please check the installation of the compiler package 
        %echo        and/or the belonging environment settings.
        %do make_abort
    %endif
    %if !%exist($(AS)) 
        %echo ERROR: The assembler executeable 
        %echo        $(AS,F)
        %echo        does not exist in directory
        %echo        $(AS,D)
        %echo        Please check the installation of the compiler package 
        %echo        and/or the belonging environment settings.
        %do make_abort
    %endif
    %if !%exist($(AR)) 
        %echo ERROR: The library tool executeable 
        %echo        $(AR,F) 
        %echo        does not exist in directory
        %echo        $(AR,D) 
        %echo        Please check the installation of the compiler package 
        %echo        and/or the belonging environment settings.
        %do make_abort
    %endif     
    %foreach SRC in $(SRC_DSFXP_FILES)
        %if !%exist($(SRC)) 
        	%echo ERROR: The source file
        	%echo        $(SRC)
    	    %echo        does not exist. Please generate code first and/or
    	    %echo        check the installation            
    	    %do make_abort
        %endif 
        %if $(SRC,E) != .c
            %echo ERROR: The source file
            %echo        $(SRC)
            %echo        must have the extension .c
            %do make_abort
        %endif
    %end
    %foreach ASM in $(ASM_FILES)
        %if !%exist($(ASM)) 
            %echo ERROR: The assembler file
            %echo        $(ASM)
            %echo        does not exist. Please generate code first and/or
            %echo        check the installation            
            %do make_abort
        %endif
        %if $(ASM,E) != .s
            %echo ERROR: The assembler file
            %echo        $(ASM)
            %echo        must have the extension .s
            %do make_abort
        %endif
    %end

# -----------------------------------------------------------------------------
# Standard message rules
# -----------------------------------------------------------------------------

make_success : 
        %echo
        %echo MAKE PROCESS SUCCEEDED
        %echo
        %abort 0

make_abort : 
        %echo
        %echo MAKE PROCESS ABORTED       
        %echo
        %abort 2

# -----------------------------------------------------------------------------
# Standard exit rule for make errors
# -----------------------------------------------------------------------------

.AFTER :
    %if %error
        %do make_abort
    %endif
