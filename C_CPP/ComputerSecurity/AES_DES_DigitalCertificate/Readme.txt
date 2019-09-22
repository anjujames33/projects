/* Readme.txt */


1. Folder Structure

	Deliverable-02/
	├── bin				// Executables
	│   ├── decrypt			// Binary for decryption
	│   └── encrypt			// Binary for encryption
	├── decrypt.sh			// Script to compile and run decryption
	├── encrypt.sh			// Script to compile and run encryption
	├── files			// All the input and output files are placed in this directory
	│   ├── ciphertext.txt		// Encrypted plaintext (generated during encryption)
	│   ├── my_privkey.pem		// Private key generated in deliverable-01
	│   ├── my_pubkey.pem		// Public key generated in deliverable-01
	│   ├── new_plain_text.txt	// Plain text recovered at final step of decryption (generated during decryption)
	│   ├── plaintext.txt		// Plain text (with name,bannerID etc) to encrypt
	│   ├── pubkey.pem		// Thirdparty public key provided with the question.
	│   ├── signed_cipher		// cipher text after signing (generated during encryption)
	│   ├── symmetric.txt		// Symmetric key recovered after decrypting symm_key.bin (generated during encryption) 
	│   └── symm_key.bin		// Encrypted symmetric key provided with the question
	├── inc				// Include directory for header files.
	│   └── common.h		// Common definitions are made in this header file
	├── Makefile			// Make file to compile the program
	├── obj				// Object diectory for intermediate files
	│   ├── project2_decryption.o
	│   └── project2_encryption.o
	├── Readme.txt
	└── src				// Source directory
	    ├── project2_decryption.cpp	// Code for Decryption
	    └── project2_encryption.cpp	// Code for encryption


2. Usage:

	a. $ cd Deliverable-02/

	b. $ make clean  

		(It will delete binaries, object files and all the files dynamically generated during encryption/decryption)
		rm -rf obj (object files)
		rm -rf bin ()
		rm -rf files/ciphertext.txt 
		rm -rf files/new_plain_text.txt 
		rm -rf files/signed_cipher 
		rm -rf files/symmetric.txt

	c. $ make encrypt (build binary for encryption)

	d. $ ./bin/encrypt files/symm_key.bin files/pubkey.pem files/my_privkey.pem (run binary)

		There are 3 parameters for 'encrypt' binary (All the files are are placed in folder 'files').
		1. Encrypted symmetric key
		2. Third party public key to decrypt symmetric key
		3. Private key generated in deliverable-01 to sign plain text.

	[ Note: For steps b,c and d you can directly use "encrypt.sh" ]

	e. $ make decrypt (build binary for decryption)

	f. $ ./bin/decrypt files/signed_cipher files/my_pubkey.pem files/symmetric.txt

		There are 3 parameters for 'decrypt' binary (All the files are are placed in folder 'files').
		1. Signed cipher text generated during encryption process.
		2. Public key generated during deliverable-01 (verification key)
		3. Symmetric key to decript cipher text

	[ Note: For steps e and f you can directly use "decrypt.sh" ]


3. Output


	1. Encryption

		====== ENCRYPTION ======


		1. Decrypt symm_key.bin with public key

		Command: openssl rsautl -encrypt -pubin -inkey files/pubkey.pem -in files/symm_key.bin -raw -hexdump -out files/symmetric.txt

		Symmetric key:

		0000 - a6 62 06 66 5c aa 36 f6-                          .b.f\.6.
		0100 - <SPACES/NULS>


		2. Encrypt plaintext using symmetric key 

		Plain Text:

		Name        : Anju K. James
		Banner ID   : 800711098
		Symmetric key cryptography algorithm used : aes-256-cbc
		aes-256-cbc is 256-bit AES used to encrypt information at the TOP SECRET level.
		'salt' adds more strength to the encryption.

		Command: openssl enc -aes-256-cbc -salt -in files/plaintext.txt -out files/ciphertext.txt -pass file:files/symmetric.txt

		Cipher Text:
		Salted_�7����)8�L}
				  K溈��-S^�(�O^F�1 �@��œ�I�zgz���\���F� T��P㛭_H9�����$����`��LL��.})Qgs�`���3�'#ܷ����0
		�Ző��m_&�wا�V��^:r��ݨ>n�X�h�k��Y���_P��Y
				                        ��T3�|C�'�� i��-j���_


		3. Sign the cipher text 

		Command: openssl dgst -sha256 -sign files/my_privkey.pem -out files/signed_cipher files/ciphertext.txt

		Signed Cipher:
		t!������3�]�o�E�r��JA��P��J�3%-�|�
		�TC����t29���6�$���e*Ry��{�F]�b�n
		�[��($�������b����7�-T\�qpoV
		��Ƈ<b�mb��Ba��	�y�l��y;�cZ��q�"�I@W��ǎ��❴�^L|���RLQ6=�͑����Uu��\���gG���겗{�yp�����a�l�oݓ<�v����$Z��.k���z�jŢ����F


	2. Decryption

		====== DECRYPTION ======

		1. Verify signed cipher

		Command: openssl dgst -sha256 -verify files/my_pubkey.pem -signature files/signed_cipher files/ciphertext.txt

		Verified OK


		2. Decrypt cipher text 

		Command: openssl enc -d -aes-256-cbc -in files/ciphertext.txt -out files/new_plain_text.txt -pass file:files/symmetric.txt

		Original plain text:

		Name        : Anju K. James
		Banner ID   : 800711098
		Symmetric key cryptography algorithm used : aes-256-cbc
		aes-256-cbc is 256-bit AES used to encrypt information at the TOP SECRET level.
		'salt' adds more strength to the encryption.



/* end */



