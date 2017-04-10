#include <iostream>
#include <fstream>
#include "pdf-analyze-report.h"
#include "pdf-checker.h"
#include "pdf.h"

PdfChecker::PdfChecker() :_pdf{ nullptr } {

}

bool PdfChecker::read_pdf(const std::wstring& path) {
	if (!_pdf) {
		_pdf.reset(new Pdf{ path });
	}
	bool can_read = _pdf->Read(path);
	
	return can_read;
}

PdfAnalyzeReport PdfChecker::GetReport(const std::wstring& path) {
	read_pdf(path);
	return _pdf->AnalyzeAll();
}

void PdfChecker::ShowPdfData() const {
	if (_pdf)
		_pdf->Show();
}

std::vector<char> PdfChecker::get_pdf_data(unsigned int begin, unsigned int end) const {
	if (_pdf)
		return _pdf->get_data(begin, end);
	else {
		std::vector<char> tmp{ '\0' };
		return tmp;
	}
		
}