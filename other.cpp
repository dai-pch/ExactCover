#include "stdafx.h"

int PrintLink(Head &head)
{
	Node *node;
	Node *rowhead;

	std::cout << "The link is:" << std::endl;
	rowhead = &(head.GetDownNode());

	while (dynamic_cast<Node*>(rowhead) != dynamic_cast<Node*>(&head))
	{
	node = &(rowhead->GetRightNode());
	while (dynamic_cast<Node*>(node) != rowhead)
	{
	std::cout << "(" << (static_cast<Unit*>(node))->GetRowNumber() << ", " << (static_cast<Unit*>(node))->GetColumnHead().GetColumnName() << ")" << " ";
	node = &(node->GetRightNode());
	}
	std::cout << std::endl;

	rowhead = &(rowhead->GetDownNode());
	}

/*	Node *node;
	Node *columnHead;

	columnHead = &(head.rightnode());

	while (dynamic_cast<Node*>(columnHead) != dynamic_cast<Node*>(&head))
	{
	node = &(columnHead->downnode());
	while (dynamic_cast<Node*>(node) != columnHead)
	{
	std::cout << "(" << (static_cast<Unit*>(node))->rowhead().getrownumber() << ", " << (static_cast<Unit*>(node))->GetColumnHead().getcolumnnumber() << ")" << " ";
	node = &(node->downnode());
	}
	std::cout << std::endl;

	columnHead = &(columnHead->rightnode());
	}
	std::cout << std::endl;*/

	return 0;
}
