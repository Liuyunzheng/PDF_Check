#include <iostream>
#include "pdf-header.h"
#include "pdf-analyze-result.h"

PdfAnalyzeResult PdfHeader::Analyze(const std::unique_ptr<DataPool>& in_data) {
	PdfAnalyzeResult result;
	std::vector<char> header = in_data->get_data(0, 1024); /* pdf 规定pdf头必须出现在前1024字节中 */

	return result;
}

