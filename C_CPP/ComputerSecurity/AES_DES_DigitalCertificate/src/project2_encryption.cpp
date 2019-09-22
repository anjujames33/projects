/*********************************************************************************
** File Name    : project2_encryption.cpp                                       **
** Purpose      : Encryption 				                        **
** Author       : Anju K.James<anju@nmsu.edu>                                   **
** Version      : 1.0                                                           **
*********************************************************************************/

/* HEADERS */

#include "common.h"


/* FUNCTIONS */

/*********************************************************************************
** Function     : DecryptSymmetricKey()
** Description  : Decrypt symm_key.bin with public key provided(pubkey.pem) 
				  to generate symmetric key(symmetric.txt)
 *********************************************************************************/
void DecryptSymmetricKey( char enc_sym_key_file_name[], char thirdparty_pubkey_file_name[] )
{
	string cmd;
	string data;
	ifstream fin;

	//Decrypt symm_key.bin to get symmetric key
	cout <<"\n\n1. Decrypt symm_key.bin with public key\n" << endl;

	cmd = "openssl rsautl -encrypt -pubin -inkey " + std::string( thirdparty_pubkey_file_name ) 
		+ " -in " + std::string( enc_sym_key_file_name ) + " -raw -hexdump -out " + std::string( SYM_KEY_FILE );

	//Execute command 'cmd' with system() to decrypt
	cout << "Command: " << cmd << endl;
	const char *command = cmd.c_str(); 
	system(command);

	//Display symmetric key
	cout << "\nSymmetric key:\n" << endl;
	fin.open( SYM_KEY_FILE );
	if( fin.fail() )
	{
		cout << "Error: symmetric.txt file open failed!!! " << endl;
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
 ** Function    : EncryptPlainText()
 ** Description : Encrypt plaintext.txt with symmetric key using OpenSSL to
				  generate ciphertext.txt
 *********************************************************************************/
void EncryptPlainText()
{
	ifstream fin;
	string data;
	string cmd;

	cout <<"\n2. Encrypt plaintext using symmetric key " << endl;

	//Display plain text to encrypt
	cout << "\nPlain Text:\n" << endl;
	fin.open( PLAIN_TEXT_FILE );
	if( fin.fail() )
	{
		cout << "Error: plain text file open failed!!! " << endl;
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

	//Encrypt plaintext using '-aes-256-cbc' algorithm.
	cmd = "openssl enc -aes-256-cbc -salt -in " + std::string( PLAIN_TEXT_FILE )
		+ " -out " + std::string( CIPHER_TEXT_FILE ) + " -pass file:" + std::string( SYM_KEY_FILE );

	//Execute command 'cmd' with system() to decrypt
	cout << "Command: " << cmd << endl;
	const char *command = cmd.c_str(); 
	system(command);

	//Display cipher text
	cout << "\nCipher Text:" << endl;
	fin.open( CIPHER_TEXT_FILE );
	if( fin.fail() )
	{
		cout << "Error: Cipher text file open failed!!! " << endl;
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
** Function     : SignEncryptedText() 
** Description  : Sign ciphertext.txt with my private key to generate signcrypted.txt
*********************************************************************************/
void SignEncryptedText( char signing_key[] )
{
	string cmd;
	string data;
	ifstream fin;
	cout <<"\n\n3. Sign the cipher text " << endl;

	//Sign cipher.
	cmd = "openssl dgst -sha256 -sign " + std::string( signing_key )
		+ " -out " + std::string( SIGNED_CIPHER ) + " " + std::string( CIPHER_TEXT_FILE );

	//Execute command 'cmd' with system() to decrypt
	cout << "\nCommand: " << cmd << endl;
	const char *command = cmd.c_str(); 
	system(command);

	//Display cipher text
	cout << "\nSigned Cipher:" << endl;
	fin.open( SIGNED_CIPHER );
	if( fin.fail() )
	{
		cout << "Error: Signed cipher text file open failed!!! " << endl;
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
	char* encrypted_symmetric_key = NULL;
	char* third_party_public_key = NULL;
	char* my_private_key = NULL;

	if ( argc == 4 )
	{
		encrypted_symmetric_key = argv[ 1 ];
		third_party_public_key = argv[ 2 ];
		my_private_key = argv[ 3 ];

		fs.open( encrypted_symmetric_key );
		if( fs.fail() )
		{
			cout << "Error: Encrypted symmetric key file is invalid!!! " << endl;
			fs.close();
			return 0;
		}
		else if( fs.peek() == std::ifstream::traits_type::eof() )
		{
			cout << "Error: Encrypted symmetric key file is Empty!!! " << endl;
			fs.close();
			return 0;
		}
		fs.close();

		fp.open( third_party_public_key );
		if( fp.fail() )
		{
			cout << "Error: Third party publickey file is invalid!!! " << endl;
			fp.close();
			return 0;
		}
		else if( fp.peek() == std::ifstream::traits_type::eof() )
		{
			cout << "Error: Third party publickey file is Empty!!!! " << endl;
			fp.close();
			return 0;
		}
		fp.close();

		fc.open( my_private_key );
		if( fc.fail() )
		{
			cout << "Error: Private key file is invalid!!! " << endl;
			fc.close();
			return 0;
		}
		else if( fc.peek() == std::ifstream::traits_type::eof() )
		{
			cout << "Error: Private key file is Empty!!! " << endl;
			fc.close();
			return 0;
		}
		fc.close();


		cout <<"\n====== ENCRYPTION ======" << endl;

		//1. Decrypt Encrypted message to get symmetric key
		DecryptSymmetricKey( encrypted_symmetric_key, third_party_public_key );

		//2. Encrypt text file
		EncryptPlainText();

		//3. Sign the encrypted text
		SignEncryptedText( my_private_key );

	}
	else
	{
		cout <<"\n====== ENCRYPTION ======\n" << endl;
		cout << "Usage: ./<binary_name> <path/encrypted_message> <path/third_party_publickey> <path/privatekey>\n" << endl;
		cout << "Example: ./bin/encrypt files/symm_key.bin files/pubkey.pem files/my_privkey.pem\n" << endl; 
		return 0;
	}

	return 0;
}

