#ifndef AC_SCANNER_H_
#define AC_SCANNER_H_

#include "basic-type.h"
#include "scan-result.h"

namespace PDF_CHECK {
	
	class DataPool;
	class AcTree;

	class AcScanner {	
	public:
		ScanResult Scan(const AcTree& tree, const DataPool& data, unsigned int begin = 0, unsigned int end = 0) const;
	};
}

#endif /* end of AC_SCANNER_H_ */