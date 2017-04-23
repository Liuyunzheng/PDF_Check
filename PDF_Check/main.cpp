#include <iostream>
#include "pdf-checker.h"
#include "basic-type.h"
#include "pdf.h"

using namespace PDF_CHECK;

int main(int argc, char **argv) {
	std::wstring path{ L"F:\\test.pdf" };
	PdfChecker checker{ path };
	//checker.read_pdf(path);
	checker.ShowPdfData();
	
	_CrtDumpMemoryLeaks();
	system("pause");
	return 0;
}