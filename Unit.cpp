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

int Unit::RemoveFromColumn()
{
	__up->SetDown(*__down);
	__down->SetUp(*__up);
	__column->AddUnitNumber(-1);
	return 0;
}

int Unit::InsertToColumn()
{
	__up->SetDown(*this);
	__down->SetUp(*this);
	__column->AddUnitNumber(1);
	return 0;
}

//remove node in this column from the link, return 0
int Unit::RemoveColumn()
{
	Node *node;

	//debug
	#ifdef _DEBUG_MODE
	std::cout << "Delete column:" << this->GetColumnHead().GetColumnName() << std::endl;
	#endif

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
	#ifdef _DEBUG_MODE
	std::cout << "Insert column:" << this->GetColumnHead().GetColumnName() << std::endl;
	#endif

	node = __up;
	while (node != this)
	{
		node->InsertToRow();
		node = &(node->GetUpNode());
	}
	return 0;
}

int Unit::RemoveRow()
{
	Node *node;

	//debug
	#ifdef _DEBUG_MODE
	std::cout << "Delete row:" << this->GetRowNumber() << std::endl;
	#endif

	node = __right;
	while (node != this)
	{
		node->RemoveFromColumn();
		node = &(node->GetRightNode());
	}
	return 0;
}

int Unit::InsertRow()
{
	Node *node;

	//debug
	#ifdef _DEBUG_MODE
	std::cout << "Insert row:" << this->GetRowNumber() << std::endl;
	#endif

	node = __left;
	while (node != this)
	{
		node->InsertToColumn();
		node = &(node->GetLeftNode());
	}
	return 0;
}

//delete the column that have node in this row.
int Unit::RemoveAllRowRelatedToColumn()
{
	Node *temp;
	HeadofColumn &columnHead = this->GetColumnHead();

	//debug
	#ifdef _DEBUG_MODE
		std::cout << std::endl << "Remove all row related to column:" << columnHead.GetColumnName() << std::endl;
	#endif

	temp = __down;
	while (temp != this)
	{
		if (temp == &columnHead)
			temp->RemoveFromRow();
		else
			(static_cast<Unit*> (temp))->RemoveRow();
		temp = &(temp->GetDownNode());
	}

	return 0;
}

//insert the column that delrelatedcol delete.
int Unit::InsertAllRowRelatedToColumn()
{
	Node *temp;
	HeadofColumn &columnHead = this->GetColumnHead();

	//debug
	#ifdef _DEBUG_MODE
	std::cout << std::endl << "Insert all row related to column:" << columnHead.GetColumnName() << std::endl;
	#endif

	temp = __up;
	while (temp != this)
	{
		if (temp == &columnHead)
			temp->InsertToRow();
		else
			(static_cast<Unit*> (temp))->InsertRow();
		temp = &(temp->GetUpNode());
	}

	return 0;
}

int Unit::SelectRow()
{
	Node *temp;

	//debug
	#ifdef _DEBUG_MODE
	std::cout << std::endl << "Select row:" << this->GetRowNumber() << std::endl;
	#endif

	this->RemoveAllRowRelatedToColumn();

	temp = __right;
	while (temp != this)
	{
		(static_cast<Unit*> (temp))->RemoveAllRowRelatedToColumn();
		temp = &(temp->GetRightNode());
	}

	return 0;
}
int Unit::UnSelectRow()
{
	Node *temp;

	//debug
	#ifdef _DEBUG_MODE
	std::cout << std::endl << "Unselect row:" << this->GetRowNumber() << std::endl;
	#endif

	temp = __left;
	while (temp != this)
	{
		(static_cast<Unit*> (temp))->InsertAllRowRelatedToColumn();
		temp = &(temp->GetLeftNode());
	}

	this->InsertAllRowRelatedToColumn();

	return 0;
}
