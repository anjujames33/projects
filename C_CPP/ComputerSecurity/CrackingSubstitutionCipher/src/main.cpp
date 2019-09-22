/*********************************************************************************
** File Name	: Main.cpp							**
** Purpose	: Execution starts from main.cpp			 	**
** Author	: Anju K.James<anju@nmsu.edu>					**
** Version	: 1.0								**
*********************************************************************************/

/* HEADERS */

#include "common.h"


/* FUNCTIONS */

int main( int argc, char* argv[] )
{
    fstream fs;
    char* cipher_text = NULL;
    char* user_key = NULL;

    if ( argc == 2 )
    {
	cipher_text = argv[ 1 ];
    }
    else if( argc == 3 )
    {
	cipher_text = argv[ 1 ];
	user_key = argv[ 2 ];
    }
    else
    {
	cout << "Usage: ./<binary_name> <path/cipher_text_file>" << endl;
	return 0;
    }

    fs.open( cipher_text );
    if( fs.fail() )
    {
	cout << "Error: Cipher Text File does not exist: " << cipher_text << endl;
	fs.close();
	return 0;
    }
    else if( fs.peek() == std::ifstream::traits_type::eof() )
    {
	cout << "Error: Empty Cipher Text File: " << cipher_text << endl;
	fs.close();
	return 0;
    }
    else
    {
	//Valid cipher text file. Start decryption
	ReadCipherText( cipher_text );
	FrequencyAnalysisCipher( cipher_text );

	if( user_key != NULL )
	{
	    //Decrypt the cipher using user provided key
	    cout << "\nUser provided key: " << user_key << endl;
	    Decrypt( cipher_text, user_key );
	}
	else
	{
	    //No key provided by user. So we have to find the key to decrypt cipher text.
	    EnglishFrequency();
	    FindKey( cipher_text );
	}
    }
    fs.close();

    return 0;
}
