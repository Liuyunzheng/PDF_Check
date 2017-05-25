#include <iostream>
#include "pdf-trailer.h"
#include "scan-result.h"
#include "pdf-analyze-result.h"
#include "ac-tree.h"
#include "ac-scanner.h"

namespace PDF_CHECK {

	const std::vector<Bytes> PdfTrailer::kKeyWordList{
		{ 't', 'r', 'a', 'i', 'l', 'e', 'r' },
		{ '%', '%', 'E', 'O', 'F' }
	};

	const AcTree PdfTrailer::kAcTree{ kKeyWordList };

	ScanResult PdfTrailer::Scan(const std::unique_ptr<DataPool>& in_data) const {
		AcScanner scanner;
		ScanResult scan_result = scanner.Scan(kAcTree, *in_data.get());
		scan_result.Show();

		return scan_result;
	}

	PdfAnalyzeResult PdfTrailer::Analyze(const std::unique_ptr<DataPool>& in_data) const {
		Scan(in_data);
		PdfAnalyzeResult result;

		return result;
	}
}