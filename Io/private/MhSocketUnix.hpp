#ifndef MHSOCKETUNIX_HPP
#define MHSOCKETUNIX_HPP
#include "../MhSocket.hpp"
extern "C" {
#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <unistd.h>
#include <sys/ioctl.h>
}

namespace MH33 {
struct Socket::SocketPriv
{
	sockaddr_in socketAddress;
	int sockfd;
	CONNECTION_TYPE conType;
	SocketPriv();
	std::string getIpAddr() const;

	bool connectTo();
	bool connectTo(const char* addr, int port);
	bool bindTo();
	bool bindTo(const char* addr, int port);
	CONNECTION_TYPE getConType() const;

	long sendMessage(const void *msg, size_t len, int flags = 0) const;
	long receiveMessage(void *buf, size_t len, int flags = 0) const;
	int listenTo(int backlog) const;

	// Wrapper for setsocketopt and getsocketopt
	bool getDebug() const;
	void setDebug(bool nval);
	bool getBroadcast() const;
	void setBroadcast(bool nval);
	bool getReuseAddr() const;
	void setReuseAddr(bool nval);
	bool getKeepAlive() const;
	void setKeepAlive(bool nval);
	int getOobinline() const;
	void setOobinline(int nval);
	int getSndBuffSize() const;
	void setSndBuffSize(int nval);
	int getRcvBuffSize() const;
	void setRcvBuffSize(int nval);
	bool getDontRoute() const;
	void setDontRoute(bool nval);
	int getRclLoWat() const;
	void setRclLoWat(int nval);
	timeval getRcvTimeout() const;
	void setRcvTimeout(timeval nval);
	int getSndLoWat() const;
	void setSndLoWat(int nval);
	timeval getSndTimeout() const;
	void setSndTimeout(timeval nval);

	void setBlocking(bool isBlocking);
};
}
#endif // MHSOCKETUNIX_HPP
