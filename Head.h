#ifndef HEAD_H
#define HEAD_H

struct nonzeroposition
{
	int row;
	int column;
};

class Head :public Node
{
private:
	int __totalrow, __totalcolumn;

	//creat HeadofColumn object and add it into link, return the total number of column after add
	int creatcolumnhead();
	//creat HeadofRow object and add it into link, return the total number of row after add
	int creatrowhead();
	//creat Unit object and add it into link, (column, row) are its position, return 0
	int creatunit(int row, int column);

public:
//	Head();
	Head(int matrix[],int m, int n);
	Head(const std::vector<int> &matric, int m, int n);
	Head(const std::vector<nonzeroposition> &matric, int m, int n);
	~Head();

	friend int solveexactcover(Head &head, std::vector<int> &res);
	friend int findmincol(Head &head, HeadofColumn* &minhead);
};

#endif