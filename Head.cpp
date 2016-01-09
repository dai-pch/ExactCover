#include "stdafx.h"

extern bool debug;

//Head::Head(): Node(), __totalcolumn(0), __totalrow(0){}
Head::Head(int matric[], int m, int n)
{
	int mn = m*n;
/*	if (mn*sizeof(int) != sizeof(matric))
		throw std::logic_error("Matric size does not match.");*/

	//debug
	if (debug)
		std::cout << "Creat links:" << std::endl;

	for (int i = 0; i < n; i++)
	{
		creatcolumnhead();
	}
	for (int i = 0; i < m; i++)
	{
		creatrowhead();
	}
	for (int i = 0; i < mn; i++)
	{
		if (matric[i] != 0)
			creatunit(i / n + 1, i % n + 1);
	}

}

Head::Head(const std::vector<int> &matric, int m, int n)
{
	int mn = m*n;
	std::vector<int>::const_iterator it;
	int ii;

	if (matric.size() != mn)
		throw std::logic_error("Matric size does not match.");

	for (int i = 0; i < n; i++)
	{
		creatcolumnhead();
	}
	for (int i = 0; i < m; i++)
	{
		creatrowhead();
	}
	for (it = matric.begin(), ii = 0; it != matric.end(); it++, ii++)
	{
		if (*it != 0)
			creatunit(ii / n + 1, ii % n + 1);
	}
}

Head::Head(const std::vector<nonzeroposition> &matric, int m, int n)
{
	std::vector<nonzeroposition>::const_iterator it;

	for (int ii = 0; ii < n; ii++)
	{
		creatcolumnhead();
	}
	for (int ii = 0; ii < m; ii++)
	{
		creatrowhead();
	}
	for (it = matric.begin(); it != matric.end(); it++)
	{
		if ((*it).row > m || (*it).column > n)
			throw std::logic_error("Node is out of the matric.");
		creatunit((*it).row, (*it).column);
	}
}

Head::~Head()
{
	Node *node;
	while (__right != this)
	{
		node = &(__right->rightnode());
		delete __right;
		__right = node;
	}
	while (__down != this)
	{
		node = &(__down->downnode());
		delete __down;
		__down = node;
	}
}

//creat HeadofColumn object and add it into link, return the total number of column after add
int Head::creatcolumnhead()
{
	HeadofColumn *newhead;
	int col = 1;

	if (__left == this)
	{
		newhead = new HeadofColumn(*this, *this, col);
	}
	else
	{
		col = ((static_cast<HeadofColumn*> (__left))->getcolumnnumber()) + 1;
		newhead = new HeadofColumn(*__left, *this, col);
	}
	if (newhead != NULL)
	{
		newhead->inserttorow();
		__totalcolumn++;
	}
	else
		throw std::logic_error("Can't creat new columnhead.");

	//debug
	if (debug)
		std::cout << "Creat column" << col << std::endl;

	return col;
}
//creat HeadofRow object and add it into link, return the total number of row after add
int Head::creatrowhead()
{
	HeadofRow *newhead;
	int row = 1;

	if (__up == this)
	{
		newhead = new HeadofRow(*this, *this, row);
	}
	else
	{
		row = ((static_cast<HeadofRow*> (__up))->getrownumber()) + 1;
		newhead = new HeadofRow(*__up, *this, row);
	}
	if (newhead != NULL)
	{
		newhead->inserttocolumn();
		__totalrow++;
	}
	else
		throw std::logic_error("Can't creat new rowhead.");

	//debug
	if (debug)
		std::cout << "Creat row" << row << std::endl;

	return row;
}
//creat Unit object and add it into link, (column, row) are its position, return 0
int Head::creatunit(int row, int column)
{
	HeadofColumn *colhead;
	HeadofRow *rowhead;
	Node *tempcol, *temprow;
	Unit *newunit;

	if (__totalcolumn < column)
		throw std::logic_error("Column not found.");
	if (__totalrow < row)
		throw std::logic_error("Row not found.");

	tempcol = __right;
	for (int i = 1; i < column; i++)
	{
		tempcol = &(tempcol->rightnode());
	}
	colhead = static_cast<HeadofColumn*> (tempcol);

	temprow = __down;
	for (int i = 1; i < row; i++)
	{
		temprow = &(temprow->downnode());
	}
	rowhead = static_cast<HeadofRow*> (temprow);

	tempcol = &(tempcol->upnode());
	while ((tempcol != colhead) && ((static_cast<Unit*> (tempcol))->rowhead().getrownumber() > row))
		tempcol = &(tempcol->upnode());
	
	temprow = &(temprow->leftnode());
	while ((temprow != rowhead) && ((static_cast<Unit*> (temprow))->columnhead().getcolumnnumber() > column))
		temprow = &(temprow->leftnode());

	newunit = new Unit(*temprow, temprow->rightnode(), *tempcol, tempcol->downnode(), *colhead, *rowhead);
	if (newunit != NULL)
		newunit->insertself();
	else
		throw std::logic_error("Can't creat new unit.");

	//debug
	if (debug)
		std::cout << "Creat unit " << "(" << newunit->rowhead().getrownumber() << ", " << newunit->columnhead().getcolumnnumber() << ")" << std::endl;

	return 0;
}

int solveexactcover(Head &head, std::vector<int> &res)
{
	HeadofColumn *colhead;
	Unit *unit;
	Node *node;
	int minunit, temp;

	if (&(head.rightnode()) == &head)
	{
		if (debug)
			std::cout << "Success." << std::endl;
		return 1;
	}
	

	minunit = findmincol(head, colhead);
	if (minunit == 0)
	{
		if (debug)
			std::cout << "Column " << colhead->getcolumnnumber() << " have no unit." << std::endl;
		return 0;
	}

	//begin to solve
	node = dynamic_cast<Node*> (colhead);
	unit = static_cast<Unit*>(&(colhead->downnode()));
	while (unit != node)
	{
		unit->rowhead().delrelatedcol();
		temp = solveexactcover(head, res);
		unit->rowhead().insrelatedcol();

		if (temp == 1)
		{
			res.push_back(unit->rowhead().getrownumber());

			//debug
			if (debug)
			{
				std::cout << "Success, return vector: ";
				printvector(res);
			}

			return 1;
		}
		else if (temp == 0)
			unit = static_cast<Unit*>(&(unit->downnode()));
	}
	
	return 0;
}

//find the column that contain minimal node
int findmincol(Head &head, HeadofColumn* &minhead)
{
	Node *node;
	int minunit, temp;

	//if there is no column head, return -1
	if (&(head.rightnode()) == &head)
		return -1;

	node = &(head.rightnode());
	minhead = static_cast<HeadofColumn*>(node);
	minunit = (static_cast<HeadofColumn*>(node))->getunitnumber();
	while (node != &head)
	{
		temp = (static_cast<HeadofColumn*>(node))->getunitnumber();
		if (temp < minunit)
		{
			minunit = temp;
			minhead = static_cast<HeadofColumn*>(node);
		}
		node = &(node->rightnode());
	}
	return minunit;
}