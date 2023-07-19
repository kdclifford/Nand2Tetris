# Project 4
In this project you will write and execute some low-level machine language programs. In
particular, you will write programs in the Hack assembly language, use an assembler to translate
them into binary code, and test the resulting code. Since the Hack computer will be built only in
the next project, in this project you will run the programs on a CPU Emulator, designed to execute
binary code written in the Hack instruction set.
# Objectives
- Get a hands-on taste of low-level programming in machine language;
- Get acquainted with the Hack instruction set, before building the Hack computer in project 5;
- Get acquainted with the assembly process, before building an assembler in project 6.
# Tasks
## Write and test two programs:
- Mult.asm (example of an arithmetic task): The inputs of this program are the values stored in R0
and R1 (RAM[0] and RAM[1]). The program computes the product R0 * R1 and stores the result in
R2 (RAM[2]). Assume that R0 ≥ 0, R1 ≥ 0, and R0 * R1 < 32768 (your program need not test these
conditions). The supplied Multi.test script and Mult.cmp compare file are designed to test your
program on some representative values.

- Fill.asm (example of an input/output task): This program runs an infinite loop that listens to the
keyboard. When a key is pressed (any key), the program blackens the entire screen by writing
"black" in every pixel. When no key is pressed, the program clears the screen by writing "white" in
every pixel. You may choose to blacken and clear the screen in any spatial pattern, as long as
pressing a key continuously for long enough will result in a fully blackened screen, and not pressing
any key for long enough will result in a cleared screen. This program has a test script (Fill.tst) but no
compare file – it should be checked by visibly inspecting the simulated screen in the CPU emulator.
You will write these assembly programs using a plain text editor, translate them into Hack binary
code using an assembler, and execute them using a CPU Emulator.