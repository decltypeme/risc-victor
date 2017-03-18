ENTRY(_start)

/* Define the physical memory */
/* One memory block of 64KB   */
/* 1st 54KB is called ram     */
/* last 10KB is called stack  */ 

MEMORY
{
    ram :
        ORIGIN = 0x00000000,
        LENGTH = 65536 - 10240
    stack :
        ORIGIN = 65536 - 10240,
        LENGTH = 10240
}

SECTIONS
 {
 . = 0x00;
 
 /* text: test code section */
 .text :
 {
    *(.text)
 } > ram
 
 /* data: Initialized data segment */
 .data :
 {
    *(.data)
 } > ram
 
 /* Uintialized data */
  .bss :
  {
    *(.bss)
  } > ram
 /* End of uninitalized data segement */
 _end = .;
 }

PROVIDE(_endram = ORIGIN(stack));
PROVIDE(_fstack = ORIGIN(stack) + LENGTH(stack) - 4);