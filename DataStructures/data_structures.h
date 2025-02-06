//Header guard
#ifndef DATA_STRUCTURES_H

#define DATA_STRUCTURES_H

#include<iostream>
#include<functional>

#pragma region Exporter / Importer Specificator

#if defined(DATASTRUCTURES_EXPORT)//Case when we are building the dll inside this project
#define DS_API __declspec(dllexport)
#else
#define DS_API __declspec(dllimport)
#endif

#pragma endregion

#pragma region Macroses

#define SUCCESS 0;
#define FAILED -1;

#define tmpl template<class TObject>

#pragma endregion

namespace add_tools
{	
	typedef std::function<void(void)> exec_delegate;

	struct DS_API executor
	{				
		int execute(exec_delegate& function, std::exception& error);

		int execute(const exec_delegate& function, std::exception& error);

		executor();

		~executor();
		
	private:

		int executeInternal(const exec_delegate& function, std::exception& error);
	};
}

namespace ds
{
	namespace linear_ds
	{
		tmpl
		struct single_linked_list_node
		{
			typedef single_linked_list_node<TObject> SLLN;
			typedef single_linked_list_node<TObject>* SLLNPtr;

			single_linked_list_node()
			{
				_next = nullptr;
			}
			
			explicit single_linked_list_node(const TObject& data) :
				single_linked_list_node<TObject>()
			{
				_data = data;
			}
			
			single_linked_list_node(const single_linked_list_node<TObject>& other)
			{
				
			}

			SLLN& operator = (const SLLN& other)
			{
				return *this;
			}

			TObject& getData() noexcept
			{
				return _data;
			}

			SLLNPtr& getNext() noexcept
			{
				return _next;
			}

		private:
			TObject _data;
			SLLNPtr _next;			
		};

		tmpl
		struct single_linked_list
		{
			typedef single_linked_list_node<TObject> SLLN;
			typedef single_linked_list<TObject> SLL;
			typedef single_linked_list_node<TObject>* SLLNPtr;

			single_linked_list() 				
			{
				_count = 0;
				_start = nullptr;
				_end = nullptr;
			}

			~single_linked_list()
			{
				std::exception ex_;
				this->clear(ex_);
			}

			//No copy semantic for now
			//single_linked_list(const SLL& other) = delete;

			//SLL& operator = (const SLL& other) = delete;

			int addToStart(TObject data, std::exception& error)
			{		
				return _executor.execute([data, this]()
					{
						SLLNPtr dataPtr = new SLLN(data);

						if (_start == nullptr && _end == nullptr)//SLL is empty, so add new data to the start 
						{
							//Now _start and end are pointing at the first node
							_start = dataPtr;
							_end = dataPtr;
						}
						else
						{
							dataPtr->getNext() = _start;
							_start = dataPtr;
						}

						_count++;

				}, error);				
			}

			int addToEnd(TObject data, std::exception& error)
			{
				return _executor.execute([data, this]()
					{
						SLLNPtr dataPtr = new SLLN(data);

						if (_start == nullptr && _end == nullptr)// SLL is empty
						{
							_start = dataPtr;
							_end = dataPtr;
						}
						else
						{
							_end->getNext() = dataPtr;
							_end = dataPtr;
						}
					}, error
				);
			}

			int ToArray(TObject* result, std::exception& error)
			{
				return this->iterate([&result](TObject& obj, int index)->bool
					{						
						result[index] = obj;

						return true;
					}, error
				);			
			}
						
			int iterate(std::function<bool(TObject& obj, int index)> iterator, std::exception& error)
			{
				return _executor.execute([this, iterator]()
					{
						if (iterator == nullptr)
							return;

						bool stop = false;
						SLLNPtr temp = _start;
						int i = 0;
						while (temp != nullptr)
						{
							stop = iterator(temp->getData(), i);

							if (!stop)
								break;

							++i;

							temp = temp->getNext();
						}
					}, error);
			}

			unsigned int length()
			{
				return _count;
			}

			int clear(std::exception& error)
			{
				return _executor.execute([this]()
					{
						this->clearRec(_start);
						_start = nullptr;
						_end = nullptr;

					}, error);
			}

		private:
			SLLNPtr _start;
			SLLNPtr _end;
			add_tools::executor _executor;
			unsigned int _count;

			void clearRec(SLLNPtr ptrToStart)
			{
				if (ptrToStart == nullptr)//Recurtion base case(we get the end node)
					return;
				else
				{
					clearRec(ptrToStart->getNext());
				}
				//Release the memory pointed by the current Pointer
				if(ptrToStart != nullptr)
					delete ptrToStart;
			}			
		};				
	}
}

#endif // !DATASTRUCTURES_H


