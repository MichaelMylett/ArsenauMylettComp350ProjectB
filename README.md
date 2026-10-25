# James Arsenau, Michael Mylett
# Project B

For testing our functions, we ran them in main using generic string buffers as described in the project directions. These were all commented out before completing the last step, but are all visible directly under main(). For the Step 5 test, we used another generic buffer "line" of 80 characters, called the
makeInterrupt() function provided to us in Assembly code, and were successfully able to call on each of our previously defined functions in the interrupt format of "interrupt(0x21, AX, BX, CX, DX). The inner workings of each step of the project are explained below.

# void printString(char* chars)

printString() takes in a character array (essentially a "string"), then iterates through each individual character in the array and prints it onto the screen. The loop ends when the while loop reaches the null terminator of the array, or 0x0 in hex.

# void readString(char* array)

readString() takes in a character array similarly to our first function. The function repeatedly calls "c= interrupt(0x16,0,0,0,0);" inside a while loop, recording the current keyboard input in the variable c. If "enter" is pressed, the function adds the ASCII for "enter" as well as the line feed sequentially
in the array, then ends it with the null terminator "0x0" and breaks from the infinite while loop, ending the function. The entire array is then printed. If "backspace" is pressed, the cursor is moved to the left and the last character is replaced by an empty space. If any other key is pressed, the function
adds that character to the end of the array.

# void readSector(char* buffer, int sector)

readSector() takes in a character array and an integer. It then calls "interrupt(0x13,2*256+1,buffer, 0*256+relative_sec, 0*256+0x80)", with relative_sec being the provided integer + 1. This interrupt writes the data that it reads from the sector in the function's input and writes it into the buffer which was
also provided.

# void handleInterrupt21(int ax, int bx, int cx, int dx)

handleInterrupt21() is as simple if and else statement that takes in an AX, BX, CX, and DX value (all of which are integers). AX refers to the previously defined function you want to call, with 0 being printString, 1 being readString, and 2 being readSector. Any AX input above 2 results in an error message being
printed, using our printString function. Every function in the if else chain references BX as "(char*) bx", which essentially tells the function that BX is a memory address intended for reading/writing. CX is only used in the case of AX being 2, where it is used as the integer representing sector in the calling
of readSector. DX is not used at all, and is always a 0 in our test calls above in main().
