/*
	base64.c - by Joe DF (joedf@ahkscript.org)
	Released under the MIT License
	
	Revision: 00:06 2014-09-22
	
	Thank you for inspiration:
	http://www.codeproject.com/Tips/813146/Fast-base-functions-for-encode-decode
*/


unsigned int b64_int(unsigned int ch);
unsigned int b64e_size(unsigned int in_size);
unsigned int b64d_size(unsigned int in_size);
unsigned int b64_encode(const unsigned int* in, unsigned int in_len, unsigned char* out);
unsigned int b64_decode(const unsigned char* in, unsigned int in_len, unsigned int* out);


//Base64 char table - used internally for encoding
unsigned char b64_chr[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

//Base64 char table function - used internally for decoding
unsigned int b64_int(unsigned int ch) {

	// ASCII to base64_int
	// 65-90  Upper Case  >>  0-25
	// 97-122 Lower Case  >>  26-51
	// 48-57  Numbers     >>  52-61
	// 43     Plus (+)    >>  62
	// 47     Slash (/)   >>  63
	// 61     Equal (=)   >>  64~
	if (ch==43)
		return 62;
	if (ch==47)
		return 63;
	if (ch==61)
		return 64;
	if ((ch>47) && (ch<58))
		return ch + 4;
	if ((ch>64) && (ch<91))
		return ch - 'A';
	if ((ch>96) && (ch<123))
		return (ch - 'a') + 26;
	return 0;
}

// in_size : the number bytes to be encoded.
// Returns the recommended memory size to be allocated for the output buffer excluding the null byte
unsigned int b64e_size(unsigned int in_size) {

	// size equals 4*floor((1/3)*(in_size+2));
	int i, j = 0;
	for (i=0;i<in_size;i++) {
		if (i % 3 == 0)
			j += 1;
	}
	return (4*j);
}

// in_size : the number bytes to be decoded.
// Returns the recommended memory size to be allocated for the output buffer excluding the null byte
unsigned int b64d_size(unsigned int in_size) {

	return ((3*in_size)/4);
}

// in : buffer of "raw" binary to be encoded.
// in_len : number of bytes to be encoded.
// out : pointer to buffer with enough memory, user is responsible for memory allocation, receives null-terminated string
// returns size of output including null byte
unsigned int b64_encode(const unsigned int* in, unsigned int in_len, unsigned char* out) {

	unsigned int i=0, j=0, k=0, s[3];
	
	for (i=0;i<in_len;i++) {
		s[j++]=*(in+i);
		if (j==3) {
			out[k+0] = b64_chr[ s[0]>>2 ];
			out[k+1] = b64_chr[ ((s[0]&0x03)<<4)+((s[1]&0xF0)>>4) ];
			out[k+2] = b64_chr[ ((s[1]&0x0F)<<2)+((s[2]&0xC0)>>6) ];
			out[k+3] = b64_chr[ s[2]&0x3F ];
			j=0; k+=4;
		}
	}
	
	if (j) {
		if (j==1)
			s[1] = 0;
		out[k+0] = b64_chr[ s[0]>>2 ];
		out[k+1] = b64_chr[ ((s[0]&0x03)<<4)+((s[1]&0xF0)>>4) ];
		if (j==2)
			out[k+2] = b64_chr[ ((s[1]&0x0F)<<2) ];
		else
			out[k+2] = '=';
		out[k+3] = '=';
		k+=4;
	}

	out[k] = '\0';
	
	return k;
}

// in : buffer of base64 string to be decoded.
// in_len : number of bytes to be decoded.
// out : pointer to buffer with enough memory, user is responsible for memory allocation, receives "raw" binary
// returns size of output excluding null byte
unsigned int b64_decode(const unsigned char* in, unsigned int in_len, unsigned int* out) {

	unsigned int i=0, j=0, k=0, s[4];
	
	for (i=0;i<in_len;i++) {
		s[j++]=b64_int(*(in+i));
		if (j==4) {
			out[k+0] = (s[0]<<2)+((s[1]&0x30)>>4);
			if (s[2]!=64) {
				out[k+1] = ((s[1]&0x0F)<<4)+((s[2]&0x3C)>>2);
				if ((s[3]!=64)) {
					out[k+2] = ((s[2]&0x03)<<6)+(s[3]); k+=3;
				} else {
					k+=2;
				}
			} else {
				k+=1;
			}
			j=0;
		}
	}
	
	return k;
}
