all: a.out

a.out: main.c elf_parser.c
	gcc main.c elf_parser.c

