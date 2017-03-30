#include <iostream>
#include <fstream>
#include "analyze-report.h"
#include "Checker.h"
#include "pdf.h"

Checker::Checker() :_pdf(nullptr) {

}

void Checker::read_pdf(const std::wstring& path) {
	Bytes in_data;
	Pdf::read(path, in_data);
	_pdf.reset(new Pdf(in_data));
}

AnalyzeReport Checker::get_report(const std::wstring& path) {
	read_pdf(path);
	return _pdf->analyze_all();
}

void Checker::show_pdf_data() const {
	if (_pdf)
		_pdf->show();
}

Bytes Checker::get_pdf_data() const {
	if (_pdf)
		return _pdf->get_data();
	else
		return Bytes();
}