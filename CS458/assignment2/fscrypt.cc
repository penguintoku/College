/**
 * @file fscrypto.cc
 * @brief Blowfish cipher block cipher using ECB
 * @section Description
 * 
 * Assignment 2 of CS458: Introduction to Computer Security
 * Before starting, read the README
 *
 * Using the OpenSSL methods of Blowfish. 
 * 
 * @author Tokumaru Yahashi
 */

//Dependencies
#include "fscrypt.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

 /**
  * Since I was writing the code on a Mac, I had to include
  * the pragma which will ignore the warnings given on
  * Mac OS X Version 10.7 and higher.
  */
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

/**
 *	@brief The encrypt method using ECB method
 *	@param plaintext[in] 			Pointer to the plaintext
 *	@param bufsize[in] 				The size of the plaintext
 *  @param keystr[in]				Pointer of the key string
 *  @param resultlen[out]			Pointer to the length of result
 */

 void *fs_encrypt(void *plaintext, int bufsize, char *keystr, int *resultlen){

	//Allocate for ciphertext
	unsigned char* result = (unsigned char*) malloc((bufsize + 1));

	//intialize the key 
	BF_KEY *key = (BF_KEY*) malloc(sizeof(BF_KEY));
	BF_set_key(key, BLOCKSIZE, (const unsigned char*) keystr);

	//initalize the initial vector to 0's
	unsigned char iVec[BLOCKSIZE];
	for(int i = 0; i < BLOCKSIZE; i++){
		iVec[i] = 0;
	}

	//Pad the plain text
	int padLength = BLOCKSIZE - (bufsize % (BLOCKSIZE));
	if(!padLength){
  		padLength = BLOCKSIZE;
  	}

  	//Combine the plaintext and padlength
	memset((unsigned char*) plaintext + bufsize - 1, (char) padLength, padLength);

	//Encrypting the plaintext in block size (ECB method)
	for(int i = 0; i < strlen((const char*)plaintext); i += BLOCKSIZE){
		for(int j = 0; j < BLOCKSIZE; j++){
			result[i + j] = ((unsigned char *)plaintext)[i + j] ^ iVec[j]; 
		}
		BF_ecb_encrypt((result + i), (result + i), key, BF_ENCRYPT);
		for(int j = 0; j < BLOCKSIZE; j++){
			iVec[j] = result[i + j];
		}	
	}

	//Remove pad on the plaintext
	((char*) plaintext)[bufsize - 1] = '\0';

	//updating length
	*resultlen = bufsize + padLength;

	//return the ciphertext
	return result;
}

/**
 *	@brief The decrypt method using ECB method
 *	@param ciphertext[in] 			Pointer to the ciphertext
 *	@param bufsize[in] 				The size of the ciphertext
 *  @param keystr[in]				Pointer of the key string
 *  @param resultlen[out]			Pointer to the length of result
 */

 void *fs_decrypt(void *ciphertext, int bufsize, char *keystr, int *resultlen){

	//Allocate for plaintext
	unsigned char* result = (unsigned char*) malloc((bufsize + 1));

	//intialize the key 
	BF_KEY *key = (BF_KEY*) malloc(sizeof(BF_KEY));
	BF_set_key(key, BLOCKSIZE, (const unsigned char*) keystr);

	//initalize the initial vector to 0's
	unsigned char iVec[BLOCKSIZE];
	for(int i = 0; i < BLOCKSIZE; i++){
		iVec[i] = 0;
	}

	//Decrypt the ciphertext in block size (ECB method)
	for(int i = 0; i < bufsize; i += BLOCKSIZE){
		BF_ecb_encrypt(((unsigned char*) ciphertext + i), (result + i), key, BF_DECRYPT);
		for(int j = 0; j < BLOCKSIZE; j++){
			result[i + j] = result[i + j] ^ iVec[j];
			iVec[j] = ((unsigned char*) ciphertext)[i + j];
		}	
	} 

	//Remove pad on the ciphertext
	int padLength = result[bufsize - 2];
	result[bufsize - padLength - 1] = '\0';

	//updating length
	*resultlen = (int) strlen((const char*) result) + 1;

	//return the ciphertext
	return result;	
}