#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Test values
///////////////////////////////////////////////////////////////
#define STRING_A "9TrJ"
#define STRING_B "9TrJUQ=="
#define STRING_C "9TrJUfA="

#define HEXNUM_A {0xF5,0x3A,0xC9}
#define HEXNUM_B {0xF5,0x3A,0xC9,0x51}
#define HEXNUM_C {0xF5,0x3A,0xC9,0x51,0xF0}

#define HEXSTR_A "0xF5 0x3A 0xC9"
#define HEXSTR_B "0xF5 0x3A 0xC9 0x51"
#define HEXSTR_C "0xF5 0x3A 0xC9 0x51 0xF0"
///////////////////////////////////////////////////////////////

#define NELEMS(x)  (sizeof(x) / sizeof(x[0]))

int test_b64_encode();
int test_b64_decode();
int hexputs(unsigned int* data, unsigned int len);
int compare(int *a, int *b, int l);
char *status(int boolean);

int main() {
	
	puts("\nbase64.c [Test]");
	puts("------------------------------------");
	printf("%s           : %s\n",HEXSTR_A,STRING_A);
	printf("%s      : %s\n",HEXSTR_B,STRING_B);
	printf("%s : %s\n",HEXSTR_C,STRING_C);
	puts("\nTesting b64_encode() ...\n");
	test_b64_encode();
	puts("\nTesting b64_decode() ...\n");
	test_b64_decode();
	puts("\n[END]");

	return 0;
}

int test_b64_encode() {
	
	int test_a[] = HEXNUM_A;
	int test_b[] = HEXNUM_B;
	int test_c[] = HEXNUM_C;

	int size_a = NELEMS(test_a);
	int size_b = NELEMS(test_b);
	int size_c = NELEMS(test_c);

	int out_size_a = b64e_size(size_a) + 1;
	int out_size_b = b64e_size(size_b) + 1;
	int out_size_c = b64e_size(size_c) + 1;

	unsigned char *out_a = malloc(out_size_a);
	unsigned char *out_b = malloc(out_size_b);
	unsigned char *out_c = malloc(out_size_c);

  	out_size_a = b64_encode(test_a,size_a,out_a);
  	out_size_b = b64_encode(test_b,size_b,out_b);
  	out_size_c = b64_encode(test_c,size_c,out_c);

  	printf("%s\t%s\n",status(!strcmp(out_a,STRING_A)),out_a);
  	printf("%s\t%s\n",status(!strcmp(out_b,STRING_B)),out_b);
  	printf("%s\t%s\n",status(!strcmp(out_c,STRING_C)),out_c);
  	
  	return 0;
}

int test_b64_decode() {
	
	char test_a[] = STRING_A;
	char test_b[] = STRING_B;
	char test_c[] = STRING_C;

	int len_a = strlen(test_a);
	int len_b = strlen(test_b);
	int len_c = strlen(test_c);

	int out_size_a = b64d_size(len_a) + 1;
	int out_size_b = b64d_size(len_b) + 1;
	int out_size_c = b64d_size(len_c) + 1;

	unsigned int *out_a = malloc(out_size_a);
	unsigned int *out_b = malloc(out_size_b);
	unsigned int *out_c = malloc(out_size_c);

  	out_size_a = b64_decode(test_a,len_a,out_a);
  	out_size_b = b64_decode(test_b,len_b,out_b);
  	out_size_c = b64_decode(test_c,len_c,out_c);
	
	int r_a[] = HEXNUM_A;
	int r_b[] = HEXNUM_B;
	int r_c[] = HEXNUM_C;

  	printf("%s\t",status(compare(r_a,out_a,3))); hexputs(out_a,out_size_a);
  	printf("%s\t",status(compare(r_b,out_b,4))); hexputs(out_b,out_size_b);
  	printf("%s\t",status(compare(r_c,out_c,5))); hexputs(out_c,out_size_c);
  	
  	return 0;
}

int hexputs(unsigned int* data, unsigned int len) {
	int i;
	for (i=0;i<len;i++) {
		printf("0x%X ",(int)data[i]);
	}
	printf("\n");
	return 0;
}

int compare(int *a, int *b, int l) {
	int i;
	for (i=0;i<l;i++) {
		if (a[i]!=b[i])
			return 0;
	}
	return 1;
}

char *status(int boolean) {
	if (boolean)
		return "[PASS]";
	return "[FAIL]";
}