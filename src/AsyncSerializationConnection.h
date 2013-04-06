/*
 * AsyncSerializationConnection.h
 *
 *  Created on: Apr 6, 2013
 *      Author: tomer
 */

#ifndef ASYNCSERIALIZATIONCONNECTION_H_
#define ASYNCSERIALIZATIONCONNECTION_H_

#include <boost/tuple/tuple.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

class AsyncSerializationConnection {
public:
	AsyncSerializationConnection(boost::asio::ip::tcp::socket *socket);
	virtual ~AsyncSerializationConnection();

	template<typename T, typename Handler>
	void async_write(const T& t, Handler handler);

	template<typename T, typename Handler>
	void async_read(T& t, Handler handler);

private:

	template<typename T, typename Handler>
	void handle_read_header(const boost::system::error_code& e, T& t,
			boost::tuple<Handler> handler);
	template<typename T, typename Handler>
	void handle_read_data(const boost::system::error_code& e, T& t,
			boost::tuple<Handler> handler);

	boost::asio::ip::tcp::socket *socket_;
	enum {
		header_length = 8
	};
	std::string outbound_header_;
	std::string outbound_data_;
	char inbound_header_[header_length];
	std::vector<char> inbound_data_;
};

#endif /* ASYNCSERIALIZATIONCONNECTION_H_ */
