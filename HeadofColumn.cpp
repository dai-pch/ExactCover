#include "stdafx.h"

//HeadofColumn's code
HeadofColumn::HeadofColumn() :Node(), __columnName(0), __unitNumber(0){}
HeadofColumn::HeadofColumn(Node &left, Node &right, int columnName) : Node(left, right, left, right), __columnName(columnName), __unitNumber(0)
{
	__up = __down = this;
}
HeadofColumn::~HeadofColumn()
{
	RemoveFromRow();
	while (__down != this)
	{
		delete __down;
	}
}

int HeadofColumn::GetColumnName()
{
	return __columnName;
}

int HeadofColumn::GetUnitNumber()
{
	return __unitNumber;
}

int HeadofColumn::AddUnitNumber(int num)
{
	return __unitNumber += num;
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
		node = &(node->GetDownNode());
	}
	return time;
}
