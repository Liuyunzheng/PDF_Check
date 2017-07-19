#ifndef DETECT_DATA_POOL_H_
#define DETECT_DATA_POOL_H_

#include <iostream>
#include <memory>
#include <fstream>
#include "basic-type.h"

namespace PDF_CHECK {

	struct Data {
		static const unsigned int kCacheSize = 10240; /* when file is smaller than 10KB, the data will be stored in data (此时直接在栈data中存储文档内容) */
		unsigned int begin;
		unsigned int end; /* position of '\0' */
		char data[kCacheSize];
		
		Data() 
			: begin{ 0 }, end{ 0 } {
			memset(data, 0, sizeof(data));
		}

		void SetBoader(unsigned int begin, unsigned int end) { /* 记录data中存储的是文中的哪一部分数据：[begin, end) */
			this->begin = begin;
			this->end = end;
		}
	};

	class DataPool {
	private:
		static const unsigned int kCacheSize = Data::kCacheSize;
	public:
		explicit DataPool(const std::wstring& path);
		~DataPool();

		bool Read(const std::wstring& path);
		void Show() const;

		char at(unsigned int) const;
		char operator[](unsigned int) const; /* 这是个假的operator[]，因为返回值不是引用，所以只能读不能修改 */
		unsigned int size() const { return file_size_; } // 返回文件数据的字节数
		Bytes get_data(unsigned int begin, unsigned int end) const; /* 读取范围：[begin, end] 注意string不要太长,数据太大时，做上层封装，而不是一次性读到一个string中 */
		unsigned int current_pos() const { return current_pos_; }

		// void set_pos(unsigned int pos = 0); /* 指定current_pos_的位置 */
		// char next() const; /* 会修改current_pos_ 指针,使用该函数前需要先调用set_pos函数设置起始位置 */

	private:
		bool SaveInStack() const; /* is data saved in data ? */
		bool Read_(const std::wstring& path);

	private:
		std::wstring path_;
		std::unique_ptr<std::ifstream> file_;
		std::filebuf* pbuf_{ nullptr };
		size_t file_size_{ 0 };
		mutable Data cache_;
		mutable unsigned int current_pos_{ 0 };
	};
}

#endif /* end of DETECT_DATA_POOL_H_ */