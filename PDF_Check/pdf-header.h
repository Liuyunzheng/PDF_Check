#ifndef DETECT_PDF_HEADER_H_
#define DETECT_PDF_HEADER_H_

#include "basic-type.h"

class PdfAnalyzeResult;

class PdfHeader { /* Pdf unit */
public:
	PdfHeader() = default;
	~PdfHeader() = default;

	PdfAnalyzeResult Analyze(const std::unique_ptr<DataPool>& in_data);
};

#endif /* end of DETECT_PDF_HEADER_H_ */