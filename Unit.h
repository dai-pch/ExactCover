#ifndef UNIT_H
#define UNIT_H

class Unit: public Node
{
private:
	HeadofColumn *__column;
	HeadofRow *__row;

public:
	Unit();
	Unit(Node &left, Node &right, Node &up, Node &down, HeadofColumn &column, HeadofRow &row);
	
	HeadofColumn &columnhead();
	HeadofRow &rowhead();
	HeadofColumn &setcolumnhead(HeadofColumn &);
	HeadofRow &setrowhead(HeadofRow &);
};

#endif