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
		AcNode() 
			: end{ false }, len{ 0 } {
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
		Bytes type{};
		bool end;
		unsigned int len;
	};

	class AcScanner;

	class AcTree {
	public:
		friend AcScanner;
		AcTree() = default;
		explicit AcTree(const std::vector<Bytes>& keyword_list);
		~AcTree() { delete root_; }

		void BuildAcTree(const std::vector<Bytes>& keyword_list);
		void Show() const;
		
	private:
		void InsertAcTrie(const Bytes& keyword);
		void BuildAcAutomation();
		const AcNode *GetRoot() const { return root_; }

	private:
		AcNode *root_{ nullptr };
	};
}

#endif /* end of DETECT_AC_TREE_H_ */