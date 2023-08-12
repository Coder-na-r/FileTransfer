#pragma once

#include "Acceptor.h"

#include "boost\asio.hpp"

#include <memory>

using namespace boost;

namespace Data {

    namespace P2P {

        class P2PNetworkUnit {

        public:

            P2PNetworkUnit(std::function<void(bool, std::shared_ptr<asio::ip::tcp::socket>)> onConnected);

            void start(unsigned int thread_pool_size = 1);

            void startListen(const unsigned short port_num);

            void connectTo(std::string ip, const unsigned short port);

            void stopListen();

            void stop();

            size_t getCountConnections();

        private:

            asio::io_service ioService;
            std::unique_ptr<asio::io_service::work> ioWork;
            std::unique_ptr<Acceptor> acceptor;
            std::vector<std::unique_ptr<std::thread>> threadPool;

            std::function<void(bool, std::shared_ptr<asio::ip::tcp::socket>)> onConnectedCallback;

            std::vector<P2PNode> connections;   //  тут нужен интферфейс для threadsafe структуры + DI
        };

    }

}