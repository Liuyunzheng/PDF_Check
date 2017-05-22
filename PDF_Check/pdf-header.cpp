#include <iostream>
#include <vector>
#include "data-pool.h"
#include "pdf-header.h"
#include "pdf-analyze-result.h"
#include "ac-tree.h"
#include "ac-scanner.h"

namespace PDF_CHECK {

	const std::vector<Bytes> PdfHeader::kKeyWordList{
		"%PDF"
	};

	PdfAnalyzeResult PdfHeader::Analyze(const std::unique_ptr<DataPool>& in_data) {
		Bytes header = in_data->get_data(0, 1024); /* pdf �涨pdfͷ���������ǰ1024�ֽ��� */
		AcTree ac_tree{ PdfHeader::kKeyWordList };
		AcScanner scanner;
		PdfAnalyzeResult result;
		ScanResult scan_result = scanner.Scan(ac_tree, header);
		scan_result.Show();

		return result;
	}
}
