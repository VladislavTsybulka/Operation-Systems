#include "pch.h"
#include "CppUnitTest.h"
#include "..\Lab_Work_2_OS_CppUnitTests\Lab_Work_2_OS_CppUnitTests.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LadWorkTests
{
	TEST_CLASS(LadWorkTests)
	{
	public:
		
		TEST_METHOD(TestMinMaxFindFirst) {
			std::vector<int> arr = { 4, 2, 8, 1, 5 };
			std::streambuf* coutBuffer = std::cout.rdbuf();
			std::stringstream output;
			std::cout.rdbuf(output.rdbuf());
			MinMaxFind(arr);
			std::cout.rdbuf(coutBuffer);
			Assert::IsTrue(output.str() == "Min value: 1\nMax value: 8\n");
		}

		TEST_METHOD(TestMinMaxFindSecond) {
			std::vector<int> arr = { 0, 0, 0, 0, 0 };
			std::streambuf* coutBuffer = std::cout.rdbuf();
			std::stringstream output;
			std::cout.rdbuf(output.rdbuf());
			MinMaxFind(arr);
			std::cout.rdbuf(coutBuffer);
			Assert::IsTrue(output.str() == "Min value: 0\nMax value: 0\n");
		}

		TEST_METHOD(TestAverageFindFirst) {
			std::vector<int> arr = { 4, 2, 8, 1, 5 };
			std::streambuf* coutBuffer = std::cout.rdbuf();
			std::stringstream output;
			std::cout.rdbuf(output.rdbuf());
			AverageFind(arr);
			std::cout.rdbuf(coutBuffer);
			Assert::IsTrue(output.str() == "Average: 4\n");
		}

		TEST_METHOD(TestAverageFindSecond) {
			std::vector<int> arr = { 0, 0, 0, 0, 0 };
			std::streambuf* coutBuffer = std::cout.rdbuf();
			std::stringstream output;
			std::cout.rdbuf(output.rdbuf());
			AverageFind(arr);
			std::cout.rdbuf(coutBuffer);
			Assert::IsTrue(output.str() == "Average: 0\n");
		}

		TEST_METHOD(TestMinMaxFindExeption) {
			std::vector<int> arr;
			MinMaxFind(arr);
			Assert::AreEqual("", GetConsoleOutput().c_str());
		}

		TEST_METHOD(TestAverageFindExeption) {
			std::vector<int> arr;
			AverageFind(arr);
			Assert::AreEqual("", GetConsoleOutput().c_str());
		}

		std::string GetConsoleOutput()
		{
			std::stringstream buffer;
			std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
			std::cout.rdbuf(old);
			return buffer.str();
		}
	};
}
