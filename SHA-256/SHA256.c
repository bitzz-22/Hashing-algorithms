#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "SHA256.h"


int main(int argc, char const *argv[]){

	char* message="abc";
	uint64_t hash[8];
	SHA(message,hash);

	for (int i = 0; i < 8; i++){
		printf("%.8x",hash[i]);
	}
	return 0;

}
