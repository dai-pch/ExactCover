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

	virtual int RemoveFromColumn();
	virtual int InsertToColumn();

	int RemoveColumn();
	int InsertColumn();

	int RemoveRow();
	int InsertRow();

	//remove the row that have node in this column.
	int RemoveAllRowRelatedToColumn();
	//insert the row that RemoveAllRowRelatedToColumn removed.
	int InsertAllRowRelatedToColumn();

	int SelectRow();
	int UnSelectRow();
};

#endif