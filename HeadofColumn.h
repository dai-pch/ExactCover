#ifndef HEADOFCOLUMN_H
#define HEADOFCOLUMN_H

class HeadofColumn :public Node
{
private:
	int __column;

public:
	HeadofColumn();
	HeadofColumn(Node &left, Node &right, int column);
	~HeadofColumn();

	int getcolumnnumber();
	int getunitnumber();

	//traval the node in this column, return the quantity of the node
	int traversal(PF pf);
	//delet node in this column from the link, return the quantity of the node that deleted
	int deletcolumn();
	//insert node in this column to the link, return the quantity of the node that inserted
	int insertcolumn();

	//delete the row that have node in this column.
	int delrelatedrow(const Node &except);
	//insert the row that delrelatedrow delete.
	int insrelatedrow(const Node &except);
};

#endif