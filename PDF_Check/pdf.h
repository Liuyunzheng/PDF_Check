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
	Pdf(Pdf&&) = delete;
	Pdf& operator = (const Pdf&);
	Pdf& operator = (Pdf&&) = delete;

	bool init();
	Bytes get_data() const;
	void show() const;
	AnalyzeReport analyze_all() const;
	AnalyzeResult analyze_header() const;
	AnalyzeResult analyze_body() const;
	AnalyzeResult analyze_xref() const;
	AnalyzeResult analyze_trailer() const;

private:
	Bytes _data;
	std::unique_ptr<PdfHeader> _header;
	std::unique_ptr<PdfBody> _body;
	std::unique_ptr<PdfXref> _xref;
	std::unique_ptr<PdfTrailer> _trailer;
};

#endif /* end of DETECT_PDF_H_ */