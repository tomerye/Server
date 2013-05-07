/*
 * ClientConnection.cpp
 *
 *  Created on: Apr 6, 2013
 *      Author: tomer
 */

#include "ClientConnection.h"

ClientConnection::ClientConnection(tcp::socket *socket , Server *server,char id) :
		id_(id),connection_(socket) {
	this->pServer_=server;
}

ClientConnection::~ClientConnection() {
	// TODO Auto-generated destructor stub
}

void ClientConnection::send(Packet packet) {
	connection_.async_write(packet,
			boost::bind(&ClientConnection::sendResult, this,
					boost::asio::placeholders::error));
}

void ClientConnection::waitForPacket() {
	Packet *newPacket = new Packet();
	connection_.async_read(newPacket,
			boost::bind(&ClientConnection::handleReceivePacket, this,
					boost::asio::placeholders::error, newPacket));
}

void ClientConnection::handleReceivePacket(const boost::system::error_code& e,
		Packet *packet) {
	if (!e) {
			std::cout << "Recived id:" << packet->id_ << std::endl;
	} else {

		pServer_->deleteConnection(id_);
	}
	delete packet;
}

void ClientConnection::sendResult(const boost::system::error_code& e){
	if(!e){

	}
	else{
		pServer_->deleteConnection(id_);
		std::cout << "error send to client/n";
	}
}
