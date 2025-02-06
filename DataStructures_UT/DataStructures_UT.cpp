#include "pch.h"
#include "CppUnitTest.h"
#include"../DataStructures/data_structures.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Additinal_ToolsUT
{
	TEST_CLASS(Executor_Testing)
	{
	public:

		TEST_METHOD(ExecuteFunctionSuccededWhenFunctionExecuted)
		{
			//Arrange
			add_tools::executor* executorPtr = new add_tools::executor;
			std::exception ex("");
			//Act
			int r = executorPtr->execute([]() {  }, ex);
			//Assert
			Assert::IsTrue(r == 0, TEXT("Result is FAILED but must be SUCCESS"));
			Assert::IsTrue(strcmp("", ex.what()) == 0, TEXT("Exception was Thrown!"));
			delete executorPtr;
		}

		TEST_METHOD(ExecuteFunctionFailsExceptionIsThrown)
		{
			//Arrange
			const char* ex_msg = "Test exception";
			add_tools::executor* execPtr = new add_tools::executor;
			std::exception ex("");
			//Act
			int r = execPtr->execute([ex_msg]() { throw std::exception(ex_msg); }, ex);
			//Assert
			Assert::IsTrue(r == -1, TEXT("Result is SUCCESS but should be FAILED"));
			Assert::IsTrue(std::strcmp(ex_msg, ex.what()) == 0, TEXT("Exception was Thrown!"));
			delete execPtr;
		}
	};
}


namespace DataStructuresUT
{	
	TEST_CLASS(SingleLinkedListTesting)
	{

		typedef ds::linear_ds::single_linked_list<int> SLLInt;

	public:

		SingleLinkedListTesting()
		{
			_count = 10;
			_numbs = new int[_count];
			_numbs_reverse = new int[_count];
			
			for (size_t i = 0; i < _count; i++)
			{
				_numbs[i] = i;
			}

			for (int i = 0; i < _count; i++)
			{
				_numbs_reverse[i] = _count - (i + 1);
			}
		}

		TEST_METHOD(IterateTest_FullIteration_Success)
		{
			//Arrange
			SLLInt* list = new SLLInt();
				
			std::exception ex("");
			addDataToEndSLL(list, _numbs, _count, ex);

			//Act
			int* res_seq = new int[_count];

			int r = list->iterate([res_seq](int& Obj, int index)-> bool 
				{
					res_seq[index] = Obj;

					return true;
				}, ex);

			//Assert
			Assert::IsTrue(r == 0, TEXT("FAILED must be SUCCESS"));
			Assert::IsTrue(seqCompare(res_seq, _count, _numbs, _count), TEXT("Sequences mismatch!"));

			delete[] res_seq;
			delete list;
		}
		
		TEST_METHOD(IterateTest_PartialIteration_Success)
		{
			//Arrange
			SLLInt* list = new SLLInt();
			int v = 4;
			std::exception ex("");			
			int len = 5;
			int* test = new int[5];

			for (size_t i = 0; i < len; i++)
			{
				test[i] = i;
			}

			addDataToEndSLL(list, test, len, ex);
			
			//Act
			int* res_seq = new int[5];

			int r = list->iterate([res_seq, v](const int& Obj, int index)-> bool
				{
					res_seq[index] = Obj;

					if (index == v)
						return false;

					return true;
				}, ex);

			//Assert
			Assert::IsTrue(r == 0, TEXT("FAILED must be SUCCESS"));
			Assert::IsTrue(seqCompare(res_seq, len, test, len), TEXT("Sequences mismatch!"));

			delete[] res_seq;
			delete list;
			delete test;
		}

		TEST_METHOD(IterateTest_ThrowException_Failed)
		{
			//Arrange
			SLLInt* list = new SLLInt();

			std::exception ex("");
			addDataToEndSLL(list, _numbs, _count, ex);

			//Act
			int* res_seq = new int[_count];

			int r = list->iterate([res_seq](const int& Obj, int index)-> bool
				{
					res_seq[index] = Obj;

					throw std::exception("test");

					return true;
				}, ex);

			//Assert
			Assert::IsTrue(r == -1, TEXT("SUCCESS must be FAILED"));
			Assert::IsTrue(strcmp("test", ex.what()) == 0, TEXT("Incorrect exception message"));

			delete[] res_seq;
			delete list;
		}

		TEST_METHOD(AddToStartTest)
		{
			//Arrange
			ds::linear_ds::single_linked_list<int>* list = new ds::linear_ds::single_linked_list<int>();			
			std::exception ex("");
			int* res_seq = new int[_count];
			//Act
			addDataToSLL(list, _numbs, _count, ex);

			list->ToArray(res_seq, ex);

			//Assert
			Assert::IsTrue(seqCompare(_numbs_reverse, _count, res_seq, _count) && std::strcmp(ex.what(), "") == 0);

			delete[] res_seq;
			delete list;
		}

		TEST_METHOD(AddToEndTest)
		{
			//Arrange
			ds::linear_ds::single_linked_list<int>* list = new ds::linear_ds::single_linked_list<int>();
			std::exception ex("");
			int* res_seq = new int[_count];
			//Act
			for (size_t i = 0; i < _count; i++)
			{
				list->addToEnd(_numbs[i], ex);
			}

			list->ToArray(res_seq, ex);

			//Assert
			Assert::IsTrue(seqCompare(_numbs, _count, res_seq, _count) && std::strcmp(ex.what(), "") == 0);

			delete[] res_seq;
			delete list;
		}

		TEST_METHOD(DeallocationTesting)
		{
			ds::linear_ds::single_linked_list<int>* list = new ds::linear_ds::single_linked_list<int>();
			std::exception ex("");
			int* res_seq = new int[_count];
			//Act
			for (size_t i = 0; i < _count; i++)
			{
				list->addToEnd(_numbs[i], ex);
			}

			delete list;
		}

		~SingleLinkedListTesting()
		{
			delete[] _numbs;
			delete[] _numbs_reverse;
		}

	private:
		int* _numbs;
		int* _numbs_reverse;
		unsigned int _count;	

		bool seqCompare(int* s1, int s1_count, int*s2, int s2_count)
		{
			if (s1_count != s2_count) return false;

			for (size_t i = 0; i < s1_count; i++)
			{
				int a1 = s1[i];
				int a2 = s2[i];

				if (s1[i] != s2[i])
					return false;
			}

			return true;
		}

		template<class T>
		void addDataToSLL(
			ds::linear_ds::single_linked_list<T>* SLLptr, 
			T* src, unsigned int count,
			std::exception& error)
		{
			for (unsigned int i = 0; i < count; i++)
			{
				SLLptr->addToStart(src[i], error);
			}
		}
		template<class T>
		void addDataToEndSLL(
			ds::linear_ds::single_linked_list<T>* SLLptr,
			T* src, unsigned int count,
			std::exception& error)
		{
			for (unsigned int i = 0; i < count; i++)
			{
				SLLptr->addToEnd(src[i], error);
			}
		}

	};
}
