#include "elf_parser.h"
#include <string.h>


typedef struct
{
    struct
    {
        uint8_t ei_mag[4];
        uint8_t ei_class;
        uint8_t ei_data;
        uint8_t ei_verion;
        uint8_t ei_osabi;
        uint8_t ei_abiversion;
        uint8_t ei_pad[7]
    } e_ident;
    uint16_t e_type;
    uint16_t e_machine;
    uint32_t e_version;
    uint64_t e_entry;
    uint64_t e_phoff;
    uint64_t e_shoff;
    uint32_t e_flags;
    uint16_t e_ehsize;
    uint16_t e_phentsize;
    uint16_t e_phnum;
    uint16_t e_shentsize;
    uint16_t e_shnum;
    uint16_t e_shstrndx;
} file_elf_header_t;

typedef struct {
    uint32_t sh_name;
    uint32_t sh_type;
    uint64_t sh_flags;
    uint64_t sh_addr;
    uint64_t sh_offset;
    uint64_t sh_size;
    uint32_t sh_link;
    uint32_t sh_info;
    uint64_t sh_addralign;
    uint64_t sh_entsize;
} file_section_header_t;

typedef struct
{
    uint32_t p_type;
    uint32_t p_flags;
    uint64_t p_offset;
    uint64_t p_vaddr;
    uint64_t p_paddr;
    uint64_t p_filesz;
    uint64_t p_memsz;
    uint64_t p_align;
} file_program_header_t;




// returns a string from file at offset (stops at null, I assume)
char* read_string_from_file(FILE* file, size_t offset) {
    char read_buff[128];
    long old_loc = ftell(file);
    fseek(file, offset, SEEK_SET);
    fscanf(file, "%s", read_buff);

    int len = strlen(read_buff) + 1;
    char* ret = malloc(len);
    memcpy(ret, read_buff, len);
    fseek(file, old_loc, SEEK_SET);
    return ret;
}

int elf_parser_parse(FILE* file, elf_file_t* o_file) {

    //read data from elf header into temporary struct (file_)
    file_elf_header_t* temp_file_header = malloc(sizeof(file_elf_header_t));
    fread(temp_file_header, sizeof(file_elf_header_t), 1, file);
    
    //allocate data to program and section headers, and than read from file into temporary structs (file_)
    file_section_header_t* temp_section_headers = malloc(temp_file_header->e_shnum * sizeof(file_section_header_t));
    file_program_header_t* temp_program_headers = malloc(temp_file_header->e_phnum * sizeof(file_program_header_t));
    fseek(file, temp_file_header->e_shoff, SEEK_SET);
    fread(temp_section_headers, temp_file_header->e_shnum * sizeof(file_section_header_t), 1, file);
    fseek(file, temp_file_header->e_phoff, SEEK_SET);
    fread(temp_program_headers, temp_file_header->e_phnum * sizeof(file_program_header_t), 1, file);


    //parse elf header data into elf_header_t struct inside of o_file
    o_file->elf_header.bit_format = temp_file_header->e_ident.ei_class; 
    o_file->elf_header.data = temp_file_header->e_ident.ei_data;      
    o_file->elf_header.entry = temp_file_header->e_entry;

    //parse program and section headers into o_file appropriate structs.
    o_file->program_count = temp_file_header->e_phnum;
    o_file->programs = malloc(o_file->program_count * sizeof(program_t));
    o_file->section_count = temp_file_header->e_shnum;
    o_file->sections = malloc(o_file->section_count * sizeof(section_t));
    
    
    
    //free memory
    
    
    
    
    

    
    
    
    
    
    
   
    

    

    for (int i = 0; i < o_file->section_count; i++){
        file_section_header_t section_header;
        fread(&section_header, sizeof(file_section_header_t), 1, file);
        o_file->sections[i].name = read_string_from_file(file, section_header.sh_name);
    }
   

    return 0;

}

void elf_parser_free(elf_file_t* file) {
    free(file->programs);
    
    free(file->sections);
}