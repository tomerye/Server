/*
 * Server.cpp
 *
 *  Created on: Apr 6, 2013
 *      Author: tomer
 */

#include "Server.h"

using namespace std;

Server::Server(int port, boost::asio::io_service &io_service) :
		endpoint_(tcp::v4(), port), io_service_(io_service), acceptor_(
				io_service, endpoint_) {
	startAccept();

}

void Server::startAccept() {
	cout << "Start accept!\n";
	tcp::socket *newSocket = new tcp::socket(io_service_);
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
		size_t *clientId = new size_t();
		boost::asio::async_read(*newSocket,
				boost::asio::buffer(clientId, sizeof(size_t)),
				boost::bind(&Server::addNewConnection, this, clientId,
						newSocket, boost::asio::placeholders::error));
		startAccept();
	} else {

		std::cout << "error " << __FILE__ << __LINE__ << std::endl;
		delete newSocket;

	}

}

void Server::addNewConnection(size_t *id, tcp::socket *newSocket,
		const boost::system::error_code& e) {
	std::cout << "received new ID:" << (size_t) *id << std::endl;
	std::cout.flush();
	if (!e) {
		if (connection_map_.find(*id) == connection_map_.end()) {
			connection_map_[*id] = new ClientConnection(newSocket, this, *id);
		} else {
			std::cout << "someone with same id trying to connect!\n";
			delete newSocket;
			delete id;

		}
	} else {
		std::cout << "error addNewConnection/n";
		delete newSocket;
		delete id;
	}
}

void Server::deleteConnection(const size_t id) {
	std::map<int, ClientConnection*>::iterator it = connection_map_.find(id);
	cout << "Delete connection with ID:" << id << endl;
	if (it != connection_map_.end()) {
		connection_map_.erase(it);
		std::cout << "id" << id << "deleted!/n";
	} else {
		std::cout << "no such id/n";
	}
}

void Server::send(const size_t id, const Packet packet) {
	std::map<int, ClientConnection*>::iterator it = connection_map_.find(id);
	cout << "trying to send packet to ID:" << id << endl;
	if (it != connection_map_.end()) {
		it->second->send(packet);
	} else {
		std::cout << "no such id/n";
	}

}
