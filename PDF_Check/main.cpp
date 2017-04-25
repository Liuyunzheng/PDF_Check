#include <iostream>
#include "ac-tree.h"
#include "data-pool.h"
#include "ac-scanner.h"
#include "scan-result.h"

using namespace PDF_CHECK;

int main(int argc, char **argv) {

	std::vector<Bytes> keyword{ { 'a', 'b', 'c' }, { 'c', 'b', 'a' } };
	AcTree tree{ keyword };
	tree.Show();

	DataPool data{ L"f:\\test.txt" };

	AcScanner scanner;
	ScanResult result = scanner.Scan(tree, data);
	result.Show();

	system("pause");
	return 0;
}