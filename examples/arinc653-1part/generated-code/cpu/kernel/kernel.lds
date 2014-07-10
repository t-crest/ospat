ENTRY(_pok_reset)

SECTIONS
{


  . = SEGMENT_START(".rodata", 0x400);
  .rodata : { *(.rodata .rodata.*) }
  .init_array : { *(SORT(.init_array.*) .init_array) }
  .fini_array : { *(SORT(.fini_array.*) .fini_array) }
  .data : { *(.data) }
  .bss : { 
    __bss_start = .;
    *(.bss) 
    . = ALIGN(4);
   __bss_end = .;
  }

  . = SEGMENT_START(".text", 0x1C0000);
  .text : { 
  *(.text .text.*) 
  }

  . =  0xF00000;
  _stack = .; 
  _end = _stack; PROVIDE (end = .);

}