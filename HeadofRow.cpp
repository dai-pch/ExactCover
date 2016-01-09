#include "stdafx.h"

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
		node = &(__right->GetRightNode());
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
		node = &(node->GetRightNode());
	}
	return time;
}

//delet node in this row from the link, return the quantity of the node that deleted
int HeadofRow::deletrow()
{

	//debug
#ifdef _DEBUG
		std::cout << "Delete row:" << __row << std::endl;
#endif

	this->RemoveFromColumn();
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
#ifdef _DEBUG
		std::cout << "Insert row:" << __row << std::endl;
#endif

	this->InsertToColumn();
	return traversal(inserttocolumn1);
}
