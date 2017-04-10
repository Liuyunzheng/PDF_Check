#ifndef DETECT_PDF_TRAILER_H_
#define DETECT_PDF_TRAILER_H_

#include "basic-type.h"

class PdfAnalyzeResult;

class PdfTrailer {
public:
	PdfTrailer() = default;
	~PdfTrailer() = default;
	PdfAnalyzeResult Analyze(const std::unique_ptr<DataPool>& in_data);
};

#endif /* end of DETECT_PDF_TRAILER_H_ */