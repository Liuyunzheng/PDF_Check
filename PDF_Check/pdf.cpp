#include <iostream>
#include <fstream>
#include "pdf.h"
#include "pdf-header.h"
#include "pdf-body.h"
#include "pdf-xref.h"
#include "pdf-trailer.h"
#include "analyze-result.h"
#include "analyze-report.h"

bool Pdf::read(const std::wstring& path, Bytes& out_data) {
	std::ifstream out_file(path, std::ios::binary); /* read data from pdf */
	
	try {
		std::filebuf *pbuf = out_file.rdbuf();
		int file_size = pbuf->pubseekoff(0, std::ios::end, std::ios::in);
		pbuf->pubseekpos(0, std::ios::in);
		char *buffer(new char[file_size]);
		pbuf->sgetn(buffer, file_size);
		for (int i = 0; i < file_size; ++i)
			out_data.push_back(static_cast<Byte>(buffer[i]));
		delete[] buffer;
	}
	catch(...) {
		out_file.close();
		return false;
	}
	out_file.close();

	return true;
}

Pdf::Pdf(const Bytes& in_data) :_data(in_data), _header(nullptr), _body(nullptr), _xref(nullptr), _trailer(nullptr) {
	init();
}

Pdf::~Pdf() {

}

Pdf::Pdf(const Pdf& pdf) {
	_data = pdf._data;
	init();
}

Pdf& Pdf::operator = (const Pdf& pdf) {
	_data = pdf._data;
	init();

	return *this;
}

bool Pdf::init() {
	try {
		_header.reset(new PdfHeader());
		_body.reset(new PdfBody());
		_xref.reset(new PdfXref());
		_trailer.reset(new PdfTrailer());
	}
	catch (...) {
		return false;
	}

	return true;
}

void Pdf::show() const {
	for (auto c : _data)
		std::cout << c;
	std::cout << std::endl;
}

Bytes Pdf::get_data() const {
	return _data;
}

AnalyzeReport Pdf::analyze_all() const{
	AnalyzeReport report;
	
	return report;
}

AnalyzeResult Pdf::analyze_header() const {
	AnalyzeResult result = _header->analyze(_data);

	return result;
}

AnalyzeResult Pdf::analyze_body() const {
	AnalyzeResult result = _body->analyze(_data);

	return result;
}

AnalyzeResult Pdf::analyze_xref() const {
	AnalyzeResult result = _xref->analyze(_data);

	return result;
}

AnalyzeResult Pdf::analyze_trailer() const{
	AnalyzeResult result = _trailer->analyze(_data);

	return result;
}