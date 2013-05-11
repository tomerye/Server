/*
 * ClientConnection.cpp
 *
 *  Created on: Apr 6, 2013
 *      Author: tomer
 */

#include "ClientConnection.h"

ClientConnection::ClientConnection(tcp::socket *socket, Server *server,
		size_t id) :
		id_(id), connection_(socket) {
	this->pServer_ = server;
	waitForPacket();
}

ClientConnection::~ClientConnection() {
	// TODO Auto-generated destructor stub
}

void ClientConnection::send(Packet packet) {
	std::vector<Packet> *packetsVec = new std::vector<Packet>();
	packetsVec->push_back(packet);
	connection_.async_write(*packetsVec,
			boost::bind(&ClientConnection::sendResult, this,
					boost::asio::placeholders::error, packetsVec));
}

void ClientConnection::waitForPacket() {
	std::cout << "waiting for packets from client\n";
	std::cout.flush();
	std::vector<Packet> *packetsVec = new std::vector<Packet>();
	connection_.async_read(*packetsVec,
			boost::bind(&ClientConnection::handleReceivePacket, this,
					boost::asio::placeholders::error, packetsVec));
}

void ClientConnection::handleReceivePacket(const boost::system::error_code& e,
		std::vector<Packet> *packetsVec) {

	if (!e) {
		waitForPacket();
		std::cout << "parsing the packet\n";
		for (std::size_t i = 0; i < packetsVec->size(); ++i) {
			std::cout << "Recived id:" << ((*packetsVec)[i]).id_ << std::endl;
			std::cout << "Recived file path:" << ((*packetsVec)[i]).file_path_
					<< std::endl;
			std::cout << "Recived opcode:" << ((*packetsVec)[i]).opcode_
					<< std::endl;
			std::cout.flush();
		}
	} else {
		std::cout << "error while parsing the packet\n";
		pServer_->deleteConnection(id_);
	}
	delete packetsVec;
}

void ClientConnection::sendResult(const boost::system::error_code& e,
		std::vector<Packet> *packetsVec) {
	delete packetsVec;
	if (!e) {
		std::cout << "packet sent to client!\n";

	} else {
		std::cout << "error send to client\n";
		pServer_->deleteConnection(id_);
	}
}
