/*
* A general method for scanning the data read from document, using Ac-Tree
*/

#ifndef DETECT_AC_TREE_H_
#define DETECT_AC_TREE_H_

namespace PDF_CHECK {
	struct ACNode {
		static const unsigned int kCharCnt = 256;
	};

	class AcTree {
	public:
		void BuildAcTree();
	private:
		void _insert_ac_tree();
		void _BuildAcAutomation();
	};
}

#endif /* end of DETECT_AC_TREE_H_ */