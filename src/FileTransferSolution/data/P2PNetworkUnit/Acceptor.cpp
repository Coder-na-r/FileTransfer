#include "Acceptor.h"

namespace Data {

	namespace P2P {

        Acceptor::Acceptor(asio::io_service& ios, unsigned short port_num, std::vector<P2PNode>& connections, std::function<void(Domain::FT::Entity::ConnectionInfo)> onConnected)
            : ioService(ios),
            acceptor(ioService,
                asio::ip::tcp::endpoint(
                    asio::ip::address_v4::any(),
                    port_num)),
            isStopped(false),
            connections(&connections),
            onConnectedCallback(onConnected)
        {
        }

        void Acceptor::Start()
        {
            acceptor.listen();
            InitAccept();
        }

        void Acceptor::Stop()
        {
            isStopped.store(true);
        }

        void Acceptor::InitAccept() {

            std::shared_ptr<asio::ip::tcp::socket>
                sock(new asio::ip::tcp::socket(ioService));

            acceptor.async_accept(*sock.get(),
                [this, sock](const boost::system::error_code& error) {
                    onAccept(error, sock);
                });
        }

        void Acceptor::onAccept(const boost::system::error_code& ec, std::shared_ptr<asio::ip::tcp::socket> sock)
        {
            onConnectedCallback({ ec.value() == 0, sock->remote_endpoint().address().to_string(), sock->remote_endpoint().port() });

            if (ec.value() == 0) {
                connections->push_back({ sock });
            }
            else {
                std::cout << "Error! Error code = " << ec.value() << ". Message: " << ec.message();
            }

            if (!isStopped.load()) {
                InitAccept();
            }
            else {
                acceptor.close();
            }
        }

	}

}