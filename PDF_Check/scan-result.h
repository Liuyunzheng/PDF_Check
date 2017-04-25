#ifndef SCAN_RESULT_H_
#define SCAN_RESULT_H_

#include <vector>
#include "basic-type.h"

namespace PDF_CHECK {
	
	struct ScanResult {
		std::vector<unsigned int> offsets;
		std::vector<Bytes> keywords;
		void Add(unsigned int offset, const Bytes& keyword);
		void Clear();
		void Show() const;
	};
}

#endif /* end of SCAN_RESULT_H_ */