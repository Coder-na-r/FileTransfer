#pragma once

#include "externalInterfaces/INetworkConnection.hpp"
#include "entity/ConnectionInfo.hpp"

#include "Acceptor.h"

#include "boost\asio.hpp"

#include <memory>

using namespace boost;

namespace Data {

    namespace P2P {

        class P2PNetworkUnit : public Domain::FT::externalInterfaces::INetworkConnection {

        public:

            P2PNetworkUnit(std::function<void(Domain::FT::Entity::ConnectionInfo)> onConnected);

            virtual void setOnConnectedCallback(std::function<void(Domain::FT::Entity::ConnectionInfo)> onConnected) override;

            virtual void start(unsigned int thread_pool_size = 1) override;

            virtual void startListen(const unsigned short port_num) override;

            virtual void connectTo(std::string ip, const unsigned short port) override;

            virtual void stopListen() override;

            virtual void stop() override;

            virtual size_t getCountConnections() override;

        private:

            asio::io_service ioService;
            std::unique_ptr<asio::io_service::work> ioWork;
            std::unique_ptr<Acceptor> acceptor;
            std::vector<std::unique_ptr<std::thread>> threadPool;

            std::function<void(Domain::FT::Entity::ConnectionInfo)> onConnectedCallback;

            std::vector<P2PNode> connections;   //  тут нужен интферфейс для threadsafe структуры + DI
        };

    }

}