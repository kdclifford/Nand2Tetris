// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

// Put your code here.

//Intial Setup
@SCREEN
D=A-1
@address
M=D


(CLEAR)
@SCREEN
D=A-1
@address
M=D
@counter
M=0
@CLEARLOOP
0;JMP

(FILL)
@SCREEN
D=A-1
@addressClear
M=D
@counterClear
M=0
@LOOP
0;JMP

//Main Loop 
(LOOP)
@address
D=M
@24576
D=D-A
@KEY
D;JEQ
   @address
   A=M
   M=-1
   @address
   D=M
   @1
   D=D+A
   @address
   M=D
   @counter
   MD=M-1
   @KEY
   D;JGT


//Clear Loop 
(CLEARLOOP)
@addressClear
D=M
@24576
D=D-A
@KEY
D;JGT
   @addressClear
   A=M
   M=0
   @addressClear
   D=M
   @1
   D=D+A
   @addressClear
   M=D
   @counterClear
   MD=M-1
   @KEY
   D;JGT


//Key Pressed
(KEY)
@24576
D=M
@CLEAR
D;JEQ
@FILL
0;JMP