#pragma once

#include "externalInterfaces\IP2PNode.hpp"
#include "externalInterfaces/IHashCalc.hpp"

#include "boost\asio.hpp"

#include <memory>

#define BUFFER_SIZE 1024
#define HEADER_SIZE sizeof(MSG_INFO)

using namespace boost;

namespace Data {

	namespace P2P {

        class P2PNode : public Domain::FT::externalInterfaces::IP2PNode {

        public:

            P2PNode(std::shared_ptr<asio::ip::tcp::socket> sock);

            bool send(const char* data, const uint64_t size, uint8_t maxAttempts = 2);

            uint64_t recv(char* data);

        private:
            
            std::shared_ptr<asio::ip::tcp::socket> sock;

            std::unique_ptr<char[]> bufferIn;
            uint64_t length;

            std::unique_ptr<Data::externalInterfaces::IHashCalc> hasher;

            enum class TYPE_MSG : uint8_t {

                USER,
                SERVICE_OK,
                SERVICE_ERROR,

           };

            static struct MSG_INFO {

                MSG_INFO(TYPE_MSG typeMsg, uint64_t msgSize, uint32_t crc, uint8_t maxAttempts)
                    : typeMsg(typeMsg),
                    msgSize(msgSize),
                    crc(crc),
                    maxAttempts(maxAttempts)
                {}

                TYPE_MSG typeMsg;

                uint64_t msgSize;

                uint32_t crc;

                uint8_t maxAttempts;

            };

            void send__(const MSG_INFO& msgInfo);

            void send__(const char* data, const uint64_t size);

            void recv__(MSG_INFO& msgInfo);

        };

	}

}