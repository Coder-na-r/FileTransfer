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

				size = calcSize__();
			}
		}

		bool ParseFile::isOpen() const {

			return type != Type::ERROR;
		}

		bool ParseFile::eof() const {

			return iterator == size;
		}

		uint64_t ParseFile::getSize() const {

			return size;
		}

		uint64_t ParseFile::getData(char* buffer, const uint64_t size) {

			if (type != Type::INPUT) {

				return { 0 };
			}

			uint64_t remains = this->size - iterator;
			uint64_t length = remains <= size ? remains : size;

			file.read(buffer, length);

			iterator += length;

			return length;
		}

		bool ParseFile::writeData(const char* buffer, const uint64_t size) {

			if (type != Type::OUTPUT) {

				return { false };
			}

			file.write(buffer, size);

			iterator += size;

			this->size = calcSize__();

			return true;
		}

		uint64_t ParseFile::getPos() const {

			return iterator;
		}

		bool ParseFile::setPos(const uint64_t position) {

			if (position > size) {

				return false;
			}

			iterator = position;

			return true;
		}

		ParseFile::~ParseFile() {

			file.close();
		}

		uint64_t ParseFile::calcSize__() {

			auto beginPosition = file.tellg();

			file.seekg(0, std::ios::end);
			uint64_t size = file.tellg();
			file.seekg(beginPosition, std::ios::beg);

			return size;
		}
	}

}