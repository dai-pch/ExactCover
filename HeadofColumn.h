#ifndef HEADOFCOLUMN_H
#define HEADOFCOLUMN_H

class HeadofColumn :public Node
{
private:
	int __columnName;
	int __unitNumber;

public:
	HeadofColumn();
	HeadofColumn(Node &left, Node &right, int columnName);
	virtual ~HeadofColumn();

	int GetColumnName();
	int GetUnitNumber();
	int AddUnitNumber(int num);

	//traval the node in this column, return the quantity of the node
	int traversal(PF pf);

};

#endif