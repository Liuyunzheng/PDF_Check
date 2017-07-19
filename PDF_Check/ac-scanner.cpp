#include "ac-scanner.h"
#include "ac-tree.h"
#include "data-pool.h"


namespace PDF_CHECK {

	ScanResult AcScanner::Scan(const AcTree& tree, const DataPool& data, unsigned int begin, unsigned int end) const {
		ScanResult result;
		const AcNode *ptr = tree.GetRoot();
		const unsigned int len = data.size();
		if (end == 0)
			end = len;

		for (unsigned int i = begin; i < end; ++i) {
			unsigned char pos = data[i];
			while (ptr->children[pos] == nullptr && ptr->fail)
				ptr = ptr->fail;

			if (ptr->children[pos])
				ptr = ptr->children[pos];

			if (ptr->end) {
				const unsigned int offset = i - ptr->type.size() + 1;
				result.Add(offset, ptr->type);
			}
		}

		return result;
	}

	ScanResult AcScanner::Scan(const AcTree& tree, const Bytes& data, unsigned int begin, unsigned int end) const {
		ScanResult result;
		const AcNode *ptr = tree.GetRoot();
		const unsigned int len = data.size();
		if (end == 0)
			end = len;

		for (unsigned int i = begin; i < end; ++i) {
			unsigned char pos = data[i];
			while (ptr->children[pos] == nullptr && ptr->fail)
				ptr = ptr->fail;

			if (ptr->children[pos])
				ptr = ptr->children[pos];

			if (ptr->end) {
				const unsigned int offset = i - ptr->type.size() + 1;
				result.Add(offset, ptr->type);
			}
		}

		return result;
	}

}