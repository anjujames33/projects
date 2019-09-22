/*********************************************************************************
 ** File Name   : Common.h                                                      **
 ** Purpose     : Common header files, variables and functions are declared     **
 **               in this file.                                                 **
 ** Author      : Anju K.James<anju@nmsu.edu>                                   **
 ** Version     : 1.0                                                           **
 *********************************************************************************/

#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

/* HEADERS */
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <sys/stat.h>
#include <openssl/bio.h>
#include <openssl/err.h>

/* NAMESPACES */
using namespace std;

#define SYM_KEY_FILE "files/symmetric.txt"
#define PLAIN_TEXT_FILE "files/plaintext.txt"
#define CIPHER_TEXT_FILE "files/ciphertext.txt"
#define SIGNED_CIPHER "files/signed_cipher"
#define NEW_PLAIN_TEXT "files/new_plain_text.txt"


#endif // COMMON_H_INCLUDED
