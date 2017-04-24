#include <iostream>
#include "ac-tree.h"

using namespace PDF_CHECK;

int main(int argc, char **argv) {
	std::vector<Bytes> keyword{ { 'a', 'b', 'c' }, { 'c', 'b', 'a' } };
	AcTree tree{ keyword };
	tree.Show();
	system("pause");
	return 0;
}