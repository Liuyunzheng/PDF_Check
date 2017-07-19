#ifndef DETECT_PDF_H_
#define DETECT_PDF_H_

#include <memory>
#include "basic-type.h"
#include "pdf-header.h"
#include "pdf-body.h"
#include "pdf-xref.h"
#include "pdf-trailer.h"

namespace PDF_CHECK {

	class PdfAnalyzeReport;
	class PdfAnalyzeResult;

	class Pdf {
	public:
		explicit Pdf(const std::wstring& path);
		~Pdf() = default;
		Pdf(const Pdf&) = delete;
		Pdf(Pdf&&) = delete;
		Pdf& operator = (const Pdf&) = delete;
		Pdf& operator = (Pdf&&) = delete;

		bool Init();
		bool Read(const std::wstring& path);
		void Show() const;

		Bytes get_data(unsigned int, unsigned int) const; /* should not be too big (不应该太大，应该在上层实现对大数据的读取) */

		PdfAnalyzeReport AnalyzeAll() const;
		PdfAnalyzeResult AnalyzeHeader() const;
		PdfAnalyzeResult AnalyzeBody() const;
		PdfAnalyzeResult AnalyzeXref() const;
		PdfAnalyzeResult AnalyzeTrailer() const;

	private:
		std::unique_ptr<DataPool> data_;
		std::unique_ptr<PdfHeader> header_{ nullptr };
		std::unique_ptr<PdfBody> body_{ nullptr };
		std::unique_ptr<PdfXref> xref_{ nullptr };
		std::unique_ptr<PdfTrailer> trailer_{ nullptr };
	};
}

#endif /* end of DETECT_PDF_H_ */