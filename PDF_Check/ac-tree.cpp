#include <iostream>
#include <queue>
#include "ac-tree.h"

namespace PDF_CHECK {

	AcTree::AcTree(const std::vector<Bytes>& keyword_list) {
		BuildAcTree(keyword_list);
	}

	void AcTree::BuildAcTree(const std::vector<Bytes>& keyword_list) {
		_root = new AcNode();
		for (auto& s : keyword_list)
			_insert_ac_tree(s);
		_BuildAcAutomation();
	}

	void AcTree::Show() const{
		std::cout << "\n<<AcTree::Show>>\n";

		AcNode *ptr = _root;
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
					if (ptr->children[i]->_end)
						std::cout << "<-*" << std::ends;
					q.push({ level + 1, ptr->children[i] });
				}
			}
		}

		std::cout << "<<AcTree::Show End>>\n";
	}

	void AcTree::_insert_ac_tree(const Bytes& keyword) {
		AcNode *cur = _root;
		for (auto& i : keyword) {
			if (cur->children[i] == nullptr)
				cur->children[i] = new AcNode();
			cur = cur->children[i];
		}
		cur->_end = true;
		cur->_len = keyword.size();
		cur->_type = keyword;
	}

	void AcTree::_BuildAcAutomation() {
		AcNode *cur = nullptr;
		AcNode *ptr = nullptr;
		std::queue<AcNode *> q;
		q.push(_root);
		while (!q.empty()) {
			cur = q.front();
			q.pop();
			for (int i = 0; i < AcNode::kCharCnt; ++i) {
				if (cur->children[i]) {
					ptr = cur->fail;
					while (ptr && ptr->children[i] == nullptr) ptr = ptr->fail;
		
					if (ptr == nullptr)
						cur->children[i]->fail = _root;
					else
						cur->children[i]->fail = ptr->children[i];
					q.push(cur->children[i]);
				}
			}
		}
	}
}