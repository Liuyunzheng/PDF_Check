#include <iostream>
#include <queue>
#include "ac-trie.h"

namespace PDF_CHECK {

	AcTrie::AcTrie(const std::vector<Bytes>& keyword_list) {
		BuildAcTrie(keyword_list);
	}

	void AcTrie::BuildAcTrie(const std::vector<Bytes>& keyword_list) {
		root_ = new AcNode();
		for (auto& s : keyword_list) {
			InsertAcTrie(s);
		}
		BuildAcAutomation();
	}

	void AcTrie::Show() const{
		std::cout << "\n<<AcTrie::Show>>\n";

		AcNode *ptr = root_;
		std::queue< std::pair<int, AcNode *> > q;
		int cur_level = 0;
		q.push({ 0, ptr });
		while (!q.empty()) {
			auto pair = q.front();
			q.pop();
			ptr = pair.second;
			int level = pair.first;
			if (level > cur_level) {
				cur_level = level;
				std::cout << std::endl;
			}

			for (int i = 0; i < AcNode::kCharCnt; ++i) {
				if (ptr->children[i]) {
					std::cout << static_cast<char>(i) << std::ends;
					if (ptr->children[i]->end) {
						std::cout << "<-*" << std::ends;
					}
					q.push({ level + 1, ptr->children[i] });
				}
			}
		}

		std::cout << "<<AcTrie::Show End>>\n";
	}

	void AcTrie::InsertAcTrie(const Bytes& keyword) {
		AcNode *cur = root_;
		for (auto& i : keyword) {
			if (cur->children[i] == nullptr) {
				cur->children[i] = new AcNode();
			}
			cur = cur->children[i];
		}

		cur->end = true;
		cur->len = keyword.size();
		cur->type = keyword;
	}

	void AcTrie::BuildAcAutomation() {
		AcNode *cur = nullptr;
		AcNode *ptr = nullptr;
		std::queue<AcNode *> q;
		q.push(root_);
		while (!q.empty()) {
			cur = q.front();
			q.pop();
			for (int i = 0; i < AcNode::kCharCnt; ++i) {
				if (cur->children[i]) {
					ptr = cur->fail;
					while (ptr && ptr->children[i] == nullptr) 
						ptr = ptr->fail;
		
					if (ptr == nullptr)
						cur->children[i]->fail = root_;
					else
						cur->children[i]->fail = ptr->children[i];
					q.push(cur->children[i]);
				}
			}
		}
	}
}