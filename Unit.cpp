#include "stdafx.h"

//Unit's code
Unit::Unit() :Node(), __column(nullptr), __row(0){}
Unit::Unit(Node &left, Node &right, Node &up, Node &down, HeadofColumn &column, int row) : Node(left, right, up, down), __column(&column), __row(row)
{
	__column->AddUnitNumber(1);
}

HeadofColumn& Unit::GetColumnHead()
{
	if (__column == nullptr)
	{
		throw std::logic_error("Null pointer.");
	}
	return *__column;
}

HeadofColumn& Unit::SetColumnHead(HeadofColumn &column)
{
	__column = &column;
	return column;
}

int Unit::GetRowNumber()
{
	return __row;
}

//remove node in this column from the link, return 0
int Unit::RemoveColumn()
{
	Node *node;

	//debug
	#ifdef _DEBUG
	std::cout << "Delet column:" << this->GetColumnHead().GetColumnName() << std::endl;
	#endif

	this->RemoveFromRow();

	node = __down;
	while (node != this)
	{
	node->RemoveFromRow();
	node = &(node->GetDownNode());
	}
	return 0;
}

//insert node in this column to the link, return 0
int Unit::InsertColumn()
{
	Node *node;

	//debug
	#ifdef _DEBUG
	std::cout << "Insert column:" << this->GetColumnHead().GetColumnName() << std::endl;
	#endif

	this->InsertToRow();

	node = __up;
	while (node != this)
	{
		node->InsertToRow();
		node = &(node->GetUpNode());
	}
	return 0;
}


//delete the column that have node in this row.
int Unit::RemoveRelatedColumn()
{
	Node *temp;

	//debug
	#ifdef _DEBUG
		std::cout << std::endl << "Select row:" << __row << std::endl;
	#endif

	this->RemoveFromColumn();
	temp = __right;
	while (temp != this)
	{
		(static_cast<Unit*> (temp))->RemoveColumn();
		temp = &(temp->GetRightNode());
	}

	return 0;
}

//insert the column that delrelatedcol delete.
int Unit::InsertRelatedColumn()
{
	Node *temp;
	
	//debug
	#ifdef _DEBUG
	std::cout << std::endl << "Unselect row:" << __row << std::endl;
	#endif
	//debug
	
	this->InsertToColumn();
	temp = __left;
	while (temp != this)
	{
		(static_cast<Unit*> (temp))->InsertColumn();
		temp = &(temp->GetLeftNode());
	}

	return 0;
}
