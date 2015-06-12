#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "base64.h"

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

#define STATUS(x)  ((x>0)?"[PASS]":"[FAIL]")

int test_b64_encode();
int test_b64_decode();
int test_b64_encodef();
int test_b64_decodef();
int hexputs(const int* data, int len);
int compare(int *a, int *b, int l);

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
	puts("\nTesting test_b64_encodef() ...\n");
	printf("%s\n",STATUS(test_b64_encodef()));
	puts("\nTesting test_b64_decodef() ...\n");
	printf("%s\n",STATUS(test_b64_decodef()));
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

	printf("%s\t%s\n",STATUS(strcmp(out_a,STRING_A)==0),out_a);
	printf("%s\t%s\n",STATUS(strcmp(out_b,STRING_B)==0),out_b);
	printf("%s\t%s\n",STATUS(strcmp(out_c,STRING_C)==0),out_c);
	
	free(out_a);
	free(out_b);
	free(out_c);
	
	return 0;
}

int test_b64_decode() {
	
	char test_a[] = STRING_A;
	char test_b[] = STRING_B;
	char test_c[] = STRING_C;

	int len_a = strlen(test_a);
	int len_b = strlen(test_b);
	int len_c = strlen(test_c);

	int out_size_a = b64d_size(len_a);
	int out_size_b = b64d_size(len_b);
	int out_size_c = b64d_size(len_c);
	
	//printf("%i,%i,%i\n",out_size_a,out_size_b,out_size_c);
	//wierd ~100 bytes memory problem?

	unsigned int *out_a = malloc(out_size_a+100);
	unsigned int *out_b = malloc(out_size_b+100);
	unsigned int *out_c = malloc(out_size_c+100);
	
	out_size_a = b64_decode(test_a,len_a,out_a);
	out_size_b = b64_decode(test_b,len_b,out_b);
	out_size_c = b64_decode(test_c,len_c,out_c);
	
	int r_a[] = HEXNUM_A;
	int r_b[] = HEXNUM_B;
	int r_c[] = HEXNUM_C;

	//getchar();
	
	printf("%s\t",STATUS(compare(r_a,out_a,NELEMS(r_a)))); hexputs(out_a,out_size_a);
	printf("%s\t",STATUS(compare(r_b,out_b,NELEMS(r_b)))); hexputs(out_b,out_size_b);
	printf("%s\t",STATUS(compare(r_c,out_c,NELEMS(r_c)))); hexputs(out_c,out_size_c);
	
	//printf("addr_a = %p\n",out_a);
	//printf("addr_b = %p\n",out_b);
	//printf("addr_c = %p\n",out_c);
	
	free(out_a);
	free(out_b);
	free(out_c);
	
	return 0;
}

int test_b64_encodef() {
	
	FILE *pFile;
	pFile = fopen("B64_TEST01A.tmp","wb");
	if (pFile==NULL)
		return 0;
	
	int i, j=0;
	unsigned int test_a[] = HEXNUM_B;
	unsigned int size_a = NELEMS(test_a);
	
	for (i=0;i<size_a;i++) {
		fputc(test_a[i],pFile);
	}
	fclose(pFile);
	
	j = b64_encodef("B64_TEST01A.tmp","B64_TEST01B.tmp");
	//remove("B64_TEST01A.tmp");
	
	if (!j)
		return 0;
	
	pFile = fopen("B64_TEST01B.tmp","rb");
	if (pFile==NULL)
		return 0;
	
	char *out = malloc(j+1);
	fgets(out,j+1,pFile);
	fclose(pFile);
	//remove("B64_TEST01B.tmp");
	printf("Comparing \"%s\" to \"%s\" : ",STRING_B,out);
	if (strcmp(STRING_B,out)==0)
		return 1;
	
	return 0;
}

int test_b64_decodef() {
	
	FILE *pFile;
	pFile = fopen("B64_TEST02A.tmp","wb");
	if (pFile==NULL)
		return 0;
	
	int j=0;
	
	fputs(STRING_B,pFile);
	fclose(pFile);
	
	j = b64_decodef("B64_TEST02A.tmp","B64_TEST02B.tmp");
	//remove("B64_TEST02A.tmp");
	
	if (!j)
		return 0;
	
	pFile = fopen("B64_TEST02B.tmp","rb");
	if (pFile==NULL)
		return 0;
	
	char *out = malloc(j+1);
	fgets(out,j+1,pFile);
	fclose(pFile);
	//remove("B64_TEST02B.tmp");
	printf("Comparing \"%s\" with : ",HEXSTR_B); hexputs((int*)out,j);

	int r_b[] = HEXNUM_B;

	if (compare((int*)HEXSTR_B,(int*)out,NELEMS(r_b)))
		return 1;
	
	return 0;
}

int hexputs(const int* data, int len) {
	int i;
	for (i=0;i<len;i++) {
		printf("0x%X ",data[i]);
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