#include <iostream>
#include "pdf-xref.h"
#include "scan-result.h"
#include "pdf-analyze-result.h"
#include "ac-tree.h"
#include "ac-scanner.h"

namespace PDF_CHECK {

	const std::vector<Bytes> PdfXref::kKeyWordList{
		{ 'x', 'r', 'e', 'r' },
		{ 't', 'r', 'a', 'i', 'l', 'e', 'r' }
	};

	const AcTree PdfXref::kAcTree{ kKeyWordList };

	ScanResult PdfXref::Scan(const std::unique_ptr<DataPool>& in_data) const {
		AcScanner scanner;
		ScanResult scan_result = scanner.Scan(kAcTree, *in_data.get());
		scan_result.Show();

		return scan_result;
	}

	PdfAnalyzeResult PdfXref::Analyze(const std::unique_ptr<DataPool>& in_data) const {
		Scan(in_data);
		PdfAnalyzeResult result;

		return result;
	}
}