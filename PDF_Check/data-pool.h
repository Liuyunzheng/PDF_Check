#ifndef DETECT_DATA_POOL_H_
#define DETECT_DATA_POOL_H_

#include <iostream>
#include <memory>
#include <vector>
#include <fstream>

namespace PDF_CHECK {

	struct Data {
		static const unsigned int CACHE_SIZE = 10240; /* when file is smaller than 10KB, the data will be stored in _data (��ʱֱ����ջ_data�д洢�ĵ�����) */
		unsigned int _begin;
		unsigned int _end; /* position of '\0' */
		char _data[CACHE_SIZE];
		Data() : _begin{ 0 }, _end{ 0 } {}
		void set_boader(unsigned int begin, unsigned int end) { /* ��¼_data�д洢�������е���һ�������ݣ�[_begin, _end) */
			_begin = begin;
			_end = end;
		}
	};

	class DataPool {
	private:
		static const unsigned int CACHE_SIZE = Data::CACHE_SIZE;
	public:
		explicit DataPool(const std::wstring& path);
		~DataPool();

		bool Read(const std::wstring& path);
		void Show() const;
		unsigned int Size() const { // �����ļ����ݵ��ֽ���
			return _file_size;
		}
		std::vector<char> get_data(unsigned int begin, unsigned int end) const; /* ��ȡ��Χ��[begin, end] ע��vector��Ҫ̫��,����̫��ʱ�����ϲ��װ��������һ���Զ���һ��vector�� */
		char next() const; /* ���޸�_current_pos ָ�� */
		char at(unsigned int) const;
		char operator[](unsigned int) const; /* ���Ǹ��ٵ�operator[]����Ϊ����ֵ�������ã�����ֻ�ܶ������޸� */
		unsigned int current_pos() const { return _current_pos; }

	protected:
		void set_pos(unsigned int pos = 0); /* ָ��_current_pos��λ�� */

	private:
		bool saved_in_stack() const; /* is data saved in _data ? */
		bool _read(const std::wstring& path);

	private:
		std::wstring _path;
		std::unique_ptr<std::ifstream> _file;
		std::filebuf* _pbuf{ nullptr };
		size_t _file_size{ 0 };
		mutable Data _cache;
		mutable unsigned int _current_pos{ 0 };
	};
}

#endif /* end of DETECT_DATA_POOL_H_ */