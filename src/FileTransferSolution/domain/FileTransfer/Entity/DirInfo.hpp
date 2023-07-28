#pragma once

#include <stdint.h>	// ?

#include <vector>
#include <string>

namespace Domain {

	namespace FT {

		namespace Entity { 

			struct DirInfo {

				std::vector<std::string> files {};
				std::vector<std::string> directories {};
				uint64_t size = { 0 };

			};
		
		}

	}

}