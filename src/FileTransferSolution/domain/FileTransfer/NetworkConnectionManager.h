#pragma once

#include "externalInterfaces/INetworkConnection.hpp"
#include "Entity/ConnectionInfo.hpp"

#include <functional>
#include <memory>
#include <string>

namespace Domain {

	using namespace Domain::FT::externalInterfaces;

	namespace FT {

		class NetworkConnectionManager {

		public:

			NetworkConnectionManager(INetworkConnection* networkConnection);

			void setOnConnectedCallback(std::function<void(Domain::FT::Entity::ConnectionInfo)> onConnected);

			void start(unsigned int thread_pool_size = 1);

			void startListen(const unsigned short port_num);

			void connectTo(std::string ip, const unsigned short port);

			void stopListen();

			void stop();

			size_t getCountConnections();

		private:

			std::unique_ptr<INetworkConnection> networkConnection;

		};

	}

}