/*********************************************************************************
** File Name    : project2_decryption.cpp                                       **
** Purpose      : Decryption                                                    **
** Author       : Anju K.James<anju@nmsu.edu>                                   **
** Version      : 1.0                                                           **
*********************************************************************************/

/* HEADERS */

#include "common.h"


/* FUNCTIONS */

/*********************************************************************************
** Function     : VerifyCipher()
** Description  : Verify signed cipher text with public key 
*********************************************************************************/
void VerifyCipher( char signed_cipher_text[], char my_public_key[] )
{
	string cmd;
	string data;
	ifstream fin;

	//Verify signed cipher text using public key.
	cout <<"\n1. Verify signed cipher\n" << endl;
	cmd = "openssl dgst -sha256 -verify " + std::string( my_public_key ) 
		+ " -signature " + std::string( signed_cipher_text ) + " " + std::string( CIPHER_TEXT_FILE );

	//Execute command 'cmd' with system() to decrypt
	cout << "Command: " << cmd << endl;
	cout << endl;
	const char *command = cmd.c_str(); 
	system(command);

}


/*********************************************************************************
 ** Function     : DecryptCipher() 
 ** Description  : Decrypt cipher text with symmetric key
 *********************************************************************************/
void DecryptCipher( char symmetric_key[] )
{
	string cmd;
	string data;
	ifstream fin;
	cout <<"\n2. Decrypt cipher text " << endl;

	cmd = "openssl enc -d -aes-256-cbc -in " + std::string( CIPHER_TEXT_FILE )
		+ " -out " + std::string( NEW_PLAIN_TEXT ) + " -pass file:" + std::string( symmetric_key );

	//Execute command 'cmd' with system() to decrypt
	cout << "\nCommand: " << cmd << endl;
	cout << endl;
	const char *command = cmd.c_str(); 
	system(command);

	//Display cipher text
	cout << "Original plain text:\n" << endl;
	fin.open( NEW_PLAIN_TEXT );
	if( fin.fail() )
	{
		cout << "Error: New plain text file open failed!!! " << endl;
		fin.close();
	}
	else
	{
		while( !fin.eof() )
		{
			getline( fin, data );
			cout << data << endl;
		}
		fin.close();
	}
}

/*********************************************************************************
** Function     : main() 
** Description  : Execusion starts here.
*********************************************************************************/
int main( int argc, char* argv[] )
{
	fstream fs;
	fstream fp;
	fstream fc;
	char* signed_cipher_text = NULL;
	char* my_public_key = NULL;
	char* symmetric_key = NULL;

	if ( argc == 4 )
	{
		signed_cipher_text = argv[ 1 ];
		my_public_key = argv[ 2 ];
		symmetric_key = argv[ 3 ];

		fs.open( signed_cipher_text );
		if( fs.fail() )
		{
			cout << "Error: Signed cipher text file is invalid!!! " << endl;
			fs.close();
			return 0;
		}
		else if( fs.peek() == std::ifstream::traits_type::eof() )
		{
			cout << "Error: Signed cipher text file is Empty!!! " << endl;
			fs.close();
			return 0;
		}
		fs.close();

		fp.open( my_public_key );
		if( fp.fail() )
		{
			cout << "Error: publickey file is invalid!!! " << endl;
			fp.close();
			return 0;
		}
		else if( fp.peek() == std::ifstream::traits_type::eof() )
		{
			cout << "Error: publickey file is Empty!!!! " << endl;
			fp.close();
			return 0;
		}
		fp.close();

		fc.open( symmetric_key );
		if( fc.fail() )
		{
			cout << "Error: Symmetric key file is invalid!!! " << endl;
			fc.close();
			return 0;
		}
		else if( fc.peek() == std::ifstream::traits_type::eof() )
		{
			cout << "Error: Symmetric key file is Empty!!! " << endl;
			fc.close();
			return 0;
		}
		fc.close();


		cout <<"\n====== DECRYPTION ======" << endl;

		//1. Verify signed cipher
		VerifyCipher( signed_cipher_text, my_public_key );

		//2. Decrypt cipher text
		DecryptCipher( symmetric_key );

	}
	else
	{
		cout <<"\n====== DECRYPTION ======\n" << endl;
		cout << "Usage: ./<binary_name> <path/signed_cipher> <path/my_publickey> <path/symmetric_key>\n" << endl;
		cout << "Example: ./bin/decrypt files/signed_cipher files/my_pubkey.pem files/symmetric.txt\n" << endl; 
		return 0;
	}

	return 0;
}

