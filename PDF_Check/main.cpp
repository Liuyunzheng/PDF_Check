#include <iostream>
#include "ac-tree.h"
#include "data-pool.h"
#include "ac-scanner.h"
#include "scan-result.h"
#include "pdf-checker.h"
#include "pdf-analyze-report.h"

using namespace PDF_CHECK;

int main(int argc, char **argv) {
	std::vector<Bytes> keyword{ { 'a', 'b', 'c' }, { 'c', 'b', 'a' } };
	AcTree tree{ keyword };
	tree.Show();

	DataPool data{ L"f:\\test.pdf" };
	AcScanner scanner;
	ScanResult result = scanner.Scan(tree, data);
	// result.Show();

	std::vector<unsigned int> offsets = result.Find({ 'a', 'b', 'c' });
	for (auto& offset : offsets) {
		std::cout << offset << std::endl;
	}

	for each (char var in result.Find(8)) {
		std::cout << var;
	}
	std::cout << std::endl;

	PdfChecker checker;// { L"f:\\test.pdf" };
	checker.ShowPdfData();
	checker.GetReport(L"f:\\test.doc");

	system("pause");
	return 0;
}