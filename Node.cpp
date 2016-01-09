#include "stdafx.h"

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
	RemoveSelf();  //delet this node from the link before free
}

//get the adjacent node
Node& Node::GetLeftNode()
{
	return *__left;
}
Node& Node::GetRightNode()
{
	return *__right;
}
Node& Node::GetUpNode()
{
	return *__up;
}
Node& Node::GetDownNode()
{
	return *__down;
}

//set four pointer
Node& Node::SetLeft(Node &node)
{
	__left = &node;
	return node;
}
Node& Node::SetRight(Node &node)
{
	__right = &node;
	return node;
}
Node& Node::SetUp(Node &node)
{
	__up = &node;
	return node;
}
Node& Node::SetDown(Node &node)
{
	__down = &node;
	return node;
}

//insert this node to the row, return 0
int Node::InsertToRow()
{
	__left->SetRight(*this);
	__right->SetLeft(*this);
	return 0;
}

//insert this node to the column, return 0
int Node::InsertToColumn()
{
	__up->SetDown(*this);
	__down->SetUp(*this);
	return 0;
}

//insert this node to the link, return 0
int Node::InsertSelf()
{
	__up->SetDown(*this);
	__down->SetUp(*this);
	__left->SetRight(*this);
	__right->SetLeft(*this);
	return 0;
}


//delet this node from the row, return 0
int Node::RemoveFromRow()
{
	__left->SetRight(*__right);
	__right->SetLeft(*__left);
	return 0;
}

//delet this node from the column, return 0
int Node::RemoveFromColumn()
{
	__up->SetDown(*__down);
	__down->SetUp(*__up);
	return 0;
}

//delet this node from the link, return 0
int Node::RemoveSelf()
{
	__left->SetRight(*__right);
	__right->SetLeft(*__left);
	__up->SetDown(*__down);
	__down->SetUp(*__up);
	return 0;
}


//friend function of delete

int deletfromrow1(Node &node)
{
	node.RemoveFromRow();
/*	node.GetLeftNode().setright(*(node.__right));
	node.GetRigthNode().setleft(*(node.__left));*/
	return 0;
}

int deletfromcolumn1(Node &node)
{
	node.RemoveFromColumn();
/*	node.GetUpNode().setdown(*(node.__right));
	node.GetDownNode().setup(*(node.__left));*/
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
	node.InsertToRow();
	return 0;
}

int inserttocolumn1(Node &node)
{
	node.InsertToColumn();
	return 0;
}

int insertself1(Node &node)
{
	node.InsertSelf();
	return 0;
}
