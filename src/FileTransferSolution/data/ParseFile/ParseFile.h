#pragma once

#include "externalInterfaces/IParseFile.hpp"

#include <stdint.h>

#include <iostream>
#include <fstream>

namespace Data {

	namespace PF {

		class ParseFile : public Domain::FT::externalInterfaces::IParseFile {

		public:

			ParseFile(const char* name, const Type type);

			bool isOpen() const;

			bool eof() const;

			uint64_t getSize() const;

			uint64_t getData(char* buffer, const uint64_t size);

			bool writeData(const char* buffer, const uint64_t size);

			uint64_t getPos() const;

			bool setPos(const uint64_t position);

			~ParseFile();

		private:

			ParseFile() = delete;

			uint64_t calcSize__();

			/* fields */

			std::fstream file;

			Type type;
			uint64_t size{ 0 };
			uint64_t iterator{ 0 };
		};
	}
}