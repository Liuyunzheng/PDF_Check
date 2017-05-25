#ifndef DETECT_PDF_TRAILER_H_
#define DETECT_PDF_TRAILER_H_

#include <vector>
#include "data-pool.h"

namespace PDF_CHECK {
	
	struct ScanResult;
	class PdfAnalyzeResult;
	class AcTree;

	class PdfTrailer {
	private:
		static const std::vector<Bytes> kKeyWordList;
		static const AcTree kAcTree;

	public:
		PdfTrailer() = default;
		~PdfTrailer() = default;

		ScanResult Scan(const std::unique_ptr<DataPool>& in_data) const;
		PdfAnalyzeResult Analyze(const std::unique_ptr<DataPool>& in_data) const;
	};
}

#endif /* end of DETECT_PDF_TRAILER_H_ */