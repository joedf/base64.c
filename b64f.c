#include <stdio.h>

#include "base64.h"

int lower(int a);

int main(int argc,char** argv) {
	
	puts("\nbase64.c [Encode/Decode]");
	puts("------------------------------------");
	printf("Use the following to encode:\n\t%s e(ncode) IN_filepath OUT_filepath\n",argv[0]);
	printf("Use the following to decode:\n\t%s d(ecode) IN_filepath OUT_filepath\n",argv[0]);
	if (argc < 4) {
		puts("\nERROR: not enough parameters...");
		return 1;
	}
	char opt = lower(argv[1][0]);
	int bcoded = 0;
	switch(opt) {
		case 'd':
			puts("\nDECODING");
			bcoded = b64_decodef(argv[2],argv[3]);
			break;
		case 'e':
			puts("\nENCODING");
			bcoded = b64_encodef(argv[2],argv[3]);
			break;
		default:
			puts("\nINVALID OPTION");
			bcoded = -1;
	}
	
	printf("\nBytes encoded/decoded: %i\n",bcoded);
	
	return 0;
}

int lower(int a) { //https://stackoverflow.com/a/15709023/883015
    if ((a >= 0x41) && (a <= 0x5A))
        a |= 0x20; 
    return a;  
}
