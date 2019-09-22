#!/bin/bash
make decrypt
./bin/decrypt files/signed_cipher files/my_pubkey.pem files/symmetric.txt
