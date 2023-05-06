CFLAGS = -g -c -Winit-self -Wredundant-decls -Wundef -Wfloat-equal -Winline \
		 -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default \
 		 -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wconversion -Wctor-dtor-privacy \
		 -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers \
		 -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing \
		 -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE

EXE_FLAG = valgrind -s --leak-check=yes --show-leak-kinds=all --log-file="valgrind_log.txt"

CC = g++

DIR_ASM = ./ASM/
DIR_CPU = ./CPU/
DIR_STACK = ./STACK/
DIR_DISASM = ./DISASM/

TARGET = PROCESSOR 

all : Make_ASM Make_CPU

Make_ASM: 
	cd $(DIR_ASM) && make

Make_CPU:
	cd $(DIR_CPU) && make

Make_DISASM:
	cd $(DIR_DISASM) && make

clean_obj:
	cd $(DIR_ASM) && make clean /
	cd $(DIR_CPU) && make clean /
	cd $(DIR_DISASM) && make clean











