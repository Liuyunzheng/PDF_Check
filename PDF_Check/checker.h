#ifndef DETECT_CHECKER_H_
#define DETECT_CHECKER_H_

#include <iostream>

class Pdf;
class AnalyzeReport;

class Checker {
public:
	Checker() = default;
	~Checker() = default;
	AnalyzeReport&& get_report(const std::wstring& path);
	Pdf&& read_pdf(const std::wstring& path);
};

#endif