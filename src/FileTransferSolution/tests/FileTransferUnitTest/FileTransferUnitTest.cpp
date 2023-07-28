#include "pch.h"
#include "CppUnitTest.h"

#include "FileSystem.hpp"

using std::vector;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FileTransferUnitTest
{
	TEST_CLASS(FileSystem)
	{
	public:
	
		TEST_METHOD(TestGetDirInfo_NowDirectory)
		{
			DirInfo dirInfo = Data::FS::FileSystem::getDirInfo("..\\..\\tests\\FileTransferUnitTest\\forTestFileSystem\\");

			Assert::IsTrue(dirInfo.files[1] == vector{ "file.txt" } [0] ,
				L"File.txt not match");

			Assert::IsTrue(dirInfo.files[0] == vector{ "dir/1.txt" } [0] ,
				L"dir/1.txt not match");

			Assert::IsTrue(dirInfo.directories[0] == vector{"dir/"}[0] ,
				L"Dirs not match");
		}
	};
}