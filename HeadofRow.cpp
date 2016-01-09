#include "stdafx.h"

extern bool debug;

//HeadofRow's code
HeadofRow::HeadofRow() :Node(), __row(0){}
HeadofRow::HeadofRow(Node &up, Node &down, int row) : Node(up, down, up, down), __row(row)
{
	__left = __right = this;
}
HeadofRow::~HeadofRow()
{
	Node *node;

	while (__right != this)
	{
		node = &(__right->rightnode());
		delete __right;
		__right = node;
	}
}

int HeadofRow::getrownumber()
{
	return __row;
}

//traval the node in this row, return the quantity of the node
int HeadofRow::traversal(PF pf)
{
	Node *node;
	int time = 0;

	node = __right;
	while (node != this)
	{
		(*pf)(*node);
		time++;
		node = &(node->rightnode());
	}
	return time;
}

//delet node in this row from the link, return the quantity of the node that deleted
int HeadofRow::deletrow()
{

	//debug
	if (debug)
		std::cout << "Delete row:" << __row << std::endl;

	this->deletfromcolumn();
	return traversal(deletfromcolumn1);
/*	Node *node;
	int time = 0;

	node = __right;
	while (node != this)
	{
		node->deletfromcolumn();
		time++;
		node = &(node->rightnode());
	}
	return time;*/
}

//insert node in this row to the link, return the quantity of the node that inserted
int HeadofRow::insertrow()
{
	//debug
	if (debug)
		std::cout << "Insert row:" << __row << std::endl;

	this->inserttocolumn();
	return traversal(inserttocolumn1);
}

//delete the column that have node in this row.
int HeadofRow::delrelatedcol()
{
	Node *temp;

	//debug
	if (debug)
		std::cout << std::endl << "Select row:" << __row << std::endl;

	this->deletfromcolumn();
	temp = &(this->rightnode());
	while (temp != this)
	{
		(static_cast<Unit*> (temp))->columnhead().delrelatedrow(*temp);
		temp = &(temp->rightnode());
	}

	return 0;
}
//insert the column that delrelatedcol delete.
int HeadofRow::insrelatedcol()
{
	Node *temp;

	//debug
	if (debug)
		std::cout << std::endl << "Cancel row selection:" << __row << std::endl;

	this->inserttocolumn();
	temp = &(this->leftnode());
	while (temp != this)
	{
		(static_cast<Unit*> (temp))->columnhead().insrelatedrow(*temp);
		temp = &(temp->leftnode());
	}

	return 0;
}