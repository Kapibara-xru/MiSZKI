#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "C:\Libraries\cryptopp820\md5.h"
#include "C:\Libraries\cryptopp820\hex.h"
using namespace std;
using namespace CryptoPP;
string readFile(const std::string& fileName) {
	ifstream f(fileName, ios::binary);
	stringstream ss;
	ss << f.rdbuf();
	return ss.str();
}
std::string Encrypt(std::string message) {
	setlocale(LC_ALL, "RUS");
	byte digest[CryptoPP::Weak::MD5::DIGESTSIZE];
	Weak::MD5 hash;
	hash.CalculateDigest(digest, (const byte*)message.c_str(), message.length());
	HexEncoder encoder;
	string output;
	encoder.Attach(new StringSink(output));
	encoder.Put(digest, sizeof(digest));
	encoder.MessageEnd();
	return output;
}
int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "RUS");

	string k, name_file;
	while (true) {
		do {
			system("cls");
			cout << "\n   Доступные операции: ";
			cout << "\n1. Получить хэш";
			cout << "\n0. Выйти";
			cout << "\n   Ваш выбор: ";
			cin >> k;
		} while (k.length() > 1 || k != "1" && k != "0");
		if (k == "1") {
			system("cls");
			cout << "\n Введите название файла: ";
			cin >> name_file;
			string message = readFile(name_file);
			string crypt;
			crypt = Encrypt(message);
			ofstream fout;
			fout.open("hash.txt", ios::trunc | ios::binary);
			fout << crypt;
			fout.close();
			system("cls");
			cout << "\nХэш записан в файл. \n";
			system("pause");
		}
		if (k == "0") return 0;
	}
	return 0;
}
