

void printString(char*);
void readString(char*);
void readSector(char*, int);
void handleInterrupt21(int ax, int bx, int cx, int dx);
int interrupt(int, int, int, int, int);


int main(){
while(1){
/*
char line[80];
 char buffer[512];
/*Step 1 test 
printString("Step 1 Test:Hello World \r\n");


/*Step 2 Test* 
printString("Step 2 Test:Enter a line: \r\n ");
readString(line);
printString(line);

/*Step 3 Test
readSector(buffer, 30);
printString(buffer); 



 Step 4 Test 
makeInterrupt21();
interrupt(0x21,0,0,0,0);
*/

/*Step 5 Test*/ 
char line[80];
makeInterrupt21();
printString("Enter a line: ");
interrupt(0x21,1,line,0,0);
interrupt(0x21,0,line,0,0);

/*
char buffer[512];
readSector(buffer,30);
printString(buffer);
*/

    } 
}

/*Step 1*/ 
void printString(char* chars) {
    int i = 0;
    while (chars[i] != 0x0) { /*continues if the current char is not empty*/
        interrupt(0x10, 0xe*256+chars[i], 0, 0, 0);/*prints current char to screen*/ 
        i++;
    }
}

/*Step 2*/
void readString(char* array){
    int i =0; 
    char c; /* current key that is being pressed*/ 
    while(1){
        c= interrupt(0x16,0,0,0,0);
        if (c==0xd){   /* If enter button is pressed last 3 elements in the string will be the ASCII of Enter key, line feed and End of String values*/
            array[i]= 0xd; /*AscII of Enter key   */
            i++;
            array[i] = 0xa; /* line feed */
            i++;
            array[i]=0x0; /* end of string*/

            /*prints characters to the screen*/
            interrupt(0x10, 0xe*256+0xd, 0, 0, 0);
            interrupt(0x10, 0xe*256+0xa, 0, 0, 0);
            break;

        }else if(c== 0x8){/* if backspace key is pressed*/
            if(i >0){
                i--;
                interrupt(0x10, 0xe*256+0x8, 0, 0, 0);/*moves cursor to the left*/
               interrupt(0x10, 0xe*256+' ', 0, 0, 0); /*Displays an empty character*/ 
                interrupt(0x10, 0xe*256+0x8, 0, 0, 0); /*moves cursor to the left again*/
            }
        }else{ /*prints current char if that char isnt a backspace or enter key*/ 
            array[i]=c;
            i++;		
            interrupt(0x10,0xe*256+c, 0,0,0);
        }
    }
}

/*Step 3 */
void readSector(char* buffer, int sector){
    int relative_sec= sector+1;

    /*used formula  AX=AH*256+AL, CX=CH*256+CL and DX=DH*256+DL where AH=2, AL=1, Bx=buffer, 
      CH=0, DH=0, CL is sector+1, DL=0x80   */  
		
    interrupt(0x13,2*256+1,buffer, 0*256+relative_sec, 0*256+0x80);

}

/*step4*/




void handleInterrupt21(int ax, int bx, int cx, int dx){


char* bxString= (char*)bx; /* (char*)bx converts the int value of bx into a char*/ 


if(ax==0){
 
	printString(bxString);  
	}
else if(ax==1){
	readString(bxString);
	}
else if(ax==2){
	readSector(bxString, cx);
	}
else if(ax>=3){
	printString("Error: ax cannot be greater than 2");
	}
}


	


