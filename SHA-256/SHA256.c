#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "SHA256.h"


int main(int argc, char const *argv[]){

	//Creating the message to be hashed
	char* message="abc"; //Change this value according to need

	//Converting the data into BYTEARRAY
	uint8_t* data=(uint8_t*)message;

	//Creating the buffer to store the hash
	uint64_t hash[8];

	//Hashing the message with SHA256
	SHA256(message,hash);

	//Printing the Hash of the message
	for (int i = 0; i < 8; i++){
		printf("%.8x",hash[i]);
	}

	return 0;

}
