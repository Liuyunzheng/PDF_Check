#ifndef DETECT_PDFXREF_H_
#define DETECT_PDFXREF_H_

#include "basic-type.h"

class AnalyzeResult;

class PdfXref {
public:
	PdfXref() = default;
	~PdfXref() = default;
	AnalyzeResult analyze(const Bytes& in_data);
};

#endif /* end of DETECT_PDFXREF_H_ */