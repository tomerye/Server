/*
 * Server.cpp
 *
 *  Created on: Apr 6, 2013
 *      Author: tomer
 */

#include "Server.h"

Server::Server(int port, boost::asio::io_service &io_service) :
		endpoint_(tcp::v4(), port), io_service_(io_service), acceptor_(
				io_service, endpoint_) {
	tcp::socket *newSocket = new tcp::socket(io_service);
	acceptor_.async_accept(*newSocket,
			boost::bind(&Server::handleGetNewConnectionID, this,
					boost::asio::placeholders::error, newSocket));

}

Server::~Server() {
// TODO Auto-generated destructor stub
}

void Server::handleGetNewConnectionID(const boost::system::error_code& e,
		tcp::socket *newSocket) {
	if (!e) {
		size_t *id = new size_t();
		boost::asio::async_read(*newSocket,
				boost::asio::buffer(id, sizeof(size_t)),
				boost::bind(&Server::addNewConnection, this,
						boost::asio::placeholders::error, id, newSocket));
	} else {
		std::cout << "error " << __FILE__ << __LINE__ << std::endl;
	}
}

void Server::addNewConnection(const boost::system::error_code& e, size_t *id,
		tcp::socket *newSocket) {
	if (connection_map_.find(*id) != connection_map_.end()) {
		connection_map_[*id] = new ClientConnection(newSocket);
	} else {
		std::cout << "someone with same id trying to connect!\n";
		delete newSocket;
	}
}
