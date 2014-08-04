########################################
##
## Makefile
## LINUX compilation 
##
##############################################





#FLAGS
C++FLAG = -g -Wall

#Math Library
MATH_LIBS = -lm
EXEC_DIR=.





#Rule for .cpp files
# .SUFFIXES : .cpp.o 

.cpp.o:
	g++ $(C++FLAG) $(INCLUDES)  -c $< -o $@




#Including
INCLUDES=  -I. 


LIBS_ALL =  -L/usr/lib -L/usr/local/lib $(MATH_LIBS) 

#FIRST PROGRAM
ALL_OBJ1=Verma_Main_1.o
PROGRAM_1=Hash1Test
$(PROGRAM_1): $(ALL_OBJ1)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(ALL_OBJ1) $(INCLUDES) $(LIBS_ALL)

#SECOND PROGRAM
ALL_OBJ2=Verma_Main_2.o
PROGRAM_2=Hash2Test
$(PROGRAM_2): $(ALL_OBJ2)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(ALL_OBJ2) $(INCLUDES) $(LIBS_ALL)

#THIRD PROGRAM
ALL_OBJ3=Verma_Main_3.o
PROGRAM_3=spellcheck
$(PROGRAM_3): $(ALL_OBJ3)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(ALL_OBJ3) $(INCLUDES) $(LIBS_ALL)

#FOURTH PROGRAM
ALL_OBJ4=Verma_Main_4.o
PROGRAM_4=spellcheck2
$(PROGRAM_4): $(ALL_OBJ4)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(ALL_OBJ4) $(INCLUDES) $(LIBS_ALL)


#Compiling all

all: 
	make $(PROGRAM_1)
	make $(PROGRAM_2)
	make $(PROGRAM_3)
	make $(PROGRAM_4)
	
#Clean obj files

clean:
	(rm -f *.o;)


