/*********************************************************************************
** File Name	: substitution.cpp						**
** Purpose	: Defines all the decryption functions			 	**
** Author	: Anju K.James<anju@nmsu.edu>					**
** Version	: 1.0								**
*********************************************************************************/

/* HEADERS */
#include "common.h"

/* GLOBAL VARIABLES */
char cipher[] = {0};

/* FUNCTIONS */

/*********************************************************************************
** Function	: ReadCipherText
** Description	: Read cipher text from file and print it to console
*********************************************************************************/
void ReadCipherText( char cipher_text[] )
{
    char ch;
    ifstream fin;

    //Print given cipher text
    fin.open( cipher_text );
    cout << "\n====== CIPHER TEXT ======" << endl;
    while( !fin.eof() )
    {
	if( fin.get( ch ) )
	{
	    cout << ch; 
	}
    }
    fin.close();
}

/*********************************************************************************
** Function	: FrequencyAnalysisCipher
** Description	: Computes the frequency analysis of cipher text and arrange 
		  it in descending order
*********************************************************************************/
void FrequencyAnalysisCipher( char cipher_text[] )
{
    char ch;
    int flag = 0;
    int index =0;
    ifstream fin;
    alphabet letter_frequency;
    std::vector<pairs> vec;

    //Frequency analysis of the ciphertext
    fin.open( cipher_text );
    while( !fin.eof() )
    {
	if( fin.get( ch ) )
	{
	    if( ch != NEW_LINE )
	    {
		flag =0;
		if( !letter_frequency.empty() )
		{
		    for( auto index = letter_frequency.begin(); index != letter_frequency.end(); ++index )
		    {
			if( index->first == ch )
			{
			    ++index->second;
			    flag = 1;
			    break;
			}
		    }
		    if( !flag )
		    {
			letter_frequency[ ch ] = 1;
		    }
		}
		else
		{
		    letter_frequency[ ch ] = 1;
		}
	    }
	}
    }
    fin.close();

    //Sort the frequency analysis map in descending order
    cout << "\n====== Frequency Analysis of Cipher Text ======" << endl;
    copy( letter_frequency.begin(), letter_frequency.end(), back_inserter< vector< pairs > >( vec ) );
    sort( vec.begin(), vec.end(), []( const pairs& element1, const pairs& element2 ) 
    {
	if( element1.second != element2.second )
	{
	    return element1.second > element2.second;
	}
	else
	{
	    return element1.first > element2.first;
	}
    } );

    //Display the sorted frequency list with count and copy alphabets to an array to compare with key.
    for( auto const &pairs: vec ) 
    {
	cout << "Char: "<< pairs.first << " Count: " << pairs.second << endl;
	cipher[ index ] = pairs.first;
	++index;
    }
}

/*********************************************************************************
** Function	: EnglishFrequency()
** Description	: Display the standard frequency of English alphabets 
		  it in descending order
*********************************************************************************/
void EnglishFrequency()
{
    char english[] = {'E', 'T', 'A', 'O', 'I', 'N', 'S', 'H', 'R', 'D',
	'L', 'C', 'U', 'M', 'W', 'F', 'G', 'Y', 'P', 'B', 'V', 'K', 'J', 'X', 'Q', 'Z' };

    cout << "\n====== English letter frequency ======" << endl;
    for( int i = 0; i < sizeof( english ); ++i )
    {
	cout << english[ i ];
    }
}

/*********************************************************************************
** Function	: CompareWithDictionary()
** Description	: Compare the plain text file generated with dictionary to find 
		  the number of meaningful words.
*********************************************************************************/
int CompareWithDictionary()
{
    string word;
    string buffer;
    int count = 0;
    ifstream dictionary;
    ifstream plaintxt;

    dictionary.open( DICTIONARY );
    plaintxt.open( PLAIN_TEXT );

    getline( plaintxt, buffer );

    while( !dictionary.eof() )
    {
	dictionary >> word;

	if( buffer.find( word ) != std::string::npos ) 
	{
	    ++count;
	}
    }

    dictionary.close();
    plaintxt.close();

    return count;
}

