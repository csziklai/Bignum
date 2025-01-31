# Bignum RSA Encryption and Decryption
## About
This project includes a custom Bignum class that supports the arithmetic operations of addition, subtraction, multiplication, division, mod, and modular exponentiation. It also encrypts and decrypts text, using RSA.

## Run Arithmetic Operations
After cloning the repo, cd to the `build` directory and run `make` then `./bignum op num1 num2`. For example,
```
./bignum "*" 12 334
```
The supported operators are +, -, "*", /, %, and ^ (note the quotation marks around "*"). ^ is for modular exponentiation, namely a^b % c, so `./bignum ^ a b c`.

## Run Encryption and Decryption
To perform encryption run from root directory
```
g++ -O3 -std=c++2a -Wall -o bignum main.cpp Bignum.cpp && ./bignum e < one.txt
```
where one.txt is the file of the text you want to encrypt.

For decryption, again run from root directory
```
g++ -O3 -std=c++2a -Wall -o bignum main.cpp Bignum.cpp && ./bignum d < encrypt_output.txt
```
where encrypt_output.txt is the output from running encryption (also known as the cipher text, which should look like a large number). You should get the same message back after running decryption.
