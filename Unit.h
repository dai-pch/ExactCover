#ifndef UNIT_H
#define UNIT_H

class Unit: public Node
{
private:
	HeadofColumn *__column;
	int __row;

public:
	Unit();
	Unit(Node &left, Node &right, Node &up, Node &down, HeadofColumn &column, int row);

	HeadofColumn &GetColumnHead();
	HeadofColumn &SetColumnHead(HeadofColumn &);
	int GetRowNumber();

	int RemoveColumn();
	int InsertColumn();

	//delete the column that have node in this row.
	int RemoveRelatedColumn();
	//insert the column that delrelatedcol delete.
	int InsertRelatedColumn();
};

#endif