/*********************************************************************************
** Function	: CompareWordWithDictionary()
** Description	: Compare the first word of plain text to check whether it is 
		  a meaningful word.
*********************************************************************************/
int CompareWordWithDictionary( string buffer )
{
    string word;
    ifstream dictionary;

    dictionary.open( DICTIONARY );

    while( !dictionary.eof() )
    {
	dictionary >> word;

	if ( buffer.compare( word ) == 0 )
	{
	    //found
	    cout << "\n Word: " << word << " Buff: " << buffer <<endl;
	    dictionary.close();
	    return 1;
	}
    }

    dictionary.close();
    return 0;
}

/*********************************************************************************
** Function	: Decryption()
** Description	: Decrypt the cipher text with the key provided, and generate 
		  plain_text.txt. The function returns the count of meaningful words
		  in plain text obtained.
*********************************************************************************/
int Decryption( char cipher_text[], char key[] )
{
    char ch;
    ifstream fin;
    ofstream fout;
    int count = 0; 

    cout << "\n====== Decrypt with Key: ";
    for( int i = 0; i < KEY_SIZE; ++i )
    {
	cout << key[ i ];
    }
    cout << "======\n" << endl;

    fin.open( cipher_text );
    fout.open( PLAIN_TEXT );

    while( !fin.eof() )
    {
	if( fin.get( ch ) )
	{
	    if( ch == cipher[0] )
	    {
		cout << key[0];
		fout << key[0];
	    }
	    else if( ch == cipher[1] )
	    {
		cout << key[1];
		fout << key[1];
	    }
	    else if( ch == cipher[2] )
	    {
		cout << key[2];
		fout << key[2];
	    }
	    else if( ch == cipher[3] )
	    {
		cout << key[3];
		fout << key[3];
	    }
	    else if( ch == cipher[4] )
	    {
		cout << key[4];
		fout << key[4];
	    }
	    else if( ch == cipher[5] )
	    {
		cout << key[5];
		fout << key[5];
	    }
	    else if( ch == cipher[6] )
	    {
		cout << key[6];
		fout << key[6];
	    }
	    else if( ch == cipher[7] )
	    {
		cout << key[7];
		fout << key[7];
	    }
	    else if( ch == cipher[8] )
	    {
		cout << key[8];
		fout << key[8];
	    }
	    else if( ch == cipher[9] )
	    {
		cout << key[9];
		fout << key[9];
	    }
	    else if( ch == cipher[10] )
	    {
		cout << key[10];
		fout << key[10];
	    }
	    else if( ch == cipher[11] )
	    {
		cout << key[11];
		fout << key[11];
	    }
	    else if( ch == cipher[12] )
	    {
		cout << key[12];
		fout << key[12];
	    }
	    else if( ch == cipher[13] )
	    {
		cout << key[13];
		fout << key[13];
	    }
	    else if( ch == cipher[14] )
	    {
		cout << key[14];
		fout << key[14];
	    }
	    else if( ch == cipher[15] )
	    {
		cout << key[15];
		fout << key[15];
	    }
	    else if( ch == cipher[16] )
	    {
		cout << key[16];
		fout << key[16];
	    }
	    else if( ch == cipher[17] )
	    {
		cout << key[17];
		fout << key[17];
	    }
	    else if( ch == cipher[18] )
	    {
		cout << key[18];
		fout << key[18];
	    }
	    else if( ch == cipher[19] )
	    {
		cout << key[19];
		fout << key[19];
	    }
	    else if( ch == cipher[20] )
	    {
		cout << key[20];
		fout << key[20];
	    }
	    else if( ch == cipher[21] )
	    {
		cout << key[21];
		fout << key[21];
	    }
	    else if( ch == cipher[22] )
	    {
		cout << key[22];
		fout << key[22];
	    }
	    else if( ch == NEW_LINE )
	    {
		//Do not write '\n' to file. So that we will get accurate count of meaningful 
		//words in plain text generated. else '\n' will cut words.
		cout << ch;
	    }
	    else
	    {
		cout << ch;
		fout <<ch;
	    }
	}
    }

    fin.close();
    fout.close();

    count = CompareWithDictionary();
    cout << "\nNumber of Meaningful words : " << count << endl;
    cout << "\n\n";
    return count;
}

