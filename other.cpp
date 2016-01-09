#include "stdafx.h"

extern bool debug;

int printlink(Head &head)
{
	Node *node;
	Node *rowhead;

	std::cout << "The link is:" << std::endl;
	rowhead = &(head.downnode());

	while (dynamic_cast<Node*>(rowhead) != dynamic_cast<Node*>(&head))
	{
	node = &(rowhead->rightnode());
	while (dynamic_cast<Node*>(node) != rowhead)
	{
	std::cout << "(" << (static_cast<Unit*>(node))->rowhead().getrownumber() << ", " << (static_cast<Unit*>(node))->columnhead().getcolumnnumber() << ")" << " ";
	node = &(node->rightnode());
	}
	std::cout << std::endl;

	rowhead = &(rowhead->downnode());
	}

/*	Node *node;
	Node *colhead;

	colhead = &(head.rightnode());

	while (dynamic_cast<Node*>(colhead) != dynamic_cast<Node*>(&head))
	{
	node = &(colhead->downnode());
	while (dynamic_cast<Node*>(node) != colhead)
	{
	std::cout << "(" << (static_cast<Unit*>(node))->rowhead().getrownumber() << ", " << (static_cast<Unit*>(node))->columnhead().getcolumnnumber() << ")" << " ";
	node = &(node->downnode());
	}
	std::cout << std::endl;

	colhead = &(colhead->rightnode());
	}
	std::cout << std::endl;*/

	return 0;
}
