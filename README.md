# Side-Projects
My side projects

My programming language named JPlus
simple interpreted language like python

You will need a code file as well as a buffer size.
The buffer is an array made up of 64 bit slots (can store variables by user)

Syntax:
> - move to right slot
< - move to left slot
+ - increment value in current slot
- - decrement value in current slot
& - place address of current slot in current slot
* - go to address in current slot
c - save current pc (program counter / command) in current slot (used for jumps)
j - jump to command in current slot (pc <- index)
r - places value in current slot in the global variable
w - places value in global variable in current slot
? - if global variable is other than 0 then jump to command in current slot ( if gloval_var isn't 0 then pc <- current slot value )
; - end the program
# - place a decimal (base 10) number in current slot ( example: #100# places 100 in current slot )
x - place a hex value in current slot ( example: x000fx places 15 in current slot )
" - insert string in current slots (based on number of characters) example: "hello world"
0 - used to reset index
p - used to print the character in current slot
P - used to print an entire string

to execute the interpreter you must:
- compile JPlus.c
- execute with file location and size of buffer
  example: ./JPlus test.txt 200
            execute test.txt with buffer size 200
 Good luck and enjoy



