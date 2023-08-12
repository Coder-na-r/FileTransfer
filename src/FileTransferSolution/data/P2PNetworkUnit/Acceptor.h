#pragma once

#include "P2PNode.h"

#include "boost\asio.hpp"

#include <iostream>
#include <memory>

using namespace boost;

namespace Data {

	namespace P2P {

        class Acceptor {

        public:

            Acceptor(asio::io_service& ios, unsigned short port_num, std::vector<P2PNode>& connections, std::function<void(bool, std::shared_ptr<asio::ip::tcp::socket>)> onConnected);

            void Start();

            void Stop();

        private:

            void InitAccept();

            void onAccept(const boost::system::error_code& ec, std::shared_ptr<asio::ip::tcp::socket> sock);

        private:
            asio::io_service& ioService;
            asio::ip::tcp::acceptor acceptor;
            std::atomic<bool> isStopped;

            std::function<void(bool, std::shared_ptr<asio::ip::tcp::socket>)> onConnectedCallback;

            std::vector<P2PNode>* connections;
        };

	}

}