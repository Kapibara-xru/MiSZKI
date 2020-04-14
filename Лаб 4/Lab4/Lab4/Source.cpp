#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "C:\Libraries\cryptopp820\sha.h"
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
	byte digest[CryptoPP::SHA1::DIGESTSIZE];
	SHA1 hash;
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
	string file = "text.txt";
	string message = readFile(file);
	string crypt;
	crypt = Encrypt(message);
	ofstream fout;
	fout.open("hash_" + file, ios::trunc | ios::binary);
	fout << crypt;
	fout.close();
	return 0;
}