/*********************************************************************************
** Function	: Decrypt()
** Description	: Decrypt the cipher text with the key provided by user to generate 
		  plain_text.txt
*********************************************************************************/
void Decrypt( char cipher_text[], char key[] )
{
    char ch;
    ifstream fin;
    ofstream fout;

    fin.open( cipher_text );
    fout.open( PLAIN_TEXT );

    cout << "\n\n====== Plain Text obtained with Key: ";
    fout << "\n\n====== Plain Text obtained with Key: ";
    for( int i = 0; i < KEY_SIZE; ++i )
    {
	cout << key[ i ];
	fout << key[ i ];
    }
    cout << " ======\n" << endl;
    fout << " ======\n" << endl;

    while( !fin.eof() )
    {
	if( fin.get( ch ) )
	{
	    if( ch == cipher[0] )
	    {
		cout << key[0];
		fout << key[0];
	    }
	    else if( ch == cipher[1] )
	    {
		cout << key[1];
		fout << key[1];
	    }
	    else if( ch == cipher[2] )
	    {
		cout << key[2];
		fout << key[2];
	    }
	    else if( ch == cipher[3] )
	    {
		cout << key[3];
		fout << key[3];
	    }
	    else if( ch == cipher[4] )
	    {
		cout << key[4];
		fout << key[4];
	    }
	    else if( ch == cipher[5] )
	    {
		cout << key[5];
		fout << key[5];
	    }
	    else if( ch == cipher[6] )
	    {
		cout << key[6];
		fout << key[6];
	    }
	    else if( ch == cipher[7] )
	    {
		cout << key[7];
		fout << key[7];
	    }
	    else if( ch == cipher[8] )
	    {
		cout << key[8];
		fout << key[8];
	    }
	    else if( ch == cipher[9] )
	    {
		cout << key[9];
		fout << key[9];
	    }
	    else if( ch == cipher[10] )
	    {
		cout << key[10];
		fout << key[10];
	    }
	    else if( ch == cipher[11] )
	    {
		cout << key[11];
		fout << key[11];
	    }
	    else if( ch == cipher[12] )
	    {
		cout << key[12];
		fout << key[12];
	    }
	    else if( ch == cipher[13] )
	    {
		cout << key[13];
		fout << key[13];
	    }
	    else if( ch == cipher[14] )
	    {
		cout << key[14];
		fout << key[14];
	    }
	    else if( ch == cipher[15] )
	    {
		cout << key[15];
		fout << key[15];
	    }
	    else if( ch == cipher[16] )
	    {
		cout << key[16];
		fout << key[16];
	    }
	    else if( ch == cipher[17] )
	    {
		cout << key[17];
		fout << key[17];
	    }
	    else if( ch == cipher[18] )
	    {
		cout << key[18];
		fout << key[18];
	    }
	    else if( ch == cipher[19] )
	    {
		cout << key[19];
		fout << key[19];
	    }
	    else if( ch == cipher[20] )
	    {
		cout << key[20];
		fout << key[20];
	    }
	    else if( ch == cipher[21] )
	    {
		cout << key[21];
		fout << key[21];
	    }
	    else if( ch == cipher[22] )
	    {
		cout << key[22];
		fout << key[22];
	    }
	    else if( ch == NEW_LINE )
	    {
		//Do not write to file. So that we will get accurate count of meaningful 
		//words in plain text generated. else '\n' will cut words.
		cout << ch;
		fout << ch;
	    }
	    else
	    {
		cout << ch;
		fout <<ch;
	    }
	}
    }

    fin.close();
    fout.close();

    cout << "\n\n" ;
}

