#include <iostream>
#include <vector>
#include "pdf-body.h"
#include "scan-result.h"
#include "pdf-analyze-result.h"
#include "ac-tree.h"
#include "ac-scanner.h"

namespace PDF_CHECK{

	const std::vector<Bytes> PdfBody::kKeyWordList{
		{ 'o', 'b', 'j' },
		{ '<', '<' },
		{ '>', '>' },
		{ 's', 't', 'r', 'e', 'a', 'm' },
		{ 'e', 'n', 'd', 's', 't', 'r', 'e', 'a', 'm' },
		{ 'e', 'n', 'd', 'o', 'b', 'j' },
		{ 'x', 'r', 'e', 'f' },
		{ 't', 'r', 'a', 'i', 'l', 'e', 'r' },
		{ '%', '%', 'E', 'O', 'F' }
	};

	const AcTree PdfBody::kAcTree{ kKeyWordList };

	ScanResult PdfBody::Scan(const std::unique_ptr<DataPool>& in_data) const {
		AcScanner scanner;
		ScanResult scan_result = scanner.Scan(kAcTree, *in_data.get());
		scan_result.Show();

		return scan_result;
	}

	PdfAnalyzeResult PdfBody::Analyze(const std::unique_ptr<DataPool>& in_data) const {
		PdfAnalyzeResult result;
		Scan(in_data);

		return result;
	}
}