#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


#ifndef _ELF_PARSER_H
#define _ELF_PARSER_H

/*************************************
 * Structs.
 *************************************/

typedef enum {
    BIT_FORMAT_32 = 1,
    BIT_FORMAT_64
} bit_format_t;

typedef enum {
    ENDIANNES_BIG_ENDIAN = 1,
    ENDIANNES_LITTLE_ENDIAN
} endianness_t;



//elf_header_t
typedef struct {
    bit_format_t bit_format; 
    endianness_t data;      
    uint64_t entry;
} elf_header_t;


//section_t
typedef struct {
    uint8_t* section_data;
    uint64_t size;
    char* name;
    uint64_t address;
} section_t;


//program_t
typedef struct {
    uint8_t* program_data;
    uint64_t vaddr;
    uint64_t filesz;
    uint64_t memsz;
} program_t;


//elf_file_t
typedef struct {
    elf_header_t elf_header;

    // Program headers.
    size_t program_count;
    program_t *programs;

    // Section headers.
    size_t section_count;
    section_t *sections;
} elf_file_t;



/*************************************
 * Functions.
 *************************************/

/**
 * This function will parse the given buffer as an elf file of size "file_size" and will allocate a buffer
 * onto the pointer "o_file" and return the representation of the elf file using "o_file".
 *
 * @param file         The elf file to read the data from.
 * @param o_elf        Pointer to a parsed elf struct.
 */
int elf_parser_parse(FILE *file, elf_file_t *o_elf);

/**
 * Releases the memory allocated by elf_parser_parse.
 * 
 * @param file          Pointer to the allocated file.
 */
void elf_parser_free(elf_file_t *file);

#endif // _ELF_PARSER_H