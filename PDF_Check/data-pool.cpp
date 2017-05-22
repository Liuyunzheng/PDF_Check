#include "data-pool.h"

namespace PDF_CHECK {

	DataPool::DataPool(const std::wstring& path) : _path(path), _file{ new std::ifstream{ path, std::ios::binary } }, _pbuf{ _file->rdbuf() } {
		Read(path); /* open file */

	}

	DataPool::~DataPool() {
		_pbuf->close();
	}

	bool DataPool::_read(const std::wstring& path) {
		try {
			if (_path != path) {
				_pbuf->close();
				_pbuf->open(path, std::ios::in | std::ios::binary);
				_path = path;
			}
			_current_pos = 0;
			_pbuf->pubseekpos(_current_pos, std::ios::in);

		}
		catch (...) {
			return false;
		}
		if (!_pbuf->is_open())
			return false;
		return true;
	}

	bool DataPool::Read(const std::wstring& path) {
		if (!_read(path)) return false;
		try {
			_file_size = static_cast<size_t>(_pbuf->pubseekoff(0, std::ios::end)); /* record file size */
			_pbuf->pubseekpos(0, std::ios::in);
			if (_file_size < kCacheSize) { /* read data into buffer (����ĵ�С��kCacheSize Bytesֱ�Ӵ洢��_data�У��ڴ���ʸ���) */
				_pbuf->sgetn(_cache._data, _file_size);
				_cache._data[_file_size] = '\0';
				_cache.set_boader(0, _file_size);
			}
			else {  /* read by _pbuf later (�ļ����ڻ����kCacheSize Bytesʱ��ͨ��_pbufָ���ȡ���ٶȻ���һЩ������ʡ�ڴ�) */
				_pbuf->pubseekpos(0, std::ios::in);
			}

		}
		catch (...) {
			return false;
		}

		return true;
	}

	void DataPool::Show() const {
		for (unsigned int i = 0; i < _file_size; ++i)
			std::cout << at(i);
		std::cout << std::endl;
	}

	bool DataPool::saved_in_stack() const {
		return _file_size < kCacheSize; /* ûë���� �����Լ�¼kCacheSize-1 Bytes���ݵ� _data,��Ϊ����һ�� '\0' */
	}

	char DataPool::next() const {
		if (_current_pos >= _file_size)
			throw std::out_of_range("DataPool::next()");
		++_current_pos;
		return at(_current_pos);
	}

	char DataPool::operator[](unsigned int pos) const {
		return at(pos);
	}

	char DataPool::at(unsigned int pos) const {
		if (pos >= _file_size)
			throw std::out_of_range("DataPool::at");

		if (saved_in_stack()) {
			return _cache._data[pos];
		}
		else {
			if (_cache._begin <= pos && pos < _cache._end) /* ����(ע��: pos < _cache.end) */
				return _cache._data[pos - _cache._begin];
			else { /* ��������ʣ������ζ��ļ� */
				_pbuf->pubseekpos(pos, std::ios::in);
				unsigned int len = _file_size - pos;
				len = (len >= kCacheSize ? kCacheSize - 1 : len);
				_pbuf->sgetn(_cache._data, len);
				_cache._data[len] = '\0';
				_cache.set_boader(pos, pos + len + 1);
				return _cache._data[pos - _cache._begin];
			}
		}
	}

	void DataPool::set_pos(unsigned int pos) {
		if (pos <= _file_size)
			_current_pos = pos;
		else
			throw std::out_of_range("DataPool::set_pos()");
	}

	Bytes DataPool::get_data(unsigned int begin, unsigned int end) const {
		Bytes data;
		end = (end >= _file_size ? _file_size - 1 : end);
		for (unsigned int i = begin; i <= end; ++i)
			data.push_back(at(i));

		return data;
	}
}