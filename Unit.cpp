#include "stdafx.h"

extern bool debug;

//Unit's code
Unit::Unit() :Node(), __column(NULL), __row(NULL){}
Unit::Unit(Node &left, Node &right, Node &up, Node &down, HeadofColumn &column, HeadofRow &row) : Node(left, right, up, down), __column(&column), __row(&row){}

HeadofColumn& Unit::columnhead()
{
	if (__column == NULL)
	{
		throw std::logic_error("Null pointer.");
	}
	return *__column;
}
HeadofRow& Unit::rowhead()
{
	if (__row == NULL)
	{
		throw std::logic_error("Null pointer.");
	}
	return *__row;
}
HeadofColumn& Unit::setcolumnhead(HeadofColumn &column)
{
	__column = &column;
	return column;
}
HeadofRow& Unit::setrowhead(HeadofRow &row)
{
	__row = &row;
	return row;
}