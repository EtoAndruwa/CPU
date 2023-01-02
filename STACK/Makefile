CFLAGS = -g -c -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline \
		 -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default \
 		 -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy \
		 -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers \
		 -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing \
		 -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE

EXE_FLAG = valgrind -s --leak-check=yes --show-leak-kinds=all --log-file="valgrind_log.txt"

CC = g++
TARGET = Stack


PREF_OBJ = ./obj/
PREF_SRC = ./src/

SRC = $(wildcard $(PREF_SRC)*.cpp)
OBJ = $(patsubst $(PREF_SRC)%.cpp, $(PREF_OBJ)%.o, $(SRC))

all : clean $(TARGET) run_program open_files

$(TARGET) : $(OBJ) 
	$(CC) $(OBJ) -o $(TARGET).exe

$(PREF_OBJ)%.o : $(PREF_SRC)%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

run_program :
	$(EXE_FLAG) ./$(TARGET).exe 

open_files : 
	code ./valgrind_log.txt

clean : 
	rm $(TARGET).exe $(PREF_OBJ)*.o valgrind_log.txt Action_log_stack.txt
