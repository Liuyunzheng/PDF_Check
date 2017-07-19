#ifndef DETECT_PDF_HEADER_H_
#define DETECT_PDF_HEADER_H_

#include <vector>
#include "data-pool.h"

namespace PDF_CHECK{

	struct ScanResult;
	class PdfAnalyzeResult;
	class AcTrie;

	class PdfHeader { /* Pdf unit */
	private:
		static const std::vector<Bytes> kKeyWordList;
		static const AcTrie kAcTrie;

	public:
		PdfHeader() = default;
		~PdfHeader() = default;

		ScanResult Scan(const std::unique_ptr<DataPool>& in_data) const;
		PdfAnalyzeResult Analyze(const std::unique_ptr<DataPool>& in_data) const;
	};

}

#endif /* end of DETECT_PDF_HEADER_H_ */