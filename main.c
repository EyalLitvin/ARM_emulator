#include <stdlib.h>
#include <stdio.h>
#include "elf_parser.h"

int main(int argc, char* argv[]) {

    elf_file_t parsed_file;
    FILE* file = fopen("emulate_me_arm64.out", "rb");
    elf_parser_parse(file, &parsed_file);
    
    // TODO: Eyal - Print whatever you want to make sure that your code works!
    // GOOD LUCK
    // printf("this file is an %c%c%c file\n", parsed_file.elf_header->e_ident.ei_mag[1], parsed_file.elf_header->e_ident.ei_mag[2], parsed_file.elf_header->e_ident.ei_mag[3]);
    // printf("amount of program headers: %d\n", (int)parsed_file.program_headers_count);
    // printf("amount of section headers: %d\n", (int)parsed_file.section_headers_count);
    // if(parsed_file.elf_header->e_ident.ei_class == 1){
    //     printf("this file is of 32-bit format, ");
    // } else {
    //     printf("this file is of 64-bit format, ");
    // }
    // if(parsed_file.elf_header->e_ident.ei_data == 1){
    //     printf("and is of little endianness.\n");
    // } else {
    //     printf("and is of big endianness.\n");
    // }
    // printf("entry point is at %lx\n", parsed_file.elf_header->e_entry);
    // fclose(file); // Don't know which should come first.

    // for (int i = 0; i < parsed_file.section_headers_count; i++) {
    //     printf("Section: %s\n", parsed_file.section_headers[i].name);
    // }
    // elf_parser_free(&parsed_file);
    
    return 0;
}

