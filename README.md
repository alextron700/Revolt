# Welcome To Revolt
## What is Revolt?
Revolt is a 32-bit wide virtual CPU which can take assembly-style code as input. It's written in C++, and can be run out of your compiler of choice and a terminal. 
- Simulates RAM  ( up to 16 GB)
- Decodes to binary and executes said binary
- works in words, not bytes
- 16 general-purpose registers
- console I/O at memory[0] to memory[2]
- registers are typed, RAM isn't.
- has and uses a stack buffer.
- program exits if your assembly FAULTs. 
## Revolt is open to having compilers target it.

## How do I run it?
Download main.cpp, and compile it for your machine. 
write your program instruction by instruction, then type "RUN" to execute
Have fun! 
# intructions must be written in all caps 
## Example program
LDI R0 $00000002 R0
ADD R1 R0 $00000002
STM R1 R1 $00000000
STM R0 $40000000 $00000002
RUN
$ immediate
R register
Write the upper four bits at Memory address $00000002 to interact with the console
$80000000: get keyboard character
$40000000: print integer
$20000000: print float
$10000000: print 4 characters
ADD M$[R0] R1 R2 <- writes directly to memory at address stored in R0
