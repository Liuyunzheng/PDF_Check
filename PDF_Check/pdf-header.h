#ifndef DETECT_PDFHEADER_H_
#define DETECT_PDFHEADER_H_

#include "basic-type.h"

class AnalyzeResult;

class PdfHeader {
public:
	PdfHeader() = default;
	~PdfHeader() = default;
	AnalyzeResult analyze(const Bytes& in_data);
};

#endif /* end of DETECT_PDFHEADER_H_ */