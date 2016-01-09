// Exactcover.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#define MATRIX_MOUDLE 1
#define VECTOR_MOUDLE 2

int _tmain(int argc, _TCHAR* argv[])
{
	int model = VECTOR_MOUDLE;
	bool printtime = false, aut = false;
	for (int ii = 1; ii < argc; ii++)
	{
		if (_tcscmp(argv[ii], _TEXT("-v")) == 0)
			model = VECTOR_MOUDLE;
		if (_tcscmp(argv[ii], _TEXT("-m")) == 0)
			model = MATRIX_MOUDLE;
		if (_tcscmp(argv[ii], _TEXT("-t")) == 0)
			printtime = true;
		if (_tcscmp(argv[ii], _TEXT("-a")) == 0)
			aut = true;
/*		if (_tcscmp(argv[ii], _TEXT("-d")) == 0)
			debug = true;*/
	}
/*	int matric[] = { 1, 0, 0, 1, 0, 0, 1,
		1, 0, 0, 1, 0, 0, 0,
		0, 0, 0, 1, 1, 0, 1,
		0, 0, 1, 0, 1, 1, 0,
		0, 1, 1, 0, 0, 1, 1,
		0, 1, 0, 0, 0, 0, 1 };*/
	int m = 0, n = 0, temp;
	std::vector<int> res;
	Head *dl = nullptr;

	clock_t start_time = clock();
	{
		if (!aut)
		{
			std::cout << "Please input the row and column number:" << std::endl;
		}
		std::cin >> m;
		std::cin >> n;
		if (m == 0 || n == 0)
		{
			std::cout << 0 << std::endl << "The size of the matrix can't be zero." << std::endl;
			return 0;
		}

		if (model == MATRIX_MOUDLE)
		{
			std::vector<int> ini;

			if (!aut)
			{
				std::cout << "Please input the element of the "<< m << "*" << n << " matrix:" << std::endl;
			}
			for (int i = 0; i < m * n; i++)
			{
				std::cin >> temp;
				if (temp == 0)
					ini.push_back(temp);
				else
					ini.push_back(1);
			}
			dl = new Head(ini, m, n);
		}
		else if (model == VECTOR_MOUDLE)
		{
			nonZeroPosition po;
			std::vector<nonZeroPosition> ini;

			if (!aut)
			{
				std::cout << "Please input the position of the nonzero number, input 0 or nagetive number to stop:" << std::endl;
			}
			while (1)
			{
				std::cin >> temp;
				if (temp < 1)
					break;
				else if (temp > m)
				{
					std::cout << 0 << std::endl << "Row out of range." << std::endl;
					return 0;
				}
				po.row = temp;
				std::cin >> temp;
				if (temp < 1)
					break;
				else if (temp > n)
				{
					std::cout << 0 << std::endl << "Column out of range." << std::endl;
					return 0;
				}
				po.column = temp;
				ini.push_back(po);
				if (!aut)
				{
					std::cout << std::endl;
				}
			}
			dl = new Head(ini, m, n);
		}

		try
		{
			if (dl != nullptr)
			{
				temp = SolveExactCover(*dl, res);
				delete dl;
				if (temp == 0)
				{
					std::cout << 0 << std::endl << "No solutions." << std::endl;
				}
				else
				{
					if (!aut)
					{
						std::cout << "The result is:" << std::endl;
					}
					PrintVector(res);
				}
			}
			else
				std::cout << 0 << std::endl << "Can't creat structure." << std::endl;
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	clock_t end_time = clock();
	if (printtime)
		std::cout << "Running time is: " << static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1000 << "ms" << std::endl;//输出运行时间
	
//	system("Pause");
	return 0;
}


