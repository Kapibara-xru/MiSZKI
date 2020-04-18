using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab3
{
    class Program
    {
        static string pathFile1 = Directory.GetCurrentDirectory() + "\\file1.bmp";
        static string pathFile2 = Directory.GetCurrentDirectory() + "\\file2.bmp";
        static string pathFile3 = Directory.GetCurrentDirectory() + "\\file3.bmp";

        static bool gammaResult;
        static BitArray lrs1;
        static BitArray lrs2;
        static bool buf1 = false, buf2 = false;

        static void Main(string[] args)
        {
            bool exit = true;
            while (exit)
            {
                Console.Clear();
                Console.WriteLine("1.Ввести ключ");
                Console.WriteLine("2.Зашифровать файл");
                Console.WriteLine("3.Расшифровать файл");
                Console.WriteLine("0.Выход");
                ConsoleKeyInfo cki = Console.ReadKey();
                switch (cki.KeyChar)
                {
                    case '1':
                        GenerateKey();
                        break;
                    case '2':
                        EncryptionFile(pathFile1, pathFile2, true);
                        break;
                    case '3':
                        EncryptionFile(pathFile2, pathFile3, false);
                        break;
                    case '0':
                        exit = false;
                        break;
                    default:
                        break;
                }
            }
        }
        /// <summary>
        /// Шифрование файла
        /// </summary>
        static void EncryptionFile(string pathFileIn, string pathFileOut, bool isEcrypt)
        {
            Console.Clear();
            FileStream fileIn = null;
            FileStream fileOut = null;
            try
            {
                fileIn = new FileStream(pathFileIn, FileMode.Open, FileAccess.Read);
                fileOut = new FileStream(pathFileOut, FileMode.Create, FileAccess.Write);

                byte[] t = new byte[40];
                fileIn.Read(t, 0, 40);
                fileOut.Write(t, 0, 40);

                byte[] temp = new byte[1];
                byte gamma = 0;
                while (fileIn.Length > fileIn.Position)
                {
                    gamma = 0;
                    fileIn.Read(temp, 0, 1);
                    if (GammaNext())
                        gamma = (byte)(gamma ^ 1);
                    for (int i = 0; i < 7; i++)
                    {
                        if(GammaNext())
                            gamma = (byte)(gamma ^ 1);
                        gamma = (byte)(gamma << 1);
                    }
                    temp[0] = (byte)(temp[0] ^ gamma);
                    fileOut.Write(temp, 0, 1);
                }
                if (isEcrypt)
                {
                    Console.WriteLine("Файл зашифрован " + pathFileOut);
                }
                else
                {
                    Console.WriteLine("Файл расшифрован " + pathFileOut);
                }
                
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                Console.WriteLine("Ошибка! Не удалось найти или прочитать файл!");
            }
            finally
            {
                if (fileIn != null)
                    fileIn.Close();
                if (fileOut != null)
                    fileOut.Close();
            }
            Console.ReadKey();
        }
        public static bool GammaNext()
        {
            bool temp1 = lrs1[80] ^ lrs1[9] ^ lrs1[4] ^ lrs1[2] ^ lrs1[0];
            bool temp2 = lrs2[80] ^ lrs2[5] ^ lrs2[3] ^ lrs2[2] ^ lrs2[1] ^ lrs2[0];
            gammaResult = lrs1[0] ^ lrs2[0] ^ (buf1 & buf2);
            buf2 = buf1;
            buf1 = gammaResult;
            for(int i = 0; i < 80; i++)
            {
                lrs1[i] = lrs1[i + 1];
                lrs2[i] = lrs2[i + 1];
            }
            lrs1[80] = temp1;
            lrs2[80] = temp2;
            return gammaResult;
        }
        static void GenerateKey()
        {
            Console.Clear();
            gammaResult = false;
            lrs1 = new BitArray(81);
            lrs1[0] = true;
            lrs2 = new BitArray(81);
            lrs2[80] = true;
            buf1 = false;
            buf2 = false;
            Console.WriteLine("Начальные состояния ЛРС заданны");
            Console.ReadKey();
        }
    }
}
