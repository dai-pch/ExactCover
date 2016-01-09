#ifndef OTHER_H
#define OTHER_H

template <typename T>
int printvector(std::vector<T> vec)
{
	std::vector<T>::const_iterator it;
	for (it = vec.begin(); it != vec.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	return 0;
}

int printlink(Head &head);


#endif