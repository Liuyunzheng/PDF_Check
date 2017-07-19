#include <iostream>
#include <fstream>
#include "pdf.h"
#include "pdf-analyze-result.h"
#include "pdf-analyze-report.h"

namespace PDF_CHECK {

	Pdf::Pdf(const std::wstring& path) 
		:data_{ new DataPool{ path } } {
		Init();
	}

	bool Pdf::Init() {
		try {
			header_.reset(new PdfHeader{});
			body_.reset(new PdfBody{});
			xref_.reset(new PdfXref{});
			trailer_.reset(new PdfTrailer{});
		}
		catch (...) {
			return false;
		}

		return true;
	}

	bool Pdf::Read(const std::wstring& path) {
		return data_->Read(path);
	}


	void Pdf::Show() const {
		data_->Show();
	}

	Bytes Pdf::get_data(unsigned int begin, unsigned int end) const {
		return data_->get_data(begin, end);
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
		PdfAnalyzeResult result = header_->Analyze(data_);
		return result;
	}

	PdfAnalyzeResult Pdf::AnalyzeBody() const {
		PdfAnalyzeResult result = body_->Analyze(data_);
		return result;
	}

	PdfAnalyzeResult Pdf::AnalyzeXref() const {
		PdfAnalyzeResult result = xref_->Analyze(data_);
		return result;
	}

	PdfAnalyzeResult Pdf::AnalyzeTrailer() const{
		PdfAnalyzeResult result = trailer_->Analyze(data_);
		return result;
	}
}