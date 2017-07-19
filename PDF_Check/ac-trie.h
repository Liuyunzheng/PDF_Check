/*
* A general method for scanning the data read from document, using Ac-Trie
*/

#ifndef DETECT_AC_TRIE_H_
#define DETECT_AC_TRIE_H_

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

	class AcTrie {
	public:
		friend AcScanner;
		AcTrie() = default;
		explicit AcTrie(const std::vector<Bytes>& keyword_list);
		~AcTrie() { delete root_; }

		void BuildAcTrie(const std::vector<Bytes>& keyword_list);
		void Show() const;
		
	private:
		void InsertAcTrie(const Bytes& keyword);
		void BuildAcAutomation();
		const AcNode *GetRoot() const { return root_; }

	private:
		AcNode *root_{ nullptr };
	};
}

#endif /* end of DETECT_AC_TRIE_H_ */