#   
#	File name		: Makefile
#	Date			: 
#	Version			: 
#	Author			: 
#

DEST			= .

HDRS			= global.hpp				\
			  preprocess/init_parameters.hpp	\
			  preprocess/initial_condition.hpp	\

LIBS			=	

INPS			=	

COMPILER		= g++ 

OPTFLAG			= -std=c++11 -O2

MAKEFILE		= Makefile


PROGRAM			= Conservative_Duct

SRCS			= main.cpp					\
			  preprocess/init_parameters.cpp	\
			  preprocess/initial_condition.cpp	\

OBJS			= $(SRCS:.cpp=.o) 	

.cpp.o:
			$(COMPILER) $(OPTFLAG) -c $*.cpp -o $*.o 

all:			$(PROGRAM)

$(PROGRAM):		$(OBJS) $(LIBS)
			@echo -n "Loading Program $(PROGRAM) ... "
			@$(COMPILER) $(OPTFLAG) $(LDFLAGS) $(OBJS) $(LIBS) -o $(PROGRAM)
			@echo "done"

clean:;			@rm -f $(SRCS:.cpp=.o) $(SRCS:.cpp=.il) $(PROGRAM)


