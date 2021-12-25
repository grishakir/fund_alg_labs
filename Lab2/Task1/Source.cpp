#include "TBinaryTree.h"

int main() {

	Comparator<int>* comparer = new Comparator<int>;

	binary_search_tree<int, int> tree(comparer);

	return 0;
}