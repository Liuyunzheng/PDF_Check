#include <iostream>
#include "checker.h"
#include "basic-type.h"
#include "pdf.h"

void test();

int main(int argc, char **argv) {
	Checker checker;
	std::wstring path(L"F:\\中文.txt");
	Pdf&& pdf = checker.read_pdf(path);
	Bytes data = pdf.get_data();
	std::cout << data.size();
	for (auto c : data)
		std::cout << c;
	std::cout << std::endl;

	system("pause");

	return 0;
}

void test() {
	Bytes data;
	std::wstring path(L"F:\\中文.txt");
	Pdf::read(path, data);
	for (auto c : data)
		std::cout << c;
	std::cout << std::endl;
}