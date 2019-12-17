#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "base64.h"

int lower(int a);

int main(int argc,char** argv) {
	
	char opt = ' ';
	if (argc > 1)
		opt = lower(argv[1][0]);
	
	if ( ((argc < 4) && (opt!='b' && opt!='t')) ) {
		puts("\nbase64.c [Encode/Decode]");
		puts("------------------------------------");
		printf("File mode\n");
		printf("\tUse the following to encode:\n\t%s e(ncode) IN_filepath OUT_filepath\n",argv[0]);
		printf("\tUse the following to decode:\n\t%s d(ecode) IN_filepath OUT_filepath\n",argv[0]);
		printf("\nText mode (outputs to stdout):\n");
		printf("\tUse the following to encode:\n\t%s t(ext) IN_Text\n",argv[0]);
		printf("\tUse the following to decode:\n\t%s b(ase64) IN_Base64\n",argv[0]);
		
		puts("\nERROR: insufficient or incorrect parameters...");
		return 1;
	}
	
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
		case 't':
			puts("\nENCODING from text to base64");
			
				int tlen = strlen(argv[2]);
				char *b64 = (char *)malloc(1 + (sizeof(char) * b64e_size(tlen)));
				if (b64 == NULL) {
					printf("Error: cannot allocate memory for output\n");
					exit(1);  /* End program with error status. */
				}
			
			bcoded = b64_encode(argv[2],tlen,b64);
			printf("Encoded base64 from text: %s", b64);
			free(b64);
			break;
		case 'b':
			puts("\nDECODING from base64 to text");
			
				int blen = strlen(argv[2]);
				char *txt = malloc(1 + (sizeof(char) * b64d_size(blen)));
				if (txt == NULL) {
					printf("Error: cannot allocate memory for output\n");
					exit(1);  /* End program with error status. */
				}
			
			bcoded = b64_decode(argv[2],blen,txt);
			txt[bcoded] = '\0';
			printf("Decoded text from base64: %s", txt);
			free(txt);
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
