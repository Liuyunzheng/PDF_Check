#include <iostream>
#include <fstream>
#include "analyze-report.h"
#include "Checker.h"
#include "pdf.h"

Pdf&& Checker::read_pdf(const std::wstring& path) {
	Bytes in_data;
	Pdf::read(path, in_data);
	Pdf pdf(in_data);
	return std::move(pdf);
}

AnalyzeReport&& Checker::get_report(const std::wstring& path) {
	return read_pdf(path).analyze_all();
}
