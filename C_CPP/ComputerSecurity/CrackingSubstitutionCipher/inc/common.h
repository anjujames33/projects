/*********************************************************************************
 ** File Name	: Common.h							**
 ** Purpose	: Common header files, variables and functions are declared 	**
 **		  in this file.	   						**
 ** Author	: Anju K.James<anju@nmsu.edu>					**
 ** Version	: 1.0								**
 *********************************************************************************/

#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

/* HEADERS */
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <string.h>
#include <stdio.h>
#include <openssl/bio.h>
#include <openssl/rsa.h>

/* NAMESPACES */
using namespace std;

/* CONSTANTS */
#define NEW_LINE '\n'
#define PLAIN_TEXT "plain_text.txt"
#define DICTIONARY "dictionary.txt"
#define KEY_SIZE 26

/* STATIC VARIABLES */

/* GLOBAL VARIABLES */
//const char key[23]={ 'E', 'T', 'O', 'I', 'N', 'S', 'A', 'H', 'R', 'C', 'L', 'M', 'U', 'G', 'D', 'F', 'Y', 'W', 'V', 'K', 'P', 'B', 'X' };

/* TYPEDEF */
typedef map< char, int > alphabet;
typedef pair< char, int > pairs;
struct data
{
    int max;
    char max_key[26];
};

/* FUNCTIONS */
void ReadCipherText( char cipher_text[] );

void FrequencyAnalysisCipher( char cipher_text[] );

void EnglishFrequency();

int CompareWithDictionary();

int Decryption( char cipher_text[], char key[] );

void Decrypt( char cipher_text[], char key[] );

void FindKey( char cipher_text[] );

void ShiftKey(int pos, int max, char max_key[], char cipher_text[], int n, data* ret_data);

#endif // COMMON_H_INCLUDED
