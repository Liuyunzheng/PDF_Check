#include <iostream>
#include <fstream>
#include "pdf.h"
#include "pdf-analyze-result.h"
#include "pdf-analyze-report.h"

bool Pdf::Read(const std::wstring& path) {
	return _data->Read(path);
}

Pdf::Pdf(const std::wstring& path) :_data{ new DataPool{ path } } {
	Init();
}

bool Pdf::Init() {
	try {
		_header.reset(new PdfHeader{});
		_body.reset(new PdfBody{});
		_xref.reset(new PdfXref{});
		_trailer.reset(new PdfTrailer{});
	}
	catch (...) {
		return false;
	}

	return true;
}

void Pdf::Show() const {
	_data->Show();
}

std::vector<char> Pdf::get_data(unsigned int begin, unsigned int end) const {
	return _data->get_data(begin, end);
}

PdfAnalyzeReport Pdf::AnalyzeAll() const{
	PdfAnalyzeReport report;
	
	return report;
}

PdfAnalyzeResult Pdf::AnalyzeHeader() const {
	PdfAnalyzeResult result = _header->Analyze(_data);

	return result;
}

PdfAnalyzeResult Pdf::AnalyzeBody() const {
	PdfAnalyzeResult result = _body->Analyze(_data);

	return result;
}

PdfAnalyzeResult Pdf::AnalyzeXref() const {
	PdfAnalyzeResult result = _xref->Analyze(_data);

	return result;
}

PdfAnalyzeResult Pdf::AnalyzeTrailer() const{
	PdfAnalyzeResult result = _trailer->Analyze(_data);

	return result;
}