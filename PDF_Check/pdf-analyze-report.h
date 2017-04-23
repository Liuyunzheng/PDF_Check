/* 
* report 用来记录整个文档的解析结果，是result的集合
*/

#ifndef DETECT_PDF_ANALYZE_REPORT_H_
#define DETECT_PDF_ANALYZE_REPORT_H_

namespace PDF_CHECK {

	class PdfAnalyzeReport {
	public:
		PdfAnalyzeReport() = default;
		~PdfAnalyzeReport() = default;
		PdfAnalyzeReport(const PdfAnalyzeReport&) = default;
		PdfAnalyzeReport& operator = (const PdfAnalyzeReport&) = default;

	};
}

#endif /* end of DETECT_PDF_ANALYZE_REPORT_H_ */