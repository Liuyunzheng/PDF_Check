#ifndef DETECT_PDFBODY_H_
#define DETECT_PDFBODY_H_

#include "basic-type.h"

class AnalyzeResult;

class PdfBody {
public:
	PdfBody() = default;
	~PdfBody() = default;
	AnalyzeResult analyze(const Bytes& in_data);
};


#endif /* end of DETECT_PDFBODY_H_ */