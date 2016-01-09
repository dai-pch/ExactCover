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
		~Node();

		//four pointer point to the adjacent node
		Node &leftnode();
		Node &rightnode();
		Node &upnode();
		Node &downnode();
		//set four pointer
		Node &setleft(Node &node);
		Node &setright(Node &node);
		Node &setup(Node &node);
		Node &setdown(Node &node);

		//insert this node to the row, return 0
		int inserttorow();
		//insert this node to the column, return 0
		int inserttocolumn();
		//insert this node to the link, return 0
		int insertself();

		//delet this node from the row, return 0
		int deletfromrow();
		//delet this node from the column, return 0
		int deletfromcolumn();
		//delet this node from the link, return 0
		int deletself();

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
