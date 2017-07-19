#include <iostream>
#include <vector>
#include "pdf-body.h"
#include "scan-result.h"
#include "pdf-analyze-result.h"
#include "ac-trie.h"
#include "ac-scanner.h"

namespace PDF_CHECK{

	const std::vector<Bytes> PdfBody::kKeyWordList{
		{ '<', '<' },
		{ '>', '>' },
		{ 'o', 'b', 'j' },
		{ 'x', 'r', 'e', 'f' },
		{ '%', '%', 'E', 'O', 'F' },
		{ 's', 't', 'r', 'e', 'a', 'm' },
		{ 'e', 'n', 'd', 'o', 'b', 'j' },
		{ 't', 'r', 'a', 'i', 'l', 'e', 'r' },
		{ 'e', 'n', 'd', 's', 't', 'r', 'e', 'a', 'm' }
	};

	const AcTrie PdfBody::kAcTrie{ kKeyWordList };

	ScanResult PdfBody::Scan(const std::unique_ptr<DataPool>& in_data) const {
		AcScanner scanner;
		ScanResult scan_result = scanner.Scan(kAcTrie, *in_data.get());
		scan_result.Show();

		return scan_result;
	}

	PdfAnalyzeResult PdfBody::Analyze(const std::unique_ptr<DataPool>& in_data) const {
		PdfAnalyzeResult result;
		Scan(in_data);

		return result;
	}
}