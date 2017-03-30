#include <iostream>
#include "checker.h"
#include "basic-type.h"
#include "pdf.h"

int main(int argc, char **argv) {

	Checker checker;
	std::wstring path(L"F:\\жпнд.pdf");
	checker.read_pdf(path);

	system("pause");

	return 0;
}