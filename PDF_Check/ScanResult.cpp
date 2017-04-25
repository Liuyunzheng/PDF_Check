#include "scan-result.h"
#include "basic-type.h"

namespace PDF_CHECK {

	void ScanResult::Add(unsigned int offset, const Bytes& keyword) {
		offsets.push_back(offset);
		keywords.push_back(keyword);
	}

	void ScanResult::Clear() {
		offsets.clear();
		keywords.clear();
	}

	void ScanResult::Show() const {
		std::cout << "\n<<ScanResult::Show>>\n";
		
		unsigned int len = offsets.size();
		if (len == 0)
			std::cout << "ScanResult is empty" << std::endl;

		for (unsigned int i = 0; i < len; i++) {
			std::cout << "offset: " << offsets[i] << std::ends << "keyword: ";
			for (auto& chr : keywords[i])
				std::cout << chr;
			std::cout << std::endl;
		}

		std::cout << "<<ScanResult::Show End>>\n";
	}
}