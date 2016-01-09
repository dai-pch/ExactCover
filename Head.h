#ifndef HEAD_H
#define HEAD_H

struct nonZeroPosition
{
	int row;
	int column;
};

bool IsLessNonZeroPosition(const nonZeroPosition &element1, const nonZeroPosition &element2);

class Head :public Node
{
private:
	int __totalRow, __totalColumn;

	//creat HeadofColumn object and add it into link, return the total number of column after add
	int _CreatColumnHead();
	//creat Unit object and add it into link, (column, row) are its position, return 0
	int _CreatUnit(int row, int column);

public:
//	Head();
	Head(int matrix[],int m, int n);
	Head(const std::vector<int> &matric, int m, int n);
	Head(std::vector<nonZeroPosition> &matric, int m, int n);
	~Head();

	friend int SolveExactCover(Head &head, std::vector<int> &res);
	friend int FindMinColumn(Head &head, HeadofColumn* &minHead);
};

#endif