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

		TEST_METHOD(ExecuteFunctionFailsRuntimeExceptionIsThrown)
		{
			//Arrange
			const char* ex_msg = "Test exception";
			add_tools::executor* execPtr = new add_tools::executor;
			std::exception ex("");
			//Act
			int r = execPtr->execute([ex_msg]() { throw std::runtime_error(ex_msg); }, ex);
			//Assert
			Assert::IsTrue(r == -1, TEXT("Result is SUCCESS but should be FAILED"));
			Assert::IsTrue(std::strcmp(ex_msg, ex.what()) == 0, TEXT("Exception wasn't Thrown!"));
			delete execPtr;
		}

		TEST_METHOD(ExecuteFunctionFailsUnknownExceptionThrown)
		{
			//Arrange
			const char* ex_msg = "Error! Occured at executeInternal/execute in add_tools::executor.";
			add_tools::executor* execPtr = new add_tools::executor;
			std::exception ex("");
			//Act
			int r = execPtr->execute([ex_msg]() { throw 404; }, ex);
			//Assert
			Assert::IsTrue(r == -1, TEXT("Result is SUCCESS but should be FAILED"));
			Assert::IsTrue(std::strcmp(ex_msg, ex.what()) == 0, TEXT("Exception wasn't Thrown!"));
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
			delete[] test;
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
			Assert::IsTrue(std::strcmp(ex.what(), "") == 0, TEXT("Exception was thrown!"));
			Assert::IsTrue(seqCompare(_numbs_reverse, _count, res_seq, _count), TEXT("Sequence mismatch!"));

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
			Assert::IsTrue(std::strcmp(ex.what(), "") == 0, TEXT("Exception was thrown"));
			Assert::IsTrue(seqCompare(_numbs, _count, res_seq, _count), TEXT("Sequence mismatch"));
			delete[] res_seq;
			delete list;
		}

		TEST_METHOD(DeallocationTesting)
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

			delete list;
		}

		TEST_METHOD(SearchTest_Success)
		{
			//Arrange
			SLLInt* list = new SLLInt();
			int search = 5;
			std::exception ex("");
			addDataToEndSLL(list, _numbs, _count, ex);

			int result = -1;

			//Act
			int r = list->search([search](const int& obj)->bool {
				return obj == search ? true : false;
				}, result, ex);

			//Assert
			Assert::IsTrue(r == 0, TEXT("FAILED must be SUCCESS"));
			Assert::IsTrue(result == search, TEXT("Search and actual results are different!"));
			delete list;
		}

		TEST_METHOD(SearchTest_Failed)
		{
			//Arrange
			SLLInt* list = new SLLInt();
			int search = -20;
			std::exception ex("");
			addDataToEndSLL(list, _numbs, _count, ex);
			int result = -1;
			//Act
			int r = list->search([search](const int& obj)->bool
				{
					return obj == search ? true : false;
				}, result, ex);

			//Assert
			Assert::IsTrue(r == 0, TEXT("FAILED must be SUCCESS"));
			Assert::IsTrue(result == -1, TEXT("Search result should be -1"));
			Assert::IsTrue(strcmp(ex.what(), "") == 0, TEXT("Exception was thrown"));

			delete list;
		}

		TEST_METHOD(ContainsTestSuccess)
		{
			//Arrange
			SLLInt* list = new SLLInt();

			std::exception ex("");
			addDataToEndSLL(list, _numbs, _count, ex);

			//Act
			bool contain = list->contains(1);

			//Assert
			Assert::IsTrue(contain, TEXT("Contain was false must be true"));
			delete list;
		}

		TEST_METHOD(ContainsTestFailed)
		{
			//Arrange
			SLLInt* list = new SLLInt();

			std::exception ex("");
			addDataToEndSLL(list, _numbs, _count, ex);

			//Act
			bool contain = list->contains(-100);

			//Assert
			Assert::IsFalse(contain, TEXT("Contain was true must be false"));
			delete list;
		}

		TEST_METHOD(DeleteTesting_FirstElement_Success)
		{
			SLLInt* list = new SLLInt();			
			std::exception ex("");
			addDataToEndSLL(list, _numbs, _count, ex);
			bool containsRemoved = true;
			//Act
			int r = list->remove([this](const int& obj)->bool
				{
					return obj == _numbs[0] ? true : false;
				}, ex);

			//Verify deletion
			containsRemoved = list->contains(_numbs[0]);

			//Assert
			Assert::IsTrue(r == 0, TEXT("FAILED must be SUCCESS"));
			Assert::IsFalse(containsRemoved, TEXT("First element wasn't removed"));
			delete list;
		}

		TEST_METHOD(DeleteTesting_MiddleElementRemove_Success)
		{
			SLLInt* list = new SLLInt();
			std::exception ex("");
			addDataToEndSLL(list, _numbs, _count, ex);
			bool containsRemoved = true;

			//Get Random number

			std::random_device dev;
			std::mt19937 rng(dev());
			std::uniform_int_distribution<std::mt19937::result_type> dist6(1, _count - 2);
			int n = dist6(rng);

			//Act
			int r = list->remove([this, n](const int& obj)->bool
				{
					return obj == _numbs[n] ? true : false;
				}, ex);

			//Verify deletion
			containsRemoved = list->contains(_numbs[n]);

			//Assert
			Assert::IsTrue(r == 0, TEXT("FAILED must be SUCCESS"));
			Assert::IsFalse(containsRemoved, TEXT("Random middle element wasn't removed!"));
			delete list;
		}

		TEST_METHOD(DeleteTesting_LastElement_Success)
		{
			SLLInt* list = new SLLInt();
			std::exception ex("");
			addDataToEndSLL(list, _numbs, _count, ex);
			bool containsRemoved = true;
			//Act
			int r = list->remove([this](const int& obj)->bool
				{
					return obj == _numbs[_count - 1] ? true : false;
				}, ex);

			//Verify deletion
			containsRemoved = list->contains(_numbs[_count - 1]);

			//Assert
			Assert::IsTrue(r == 0, TEXT("FAILED must be SUCCESS"));
			Assert::IsFalse(containsRemoved, TEXT("Last element wasn't removed"));
			delete list;
		}

		TEST_METHOD(LengtTesting_FullList_Success)
		{
			//Arrange
			SLLInt* list = new SLLInt();
			std::exception ex("");
			addDataToEndSLL(list, _numbs, _count, ex);

			//Act
			int count = list->length();
			//Assert
			Assert::IsTrue(count == _count, TEXT("Counts are not equal"));
			delete list;
		}

		TEST_METHOD(CopyCtorTesting_Success)
		{
			//Arrange
			SLLInt* list1 = new SLLInt();
			std::exception ex("");
			addDataToEndSLL(list1, _numbs, _count, ex);
			//Act
			SLLInt* list2 = new SLLInt(*list1);
			//Assert
			Assert::IsTrue(are2SLLEqual(list1, list2), TEXT("SLLs are not equal"));
			delete list1;
			delete list2;
		}

		TEST_METHOD(AssignmentOperatorTesting_Success)
		{
			//Arrange
			SLLInt* list1 = new SLLInt();
			SLLInt* list2 = new SLLInt();
			std::exception ex("");
			addDataToEndSLL(list1, _numbs, _count, ex);
			//Act
			*list2 = *list1;
			//Assert
			Assert::IsTrue(are2SLLEqual(list1, list2), TEXT("SLLs are not equal"));
			delete list1;
			delete list2;
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

		template<class T>
		bool are2SLLEqual(
			ds::linear_ds::single_linked_list<T>* SLLptr1,
			ds::linear_ds::single_linked_list<T>* SLLptr2)
		{
			bool result = true;

			if (SLLptr1->length() != SLLptr2->length())
				return !result;
			std::exception ex;
			SLLptr1->iterate([SLLptr2, &result](T& obj, int index)->bool
				{
					if (!SLLptr2->contains(obj))
					{
						result = false;
						return false;
					}

					return true;
				}, ex);

			return result;
		}
	};
}
