// File I/O
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <iomanip>

// ELF utils
#include <gelf.h>
#include <libelf.h>
// Include 32 bit unsigned integers
#include <stdint.h>

// Assertions
#include <assert.h>

// Command line options
#include <boost/program_options.hpp>
#include <boost/lexical_cast.hpp>

// Collect load segment headers
#include <vector>

static inline uint32_t toBigEndian(uint32_t value)
{
	return ((value & 0xFF000000) >> 24) | 
							((value & 0x00FF0000) >> 8) |
							((value & 0x0000FF00) << 8) |
						 ((value & 0xFF) << 24);
}

static void streamelf(const std::vector<std::string> filenames, const char* uart_filename, const int file_number)
{
  FILE* entry_file;
  std::string fn = uart_filename;
  fn = fn + "_entry";
  entry_file = fopen(fn.c_str(), "w");
  assert(entry_file);

  for (int j = 0; j < file_number; j++) {

    const char* elf_filename = filenames[j].c_str();
    // check libelf version
    elf_version(EV_CURRENT);

    // open elf binary
    int elf_file = open(elf_filename, O_RDONLY, 0);
    assert(elf_file > 0);

    Elf *elf = elf_begin(elf_file, ELF_C_READ, NULL);
    assert(elf);

    // check file kind
    Elf_Kind ek = elf_kind(elf);
    assert(ek == ELF_K_ELF);

    // check class
    int ec = gelf_getclass(elf);
    assert(ec == ELFCLASS32);

    // get elf header
    GElf_Ehdr hdr;
    GElf_Ehdr *tmphdr = gelf_getehdr(elf, &hdr);
    assert(tmphdr);

    // get program headers
    size_t n, i;
    int ntmp = elf_getphdrnum(elf, &n);
    assert(ntmp == 0);

    uint32_t entry = hdr.e_entry;
    uint32_t* entry_ptr = (uint32_t*) entry;
    uint32_t big_entry = toBigEndian(entry);
    std::cout << "[elf2uart] " << std::left << std::setw(10) << "ENTRY" << (void*)entry << std::endl;
  	
  	fprintf(entry_file, "%p", entry_ptr);
    
  	std::vector<GElf_Phdr> load_segments;

    for(i = 0; i < n; i++)
    {
      // get program header
      GElf_Phdr phdr;
      GElf_Phdr *phdrtmp = gelf_getphdr(elf, i, &phdr);
      assert(phdrtmp);

      if (phdr.p_type == PT_LOAD)
      {
  			load_segments.push_back(phdr);
  		}
  	}

  	int segments_number = load_segments.size();
  	std::cout << "[elf2uart] " << std::left << std::setw(10) << "SEGMENTS" << segments_number << std::endl;

  	uint32_t big_segments_number = toBigEndian(segments_number);
  	//fwrite(&big_segments_number, 4, 1, uart_file);

  	std::cout << "[elf2uart] " << std::left << std::setw(10) << "START" 
  																					<< std::setw(15) << "FILE SIZE" 
  																					<< std::setw(10) << "TOTAL SIZE" << std::endl;

    int segment_index = 0;
  	for(std::vector<GElf_Phdr>::iterator it = load_segments.begin(); it != load_segments.end(); ++it) 
  	{

      FILE* uart_file;
      std::string fn = uart_filename;
      fn = fn + "_sec" + boost::lexical_cast<std::string>(segment_index);
      uart_file = fopen(fn.c_str(), "w");
      assert(uart_file);

      segment_index++;
  		GElf_Phdr phdr = *it;

    	// some assertions
    	assert(phdr.p_vaddr == phdr.p_paddr);
    	assert(phdr.p_filesz <= phdr.p_memsz);

    	// allocate buffer
    	char *buf = (char*)malloc(phdr.p_filesz);
    	assert(buf);

    	// copy from the buffer into the main memory
    	lseek(elf_file, phdr.p_offset, SEEK_SET);
    	read(elf_file, buf, phdr.p_filesz);

    	uint32_t start_offset = phdr.p_vaddr;
    	uint32_t size = phdr.p_filesz;
    	uint32_t total_size = phdr.p_memsz;

  		std::cout << "[elf2uart] " << std::left << std::setw(10) << (void*) start_offset
  																						<< std::setw(15) << size
  																						<< std::setw(10) << total_size << "\n";

  		uint32_t big_start_offset = toBigEndian(start_offset);
  		uint32_t big_size = toBigEndian(size);

  		//fwrite(&big_start_offset, sizeof start_offset, 1, uart_file);
  		//fwrite(&big_size, sizeof size, 1, uart_file);
          
      int j;        
      for(j=0; j < size; j++)
      {
  			fwrite(&(buf[j]), 1, 1, uart_file);
      }

  	  free(buf);
      fclose(uart_file);
  	}

    elf_end(elf);
    close(elf_file);
    //uart_file.close();
  }
  fclose(entry_file);
}

int main(int argc, char* argv[]) {

	// Command line options
  boost::program_options::options_description generic_options("Generic options");
  generic_options.add_options()
    ("help,h", "produce help message")
    ("binaries,b", boost::program_options::value< std::vector<std::string> >()->required(), "elf-executable file (stdin: -)")
    ("output,o", boost::program_options::value<std::string>()->default_value("UART"), "output UART serialization in file");

  boost::program_options::positional_options_description pos;
  pos.add("binaries", 1);

	boost::program_options::options_description cmdline_options;
  cmdline_options.add(generic_options);

  // Process command-line options
  boost::program_options::variables_map vm;
  try
  {
    boost::program_options::store(
                          boost::program_options::command_line_parser(argc, argv)
                            .options(cmdline_options).positional(pos).run(), vm);
    boost::program_options::notify(vm);

    // help message
    if (vm.count("help")) {
      std::cout << cmdline_options << "\n";
      return 1;
    }
  }
  catch(boost::program_options::error &e)
  {
    std::cerr << cmdline_options << "\n" << e.what() << "\n\n";
    return 1;
  }

	std::vector<std::string> binaries(vm["binaries"].as< std::vector<std::string> >());
	std::string output(vm["output"].as<std::string>());
	
  streamelf(binaries, output.c_str(), binaries.size());  

  return 0;  
}


