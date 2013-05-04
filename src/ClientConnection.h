/*
 * ClientConnection.h
 *
 *  Created on: Apr 6, 2013
 *      Author: tomer
 */

#ifndef CLIENTCONNECTION_H_
#define CLIENTCONNECTION_H_

#include <boost/asio.hpp>
#include "AsyncSerializationConnection.h"
#include "Packet.h"
#include <boost/system/error_code.hpp>
#include <boost/bind.hpp>






using boost::asio::ip::tcp;

class ClientConnection {
public:
	ClientConnection(tcp::socket *socket);
	virtual ~ClientConnection();
	tcp::socket& getSocket() const;
	void send(Packet Packet);
private:

	void waitForPacket();
	void handleReceivePacket(const boost::system::error_code& e,
			Packet *packet);
	void sendResult(const boost::system::error_code& e);
	AsyncSerializationConnection connection_;
};

#endif /* CLIENTCONNECTION_H_ */
