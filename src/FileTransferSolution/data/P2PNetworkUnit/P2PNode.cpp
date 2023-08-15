#include "P2PNode.h"

#include "HashCRC.hpp"

namespace Data {

	namespace P2P {

		P2PNode::P2PNode(std::shared_ptr<asio::ip::tcp::socket> sock)
			: sock(sock),
			bufferIn(new char[BUFFER_SIZE]),
			length(0),
			hasher(new Data::Hash::Hash())	// DI
		{}

		bool P2PNode::send(const char* data, const uint64_t size, uint8_t maxAttempts) {

			MSG_INFO reqMsgInfo{ TYPE_MSG::USER, size, hasher->calcHash(data, size), maxAttempts };
			MSG_INFO respMsgInfo{ TYPE_MSG::USER, 0, 0, 0 };

			while (reqMsgInfo.maxAttempts > 0) {

				send__(reqMsgInfo);

				send(data, size);

				recv__(respMsgInfo);

				if (respMsgInfo.typeMsg == TYPE_MSG::SERVICE_OK) {
					return true;
				}

				--reqMsgInfo.maxAttempts;
			}


			return false;
		}

		size_t P2PNode::recv(char* data) {

			return {};

		}

		void P2PNode::send__(const MSG_INFO& msgInfo) {

			send__((const char*)&msgInfo, sizeof(MSG_INFO));
		}

		void P2PNode::send__(const char* data, const uint64_t size) {

			uint64_t done = 0;

			while (done != size) {

				done += sock->send(asio::buffer(data + done, size - done));
			}

			return;
		}

		void P2PNode::recv__(MSG_INFO& msgInfo) {



		}

	}

}