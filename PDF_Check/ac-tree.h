/*
* A general method for scanning the data read from document, using Ac-Tree
*/

#ifndef DETECT_AC_TREE_H_
#define DETECT_AC_TREE_H_

#include <vector>
#include "basic-type.h"

namespace PDF_CHECK {


	struct AcNode {
		static const int kCharCnt = 256;
		AcNode() : _end{ false }, _len{ 0 } {
			for (int i = 0; i < kCharCnt; ++i)
				children[i] = nullptr;
		}

		~AcNode() {
			for (int i = 0; i < kCharCnt; ++i) {
				delete children[i];
			}
		}

		AcNode *fail{ nullptr };
		AcNode *children[kCharCnt];
		Bytes _type{};
		bool _end;
		unsigned int _len;
	};

	class AcScanner;

	class AcTree {

	public:
		friend AcScanner;
		AcTree() = default;
		explicit AcTree(const std::vector<Bytes>& keyword_list);
		~AcTree() {
			delete _root;
		}

		void BuildAcTree(const std::vector<Bytes>& keyword_list);
		void Show() const;
		
	private:
		void _insert_ac_tree(const Bytes& keyword);
		void _BuildAcAutomation();
		const AcNode *_get_root() const {
			return _root;
		}

	private:
		AcNode *_root{ nullptr };
	};
}

#endif /* end of DETECT_AC_TREE_H_ */