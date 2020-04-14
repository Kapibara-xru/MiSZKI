#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

#include "C:\Libraries\cryptopp820\modes.h"
#include "C:\Libraries\cryptopp820\GOST.h"
#include "C:\Libraries\cryptopp820\filters.h"

using namespace std;
using namespace CryptoPP;

byte key[GOST::DEFAULT_KEYLENGTH], iv[GOST::BLOCKSIZE];

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
	CryptoPP::GOST::Encryption gostEncryption(key, CryptoPP::GOST::DEFAULT_KEYLENGTH);
	CryptoPP::ECB_Mode_ExternalCipher::Encryption ebcEncryption(gostEncryption, iv);

	// Local variable !
	std::string ciphertext;

	CryptoPP::StreamTransformationFilter stfEncryptor(ebcEncryption, new CryptoPP::StringSink(ciphertext));
	stfEncryptor.Put(reinterpret_cast<const unsigned char*>(plaintext.c_str()), plaintext.length() + 1);
	stfEncryptor.MessageEnd();
	
	return ciphertext;
}

//функция  Decrypt:
std::string Decrypt(std::string plaintext)
{
	CryptoPP::GOST::Decryption gostDecryption(key, CryptoPP::GOST::DEFAULT_KEYLENGTH);
	CryptoPP::ECB_Mode_ExternalCipher::Decryption ebcDecryption(gostDecryption, iv);

	// Local variable !
	std::string decryptedtext;

	CryptoPP::StreamTransformationFilter stfDecryptor(ebcDecryption, new CryptoPP::StringSink(decryptedtext));
	stfDecryptor.Put(reinterpret_cast<const unsigned char*>(plaintext.c_str()), plaintext.size());
	stfDecryptor.MessageEnd();
	
	return decryptedtext;
}


int main(int argc, char* argv[])
{
	memset(key, 0x00, GOST::DEFAULT_KEYLENGTH);
	memset(iv, 0x00, GOST::BLOCKSIZE);

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