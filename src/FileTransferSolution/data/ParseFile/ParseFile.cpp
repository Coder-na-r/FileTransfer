#include "ParseFile.h"

namespace Data {

	namespace PF {

		ParseFile::ParseFile(const char* name, const Type type) : type(type), iterator(0) {

			if (type == Type::INPUT) {

				file.open(name, std::fstream::in, std::fstream::binary);

				if (!file.is_open()) { this->type = Type::ERROR; }
			}
			else if (type == Type::OUTPUT) {

				file.open(name, std::fstream::out, std::fstream::binary);

				if (!file.is_open()) { this->type = Type::ERROR; }
			}

			if (this->type != Type::ERROR) {

				file.seekg(0, std::ios::end);
				size = file.tellg();
				file.seekg(0, std::ios::beg);
			}
		}

		bool ParseFile::isOpen() const {

			return type != Type::ERROR;
		}

		bool ParseFile::eof()
		{
			return false;
		}

		uint64_t ParseFile::getSize() const
		{
			return 0;
		}

		uint64_t ParseFile::getData(char* buffer, const uint64_t size)
		{
			return 0;
		}

		bool ParseFile::writeData(const char* buffer, const uint64_t size)
		{
			return false;
		}

		uint64_t ParseFile::getPos() const
		{
			return 0;
		}

		void ParseFile::setPos(const uint64_t position)
		{
		}

		ParseFile::~ParseFile()
		{
		}
	}


}