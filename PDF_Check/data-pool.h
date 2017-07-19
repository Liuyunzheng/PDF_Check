#ifndef DETECT_DATA_POOL_H_
#define DETECT_DATA_POOL_H_

#include <iostream>
#include <memory>
#include <fstream>
#include "basic-type.h"

namespace PDF_CHECK {

	struct Data {
		/** when file is smaller than 10KB, the data will be stored in data (��ʱֱ����ջdata�д洢�ĵ�����) */
		static const unsigned int kCacheSize = 10240; 
		unsigned int begin;
		/** end is the position of '\0' */
		unsigned int end; 
		char data[kCacheSize];
		
		Data() 
			: begin{ 0 }, end{ 0 } {
			memset(data, 0, sizeof(data));
		}

		void SetBoader(unsigned int begin, unsigned int end) { /* ��¼data�д洢�������е���һ�������ݣ�[begin, end) */
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
		/** ���Ǹ��ٵ�operator[]����Ϊ����ֵ�������ã�����ֻ�ܶ������޸� */
		char operator[](unsigned int) const; 
		/** �����ļ����ݵ��ֽ��� */
		unsigned int size() const { return file_size_; }
		/** ��ȡ��Χ��[begin, end] ע��string��Ҫ̫��,����̫��ʱ�����ϲ��װ��������һ���Զ���һ��string�� */
		Bytes get_data(unsigned int begin, unsigned int end) const; 
		unsigned int current_pos() const { return current_pos_; }
		
		// /** ָ��current_pos_��λ�� */
		// void set_pos(unsigned int pos = 0);
		// /** ���޸�current_pos_ ָ��,ʹ�øú���ǰ��Ҫ�ȵ���set_pos����������ʼλ�� */
		// char next() const; 

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