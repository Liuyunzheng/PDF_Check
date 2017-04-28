#ifndef DETECT_PDF_HEADER_H_
#define DETECT_PDF_HEADER_H_

#include "basic-type.h"

namespace PDF_CHECK{

	class PdfAnalyzeResult;

	class PdfHeader { /* Pdf unit */
	private:
		static const std::vector<Bytes> kKeyWordList;
	public:
		PdfHeader() = default;
		~PdfHeader() = default;

		PdfAnalyzeResult Analyze(const std::unique_ptr<DataPool>& in_data);
	};
}

#endif /* end of DETECT_PDF_HEADER_H_ */