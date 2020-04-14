#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

#include "C:\Libraries\cryptopp820\modes.h"
#include "C:\Libraries\cryptopp820\RC6.h"
#include "C:\Libraries\cryptopp820\filters.h"

using namespace std;
using namespace CryptoPP;

byte key[RC6::DEFAULT_KEYLENGTH], iv[RC6::BLOCKSIZE];

string readFile(const std::string& fileName)
{
	ifstream f(fileName, ios::binary);
	stringstream ss;
	ss << f.rdbuf();
	return ss.str();
}

//функция Encrypt:
std::string Encrypt(std::string plaintext)
{
	CryptoPP::RC6::Encryption rc6Encryption(key, CryptoPP::RC6::DEFAULT_KEYLENGTH);
	CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption(rc6Encryption, iv);

	// Local variable !
	std::string ciphertext;

	CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::StringSink(ciphertext));
	stfEncryptor.Put(reinterpret_cast<const unsigned char*>(plaintext.c_str()), plaintext.length() + 1);
	stfEncryptor.MessageEnd();
	
	return ciphertext;
}

//функция  Decrypt:
std::string Decrypt(std::string plaintext)
{
	CryptoPP::RC6::Decryption rc6Decryption(key, CryptoPP::RC6::DEFAULT_KEYLENGTH);
	CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption(rc6Decryption, iv);

	// Local variable !
	std::string decryptedtext;

	CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink(decryptedtext));
	stfDecryptor.Put(reinterpret_cast<const unsigned char*>(plaintext.c_str()), plaintext.size());
	stfDecryptor.MessageEnd();
	
	return decryptedtext;
}


int main(int argc, char* argv[])
{
	memset(key, 0x00, RC6::DEFAULT_KEYLENGTH);
	memset(iv, 0x00, RC6::BLOCKSIZE);

	string name_file = "text.txt";
	string my_file = readFile(name_file);
	
	string plaintext = my_file;	
	string crypt = Encrypt(plaintext);


	ofstream fout;
	fout.open("crypt_" + name_file, ios::trunc | ios::binary);
	fout << crypt;
	fout.close();


	string decrypt = Decrypt(crypt);
	ofstream fout1;
	fout1.open("decrypt_" + name_file, ios::trunc | ios::binary);
	fout1 << decrypt;
	fout1.close();


	return 0;
}