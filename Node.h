#ifndef Node_H
#define Node_H

class Node
{
	protected:
		Node *__left;
		Node *__right;
		Node *__up;
		Node *__down;

	public:
		Node();
		Node(Node &left, Node &right, Node &up, Node &down);
		virtual ~Node();

		//four pointer point to the adjacent node
		Node &GetLeftNode();
		Node &GetRightNode();
		Node &GetUpNode();
		Node &GetDownNode();
		//set four pointer
		Node &SetLeft(Node &node);
		Node &SetRight(Node &node);
		Node &SetUp(Node &node);
		Node &SetDown(Node &node);

		//insert this node to the row, return 0
		int InsertToRow();
		//insert this node to the column, return 0
		int InsertToColumn();
		//insert this node to the link, return 0
		int InsertSelf();

		//delet this node from the row, return 0
		int RemoveFromRow();
		//delet this node from the column, return 0
		int RemoveFromColumn();
		//delet this node from the link, return 0
		int RemoveSelf();

		//friend function of delet, used to traversal
		friend int deletfromrow1(Node &node);
		friend int deletfromcolumn1(Node &node);
		friend int deletself1(Node &node);

		//friend function of insert, used to traversal
		friend int inserttorow1(Node &node);
		friend int inserttocolumn1(Node &node);
		friend int insertself1(Node &node);
};

typedef int (*PF)(Node &);

#endif
