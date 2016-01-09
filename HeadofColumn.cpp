#include "stdafx.h"

extern bool debug;

//HeadofColumn's code
HeadofColumn::HeadofColumn() :Node(), __column(0){}
HeadofColumn::HeadofColumn(Node &left, Node &right, int column) : Node(left, right, left, right), __column(column)
{
	__up = __down = this;
}
HeadofColumn::~HeadofColumn()
{
	Node *node;

	while (__down != this)
	{
		node = &(__down->downnode());
		delete __down;
		__down = node;
	}
}

int HeadofColumn::getcolumnnumber()
{
	return __column;
}

int HeadofColumn::getunitnumber()
{
	int num = 0;
	Node *node = &(this->downnode());
	while (node != this)
	{
		num++;
		node = &(node->downnode());
	}
	return num;
}

//traval the node in this column, return the quantity of the node
int HeadofColumn::traversal(PF pf)
{
	Node *node;
	int time = 0;

	node = __down;
	while (node != this)
	{
		(*pf)(*node);
		time++;
		node = &(node->downnode());
	}
	return time;
}
//delet node in this column from the link, return the quantity of the node that deleted
int HeadofColumn::deletcolumn()
{
	//debug
	if (debug)
		std::cout << "delet collumn:" << this->getcolumnnumber() << std::endl;

	this->deletfromrow();
	return traversal(deletfromrow1);
/*	Node *node;
	int time = 0;

	node = __down;
	while (node != this)
	{
		node->deletfromrow();
		time++;
		node = &(node->downnode());
	}
	return time;*/
}

//insert node in this column to the link, return the quantity of the node that inserted
int HeadofColumn::insertcolumn()
{
	this->inserttorow();
	return traversal(inserttorow1);
}

//delete the row that have node in this column.
int HeadofColumn::delrelatedrow(const Node &except)
{
	Node *node;

	//debug
	if (debug)
		std::cout << "Delete column related:" << __column << std::endl;

	this->deletfromrow();
	node = &(this->downnode());

	while (node != this)
	{
		if (node != &except)
		{
			(static_cast<Unit*>(node))->rowhead().deletrow();
			node->inserttocolumn();
		}
		node = &(node->downnode());
	}

	return 0;
}
//insert the row that delrelatedrow delete.
int HeadofColumn::insrelatedrow(const Node &except)
{
	Node *node;

	//debug
	if (debug)
		std::cout << "Insert column related:" << __column << std::endl;

	this->inserttorow();
	node = &(this->downnode());

	while (node != this)
	{
		if (node != &except)
		{
			(static_cast<Unit*>(node))->rowhead().insertrow();
		}
		node = &(node->downnode());
	}
	return 0;
}