
#include"pch.h"
#include"data_structures.h"

int add_tools::executor::execute(
	exec_delegate& function,
	std::exception& error)
{
	return add_tools::executor::executeInternal(function, error);
}

int add_tools::executor::execute(
	const exec_delegate& function,
	std::exception& error)
{
	return add_tools::executor::executeInternal(function, error);
}

int add_tools::executor::executeInternal(
	const exec_delegate& function,
	std::exception& error)
{		
	int result = FAILED;

	try
	{
		if (function != nullptr)
		{
			function();
			result = SUCCESS;
		}
	}
	catch (const std::exception& e)
	{
		error = e;
	}
	catch (const std::runtime_error& e)
	{
		error = std::exception(e.what());
	}
	catch (...)
	{
		error = std::exception("Error! Occured at executeInternal/execute in add_tools::executor.");
	}

	return result;
}

add_tools::executor::executor() 
{}

add_tools::executor::~executor()
{}

