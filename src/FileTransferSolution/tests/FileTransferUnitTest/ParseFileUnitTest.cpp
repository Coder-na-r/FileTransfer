#include "pch.h"
#include "CppUnitTest.h"

#include "ParseFile.h"	// Для такого включения, линкеру нужна:
						// 1 - папка на бинарник (директория, где файл из пункта 2) в дополнительных зависимостях библиотек
						// 2 - Линкер - Input - Доп зависимости - указать объектный файл, где определение функций

using std::vector;
using Data::PF::ParseFile;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FileTransferUnitTest
{
	TEST_CLASS(ParseFileTest)
	{
	public:

		TEST_METHOD(TestCreateFile)
		{
			ParseFile file("..\\..\\tests\\FileTransferUnitTest\\forTestParseFile\\fileParse.txt", ParseFile::Type::OUTPUT);

			Assert::IsTrue(file.isOpen() == true, L"File no created");
		}

		TEST_METHOD(TestWriteDataInFile)
		{
			ParseFile file("..\\..\\tests\\FileTransferUnitTest\\forTestParseFile\\fileParse.txt", ParseFile::Type::OUTPUT);

			Assert::IsTrue(file.isOpen() == true, L"File no open");

			uint32_t data = 123;

			Assert::IsTrue(file.writeData((const char*)&data, 4) == true, L"Write data error");

			Assert::IsTrue(file.getSize() == 4, L"Data written, but size no match");
		}

		TEST_METHOD(TestOpenFileAndReadData)
		{
			ParseFile file("..\\..\\tests\\FileTransferUnitTest\\forTestParseFile\\fileParse1.txt", ParseFile::Type::INPUT);

			Assert::IsTrue(file.isOpen() == true, L"File no open");

			Assert::IsTrue(file.getSize() == 4, L"size file no match");

			uint32_t data = 0;

			Assert::IsTrue(file.getData((char*)&data, 4) == 4, L"Get data error");

			Assert::IsTrue(data == uint32_t(123), L"Data not matched");

			Assert::IsTrue(file.getSize() == 4, L"Data get, but size file changed");
		}
	};
}