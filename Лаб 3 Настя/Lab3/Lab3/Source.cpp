#include <fstream>
#include <iostream>
#include <bitset>
using namespace std;
bitset<65> LRC1(6525926952262);
bitset<68> LRC2(226523215896315556);
bitset<80> LRC3(7356231968533);
void Init_LRC()
{
	LRC1.reset();	LRC1 |= 6525926952262;
	LRC2.reset();	LRC2 |= 226523215896315556;
	LRC3.reset();	LRC3 |= 7356231968533;
}

char Generator_LRC() {
	char OutGamma = 0;
	for (int j = 0; j < 8; j++)
	{
		char bufGamma = 0;
		if ((LRC1[0] == 1 && LRC2[0] == 1) || (LRC2[0] == 1 && LRC3[0] == 1) || (LRC1[0] == 1 && LRC3[0] == 1)) bufGamma = 1;
		OutGamma <<= 1;
		OutGamma |= bufGamma;
		bool buf = LRC1[64] ^ LRC1[4] ^ LRC1[3] ^ LRC1[1];
		LRC1 >>= 1;		LRC1[64] = buf;
		buf = LRC2[67] ^ LRC2[5] ^ LRC2[2] ^ LRC2[1];
		LRC2 >>= 1;		LRC2[67] = buf;
		buf = LRC3[79] ^ LRC3[4] ^ LRC3[3] ^ LRC3[2];
		LRC3 >>= 1;		LRC3[79] = buf;

	}
	return OutGamma;
}
int main() {
	int kb = 0;
	char buf[16];
	bool start = true;
	setlocale(LC_ALL, "Russian");

	while (start) {
		system("cls");
		cout << "Введи 1 для шифрования или 2 для расшифрования, а для выхода нажми 3" << endl;
		int k = 0;		cin >> k;
		switch (k)
		{
		case 1: {
			Init_LRC();
			kb = 0;
			ifstream inFile("1.bmp", ios_base::binary);
			ofstream outFile("Encrypt.bmp", ios_base::binary | ios_base::trunc);
			cout << "Шифрование..." << endl;
			while (!inFile.eof()) {
				inFile.read(buf, 16);
				if (kb >= 128)
					for (int i = 0; i < inFile.gcount(); i++)
						buf[i] = buf[i] ^ Generator_LRC();
				kb++;
				outFile.write(buf, inFile.gcount());
			}
			cout << "Шифрование завершено" << endl;
			inFile.close(); outFile.close(); system("pause");
			break;
		}
		case 2: {

			Init_LRC();
			kb = 0;
			ifstream inFile("Encrypt.bmp", ios_base::binary);
			ofstream outFile("Decrypt.bmp", ios_base::binary | ios_base::trunc);
			cout << "Расшифровка..." << endl;
			while (!inFile.eof()) {
				inFile.read(buf, 16);
				if (kb >= 128)
					for (int i = 0; i < inFile.gcount(); i++)
						buf[i] = buf[i] ^ Generator_LRC();
				kb++;
				outFile.write(buf, inFile.gcount());
			}
			cout << "Расшифровка завершена" << endl;
			inFile.close(); outFile.close(); system("pause");
			break;
		}
		case 3: //exit
		{
			start = false;
			break;
		}
		default:
		{
			cout << "Неверное значение" << endl;
			system("pause");
			break;	}
		}
	}
	return 0;
}
