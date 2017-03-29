#ifndef DETECT_PDFTRAILER_H_
#define DETECT_PDFTRAILER_H_

#include "basic-type.h"

class AnalyzeResult;

class PdfTrailer {
public:
	PdfTrailer() = default;
	~PdfTrailer() = default;
	AnalyzeResult analyze(const Bytes& in_data);
};

#endif /* end of DETECT_PDFTRAILER_H_ */