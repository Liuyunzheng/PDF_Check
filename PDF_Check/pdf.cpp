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
	std::ifstream out_file(path); /* read data from pdf */
	
	try {
		while (out_file.good()) {
			char c = out_file.get();
			out_data.push_back(static_cast<Byte>(c));
		}
	}
	catch(...) {
		out_file.close();
		return false;
	}
	out_file.close();

	return true;
}

Pdf::Pdf(const Bytes& in_data) :data(in_data), header(nullptr), body(nullptr), xref(nullptr), trailer(nullptr) {
	init();
}

Pdf::~Pdf() {

}

Pdf::Pdf(const Pdf& pdf) {
	data = pdf.get_data();
	init();
}

Pdf& Pdf::operator = (const Pdf& pdf) {
	data = pdf.get_data();
	init();

	return *this;
}

bool Pdf::init() {
	try {
		header.reset(new PdfHeader());
		body.reset(new PdfBody());
		xref.reset(new PdfXref());
		trailer.reset(new PdfTrailer());
	}
	catch (...) {
		return false;
	}

	return true;
}

Bytes Pdf::get_data() const {
	return data;
}

AnalyzeReport Pdf::analyze_all() {
	AnalyzeReport report;
	
	return report;
}

AnalyzeResult Pdf::analyze_header() {
	AnalyzeResult result = header->analyze(data);

	return result;
}

AnalyzeResult Pdf::analyze_body() {
	AnalyzeResult result = body->analyze(data);

	return result;
}

AnalyzeResult Pdf::analyze_xref() {
	AnalyzeResult result = xref->analyze(data);

	return result;
}

AnalyzeResult Pdf::analyze_trailer() {
	AnalyzeResult result = trailer->analyze(data);

	return result;
}