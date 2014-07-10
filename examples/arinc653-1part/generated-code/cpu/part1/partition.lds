ENTRY(main)
SECTIONS
{

  . = SEGMENT_START(".data", 0x40000);
  .data : { 
    *(.rodata .rodata.*)
    *(.data)
    *(SORT(.init_array.*) .init_array)
    *(SORT(.fini_array.*) .fini_array)
    *(.bss)
  }

  . = SEGMENT_START(".text", 0x20000);
  .text : { 
  *(.text .text.*) 
  }

  . =  0xF00000;
  _stack = .; 
  _end = _stack; PROVIDE (end = .);

}