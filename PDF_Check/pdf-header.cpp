#include <iostream>
#include <vector>
#include "pdf-header.h"
#include "pdf-analyze-result.h"
#include "ac-tree.h"
#include "ac-scanner.h"

namespace PDF_CHECK {

	const std::vector<Bytes> PdfHeader::kKeyWordList{
		"%PDF", {0x50, 0x4b, 0x03, 0x04}
	};

	PdfAnalyzeResult PdfHeader::Analyze(const std::unique_ptr<DataPool>& in_data) const {
		Bytes header = in_data->get_data(0, 1023); /* pdf 规定pdf头必须出现在前1024字节中 */
		
		AcTree ac_tree{ PdfHeader::kKeyWordList };
		ac_tree.Show();

		AcScanner scanner;
		ScanResult scan_result = scanner.Scan(ac_tree, header);
		scan_result.Show();

		PdfAnalyzeResult result;
		return result;
	}
}
