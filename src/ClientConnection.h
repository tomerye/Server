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

using boost::asio::ip::tcp;

class ClientConnection {
public:
	ClientConnection(tcp::socket *socket);
	virtual ~ClientConnection();
	tcp::socket& getSocket() const;
private:
	AsyncSerializationConnection connection_;
};

#endif /* CLIENTCONNECTION_H_ */
