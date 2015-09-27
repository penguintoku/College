/**
 * @file rc6.cpp
 * @brief RC6-32/20/b block cipher
 * @section Description
 * 
 * Assignment 1 of CS458: Introduction to Computer Security
 * Before starting, read the README
 *
 * RC6 is a symmetric key block cipher derived from RC5 
 * 
 * @author Tokumaru Yahashi
 */

//Dependencies
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>  
#include <iomanip>

//"Magic Constants" defined in paper
#define P32 		0xB7E15163
#define Q32 		0x9E3779B9

//w = Word Size
#define WORD 		32

//r = Rounds
#define ROUNDS 		20

//Log2(32) = 5
#define LG32 		5

//Max length for Store Array
#define SMAX 		(2 * ROUNDS + 4)

//The size of words in bytes
#define BYTES		(WORD / 8)		

//This is c (in pdf) but can't be used for array
#define X 			((keyLength + BYTES - 1) / BYTES)

//Rotating Left
#define RL(x,y) (((x) << (y & (WORD - 1))) | ((x) >> (WORD - (y & (WORD - 1)))))

//Rotating Right
#define RR(x,y) (((x) >> (y & (WORD - 1))) | ((x) << (WORD - (y & (WORD - 1)))))

//Key Schedule
unsigned int S[SMAX];		

/**
 *	@brief The key schedule given by the user to for encrypt and decrypt.
 *	@param key[in] 			Pointer to the key
 *	@param keyLength[in] 	The size of the key (b)
 */

void key_schedule(unsigned int *key, int keyLength){
	//Initialize the Key Setup
	int i, j;
	unsigned int L[(WORD + BYTES - 1) / BYTES]; 
	unsigned int A, B;
	
	//Loading the keys
	L[X - 1] = 0;
	for(i = keyLength - 1; i >= 0; i--){
		L[i / BYTES] = (L[i / BYTES] << 8) + key[i];
	}

	//Initialize the first element of S
	S[0] = P32;

	//Initialize array S to a particular fixed pseudo random bit pattern
	for(i = 1; i <= SMAX - 1; ++i){
		S[i] = S[i - 1] + Q32;
	}

	//Initialize
	A = B = i = j = 0;

	//Number of iteration
	unsigned int v = 3 * std::max(X, SMAX);

	//Key Expansion
	for(int s = 0; s < v; s++){
		A = S[i] = RL(S[i] + A + B, 3);
		B = L[j] = RL(L[j] + A + B, A + B);
		i = (i + 1) % SMAX;
		j = (j + 1) % X;
	}
}

/**
 *	@brief 	The encrypt block. Encrypt plaintext to ciphertext.
 *	@param plainText[in] 	Pointer to the plaintext
 *	@param cipherText[out] 	Pointer to the cipherText
 */

void encrypt(unsigned int *plainText, unsigned int *cipherText){
	
	//Initialize
	unsigned int A, B, C, D, t, u, temp;
	int i;
	
	//Load the plaintext
	A = plainText[0];
	B = plainText[1];
	C = plainText[2];
	D = plainText[3];

	//Update B and D
	B += S[0];
	D += S[1];

	//Apply 20 rounds
	for(i = 1; i <= ROUNDS; i++){
		t = RL(B * (2 * B + 1), LG32);
		u = RL(D * (2 * D + 1), LG32);
		A = RL(A ^ t, u) + S[2 * i];
		C = RL(C ^ u, t) + S[2 * i + 1];

		temp = A;
		A = B;
		B = C;
		C = D;
		D = temp;
	}

	//Update A and C
	A += S[SMAX - 2];
	C += S[SMAX - 1];

	//Store the ciphertext
	cipherText[0] = A;
	cipherText[1] = B;
	cipherText[2] = C;
	cipherText[3] = D;
}

/**
 *	@brief 	The decrypt block. decrypt ciphertext to plaintext.
 *	@param cipherText[in] 	Pointer to the cipherText
 *	@param plainText[out] 	Pointer to the plainText
 */

void decrypt(unsigned int *cipherText, unsigned int *plainText){
	
	//Initialize
	unsigned int A, B, C, D, t, u, temp;
	int i;
	
	//Load the ciphertext
	A = cipherText[0];
	B = cipherText[1];
	C = cipherText[2];
	D = cipherText[3];
	
	//Update C and A
	C -= S[SMAX - 1];
	A -= S[SMAX - 2];

	//Apply 20 rounds
	for(i = ROUNDS; i >= 1; i--){

		temp = D;
		D = C;
		C = B;
		B = A;
		A = temp;

		u = RL(D * (2 * D + 1), LG32);
		t = RL(B * (2 * B + 1), LG32);
		C = RR(C - S[2 * i + 1], t) ^ u;
		A = RR(A - S[2 * i], u) ^ t;
	}

	//Update D and B
	D -= S[1];
	B -= S[0];

	//Store the plaintext
	plainText[0] = A;
	plainText[1] = B;
	plainText[2] = C;
	plainText[3] = D;  
}

int main(int argc, char* argv[]){

	//Check if valid format
	if (argc != 3){
		std::cout << "Usage: " << argv[0] << " [input file name] [output file name]\n" << std::endl;
		return 1;
	}
	//Setup I/O
	std::ifstream fileIn;
	std::ofstream fileOut;

	//Initialize
	unsigned int startText[4];
	unsigned int endText[4];
	unsigned int keyText[32];
	unsigned int i;
	unsigned int valOne, valTwo, valThree, valFour;

	//Open file
	fileIn.open(argv[1]);
	fileOut.open(argv[2]);
	
	//Take in input to determine mode
	std::string mode;
	fileIn >> mode;

	//get the next line
	std::string next;
	fileIn >> next;
	
	//get the cipher/plain text 
	for(i = 0; i < 4; i++){	
		fileIn >> std::hex >> valOne;
		fileIn >> std::hex >> valTwo;
		fileIn >> std::hex >> valThree;
		fileIn >> std::hex >> valFour;
		startText[i] = valOne | valTwo << 8 | valThree << 16 | valFour << 24;
	}

	//get the next line
	fileIn >> next;

	//initialize 0 to get key length
	i = 0;

	//read in the key
	while(!fileIn.eof()){
		fileIn >> std::hex >> keyText[i];
		i++;
	}

	//initialize key length
	int keylen = i;

	//run the key_schedule to be used for encrypt or decrypt
	key_schedule(keyText, keylen);
	
	//Determine either to encrypt or decrypt
	if(mode.compare("Encryption") == 0){
		encrypt(startText, endText);
		fileOut << "ciphertext: ";
	} 
	else {
		decrypt(startText, endText);
		fileOut << "plaintext: ";
	}

	//Display the output text
	for(i = 0; i < 4; i++){
		fileOut << std::hex << std::setw(2) << std::setfill('0') << (endText[i] & 0xff) << " " ;
		fileOut << std::hex << std::setw(2) << std::setfill('0') << ((endText[i] >> 8) & 0xff) << " " ;
		fileOut << std::hex << std::setw(2) << std::setfill('0') << ((endText[i] >> 16) & 0xff) << " " ;
		fileOut << std::hex << std::setw(2) << std::setfill('0') << ((endText[i] >> 24) & 0xff) << " " ;
	}

	//close file
	fileIn.close();
	fileOut.close();

	return 0;
}