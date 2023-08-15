#include "P2PNetworkUnit.h"

namespace Data {

	namespace P2P {

        P2PNetworkUnit::P2PNetworkUnit(std::function<void(Domain::FT::Entity::ConnectionInfo)> onConnected)
            : onConnectedCallback(onConnected)
        {
            ioWork.reset(new asio::io_service::work(ioService));
        }

        void P2PNetworkUnit::setOnConnectedCallback(std::function<void(Domain::FT::Entity::ConnectionInfo)> onConnected) {
            onConnected = onConnected;
        }

        void P2PNetworkUnit::start(unsigned int thread_pool_size) {

            if (thread_pool_size == 0) {
                thread_pool_size = 1;
            }

            for (unsigned int i = 0; i < thread_pool_size; i++)
            {
                std::unique_ptr<std::thread> th(
                    new std::thread([this]()
                        { ioService.run(); }));

                threadPool.push_back(std::move(th));
            }
        }

        void P2PNetworkUnit::startListen(const unsigned short port_num)
        {

            acceptor.reset(new Acceptor(ioService, port_num, connections, onConnectedCallback));
            acceptor->Start();
        }

        void P2PNetworkUnit::connectTo(std::string ip, const unsigned short port) {

            std::shared_ptr<asio::ip::tcp::socket> sock(new asio::ip::tcp::socket(ioService));

            sock->async_connect({ asio::ip::address_v4::from_string(ip), port }, [this, sock](const boost::system::error_code& error) {

                onConnectedCallback({ error.value() == 0, sock->remote_endpoint().address().to_string(), sock->remote_endpoint().port() });

                if (error.value() == 0) {
                    connections.push_back({ sock });
                }
                else {
                    std::cout << "Error! Error code = " << error.value() << ". Message: " << error.message();
                }

                });
        }

        void P2PNetworkUnit::stopListen()
        {
            acceptor->Stop();
        }

        void P2PNetworkUnit::stop() {

            ioService.stop();

            for (auto& th : threadPool)
            {
                th->join();
            }
        }

        size_t P2PNetworkUnit::getCountConnections() {
            return connections.size();
        }

	}

}