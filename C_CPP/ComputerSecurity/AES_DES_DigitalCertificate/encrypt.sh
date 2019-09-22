#!/bin/bash
make clean
make encrypt
./bin/encrypt files/symm_key.bin files/pubkey.pem files/my_privkey.pem
