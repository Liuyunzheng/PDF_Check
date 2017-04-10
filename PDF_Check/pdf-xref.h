#ifndef DETECT_PDF_XREF_H_
#define DETECT_PDF_XREF_H_

#include "basic-type.h"

class PdfAnalyzeResult;

class PdfXref {
public:
	PdfXref() = default;
	~PdfXref() = default;
	PdfAnalyzeResult Analyze(const std::unique_ptr<DataPool>& in_data);
};

#endif /* end of DETECT_PDF_XREF_H_ */