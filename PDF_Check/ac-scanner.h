#ifndef AC_SCANNER_H_
#define AC_SCANNER_H_

#include "basic-type.h"
#include "scan-result.h"

namespace PDF_CHECK {
	
	class DataPool;
	class AcTree;

	class AcScanner {	
	public:
		ScanResult Scan(const AcTree& tree, const DataPool& data) const;
	};
}

#endif /* end of AC_SCANNER_H_ */