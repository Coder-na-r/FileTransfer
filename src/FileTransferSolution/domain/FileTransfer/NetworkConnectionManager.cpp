#include "NetworkConnectionManager.h"

namespace Domain {

	namespace FT {

		NetworkConnectionManager::NetworkConnectionManager(INetworkConnection* networkConnection)
			: networkConnection(networkConnection)
		{}

		void NetworkConnectionManager::setOnConnectedCallback(std::function<void(Domain::FT::Entity::ConnectionInfo)> onConnected) {
			networkConnection->setOnConnectedCallback(onConnected);
		}

		void NetworkConnectionManager::start(unsigned int thread_pool_size) {
			networkConnection->start(thread_pool_size);
		}

		void NetworkConnectionManager::startListen(const unsigned short port_num) {
			networkConnection->startListen(port_num);
		}

		void NetworkConnectionManager::connectTo(std::string ip, const unsigned short port) {
			networkConnection->connectTo(ip, port);
		}

		void NetworkConnectionManager::stopListen() {
			networkConnection->stopListen();
		}

		void NetworkConnectionManager::stop() {
			networkConnection->stop();
		}

		size_t NetworkConnectionManager::getCountConnections() {
			return networkConnection->getCountConnections();
		}

	}

}