#ifndef SCAN_RESULT_H_
#define SCAN_RESULT_H_

#include <vector>
#include <map>
#include "basic-type.h"

namespace PDF_CHECK {
	
	struct ScanResult {
		std::map<unsigned int, Bytes> off_key_pairs;

		void Add(unsigned int offset, const Bytes& keyword);
		void Clear();
		void Show() const;
		std::vector<unsigned int> Find(const Bytes& keyword) const; /* find the keyword's offset, return empty vector if not find keyword */
		Bytes Find(unsigned int offset) const; /* find the keyword begin with offset, return empty Bytes if not find */
	};
}

#endif /* end of SCAN_RESULT_H_ */