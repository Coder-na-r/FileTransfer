#pragma once

#include <stdint.h>

namespace Data {

	namespace externalInterfaces {

		class IHashCalc {

		public:

			virtual uint32_t calcHash(const char* data, const uint64_t size) = 0;

			//virtual ~IHashCalc() = 0;

		};

	}

}