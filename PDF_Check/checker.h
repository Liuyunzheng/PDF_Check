#ifndef DETECT_CHECKER_H_
#define DETECT_CHECKER_H_

#include <iostream>
#include <memory>
#include "basic-type.h"

class Pdf;
class AnalyzeReport;

class Checker {
public:
	Checker();
	~Checker() = default;
	AnalyzeReport get_report(const std::wstring& path);
	void read_pdf(const std::wstring& path);
	void show_pdf_data() const;
	Bytes get_pdf_data() const;

private:
	std::unique_ptr<Pdf> _pdf;
};

#endif