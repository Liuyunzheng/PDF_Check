#include "data-pool.h"

namespace PDF_CHECK {

	DataPool::DataPool(const std::wstring& path) 
		: path_(path), 
		  file_{ new std::ifstream{ path, std::ios::binary } }, 
		  pbuf_{ file_->rdbuf() } {
		Read(path); /* open file */
	}

	DataPool::~DataPool() {
		pbuf_->close();
	}

	bool DataPool::Read_(const std::wstring& path) {
		try {
			if (path_ != path) {
				pbuf_->close();
				pbuf_->open(path, std::ios::in | std::ios::binary);
				path_ = path;
			}
			current_pos_ = 0;
			pbuf_->pubseekpos(current_pos_, std::ios::in);

		}
		catch (...) {
			return false;
		}

		if (!pbuf_->is_open())
			return false;
		
		return true;
	}

	bool DataPool::Read(const std::wstring& path) {
		if (!Read_(path)) {
			return false;
		}

		try {
			file_size_ = static_cast<size_t>(pbuf_->pubseekoff(0, std::ios::end)); /* record file size */
			pbuf_->pubseekpos(0, std::ios::in);
			if (file_size_ < kCacheSize) { /* read data into buffer (如果文档小于kCacheSize Bytes直接存储在data中，内存访问更快) */
				pbuf_->sgetn(cache_.data, file_size_);
				cache_.data[file_size_] = '\0';
				cache_.SetBoader(0, file_size_);
			} 
			else {  /* read by pbuf_ later (文件大于或等于kCacheSize Bytes时，通过pbuf_指针读取，速度会慢一些，但是省内存) */
				pbuf_->pubseekpos(0, std::ios::in);
			}

		}
		catch (...) {
			return false;
		}

		return true;
	}

	void DataPool::Show() const {
		for (unsigned int i = 0; i < file_size_; ++i)
			std::cout << at(i);
		std::cout << std::endl;
	}

	bool DataPool::SaveInStack() const {
		return file_size_ < kCacheSize; /* 没毛病， 最多可以记录kCacheSize-1 Bytes数据到 data,因为多了一个 '\0' */
	}

	//char DataPool::next() const {
	//	if (current_pos_ >= file_size_)
	//		throw std::out_of_range("DataPool::next()");
	//	++current_pos_;
	//	return at(current_pos_);
	//}

	char DataPool::operator[](unsigned int pos) const {
		return at(pos);
	}

	char DataPool::at(unsigned int pos) const {
		if (pos >= file_size_)
			throw std::out_of_range("DataPool::at");

		if (SaveInStack()) {
			return cache_.data[pos];
		}
		else {
			if (cache_.begin <= pos && pos < cache_.end) /* 命中(注意: pos < cache_.end) */
				return cache_.data[pos - cache_.begin];
			else { /* 提高命中率，避免多次读文件 */
				pbuf_->pubseekpos(pos, std::ios::in);
				unsigned int len = file_size_ - pos;
				len = (len >= kCacheSize ? kCacheSize - 1 : len);
				pbuf_->sgetn(cache_.data, len);
				cache_.data[len] = '\0';
				cache_.SetBoader(pos, pos + len + 1);
				return cache_.data[pos - cache_.begin];
			}
		}
	}

	//void DataPool::set_pos(unsigned int pos) {
	//	if (pos <= file_size_)
	//		current_pos_ = pos;
	//	else
	//		throw std::out_of_range("DataPool::set_pos()");
	//}

	Bytes DataPool::get_data(unsigned int begin, unsigned int end) const {
		end = (end >= file_size_ ? file_size_ - 1 : end);
		Bytes data(end + 1, '\0');
		for (unsigned int i = begin; i <= end; ++i)
			data[i - begin] = at(i);

		return data;
	}
}