#include "List_of_platforms.h"
#include <SFML/Graphics.hpp>


int main()
{
	List_of_platforms lop;
	lop.init();
	lop.list.print();
	printf("\n");
	lop.update(10, 1);
	lop.list.print();
	printf("\n");
	lop.update(550, 1);
	lop.list.print();

	return 0;
}
