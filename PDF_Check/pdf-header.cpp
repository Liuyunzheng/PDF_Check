#include <iostream>
#include "pdf-header.h"
#include "pdf-analyze-result.h"

PdfAnalyzeResult PdfHeader::Analyze(const std::unique_ptr<DataPool>& in_data) {
	PdfAnalyzeResult result;
	std::vector<char> header = in_data->get_data(0, 1024); /* pdf �涨pdfͷ���������ǰ1024�ֽ��� */

	return result;
}

