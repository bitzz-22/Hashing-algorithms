#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static const uint32_t K[64]={
	0x428a2f98 ,0x71374491 ,0xb5c0fbcf ,0xe9b5dba5 ,0x3956c25b ,0x59f111f1 ,0x923f82a4 ,0xab1c5ed5
	,0xd807aa98 ,0x12835b01 ,0x243185be ,0x550c7dc3 ,0x72be5d74 ,0x80deb1fe ,0x9bdc06a7 ,0xc19bf174
	,0xe49b69c1 ,0xefbe4786 ,0x0fc19dc6 ,0x240ca1cc ,0x2de92c6f ,0x4a7484aa ,0x5cb0a9dc ,0x76f988da
	,0x983e5152 ,0xa831c66d ,0xb00327c8 ,0xbf597fc7 ,0xc6e00bf3 ,0xd5a79147 ,0x06ca6351 ,0x14292967
	,0x27b70a85 ,0x2e1b2138 ,0x4d2c6dfc ,0x53380d13 ,0x650a7354 ,0x766a0abb ,0x81c2c92e ,0x92722c85
	,0xa2bfe8a1 ,0xa81a664b ,0xc24b8b70 ,0xc76c51a3 ,0xd192e819 ,0xd6990624 ,0xf40e3585 ,0x106aa070
	,0x19a4c116 ,0x1e376c08 ,0x2748774c ,0x34b0bcb5 ,0x391c0cb3 ,0x4ed8aa4a ,0x5b9cca4f ,0x682e6ff3
	,0x748f82ee ,0x78a5636f ,0x84c87814 ,0x8cc70208 ,0x90befffa ,0xa4506ceb ,0xbef9a3f7 ,0xc67178f2
};

struct hash{
	int H[8];
	int* message;
	int number_of_blocks;
};

uint32_t rotr(uint32_t value,int shift);
uint32_t Ch(uint32_t x,uint32_t y, uint32_t z);
uint32_t Maj(uint32_t x,uint32_t y, uint32_t z);
uint32_t sumation_0(uint32_t x);
uint32_t sumation_1(uint32_t x);
uint32_t sigma_0(uint32_t x);
uint32_t sigma_1(uint32_t x);

void initialise(struct hash* sha);

void pad(char* message,struct hash* sha);

void update_W(uint32_t* block , uint32_t* W);

void main_(struct hash* sha);

void SHA(char* message,uint64_t* hash);










uint32_t rotr(uint32_t value,int shift){
    return (value >> shift) | (value << (32 - shift));
}

uint32_t Ch(uint32_t x,uint32_t y, uint32_t z){
	return ((x & y) ^ ((~x) & z));
}

uint32_t Maj(uint32_t x,uint32_t y, uint32_t z){
	return ((x & y) ^ (x & z) ^ (y & z));
}

uint32_t sumation_0(uint32_t x){
	return (rotr(x,2) ^ rotr(x,13) ^ rotr(x,22));
} 

uint32_t sumation_1(uint32_t x){
	return (rotr(x,6) ^ rotr(x,11) ^ rotr(x,25));
}

uint32_t sigma_0(uint32_t x){
	return (rotr(x,7) ^ rotr(x,18) ^ (x >> 3));
} 

uint32_t sigma_1(uint32_t x){
	return (rotr(x,17) ^ rotr(x,19) ^ (x >> 10));
}

void initialise(struct hash* sha){
	uint32_t H[8]={
		0x6a09e667,0xbb67ae85,0x3c6ef372,0xa54ff53a,
		0x510e527f,0x9b05688c,0x1f83d9ab,0x5be0cd19
	};
	for (int i = 0; i < 8; i++){
		sha->H[i]=H[i];
	}
}

void pad(char* message,struct hash* sha){

	uint64_t length=strlen(message);
	int k=((512 + 448 - ((length*8) % 512 + 8)) % 512)/8;
	int newlen_bytes = length + 1 + k + 8; 
	int* buffer = (int*)malloc(newlen_bytes*sizeof(int));
	int buffer_index=0;

	// Putting the message in...
	for(buffer_index;buffer_index<length;buffer_index++){
		buffer[buffer_index]=message[buffer_index];
	}
	// Putting the bit "1" in...
	buffer[buffer_index++]=0x80;

	// Padding the message with 0s until its length is 448
	for(buffer_index;buffer_index<length+k+1;buffer_index++){
		buffer[buffer_index]=0x00;
	}
	length*=8;

	// Putting the 64bit(8 byte) length after the padding 
	for (int i = 7; i >= 0; i--){                     //THIS SNIPPET IS COPPIED NoT MINE
        int byte = (length >> 8 * i) & 0xff;
        buffer[buffer_index++]=byte;
    }

	// Putting the length of original message in...
    sha->number_of_blocks=newlen_bytes/64;
	sha->message=buffer;
}

void update_W(uint32_t* block , uint32_t* W){
	
	for (int j = 0; j < 16; j++){
		uint32_t buffer=(((uint32_t)block[(4*j)+0] << 24) |
		                 ((uint32_t)block[(4*j)+1] << 16) |
		                 ((uint32_t)block[(4*j)+2] <<  8) |
		                 ((uint32_t)block[(4*j)+3]));
		W[j]=(uint32_t)buffer;
	};

	for (int j = 16; j < 64; j++){
		W[j]=sigma_1(W[j-2]) + W[j-7] + sigma_0(W[j-15]) + W[j-16];
	}
}

void main_(struct hash* sha){
	uint32_t a,b,c,d,e,f,g,h;
	uint32_t W[64];
	for (int i = 1; i < sha->number_of_blocks+1; i++){
		a=sha->H[0];
		b=sha->H[1];
		c=sha->H[2];
		d=sha->H[3];
		e=sha->H[4];
		f=sha->H[5];
		g=sha->H[6];
		h=sha->H[7];

		update_W((uint32_t*)((sha->message))+64*(i-1) , W);

		for (int j = 0; j < 64; j++){
			uint32_t T1=h+sumation_1(e)+Ch(e,f,g)+K[j]+W[j];
			uint32_t T2=sumation_0(a)+Maj(a,b,c);
			h=g;
			g=f;
			f=e;
			e=d+T1;	
			d=c;
			c=b;
			b=a;
			a=T1+T2;
		}

		sha->H[0]+=a;
		sha->H[1]+=b;
		sha->H[2]+=c;
		sha->H[3]+=d;
		sha->H[4]+=e;
		sha->H[5]+=f;
		sha->H[6]+=g;
		sha->H[7]+=h;
	}
}


void SHA(char* message,uint64_t* hash){
	struct hash sha;
	initialise(&sha);
	pad(message,&sha);
    main_(&sha);
    for (int i = 0; i < 8; i++) {
        hash[i] = (uint64_t)sha.H[i];
    }
    free(sha.message);
    sha.message=NULL;
}
