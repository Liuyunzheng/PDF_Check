#include <iostream>
#include "scan-result.h"

namespace PDF_CHECK {

	void ScanResult::Add(unsigned int offset, const Bytes& keyword) {
		off_key_pairs.insert({ offset, keyword });
	}

	void ScanResult::Clear() {
		off_key_pairs.clear();
	}

	void ScanResult::Show() const {
		std::cout << "\n<<ScanResult::Show>>\n";
		
		for (auto& pair : off_key_pairs) {
			std::cout << "offset: " << pair.first << " keyword: ";
			//std::cout << pair.second << std::endl; // if Bytes is string
			for (auto& c : pair.second) {
				std::cout << std::hex << static_cast<int>(c);
			}
			std::cout << std::endl;
		}
		std::cout << "<<ScanResult::Show End>>\n";
	}

	std::vector<unsigned int> ScanResult::Find(const Bytes& keyword) const {
		std::vector<unsigned int> offsets;
		for (auto& pair : off_key_pairs) {
			if (pair.second == keyword)
				offsets.push_back(pair.first);
		}
		return offsets;
	}

	Bytes ScanResult::Find(unsigned int offset) const {
		for (auto& pair : off_key_pairs) {
			if (pair.first == offset)
				return pair.second;
		}
		return Bytes{};
	}
}