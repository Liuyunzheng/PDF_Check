#include <iostream>
#include <vector>
#include "pdf-header.h"
#include "scan-result.h"
#include "pdf-analyze-result.h"
#include "ac-tree.h"
#include "ac-scanner.h"

namespace PDF_CHECK {

	const std::vector<Bytes> PdfHeader::kKeyWordList{
		{ '%', 'P', 'D', 'F' }, /*"%PDF"*/
		{ 0x50, 0x4b, 0x03, 0x04 }, /* OFFICE DOCX */
		{ 0xd0, 0xcf, 0x11, 0xe0 } /* OFFICE DOC */
	};

	const AcTree PdfHeader::kAcTree{ kKeyWordList };

	ScanResult PdfHeader::Scan(const std::unique_ptr<DataPool>& in_data) const {
		Bytes header = in_data->get_data(0, 1023); /* pdf 规定pdf头必须出现在前1024字节中 */

		AcScanner scanner;
		ScanResult scan_result = scanner.Scan(kAcTree, header);
		scan_result.Show();

		return scan_result;
	}

	PdfAnalyzeResult PdfHeader::Analyze(const std::unique_ptr<DataPool>& in_data) const {
		ScanResult scan_result = Scan(in_data);
		PdfAnalyzeResult result;

		return result;
	}
}
