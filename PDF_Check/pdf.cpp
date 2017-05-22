#include <iostream>
#include <fstream>
#include "pdf.h"
#include "pdf-analyze-result.h"
#include "pdf-analyze-report.h"

namespace PDF_CHECK {

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

	bool Pdf::Read(const std::wstring& path) {
		return _data->Read(path);
	}


	void Pdf::Show() const {
		_data->Show();
	}

	Bytes Pdf::get_data(unsigned int begin, unsigned int end) const {
		return _data->get_data(begin, end);
	}

	PdfAnalyzeReport Pdf::AnalyzeAll() const{
		PdfAnalyzeReport report;

		PdfAnalyzeResult head_result = AnalyzeHeader();
		PdfAnalyzeResult body_result = AnalyzeBody();
		PdfAnalyzeResult xref_result = AnalyzeXref();
		PdfAnalyzeResult trailer_result = AnalyzeTrailer();
		
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
}