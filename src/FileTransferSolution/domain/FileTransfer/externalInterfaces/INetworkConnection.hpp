#pragma once

#include "../Entity/ConnectionInfo.hpp"

#include <functional>
#include <string>

namespace Domain {

	namespace FT {

		namespace externalInterfaces {

			class INetworkConnection {

			public:

				virtual void setOnConnectedCallback(std::function<void(Domain::FT::Entity::ConnectionInfo)> onConnected) = 0;

				virtual void start(unsigned int thread_pool_size = 1) = 0;

				virtual void startListen(const unsigned short port_num) = 0;

				virtual void connectTo(std::string ip, const unsigned short port) = 0;

				virtual void stopListen() = 0;

				virtual void stop() = 0;

				virtual size_t getCountConnections() = 0;

			};

		}

	}

}