#include "stdafx.h"

//Head::Head(): Node(), __totalColumn(0), __totalRow(0){}
Head::Head(int matric[], int m, int n)
{
	int mn = m*n;
	Node *columnHead, *rowHead;
	Node *newUnit;
/*	if (mn*sizeof(int) != sizeof(matric))
		throw std::logic_error("Matric size does not match.");*/

	//debug
	#ifdef _DEBUG
	std::cout << "Creat links:" << std::endl;
	#endif

	for (int ii = 0; ii < n; ii++)
	{
		_CreatColumnHead();
	}

	for (int ii = 0; ii < m; ii++)
	{
		rowHead = nullptr;
		columnHead = this;
		for (int jj = 0; jj < n; jj++)
		{
			columnHead = &(columnHead->GetRightNode());
			if (matric[n*ii + jj] != 0)
			{
				if (rowHead == nullptr)
				{
					newUnit = new Unit(*columnHead, *columnHead, columnHead->GetUpNode(), *columnHead, *(static_cast<HeadofColumn*>(columnHead)), ii);
					if (newUnit != nullptr)
					{
						newUnit->SetLeft(*newUnit);
						newUnit->SetRight(*newUnit);
						newUnit->InsertSelf();
						rowHead = newUnit;
					}
					else
						throw std::logic_error("Can't creat new unit.");
				}
				else
				{
					newUnit = new Unit(rowHead->GetLeftNode(), *rowHead, columnHead->GetUpNode(), *columnHead, *(static_cast<HeadofColumn*>(columnHead)), ii);
					if (newUnit != nullptr)
						newUnit->InsertSelf();
					else
						throw std::logic_error("Can't creat new unit.");
				}
			}
		}
	}

}

Head::Head(const std::vector<int> &matric, int m, int n)
{
	int mn = m*n;
	int ii;
	Node *columnHead, *rowHead;
	Node *newUnit;

	//debug
	#ifdef _DEBUG
	std::cout << "Creat links:" << std::endl;
	#endif

	if (matric.size() != mn)
		throw std::logic_error("Matric size does not match.");

	for (int i = 0; i < n; i++)
	{
		_CreatColumnHead();
	}

	for (int ii = 0; ii < m; ii++)
	{
		rowHead = nullptr;
		columnHead = this;
		for (int jj = 0; jj < n; jj++)
		{
			columnHead = &(columnHead->GetRightNode());
			if (matric[n*ii + jj] != 0)
			{
				if (rowHead == nullptr)
				{
					newUnit = new Unit(*columnHead, *columnHead, columnHead->GetUpNode(), *columnHead, *(static_cast<HeadofColumn*>(columnHead)), ii + 1);
					if (newUnit != nullptr)
					{
						newUnit->SetLeft(*newUnit);
						newUnit->SetRight(*newUnit);
						newUnit->InsertSelf();
						rowHead = newUnit;
					}
					else
						throw std::logic_error("Can't creat new unit.");
				}
				else
				{
					newUnit = new Unit(rowHead->GetLeftNode(), *rowHead, columnHead->GetUpNode(), *columnHead, *(static_cast<HeadofColumn*>(columnHead)), ii + 1);
					if (newUnit != nullptr)
						newUnit->InsertSelf();
					else
						throw std::logic_error("Can't creat new unit.");
				}
			}
		}
	}

}

