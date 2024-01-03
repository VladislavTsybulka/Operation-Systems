#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab_Work_3_OS/Lab_Work_3_OS.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LabTests
{
	TEST_CLASS(LabTests)
	{
	public:
		
		TEST_METHOD(AllZeroTest)
		{
			std::vector<int> threads = { 0, 0, 0, 0, 0 };
			bool result = all_zero(threads);
			Assert::IsTrue(result);
		}

		TEST_METHOD(MarkerTest)
		{
			std::vector<int> Arr(10);
			for (int i = 0; i < Arr.size(); ++i)
				Arr[i] = 0;

			Marker_Mutex = new std::mutex;
			cond_val_continue = new std::condition_variable;
			cond_val_end = new std::condition_variable;
			cond_val_temporal_workend = new std::condition_variable;

			Vector_Lock.lock();
			std::thread markerThread(Marker, std::ref(Arr), 1);
			Vector_Lock.unlock();

			// Wait for the marker to finish its work
			markerThread.join();

			// Verify the result
			for (int i = 0; i < Arr.size(); ++i)
			{
				Assert::AreEqual(0, Arr[i]);
			}

			delete Marker_Mutex;
			delete cond_val_continue;
			delete cond_val_end;
			delete cond_val_temporal_workend;
		}
	};
}
