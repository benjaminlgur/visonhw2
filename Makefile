########################################
##
## Makefile
## LINUX compilation 
##
##############################################





#FLAGS
C++FLAG = -g -std=c++11

MATH_LIBS = -lm

EXEC_DIR=.


.cc.o:
	g++ $(C++FLAG) $(INCLUDES)  -c $< -o $@


#Including
INCLUDES=  -I. 

#-->All libraries (without LEDA)
LIBS_ALL =  -L/usr/lib -L/usr/local/lib 

#Programs

Cpp_OBJ=image.o image_demo.o
Cpp_OBJ_1 = image.o p1.o
Cpp_OBJ_2 = image.o p2.o

PROGRAM_NAME=image_demo
PROGRAM_1_NAME=p1
PROGRAM_2_NAME=p2

$(PROGRAM_NAME): $(Cpp_OBJ)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(Cpp_OBJ) $(INCLUDES) $(LIBS_ALL)

$(PROGRAM_1_NAME): $(Cpp_OBJ_1)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(Cpp_OBJ_1) $(INCLUDES) $(LIBS_ALL)

$(PROGRAM_2_NAME): $(Cpp_OBJ_2)
	g++ -g $(C++FLAG) -o $(EXEC_DIR)/$@ $(Cpp_OBJ_2) $(INCLUDES) $(LIBS_ALL)

all: $(PROGRAM_NAME) $(PROGRAM_1_NAME) $(PROGRAM_2_NAME) 


clean:
	(rm -f *.o; rm image_demo; rm p1; rm p2)

(:
