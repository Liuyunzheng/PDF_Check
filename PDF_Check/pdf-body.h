#ifndef DETECT_PDF_BODY_H_
#define DETECT_PDF_BODY_H_

#include "basic-type.h"

class PdfAnalyzeResult;

class PdfBody {
public:
	PdfBody() = default;
	~PdfBody() = default;
	PdfAnalyzeResult Analyze(const std::unique_ptr<DataPool>& in_data);
};


#endif /* end of DETECT_PDF_BODY_H_ */