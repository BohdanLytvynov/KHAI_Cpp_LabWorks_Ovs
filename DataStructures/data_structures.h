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

		int execute(const exec_delegate& function, std::exception& error) const;

		executor();

		~executor();

	private:

		int executeInternal(const exec_delegate& function, std::exception& error) const;
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

			single_linked_list_node(const TObject& data) :
				single_linked_list_node()
			{
				_data = data;
			}

			single_linked_list_node(const single_linked_list_node<TObject>& other) = delete;

			SLLN& operator = (const SLLN& other) = delete;

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
			
			single_linked_list(const SLL& other) : 
				single_linked_list()
			{
				std::exception ex_;
				this->clear(ex_);

				other.iterate([this, &ex_](const TObject& obj, int index)->bool
					{
						addToEnd(obj, ex_);

						return true;
					}, ex_);
			}

			SLL& operator = (const SLL& other)
			{
				std::exception ex_;
				this->clear(ex_);

				other.iterate([this, &ex_](const TObject& obj, int index)->bool
					{
						addToEnd(obj, ex_);

						return true;
					}, ex_);

				return *this;
			}

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

						_count++;

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

			int iterate(std::function<bool(const TObject& obj, int index)> iterator, std::exception& error) const
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
			
			int search(std::function<bool(const TObject& object)> predicate, TObject& result, std::exception& error)
			{
				return this->iterate([&result, predicate](TObject& obj, int index)->bool
					{
						if (predicate(obj))
						{
							result = obj;

							return false;
						}

						return true;
					}, error);
			}

			int remove(std::function<bool(const TObject& object)> predicate, std::exception& error)
			{
				return _executor.execute([this, predicate]()
				{
						SLLNPtr temp = nullptr;

						if (predicate(_start->getData()))//Node to remove located at the start 
						{
							temp = _start;
							_start = temp->getNext();
							delete temp;							
							--_count;
						}
						else //Node located at the middle we need to perform the lookup operation
						{
							SLLNPtr current = _start;

							while (current != nullptr)
							{
								if (predicate(current->getNext()->getData()))//We have found node for deleting
								{
									if (current->getNext()->getNext() == nullptr)//we need to delete last element
									{
										delete current->getNext();
										current->getNext() = nullptr;
										_end = current;
										--_count;
									}
									else
									{
										current->getNext() = current->getNext()->getNext();
										delete current->getNext();
										current->getNext() = nullptr;
										--_count;
									}	

									break;
								}

								current = current->getNext();
							}
						}						
				}, error);
			}

			unsigned int length()
			{
				return _count;
			}

			int clear(std::exception& error)
			{
				if (_count == 0)
					return SUCCESS;

				return _executor.execute([this]()
					{
						this->clearRec(_start);
						_start = nullptr;
						_end = nullptr;
						_count = 0;
					}, error);
			}

			bool contains(const TObject& data)
			{
				if (_count == 0)
					return false;

				bool result = false;
				std::exception ex;
				this->iterate([data, &result](TObject& obj, int index)-> bool
					{
						if (data == obj)
						{
							result = true;
							return false;
						}

						return true;
					}, ex);

				return result;
			}

		private:
			SLLNPtr _start;
			SLLNPtr _end;
			add_tools::executor _executor;
			unsigned int _count;

			void clearRec(SLLNPtr ptrToStart)
			{				
				if (ptrToStart == nullptr)//Recurtion base case (we get the memory after the end node)
					return;
				else
				{
					clearRec(ptrToStart->getNext());
				}
				//Release the memory pointed by the current Pointer
				if (ptrToStart != nullptr)
				{
					delete ptrToStart;				
				}
					
			}
		};
	}
}

#endif // !DATASTRUCTURES_H