/*********************************************************************************
** Function	: ShiftKey()
** Description	: Shift the key by swapping key letters in index 'pos' and 'n'  
		  and decrypt after each swap until count of meaningful words 
		  is constant
*********************************************************************************/
void ShiftKey( int pos, int max, char max_key[], char cipher_text[], int n, data* ret_data )
{
    char temp;
    char key[] = {'e', 't', 'a', 'o', 'i', 'n', 's', 'h', 'r', 'd', 'l', 'c', 'u',
	'm', 'w', 'f', 'g', 'y', 'p', 'b', 'v', 'k', 'j', 'x', 'q', 'z' };
    int prev_letter_count = 0;
    int letter_count = 1;

    memcpy( key, max_key, KEY_SIZE );

    while( letter_count != prev_letter_count )
    {
	prev_letter_count = letter_count;
	letter_count = Decryption( cipher_text, key );

	if( max < letter_count )
	{
	    max = letter_count;
	    memcpy( max_key, key, KEY_SIZE );
	}

	temp = key[pos + n];
	key[pos + n] = key[pos];
	key[pos ] = temp;
	++pos;
    }

    ret_data->max = max;
    memcpy( ret_data->max_key, max_key, KEY_SIZE );
}

/*********************************************************************************
** Function	: FindKey()
** Description	: Find the key to decrypt cipher text by comparing with english 
		  letter frequncy analysis and key shifts  
*********************************************************************************/
void FindKey( char cipher_text[] )
{
    int letter_count = 0;
    char prev_key[26] = { 0 };
    int prev_letter_count = -1;
    int round = 1;
    char first[ 3 ] = { '\0' };
    char second[ 4 ] = { '\0' };
    char third[ 5 ] = { '\0' };
    int ret = 0;
    char max_key[26] = {'\0'};
    int max = 0;
    char temp;
    data ret_data;


    //Use English letter frequency list as initial key
    char key[] = {'E', 'T', 'A', 'O', 'I', 'N', 'S', 'H', 'R', 'D', 'L', 'C', 'U',
    	'M', 'W', 'F', 'G', 'Y', 'P', 'B', 'V', 'K', 'J', 'X', 'Q', 'Z' };

    //Start decryption using english letter frequency key
    max = Decryption( cipher_text, key );

    //Check plain text whether first word( 3,4,5 letters ) is meaningful or not
    ifstream plaintxt;
    plaintxt.open( PLAIN_TEXT );

    //Read first first 3 characters of plain text
    plaintxt >> first[ 0 ] >> first[ 1 ] >> first[ 2 ];

    //Read first first 4 characters of plain text
    plaintxt >> second[ 0 ] >> second[ 1 ] >> second[ 2 ] >> second[ 3 ];

    //Read first first 5 characters of plain text
    plaintxt >> third[ 0 ] >> third[ 1 ] >> third[ 2 ] >> third[ 3 ] >> third[ 4 ];

    if( CompareWordWithDictionary( first ) )
    {
	cout << "\nFirst word is a meaningful 3 letter word now : ";
	for( int i = 0; i < sizeof( first ); ++i )
	{
	    cout << first[ i ];
	}
	cout << "\n";
    }
    else if( CompareWordWithDictionary( second ) )
    {
	cout << "\nFirst word is a meaningful 4 letter word now : ";
	for( int i = 0; i < sizeof( second ); ++i )
	{
	    cout << second[ i ];
	}
	cout << "\n";
    }
    else if( CompareWordWithDictionary( third ) )
    {
	cout << "\nFirst word is a meaningful 5 letter word now : ";
	for( int i = 0; i < sizeof( third ); ++i )
	{
	    cout << third[ i ];
	}
	cout << "\n";
    }
    else
    {
	ret_data.max = max;
	memcpy( ret_data.max_key, key, KEY_SIZE );

	//Shift key randomly to get the accurate key and note the key for maximum meaningful words.
	ShiftKey( 2, ret_data.max, ret_data.max_key, cipher_text, 1, &ret_data );
	ShiftKey( 9, ret_data.max, ret_data.max_key, cipher_text, 2, &ret_data );
	ShiftKey( 11, ret_data.max, ret_data.max_key, cipher_text, 1, &ret_data );
	ShiftKey( 11, ret_data.max, ret_data.max_key, cipher_text, 2, &ret_data );
	ShiftKey( 13, ret_data.max, ret_data.max_key, cipher_text, 1, &ret_data );
	ShiftKey( 17, ret_data.max, ret_data.max_key, cipher_text, 2, &ret_data );
	ShiftKey( 22, ret_data.max, ret_data.max_key, cipher_text, 1, &ret_data );

	//Decrypt th cipher text with the key obtained.
	Decrypt( cipher_text, ret_data.max_key );
    }

    plaintxt.close();
}
