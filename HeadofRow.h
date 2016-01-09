#ifndef HEADOFROW_H
#define HEADOFROW_H

class HeadofRow :public Node
{
private:
	int __row;
public:
	HeadofRow();
	HeadofRow(Node &up, Node &down, int row);
	~HeadofRow();

	int getrownumber();

	//traval the node in this row, return the quantity of the node
	int traversal(PF pf);
	//delet node in this row from the link, return the quantity of the node that deleted
	int deletrow();
	//insert node in this row to the link, return the quantity of the node that inserted
	int insertrow();

	//delete the column that have node in this row.
	int delrelatedcol();
	//insert the column that delrelatedcol delete.
	int insrelatedcol();

};

#endif