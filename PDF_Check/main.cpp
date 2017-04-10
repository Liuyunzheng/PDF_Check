#include <iostream>
#include "pdf-checker.h"
#include "basic-type.h"
#include "pdf.h"

int main(int argc, char **argv) {

	PdfChecker checker;
	std::wstring path{ L"F:\\test.pdf" };
	checker.read_pdf(path);
	checker.ShowPdfData();
	system("pause");
	return 0;
}