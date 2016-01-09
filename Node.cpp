#include "stdafx.h"

extern bool debug;

//Node's code
Node::Node():__left(this), __right(this), __up (this), __down(this)
{
//	__left = __right = __up = __down = &this;
}

Node::Node(Node &left, Node &right, Node &up, Node &down):__left(&left), __right(&right), __up(&up), __down(&down)
{
//	__left = left;
//	__right = right;
//	__up = up;
//	__down = down;
}

Node::~Node()
{
	deletself();  //delet this node from the link before free
}

//get the adjacent node
Node& Node::leftnode()
{
	return *__left;
}
Node& Node::rightnode()
{
	return *__right;
}
Node& Node::upnode()
{
	return *__up;
}
Node& Node::downnode()
{
	return *__down;
}

//set four pointer
Node& Node::setleft(Node &node)
{
	__left = &node;
	return node;
}
Node& Node::setright(Node &node)
{
	__right = &node;
	return node;
}
Node& Node::setup(Node &node)
{
	__up = &node;
	return node;
}
Node& Node::setdown(Node &node)
{
	__down = &node;
	return node;
}

//insert this node to the row, return 0
int Node::inserttorow()
{
	__left->setright(*this);
	__right->setleft(*this);
	return 0;
}

//insert this node to the column, return 0
int Node::inserttocolumn()
{
	__up->setdown(*this);
	__down->setup(*this);
	return 0;
}

//insert this node to the link, return 0
int Node::insertself()
{
	this->inserttocolumn();
	this->inserttorow();
	return 0;
}


//delet this node from the row, return 0
int Node::deletfromrow()
{
	__left->setright(*__right);
	__right->setleft(*__left);
	return 0;
}

//delet this node from the column, return 0
int Node::deletfromcolumn()
{
	__up->setdown(*__down);
	__down->setup(*__up);
	return 0;
}

//delet this node from the link, return 0
int Node::deletself()
{
	this->deletfromrow();
	this->deletfromcolumn();
	return 0;
}


//friend function of delete

int deletfromrow1(Node &node)
{
	node.deletfromrow();
/*	node.leftnode().setright(*(node.__right));
	node.rightnode().setleft(*(node.__left));*/
	return 0;
}

int deletfromcolumn1(Node &node)
{
	node.deletfromcolumn();
/*	node.upnode().setdown(*(node.__right));
	node.downnode().setup(*(node.__left));*/
	return 0;
}

int deletself1(Node &node)
{
	deletfromrow1(node);
	deletfromcolumn1(node);
	return 0;
}


//friend function of insert

int inserttorow1(Node &node)
{
	node.inserttorow();
	return 0;
}

int inserttocolumn1(Node &node)
{
	node.inserttocolumn();
	return 0;
}

int insertself1(Node &node)
{
	node.insertself();
	return 0;
}
