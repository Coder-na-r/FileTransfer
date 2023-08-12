#include "P2PNode.h"

namespace Data {

	namespace P2P {

		P2PNode::P2PNode(std::shared_ptr<asio::ip::tcp::socket> sock)
			: sock(sock)
		{}

	}

}