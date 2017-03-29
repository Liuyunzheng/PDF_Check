#ifndef DETECT_PDF_H_
#define DETECT_PDF_H_

#include <memory>
#include "basic-type.h"

class PdfHeader;
class PdfBody;
class PdfXref;
class PdfTrailer;
class AnalyzeReport;
class AnalyzeResult;

class Pdf {
public:
	static bool read(const std::wstring& path, Bytes& out_data);

public:
	Pdf(const Bytes& in_data);
	~Pdf();
	Pdf(const Pdf& );
	Pdf& operator = (const Pdf&);

	bool init();
	Bytes get_data() const;
	AnalyzeReport analyze_all();
	AnalyzeResult analyze_header();
	AnalyzeResult analyze_body();
	AnalyzeResult analyze_xref();
	AnalyzeResult analyze_trailer();

private:
	Bytes data;
	std::unique_ptr<PdfHeader> header;
	std::unique_ptr<PdfBody> body;
	std::unique_ptr<PdfXref> xref;
	std::unique_ptr<PdfTrailer> trailer;
};

#endif /* end of DETECT_PDF_H_ */