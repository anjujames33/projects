1. Problem 1 ( Cracking a substitution cipher )

	a. Folder structure :
	
		prob1
		├── bin
		│   └── substitution_cipher	//binary
		├── ciphertext.txt		//cipher text file
		├── dictionary.txt		//dictionary file
		├── inc
		│   └── common.h		//Common header file
		├── Makefile			//Makefile to compile the code
		├── obj
		│   ├── main.o
		│   └── substitution.o
		├── plain_text.txt		//plain text generated with key
		├── Readme.txt			
		└── src				//Source files
		    ├── main.cpp
		    └── substitution.cpp

	b. Usage :

		a. $ cd prob1
		b. $ make clean 	// 'bin','obj' directories and 'plain_text.txt' will be removed.
		c. $ make		// binary will be created in 'bin' folder. 
		d. $ ./bin/substitution_cipher ciphertext.txt [key]	// 'plain_text.txt' will be generated in current folder.
		
			//'Key' is optional parameter. 
			
			Eg:
			1. ./bin/substitution_cipher ciphertext.txt
			2. ./bin/substitution_cipher ciphertext.txt ETOINSAHRCLMUGDFYWVKPBXJQZ


	c. Output :
	
		a. Display the frequency analysis of the cipher text

			The frequency analysis is displayed in the beginning of console logs as below.

			====== Frequency Analysis of Cipher Text ======
			Char: K Count: 57
			Char: R Count: 46
			Char: B Count: 38
			Char: T Count: 29
			Char: P Count: 29
			Char: V Count: 28
			Char: I Count: 28
			Char: L Count: 27
			Char: W Count: 22
			Char: J Count: 17
			Char: C Count: 17
			Char: A Count: 17
			Char: N Count: 15
			Char: O Count: 12
			Char: Y Count: 10
			Char: Q Count: 10
			Char: S Count: 9
			Char: M Count: 9
			Char: E Count: 9
			Char: G Count: 8
			Char: Z Count: 7
			Char: U Count: 7
			Char: D Count: 1


		******************************************************************************************************************


		b. Use the program to guess the cipher key and decrypt the text using it.

			1. Run the binary as "./bin/substitution_cipher ciphertext.txt".

			2. The key is obtained by randomly shifting english letter frequency analysis result.

			3. All the key shifts and corresponding plaintext obtained is displayed in the console.

			4. Final "key" and "plaintext" is available in file "plain_text.txt".
			
  
				====== Plain Text obtained with Key: ETOINSAHRCLMUWDFGBVKPYXJQZ ======

				EVENTHOUWHBEDONTKNOBBHICHCOMPANIESTHENSAHASCOMPROMISEDORYGBHATMEANSKNOBINWTHATTH
				EGCOULDHAVECOMPROMISEDANGOFTHEMISENOUWHTOMAKEUSMISTRUSTFULOFALLOFTHEMTHISISWOINW
				TOMAKEITHARDFORLARWECOMPANIESLIKEWOOWLEANDMICROSOFTTOWETYACKTHETRUSTTHEGLOSTEVEN
				IFTHEGSUCCEEDINLIMITINWWOVERNMENTSURVEILLANCEEVENIFTHEGSUCCEEDINIMPROVINWTHEIROB
				NINTERNALSECURITGTHEYESTTHEGLLYEAYLETOSAGISBEHAVESECUREDOURSELVESFROMTHENSAEXCEP
				TFORTHEPARTSTHATBEEITHERDONTKNOBAYOUTORCANTTALKAYOUT


			5. Manual cryptanalysis is required after running the program to finish decryption.
				
				Compare cipher text and plain text to guess the following mappings.

				W - G
				G - Y
				B - W
				Y - B
				
				Final Key : ETOINSAHRCLMUGDFYWVKPBXJQZ
				
				Plain Text :

				EVENTHOUGHWEDONTKNOWWHICHCOMPANIESTHENSAHASCOMPROMISEDORBYWHATMEANSKNOWINGTHATTH
				EYCOULDHAVECOMPROMISEDANYOFTHEMISENOUGHTOMAKEUSMISTRUSTFULOFALLOFTHEMTHISISGOING
				TOMAKEITHARDFORLARGECOMPANIESLIKEGOOGLEANDMICROSOFTTOGETBACKTHETRUSTTHEYLOSTEVEN
				IFTHEYSUCCEEDINLIMITINGGOVERNMENTSURVEILLANCEEVENIFTHEYSUCCEEDINIMPROVINGTHEIROW
				NINTERNALSECURITYTHEBESTTHEYLLBEABLETOSAYISWEHAVESECUREDOURSELVESFROMTHENSAEXCEP
				TFORTHEPARTSTHATWEEITHERDONTKNOWABOUTORCANTTALKABOUT



		******************************************************************************************************************



		c. Decrypt the text using a key entered by the user.

			1. Execute program with key provided as  "./bin/substitution_cipher ciphertext.txt ETOINSAHRCLMUGDFYWVKPBXJQZ"

			====== Plain Text obtained with Key: ETOINSAHRCLMUGDFYWVKPBXJQZ ======

			EVENTHOUGHWEDONTKNOWWHICHCOMPANIESTHENSAHASCOMPROMISEDORBYWHATMEANSKNOWINGTHATTH
			EYCOULDHAVECOMPROMISEDANYOFTHEMISENOUGHTOMAKEUSMISTRUSTFULOFALLOFTHEMTHISISGOING
			TOMAKEITHARDFORLARGECOMPANIESLIKEGOOGLEANDMICROSOFTTOGETBACKTHETRUSTTHEYLOSTEVEN
			IFTHEYSUCCEEDINLIMITINGGOVERNMENTSURVEILLANCEEVENIFTHEYSUCCEEDINIMPROVINGTHEIROW
			NINTERNALSECURITYTHEBESTTHEYLLBEABLETOSAYISWEHAVESECUREDOURSELVESFROMTHENSAEXCEP
			TFORTHEPARTSTHATWEEITHERDONTKNOWABOUTORCANTTALKABOUT


		******************************************************************************************************************


	d. Algorithm:

		1. Find the frequency analysis of cipher text.
		2. Use English frequency analysis as first key and substitute cipher text with it to get plain text.
		3. Check whether first word in the plain text is a meaningful word.
		4. if not, perform random shifts in key positions and keep a track of key with which we obtained a plaintext 
		   having maximum number of meningful words.
		5. Compare cipher text and plain text obtained to finish cryptanalysis.



