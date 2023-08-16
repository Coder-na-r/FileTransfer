#include "P2PNode.h"

#include "HashCRC.hpp"

namespace Data {

	namespace P2P {

		P2PNode::P2PNode(std::shared_ptr<asio::ip::tcp::socket> sock)
			: sock(sock),
			hasher(new Data::Hash::Hash())	// DI
		{}

		bool P2PNode::send(const char* data, const uint64_t size, uint8_t maxAttempts) {

			MSG_INFO reqMsgInfo{ TYPE_MSG::USER, size, hasher->calcHash(data, size), maxAttempts };
			static MSG_INFO respMsgInfo{ TYPE_MSG::USER, 0, 0, 0 };

			send__(reqMsgInfo);

			while (reqMsgInfo.maxAttempts > 0 && reqMsgInfo.msgSize != 0) {

				send(data, size);

				recv__(respMsgInfo);

				if (respMsgInfo.typeMsg == TYPE_MSG::SERVICE_OK) {
					return true;
				}

				--reqMsgInfo.maxAttempts;
			}

			return false;
		}

		std::optional<uint64_t> P2PNode::recv(char* data, const uint64_t sizeBuffer) {

			static bool isHeaderRead = false;
			static MSG_INFO msgInfo{ TYPE_MSG::USER, 0, 0, 0 };
			static MSG_INFO respMsgInfo{ TYPE_MSG::SERVICE_OK, 0, 0, 0 };

			if (!isHeaderRead) {

				recv__(msgInfo);
				isHeaderRead = true;
			}

			if (msgInfo.msgSize > sizeBuffer) {

				return {};
			}

			isHeaderRead = false;

			for (uint8_t i = 0; i < msgInfo.maxAttempts; i++) {

				recv__(data, msgInfo.msgSize);

				if (hasher->calcHash(data, msgInfo.msgSize) == msgInfo.crc) {

					respMsgInfo.typeMsg = TYPE_MSG::SERVICE_OK;
					send__(respMsgInfo);
					return { msgInfo.msgSize };
				}

				respMsgInfo.typeMsg = TYPE_MSG::SERVICE_ERROR;
				send__(respMsgInfo);
			}

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

			recv__((char*)&msgInfo, sizeof(MSG_INFO));
		}

		void P2PNode::recv__(char* data, const uint64_t sizeWaiting) {

			uint64_t done = 0;

			while (done != sizeWaiting) {

				done += sock->receive(asio::buffer(data + done, sizeWaiting - done));
			}

			return;
		}

	}

}