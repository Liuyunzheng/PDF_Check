#include <iostream>
#include <fstream>
#include "pdf-analyze-report.h"
#include "pdf-checker.h"

namespace PDF_CHECK {

	PdfChecker::PdfChecker() 
		: pdf_{ nullptr } {

	}

	PdfChecker::PdfChecker(const std::wstring& path) 
		: pdf_{ new Pdf{ path } } {

	}

	bool PdfChecker::ReadPdf(const std::wstring& path) {
		if (!pdf_) {
			pdf_.reset(new Pdf{ path });
		}
		bool can_read = pdf_->Read(path);

		return can_read;
	}

	PdfAnalyzeReport PdfChecker::GetReport(const std::wstring& path) {
		ReadPdf(path);
		return pdf_->AnalyzeAll();
	}

	void PdfChecker::ShowPdfData() const {
		if (pdf_)
			pdf_->Show();
	}

	Bytes PdfChecker::get_pdf_data(unsigned int begin, unsigned int end) const {
		if (pdf_)
			return pdf_->get_data(begin, end);
		else {
			Bytes tmp{ '\0' };
			return tmp;
		}
	}
}