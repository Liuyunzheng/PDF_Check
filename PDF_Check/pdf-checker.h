/* 
* A check unit 
*/

#ifndef DETECT_PDF_CHECKER_H_
#define DETECT_PDF_CHECKER_H_

#include <iostream>
#include <memory>
#include "basic-type.h"

class Pdf;
class PdfAnalyzeReport;

class PdfChecker { 
public:
	PdfChecker();
	~PdfChecker() = default;
	PdfChecker(const PdfChecker&) = delete;
	PdfChecker(PdfChecker&&) = delete;
	PdfChecker& operator = (const PdfChecker&) = delete;
	PdfChecker& operator = (PdfChecker&&) = delete;


	PdfAnalyzeReport GetReport(const std::wstring& path);
	bool read_pdf(const std::wstring& path);
	void ShowPdfData() const;
	std::vector<char> get_pdf_data(unsigned int, unsigned int) const; 

private:
	std::unique_ptr<Pdf> _pdf;
};

#endif /* end of DETECT_PDF_CHECKER_H_ */