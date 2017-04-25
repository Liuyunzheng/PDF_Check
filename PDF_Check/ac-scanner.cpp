
#include "ac-scanner.h"
#include "ac-tree.h"
#include "data-pool.h"

namespace PDF_CHECK {

	ScanResult AcScanner::Scan(const AcTree& tree, const DataPool& data) const {
		ScanResult result;
		const AcNode *ptr = tree._get_root();
		const unsigned int len = data.Size();

		for (unsigned int i = 0; i < len; ++i) {
			char pos = data[i];
			while (ptr->children[pos] == nullptr && ptr->fail)
				ptr = ptr->fail;

			if (ptr->children[pos])
				ptr = ptr->children[pos];

			if (ptr->_end) {
				const unsigned int offset = i - ptr->_type.size() + 1;
				result.Add(offset, ptr->_type);
			}
		}
		return result;
	}
}