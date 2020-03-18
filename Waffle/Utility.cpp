#include "Utility.h"

#include <string>
#include <iostream>
#include <Windows.h>

namespace waffle
{
	void PrintNestedException(const std::exception& e, int level)
	{
		if (level == 0)
			std::cerr << "----------Exception Stack Trace----------" << std::endl;

		std::cerr << std::string(level, ' ') << e.what() << std::endl;
		try
		{
			std::rethrow_if_nested(e);
			std::cerr << "-----------------------------------------" << std::endl;
		}
		catch (const std::exception & e)
		{
			PrintNestedException(e, level + 1);
		}
		catch (...) {}
	}

	std::wstring ExePath()
	{
		std::wstring path;
		path.resize(1024);
		GetModuleFileNameW(NULL, path.data(), path.size());
		path.erase(path.begin() + path.find_last_of(L"\\"), path.end());
		return path + L"\\";
	}
}