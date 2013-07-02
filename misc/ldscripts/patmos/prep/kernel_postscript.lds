   . = 0x1C0000 ; 

  .text           :
  {
    *(.start)
    *(.text .text.*)
    __text_end = .;
  } = 0

  . = 0xF00000;

  .bss  :
  {
   __bss_start = .;
   *(.dynbss)
   *(.bss .bss.*)
   *(COMMON)
   . = ALIGN(4);
   __bss_end = .;

   _stack = ALIGN(4) + 0xF00000;
   _end = _stack;
  }


}