Head::Head(std::vector<nonZeroPosition> &matric, int m, int n)
{
	std::vector<nonZeroPosition>::const_iterator it;
	int currentRow, currentColumn, lastRow=1;
	Node *columnHead, *rowHead;
	Node *newUnit;

	std::sort(matric.begin(), matric.end(), IsLessNonZeroPosition);

	for (int ii = 0; ii < n; ii++)
	{
		_CreatColumnHead();
	}

	for (it = matric.begin(); it != matric.end(); it++)
	{
		currentRow = (*it).row;
		currentColumn = (*it).column;
		if (currentRow > m || currentColumn > n)
			throw std::logic_error("Node is out of the matric.");

		if (currentRow != lastRow)
		{
			lastRow = currentRow;
			rowHead = nullptr;
			columnHead = this;
		}
		for (int ii = 0; ii < currentColumn; ii++)
			columnHead = &(columnHead->GetRightNode());

		//debug
		#ifdef _DEBUG
		std::cout << "Creat unit " << "(" << currentRow << ", " << currentColumn << ")" << std::endl;
		#endif

		if (rowHead == nullptr)
		{
			newUnit = new Unit(*columnHead, *columnHead, columnHead->GetUpNode(), *columnHead, *(static_cast<HeadofColumn*>(columnHead)), currentRow);
			if (newUnit != nullptr)
			{
				newUnit->SetLeft(*newUnit);
				newUnit->SetRight(*newUnit);
				newUnit->InsertSelf();
				rowHead = newUnit;
			}
			else
				throw std::logic_error("Can't creat new unit.");
		}
		else
		{
			newUnit = new Unit(rowHead->GetLeftNode(), *rowHead, columnHead->GetUpNode(), *columnHead, *(static_cast<HeadofColumn*>(columnHead)), currentRow);
			if (newUnit != nullptr)
				newUnit->InsertSelf();
			else
				throw std::logic_error("Can't creat new unit.");
		}
	}
}

Head::~Head()
{
	while (__right != this)
	{
		delete __right;
	}
}

//creat HeadofColumn object and add it into link, return the total number of column after add
int Head::_CreatColumnHead()
{
	HeadofColumn *newhead;
	int col = 1;

	if (__left == this)
	{
		newhead = new HeadofColumn(*this, *this, col);
	}
	else
	{
		col = ((static_cast<HeadofColumn*> (__left))->GetColumnName()) + 1;
		newhead = new HeadofColumn(*__left, *this, col);
	}

	if (newhead != nullptr)
	{
		newhead->InsertToRow();
		__totalColumn++;
	}
	else
		throw std::logic_error("Can't creat new columnhead.");

	//debug
	#ifdef _DEBUG
		std::cout << "Creat column:" << col << std::endl;
	#endif

	return col;
}

int SolveExactCover(Head &head, std::vector<int> &res)
{
	HeadofColumn *columnHead;
	Unit *unit;
	Node *node;
	int minunit, temp;

	if (&(head.GetRightNode()) == &head)
	{
		#ifdef _DEBUG
			std::cout << "Success." << std::endl;
		#endif
		return 1;
	}
	

	minunit = FindMinColumn(head, columnHead);
	if (minunit == 0)
	{
		#ifdef _DEBUG
			std::cout << "Column " << columnHead->GetColumnName() << " have no unit." << std::endl;
		#endif
		return 0;
	}

	//begin to solve
	node = dynamic_cast<Node*> (columnHead);
	unit = static_cast<Unit*>(&(columnHead->GetDownNode()));
	while (unit != node)
	{
		unit->RemoveRelatedColumn();
		temp = SolveExactCover(head, res);
		unit->InsertRelatedColumn();

		if (temp == 1)
		{
			res.push_back(unit->GetRowNumber());

			//debug
			#ifdef _DEBUG
				std::cout << "Success, return vector: ";
				PrintVector(res);
			#endif

			return 1;
		}
		else if (temp == 0)
			unit = static_cast<Unit*>(&(unit->GetDownNode()));
	}

	return 0;
}

//find the column that contain minimal node
int FindMinColumn(Head &head, HeadofColumn* &minHead)
{
	Node *node;
	int temp;

	//if there is no column head, return -1
	node = &(head.GetRightNode());
	if (node == &head)
		return -1;

	minHead = static_cast<HeadofColumn*>(node);
	while (node != &head)
	{
		temp = (static_cast<HeadofColumn*>(node))->GetUnitNumber();
		if (temp < (static_cast<HeadofColumn*>(minHead))->GetUnitNumber())
		{
			minHead = static_cast<HeadofColumn*>(node);
		}
		node = &(node->GetRightNode());
	}
	return (static_cast<HeadofColumn*>(minHead))->GetUnitNumber();
}


bool IsLessNonZeroPosition(const nonZeroPosition &element1, const nonZeroPosition &element2)
{
	if (element1.row < element2.row)
		return true;
	else
		return  (element1.column < element2.column)?true:false;
}
