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

  . = SEGMENT_START(".text", 0x20000);
  .text : { 
  *(.text .text.*) 
  }
