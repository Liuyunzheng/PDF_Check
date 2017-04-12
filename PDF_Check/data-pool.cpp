#include "data-pool.h"

DataPool::DataPool(const std::wstring& path) : _path(path), _file{ new std::ifstream{ path, std::ios::binary } }, _pbuf{ _file->rdbuf() } {
	Read(path); /* open file */

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
		if (_file_size < FILE_SIZE) { /* read data into buffer (����ĵ�С��FILE_SIZE Bytesֱ�Ӵ洢��_data�У��ڴ���ʸ���) */
			_pbuf->sgetn(_cache._data, _file_size);
			_cache._data[_file_size] = '\0';
			_cache.set_boader(0, _file_size);
		}
		else {  /* read by _pbuf later (�ļ����ڻ����FILE_SIZE Bytesʱ��ͨ��_pbufָ���ȡ���ٶȻ���һЩ������ʡ�ڴ�) */
			_pbuf->pubseekpos(0, std::ios::in);
		}

	}
	catch (...) {
		return false;
	}

	return true;
}

void DataPool::Show() {
	for (unsigned int i = 0; i < _file_size; ++i)
		std::cout << at(i);
	std::cout << std::endl;
}

bool DataPool::saved_in_stack() const {
	return _file_size < FILE_SIZE; /* ûë���� �����Լ�¼FILE_SIZE-1 Bytes���ݵ� _data,��Ϊ����һ�� '\0' */
}

char DataPool::next() {
	if (_current_pos >= _file_size)
		throw std::out_of_range("DataPool::next()");
	++_current_pos;
	return at(_current_pos);
}

char DataPool::at(unsigned int pos) {
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
			len = (len >= FILE_SIZE ? FILE_SIZE - 1 : len);
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

std::vector<char> DataPool::get_data(unsigned int begin, unsigned int end) {
	std::vector<char> data;
	end = (end >= _file_size ? _file_size : end);
	for (unsigned int i = begin; i <= end; ++i)
		data.push_back(at(i));

	return data;
}