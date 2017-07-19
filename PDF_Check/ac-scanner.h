#ifndef AC_SCANNER_H_
#define AC_SCANNER_H_

#include "scan-result.h"

namespace PDF_CHECK {
	
	class DataPool;
	class AcTrie;

	class AcScanner {	
	public:

		/* 暂时不用模版 */
		ScanResult Scan(const AcTrie& trie, const DataPool& data, unsigned int begin = 0, unsigned int end = 0) const;
		ScanResult Scan(const AcTrie& trie, const Bytes& data, unsigned int begin = 0, unsigned int end = 0) const;
	};

}

#endif /* end of AC_SCANNER_H_ */