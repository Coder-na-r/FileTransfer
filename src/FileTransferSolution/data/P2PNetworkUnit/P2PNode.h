#pragma once

#include "externalInterfaces\IP2PNode.hpp"

#include "boost\asio.hpp"

#include <memory>

using namespace boost;

namespace Data {

	namespace P2P {

        class P2PNode : public Domain::FT::externalInterfaces::IP2PNode {

        public:

            P2PNode(std::shared_ptr<asio::ip::tcp::socket> sock);

        private:

            std::shared_ptr<asio::ip::tcp::socket> sock;

        };

	}

}