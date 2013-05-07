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
		cout << "handleGetNewConnectionID\n";
		char *clientId = new char();
		boost::asio::async_read(*newSocket,
				boost::asio::buffer(clientId, sizeof(char)),
				boost::bind(&Server::addNewConnection, this,
						boost::asio::placeholders::error, clientId, newSocket));
	} else {

		std::cout << "error " << __FILE__ << __LINE__ << std::endl;
		delete newSocket;

	}
	startAccept();
}

void Server::addNewConnection(const boost::system::error_code& e, char *id,
		tcp::socket *newSocket) {
	std::cout << "received new ID:" << *id;
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
	}
}

void Server::deleteConnection(const char id) {
	std::map<int, ClientConnection*>::iterator it = connection_map_.find(id);
	cout << "Delete connection with ID:" << id <<endl;
	if (it != connection_map_.end()) {
		connection_map_.erase(it);
		std::cout << "id" << id << "deleted!/n";
	} else {
		std::cout << "no such id/n";
	}
}

void Server::send(const char id, const Packet packet) {
	std::map<int, ClientConnection*>::iterator it = connection_map_.find(id);
	cout << "trying to send packet to ID:" << id << endl;
	if (it != connection_map_.end()) {
		it->second->send(packet);
	} else {
		std::cout << "no such id/n";
	}

}
