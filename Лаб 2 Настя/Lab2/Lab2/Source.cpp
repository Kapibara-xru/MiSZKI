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

byte key[GOST::DEFAULT_KEYLENGTH];

string readFile(const std::string& fileName)
{
	ifstream f(fileName, ios::binary);
	stringstream ss;
	ss << f.rdbuf();
	return ss.str();
}

//������� Encrypt:
std::string Encrypt(std::string plaintext)
{
	CryptoPP::GOST::Encryption gostEncryption(key, CryptoPP::GOST::DEFAULT_KEYLENGTH);
	CryptoPP::ECB_Mode_ExternalCipher::Encryption ebcEncryption(gostEncryption, key);

	// Local variable !
	std::string ciphertext;

	CryptoPP::StreamTransformationFilter stfEncryptor(ebcEncryption, new CryptoPP::StringSink(ciphertext));
	stfEncryptor.Put(reinterpret_cast<const unsigned char*>(plaintext.c_str()), plaintext.length() + 1);
	stfEncryptor.MessageEnd();
	
	return ciphertext;
}

//�������  Decrypt:
std::string Decrypt(std::string plaintext)
{
	CryptoPP::GOST::Decryption gostDecryption(key, CryptoPP::GOST::DEFAULT_KEYLENGTH);
	CryptoPP::ECB_Mode_ExternalCipher::Decryption ebcDecryption(gostDecryption, key);

	// Local variable !
	std::string decryptedtext;

	CryptoPP::StreamTransformationFilter stfDecryptor(ebcDecryption, new CryptoPP::StringSink(decryptedtext));
	stfDecryptor.Put(reinterpret_cast<const unsigned char*>(plaintext.c_str()), plaintext.size());
	stfDecryptor.MessageEnd();
	
	return decryptedtext;
}


int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "rus");
	string k, name_file;
	while (true) {
		do {
			system("cls");
			cout << "\n   ��������� ��������: ";
			cout << "\n1. ����������� ����";
			cout << "\n2. ������������ ����";
			cout << "\n0. �����";
			cout << "\n   ��� �����: ";
			cin >> k;
		} while (k.length() > 1 || k != "1" && k != "2" && k != "0");
		if (k == "1") {
			system("cls");
			cout << "\n ������� ����� 16 ��������: ";
			cin >> key;

			system("cls");
			cout << "\n ������� �������� �����: ";
			cin >> name_file;
			string my_file = readFile(name_file);
			string crypt = Encrypt(my_file);

			ofstream fout;
			fout.open("crypt_" + name_file, ios::trunc | ios::binary);
			fout << crypt;
			fout.close();
		}
		if (k == "2") {
			system("cls");
			cout << "\n ������� ����� 16 ��������: ";
			cin >> key;
			system("cls");
			cout << "\n ������� �������� �����: ";
			cin >> name_file;
			string my_file = readFile(name_file);
			string decrypt = Decrypt(my_file);

			ofstream fout1;
			fout1.open("decrypt_" + name_file, ios::trunc | ios::binary);
			fout1 << decrypt;
			fout1.close();
		}
		if (k == "0") return 0;
	}
	return 0;
}