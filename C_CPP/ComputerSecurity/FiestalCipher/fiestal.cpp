/* Author       : Anju K James
** Purpose      : Familiarization of Fiestal cipher
** Description  : Encryption and decription of given plain text using given keys.
*/

#include<iostream>
#include<bitset>
#include<vector>
#include <string>
#include <cstring>

#define BLOCK_SIZE  		8
#define HALF_BLOCK_SIZE		(BLOCK_SIZE/2)
#define NUMBER_OF_ROUNDS	4
#define PLAIN_TEXT  		"10110101"

using namespace std;

typedef bitset < HALF_BLOCK_SIZE > keystream;
typedef bitset< BLOCK_SIZE > text;

string Encrypt( keystream keys[], text plain_text )
{
    bitset < HALF_BLOCK_SIZE > left_half;
    bitset < HALF_BLOCK_SIZE > right_half;
    bitset < HALF_BLOCK_SIZE > prev_left;
    bitset < HALF_BLOCK_SIZE > prev_right;

    cout << "\n===========Encryption===========\n" << endl;

    cout<< "Plain Text: " << plain_text << endl;

    for( int i = 0; i < BLOCK_SIZE; ++i )
    {
        if( i < HALF_BLOCK_SIZE )
        {
            //'0' index starts from right side
            right_half.set( i, plain_text[ i ] );
        }
        else
        {
            left_half.set( i - 4, plain_text[ i ] );
        }
    } 

    cout << "Initial Left Half : " << left_half << endl;
    cout << "Initial Right Half : " << right_half << endl;

    prev_left = left_half;
    prev_right = right_half;

    for(int i = 0; i < NUMBER_OF_ROUNDS; ++i ) 
    {
        cout << "\n---------Round : " << i+1 << " Key: " << keys[ i ] << "---------" << endl;
        left_half = prev_right;
        right_half = prev_left ^ ( prev_right ^ keys[ i ] );

        cout << "Left Half : " << left_half << endl;
        cout << "Right Half : " << right_half << endl;

        prev_left = left_half;
        prev_right = right_half;

    }

    string cipher_text = left_half.to_string() + right_half.to_string();
    cout<< "Cipher Text: " <<  cipher_text << endl;
    return cipher_text;

}

void Decrypt( keystream keys[], string cipher )
{
    text cipher_text = bitset< 8 >( string( cipher ));
    bitset < HALF_BLOCK_SIZE > left_half;
    bitset < HALF_BLOCK_SIZE > right_half;
    bitset < HALF_BLOCK_SIZE > prev_left;
    bitset < HALF_BLOCK_SIZE > prev_right;

    cout << "\n===========Decryption===========\n" << endl;

    cout<< "Cipher Text: " << cipher_text << endl;

    for( int i = 0; i < BLOCK_SIZE; ++i )
    {
        if( i < HALF_BLOCK_SIZE )
        {
            //'0' index starts from right side
            right_half.set( i, cipher_text[ i ] );
        }
        else
        {
            left_half.set( i - 4, cipher_text[ i ] );
        }
    } 

    cout << "Initial Left Half : " << left_half << endl;
    cout << "Initial Right Half : " << right_half << endl;

    prev_left = left_half;
    prev_right = right_half;

    for(int i = NUMBER_OF_ROUNDS - 1 ; i >= 0; --i ) 
    {
        cout << "\n---------Round : " << i+1 << " Key: " << keys[ i ] << "---------" << endl;
        right_half = prev_left;
        left_half = prev_right ^ ( prev_left ^ keys[ i ] );

        cout << "Left Half : " << left_half << endl;
        cout << "Right Half : " << right_half << endl;

        prev_left = left_half;
        prev_right = right_half;

    }

    string plain_text = left_half.to_string() + right_half.to_string();
    cout<< "Plain Text: " <<  plain_text << endl;

}

int main()
{
    text plain_text = bitset< 8 >( string( PLAIN_TEXT ));
    keystream keys[ NUMBER_OF_ROUNDS ];
    string cipher;

    keys[0] = bitset< 4 >( string( "1011" ));
    keys[1] = bitset< 4 >( string( "0100" ));
    keys[2] = bitset< 4 >( string( "0101" ));
    keys[3] = bitset< 4 >( string( "1010" ));

    cipher = Encrypt( keys, plain_text );
    cout << "-----------" << endl;
    cout << " CIPHER: " << cipher << endl;
    Decrypt( keys, cipher );

    return 0;
}
