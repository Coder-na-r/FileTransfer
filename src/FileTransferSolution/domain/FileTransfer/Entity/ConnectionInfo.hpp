#pragma once

#include <vector>
#include <string>

namespace Domain {

	namespace FT {

		namespace Entity {

			struct ConnectionInfo {

				ConnectionInfo(bool isSuccess, std::string ip, unsigned short port)
					: isSuccess(isSuccess),
					ip(ip),
					port(port)
				{}

				bool isSuccess;

				std::string ip;
				unsigned short port;

			};

		}

	}

}