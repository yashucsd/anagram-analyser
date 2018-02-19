#
# Makefile for CSE 30 -- PA3
# You should not need to change anything in this file.
#

HEADERS		= pa3.h pa3Strings.h test.h

C_SRCS		= initAnagram.c loadDict.c upperCaseSortString.c \
		  usage.c findAnagrams.c pa3Globals.c printStats.c

EC_C_SRCS	= initAnagram.c loadDict.c upperCaseSortString.c \
		  findAnagramsEC.c usage.c pa3Globals.c printStats.c

EXE_C_SRCS	= main.c 

EXE_C_SRCS_EC	= mainEC.c 

ASM_SRCS	= isInBounds.s charCompare.s hash.s getTableIndex.s


C_OBJS			= $(C_SRCS:.c=.o)
ASM_OBJS		= $(ASM_SRCS:.s=.o)
EC_OBJ			= $(EC_C_SRCS:.c=.o)
EXE_C_OBJS		= $(EXE_C_SRCS:.c=.o)
EXE_C_OBJS_EC	= $(EXE_C_SRCS_EC:.c=.o)


TEST_BINS	= testhash testcharCompare testupperCaseSortString \
		  testgetTableIndex


OBJS		= $(C_OBJS) $(ASM_OBJS)
EC_OBJS		= $(EC_OBJ) $(ASM_OBJS)

EXE		= pa3
EXE_EC 		= pa3EC


GCC		= gcc
ASM		= $(GCC)
LINT		= lint


GCC_FLAGS	= -c -g -W -Wall -D__EXTENSIONS__ -std=c99
LINT_FLAGS1	= -c -err=warn
LINT_FLAGS2	= -u -err=warn
ASM_FLAGS	= -c -g
LD_FLAGS	= -g -W -Wall


#
# Standard rules
#

.s.o:
	@echo "Assembling each assembly source file separately ..."
	$(ASM) $(ASM_FLAGS) $<
	@echo ""

.c.o:
	@echo "Linting each C source file separately ..."
	$(LINT) $(LINT_FLAGS1) $<
	@echo ""
	@echo "Compiling each C source file separately ..."
	$(GCC) $(GCC_FLAGS) $<
	@echo ""

#
# Simply have our project target be a single default $(EXE) executable.
#

$(EXE):	$(EXE_C_OBJS) $(OBJS)
	@echo "2nd phase lint on all C source files ..."
	$(LINT) $(LINT_FLAGS2) *.ln
	@echo ""
	@echo "Linking all object modules ..."
	$(GCC) -o $(EXE) $(LD_FLAGS) $(EXE_C_OBJS) $(OBJS)
	@echo ""
	@echo "Done."

#
# Simply have our project target be a single default $(EXE) executable.
#

$(EXE_EC):	$(EXE_C_OBJS_EC) $(EC_OBJS)
	@echo "2nd phase lint on all C source files ..."
	$(LINT) $(LINT_FLAGS2) *.ln
	@echo ""
	@echo "Linking all object modules ..."
	$(GCC) -o $(EXE_EC) $(LD_FLAGS) $(EXE_C_OBJS_EC) $(EC_OBJS)\
	 $(HEADERS_EC)
	@echo ""
	@echo "Done."

${EC_OBJS}:      ${HEADERS_EC}


${C_OBJS}:      ${HEADERS}


clean:
	@echo "Cleaning up project directory ..."
	/usr/bin/rm -f *.o $(EXE) $(EXE_EC) *.ln core a.out ${TEST_BINS}
	@echo ""
	@echo "Clean."

# --- Test for hash ---
testhash: ${HEADERS} hash.o testhash.o
	@echo "Compiling testhash.c"
	gcc -o testhash $(LD_FLAGS) testhash.o hash.o pa3Globals.c
	@echo "Done."

# --- Test for charCompare ---
testcharCompare: ${HEADERS} charCompare.o testcharCompare.o
	@echo "Compiling testcharCompare.c"
	gcc -o testcharCompare $(LD_FLAGS) testcharCompare.o charCompare.o
	@echo "Done."

# --- Test for upperCaseSortString ---
testupperCaseSortString: ${HEADERS} upperCaseSortString.o charCompare.o\
			 testupperCaseSortString.o
	@echo "Compiling testupperCaseSortString.c"
	gcc -o testupperCaseSortString $(LD_FLAGS) testupperCaseSortString.o\
	 upperCaseSortString.o charCompare.o 
	@echo "Done."

# --- Test for getTableIndex ---
testgetTableIndex: ${HEADERS} getTableIndex.o testgetTableIndex.o hash.o \
		pa3Globals.c
	@echo "Compiling testgetTableIndex.c"
	gcc -o testgetTableIndex $(LD_FLAGS) getTableIndex.o \
		testgetTableIndex.o hash.o pa3Globals.c
	@echo "Done."

new:
	make clean
	make
