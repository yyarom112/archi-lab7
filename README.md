# archi-lab7


ELF- Executable and Linkable Format-exe file.
the ELF consists of the follow parts:
1. file header
2. section table- use to relocate file or optional to load file
3. program header table- the table describe all the loadable segment and other DS required for the program or linking file .
4. Contents of the sections or segments, including loadable data, relocations, and string and symbol tables.


-----------------------------------------------------------------------------------------------------------------------
readelf- displays information about one or more ELF format object files. The options control what particular information to display. 


-----------------------------------------------------------------------------------------------------------------------
reading material answer-
1) the start of the program is specified by the "e_entry" field of the ELF executable header. This field normally points 	to the C library's initialization code, and not directly to main.
	"e_entry" gives the virtual address to which the system first transfers control, thus starting the process. If 		the file has no associated entry point, this member holds zero.

2) 


3) to know (not in programing) use:
	a. readelf -S
	b. . The Addr column gives the virtual address at which the section is loaded, the Off column gives the offset within the file to the section, and the Size column gives the size of the section. All numbers are expressed in hex.

4) Certain symbols are reserved and their values are defined by the linker. A user program can reference these symbols, but cannot define them; an error is generated if a user program attempts to define one of these symbols.one of them is "_end"- First location after bss segment . 



7)
To get the file offset of a function, you first need to find out in which section it resides. Afterwards, the offset can be calculated from the following formula: section_file_offset + function_virtual_address - section_virtual_address?







-----------------------------------------------------------------------------------------------------------------------
task0a:
	changed the first for from i<=n to i<n that remove out of boundry.
	freed the array of numbers in the end of main and temp in end of any itertion

-----------------------------------------------------------------------------------------------------------------------
task0b:
1. entry point address 0x80482e0

2. The section header table is an array of Elf64_Shdr .  A section header table index is a subscript into this array.  The ELF header’s e_shoff member gives the byte offset from the 		beginning of the file to the section header table;
	e_shnum tells how many entries the section header table contains; e_shentsize gives the size in bytes of each entry.
	in this file the section header table include 33 entries and the dynamic section incluse 20 enteries.

3. from section headers table the size is 0x0001b8 that is 440 byte

4. from Symbol table '.symtab' the _start occur
    num: value       size type    bind	  vis      ndx name
    57: 080482e0      0   FUNC    GLOBAL DEFAULT   12 _start

	
    Num: = The symbol number
    Value = The address of the Symbol
    Size = The size of the symbol
    Type = symbol type: Func = Function, Object, File (source file name), Section = memory section, Notype = untyped 		absolute symbol or undefined
    Bind = GLOBAL binding means the symbol is visible outside the file. LOCAL binding is visible only in the file. WEAK 	is like global, the symbol can be overridden.
    Vis = Symbols can be default, protected, hidden or internal.
    Ndx = The section number the symbol is in. ABS means absolute: not adjusted to any section address's relocation
    Name = symbol name

5. yes 
    num: value     size type    bind   vis      ndx name
    60: 08048388    51 FUNC    GLOBAL DEFAULT   12 main

6. One can enter main() in gdb in 4 steps:

    1. Find the program entry point
    2. Find where __libc_start_main is called
    3. Set a break point to the address last saved on stack prior to the call to _libc_start_main
    4. Let program execution continue until the break point for main() is hit

The process is the same for both 32-bit and 64-bit ELF binaries. 

-------------------------------------------------------------------------------------------------------------------------
task1a:
my program entry point is 0x4007d0

-----------------------------------------------------------------------------------------------------------------------
task2 
in buggy elf the entry point is 0x4000b5
but the start program is in 0x4000b0

i find that the entry point saved in 0x18 adress.
by self modifie of the program i changed the entry point and fixed the program


-----------------------------------------------------------------------------------------------------------------------
task3a:

	*Find the entry for the function main in the symbol table of the ELF executable-
		Num:    Value          Size Type    Bind   Vis      Ndx Name
	       	71: 00000000004006d6   1695  FUNC    GLOBAL DEFAULT 14  main
	the entry point =0x04006d6
	the function size =1695 byte
	the section number =14


	 [Nr] Name              Type             Address           Offset
       Size              EntSize          Flags  Link  Info  Align
	[14] .text             PROGBITS         00000000004005e0  000005e0
       	000000000000082f  0000000000000000  AX       0     0     16

	section virtual address=0x004005e0
	section virtual offset=0x000005e0

	to get the file offset of a function, you first need to find out in which section it resides. Afterwards, the offset can be calculated from the following formula: 			section_file_offset + function_virtual_address - section_virtual_address.=>
				=>000005e0+04006d6-004005e0=1504+4196054-4195808=1750=000006D6=file offset of a function


-----------------------------------------------------------------------------------------------------------------------
task3b:
	the problem is the counter is not count 0 or 9

	step to correct the bug:
		1.check the place of my function
			64: 0000000000400526    97 FUNC    GLOBAL DEFAULT   14 counter_digit
				the entry point =0x0400526
				the function size =97 byte
				the section number =14

			 [14] .text             PROGBITS         0000000000400430  00000430
       				0000000000000232  0000000000000000  AX       0     0     16
				section virtual address=0x00400430
				section virtual offset=0x00000430

		section_file_offset + function_virtual_address - section_virtual_address=430+400526-400430=526
		src_address=0x526

		2. check the place of digit_cnt(same calc)=0x707
		3. copy the function by hexeditplus
		4. check ntsc
