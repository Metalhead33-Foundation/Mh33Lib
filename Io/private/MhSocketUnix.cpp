#include "MhSocketUnix.hpp"
#include <cstring>

namespace MH33 {
Socket::SocketPriv::SocketPriv()
{

}
/*
Socket::SocketPriv::Socket::SocketPriv(const Socket::SocketPriv& cpy)
{
	socklen_t sizeToPass = sizeof(socketAddress);
	sockfd = accept(cpy.sockfd,reinterpret_cast<struct sockaddr*>(&socketAddress),&sizeToPass);
	if(sockfd < 0) throw std::runtime_error("Could not accept connection!\n");
	conType = CONNECTION_TYPE::CONNECTED;
}

void Socket::SocketPriv::operator=(const Socket::SocketPriv &cpy)
{
	if(sockfd != -1) close(sockfd);
	socklen_t sizeToPass = sizeof(socketAddress);
	sockfd = accept(cpy.sockfd,reinterpret_cast<struct sockaddr*>(&socketAddress),&sizeToPass);
	if(sockfd < 0) throw std::runtime_error("Could not accept connection!\n");
	conType = CONNECTION_TYPE::CONNECTED;
}
Socket::SocketPriv::Socket::SocketPriv()
	: sockfd(socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)), conType(CONNECTION_TYPE::DISCONNECTED)
{
	if(sockfd < 0) throw std::runtime_error("Could not open socket!\n");
}
Socket::SocketPriv::Socket::SocketPriv(const char *addr, int port, CONNECTION_TYPE nConType)
{
	sockfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(sockfd < 0) throw std::runtime_error("Could not open socket!\n");
	socketAddress.sin_family = AF_INET;
	socketAddress.sin_port = htons(port);
	socketAddress.sin_addr.s_addr = INADDR_ANY;
	//inet_aton(addr,&(socketAddress.sin_addr));
	std::memset(socketAddress.sin_zero,0,8);
	switch (nConType) {
	case CONNECTION_TYPE::CONNECTED:
	{
		if(!connectTo())
			throw std::runtime_error("Could not connect to socket!\n");
		conType = CONNECTION_TYPE::CONNECTED;
		break;
	}
	case CONNECTION_TYPE::BOUND:
	{
		if(!bindTo())
			throw std::runtime_error("Could not bind to socket!\n");
		conType = CONNECTION_TYPE::BOUND;
		break;
	}
	default:
		conType = CONNECTION_TYPE::DISCONNECTED;
		break;
	}
}

Socket::SocketPriv::Socket::SocketPriv(Socket::SocketPriv &&mov)
	: sockfd(mov.sockfd), conType(mov.conType)
{
	mov.conType = CONNECTION_TYPE::DISCONNECTED;
	mov.sockfd = -1;
	std::memcpy(&socketAddress,&(mov.socketAddress),sizeof(socketAddress));
	std::memset(&(mov.socketAddress),0,sizeof(socketAddress));
}

void Socket::SocketPriv::operator=(Socket::SocketPriv &&mov)
{
	this->sockfd = mov.sockfd;
	mov.sockfd = -1;
	this->conType = mov.conType;
	mov.conType = CONNECTION_TYPE::DISCONNECTED;
	std::memcpy(&socketAddress,&(mov.socketAddress),sizeof(socketAddress));
	std::memset(&(mov.socketAddress),0,sizeof(socketAddress));
}

Socket::SocketPriv::~Socket::SocketPriv()
{
	if(sockfd != -1) close(sockfd);
}

Socket::SocketPriv Socket::SocketPriv::acceptConnection() const
{
	return Socket::SocketPriv(*this);
}
*/

MH33::CONNECTION_TYPE Socket::SocketPriv::getConType() const
{
	return conType;
}

std::string Socket::SocketPriv::getIpAddr() const
{
	return std::string(inet_ntoa(socketAddress.sin_addr));
}

bool Socket::SocketPriv::connectTo()
{
	if(connect(sockfd,reinterpret_cast<struct sockaddr *>(&socketAddress),sizeof(socketAddress)) == -1)
	{
		conType = CONNECTION_TYPE::DISCONNECTED;
		return false;
	}
	else {
		conType = CONNECTION_TYPE::CONNECTED;
		return true;
	}
}

bool Socket::SocketPriv::connectTo(const char *addr, int port)
{
	socketAddress.sin_port = htons(port);
	inet_aton(addr,&(socketAddress.sin_addr));
	std::memset(socketAddress.sin_zero,0,8);
	if(connect(sockfd,reinterpret_cast<struct sockaddr *>(&socketAddress),sizeof(socketAddress)) < 0)
	{
		return false;
	}
	else {
		conType = CONNECTION_TYPE::CONNECTED;
		return true;
	}
}

bool Socket::SocketPriv::bindTo()
{
	if(bind(sockfd,reinterpret_cast<struct sockaddr *>(&socketAddress),sizeof(socketAddress)) < 0)
	{
		conType = CONNECTION_TYPE::DISCONNECTED;
		return false;
	}
	else {
		conType = CONNECTION_TYPE::BOUND;
		return true;
	}
}

bool Socket::SocketPriv::bindTo(const char *addr, int port)
{
	socketAddress.sin_port = htons(port);
	inet_aton(addr,&(socketAddress.sin_addr));
	std::memset(socketAddress.sin_zero,0,8);
	if(bind(sockfd,reinterpret_cast<struct sockaddr *>(&socketAddress),sizeof(socketAddress)) < 0)
	{
		return false;
	}
	else {
		conType = CONNECTION_TYPE::BOUND;
		return true;
	}
}

long Socket::SocketPriv::sendMessage(const void *msg, size_t len, int flags) const
{
	return send(sockfd,msg,len,flags);
}

long Socket::SocketPriv::receiveMessage(void *buf, size_t len, int flags) const
{
	return recv(sockfd,buf,len,flags);
}

int Socket::SocketPriv::listenTo(int backlog) const
{
	return listen(sockfd,backlog);
}

bool Socket::SocketPriv::getDebug() const
{
	ReceptClass retval;
	socklen_t len=sizeof(int);
	if(getsockopt(sockfd,IPPROTO_TCP,SO_DEBUG,&retval,&len) == -1) return false;
	else return bool(retval.integer);
}
void Socket::SocketPriv::setDebug(bool nval)
{
	int setto = nval;
	setsockopt(sockfd,SOL_SOCKET,SO_DEBUG,&setto,sizeof(int));
}
bool Socket::SocketPriv::getBroadcast() const
{
	ReceptClass retval;
	socklen_t len=sizeof(int);
	if(getsockopt(sockfd,SOL_SOCKET,SO_BROADCAST,&retval,&len) == -1) return false;
	else return bool(retval.integer);
}
void Socket::SocketPriv::setBroadcast(bool nval)
{
	int setto = nval;
	setsockopt(sockfd,SOL_SOCKET,SO_BROADCAST,&setto,sizeof(int));
}
bool Socket::SocketPriv::getReuseAddr() const
{
	ReceptClass retval;
	socklen_t len=sizeof(int);
	if(getsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&retval,&len) == -1) return false;
	else return bool(retval.integer);
}
void Socket::SocketPriv::setReuseAddr(bool nval)
{
	int setto = nval;
	setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&setto,sizeof(int));
}
bool Socket::SocketPriv::getKeepAlive() const
{
	ReceptClass retval;
	socklen_t len=sizeof(int);
	if(getsockopt(sockfd,SOL_SOCKET,SO_KEEPALIVE,&retval,&len) == -1) return false;
	else return bool(retval.integer);
}
void Socket::SocketPriv::setKeepAlive(bool nval)
{
	int setto = nval;
	setsockopt(sockfd,SOL_SOCKET,SO_KEEPALIVE,&setto,sizeof(int));
}
int Socket::SocketPriv::getOobinline() const
{
	ReceptClass retval;
	socklen_t len=sizeof(int);
	if(getsockopt(sockfd,SOL_SOCKET,SO_OOBINLINE,&retval,&len) == -1) return -1;
	else return retval.integer;
}
void Socket::SocketPriv::setOobinline(int nval)
{
	setsockopt(sockfd,SOL_SOCKET,SO_OOBINLINE,&nval,sizeof(int));
}
int Socket::SocketPriv::getSndBuffSize() const
{
	ReceptClass retval;
	socklen_t len=sizeof(int);
	if(getsockopt(sockfd,SOL_SOCKET,SO_SNDBUF,&retval,&len) == -1) return -1;
	else return retval.integer;
}
void Socket::SocketPriv::setSndBuffSize(int nval)
{
	setsockopt(sockfd,SOL_SOCKET,SO_SNDBUF,&nval,sizeof(int));
}
int Socket::SocketPriv::getRcvBuffSize() const
{
	ReceptClass retval;
	socklen_t len=sizeof(int);
	if(getsockopt(sockfd,SOL_SOCKET,SO_RCVBUF,&retval,&len) == -1) return -1;
	else return retval.integer;
}
void Socket::SocketPriv::setRcvBuffSize(int nval)
{
	setsockopt(sockfd,SOL_SOCKET,SO_RCVBUF,&nval,sizeof(int));
}
bool Socket::SocketPriv::getDontRoute() const
{
	ReceptClass retval;
	socklen_t len=sizeof(int);
	if(getsockopt(sockfd,SOL_SOCKET,SO_DONTROUTE,&retval,&len) == -1) return false;
	else return bool(retval.integer);
}
void Socket::SocketPriv::setDontRoute(bool nval)
{
	int setto = nval;
	setsockopt(sockfd,SOL_SOCKET,SO_DONTROUTE,&setto,sizeof(int));
}
int Socket::SocketPriv::getRclLoWat() const
{
	ReceptClass retval;
	socklen_t len=sizeof(int);
	if(getsockopt(sockfd,SOL_SOCKET,SO_RCVLOWAT,&retval,&len) == -1) return -1;
	else return retval.integer;
}
void Socket::SocketPriv::setRclLoWat(int nval)
{
	setsockopt(sockfd,SOL_SOCKET,SO_RCVLOWAT,&nval,sizeof(int));
}
timeval Socket::SocketPriv::getRcvTimeout() const
{
	ReceptClass retval;
	socklen_t len=sizeof(timeval);
	if(getsockopt(sockfd,SOL_SOCKET,SO_RCVTIMEO,&retval,&len) == -1) return timeval();
	else return retval.tim;
}
void Socket::SocketPriv::setRcvTimeout(timeval nval)
{
	setsockopt(sockfd,SOL_SOCKET,SO_RCVTIMEO,&nval,sizeof(timeval));
}
int Socket::SocketPriv::getSndLoWat() const
{
	ReceptClass retval;
	socklen_t len=sizeof(int);
	if(getsockopt(sockfd,SOL_SOCKET,SO_SNDLOWAT,&retval,&len) == -1) return -1;
	else return retval.integer;
}
void Socket::SocketPriv::setSndLoWat(int nval)
{
	setsockopt(sockfd,SOL_SOCKET,SO_SNDLOWAT,&nval,sizeof(int));
}
timeval Socket::SocketPriv::getSndTimeout() const
{
	ReceptClass retval;
	socklen_t len=sizeof(timeval);
	if(getsockopt(sockfd,SOL_SOCKET,SO_SNDTIMEO,&retval,&len) == -1) return timeval();
	else return retval.tim;
}
void Socket::SocketPriv::setSndTimeout(timeval nval)
{
	setsockopt(sockfd,SOL_SOCKET,SO_SNDTIMEO,&nval,sizeof(timeval));
}

void Socket::SocketPriv::setBlocking(bool isBlocking)
{
	unsigned long n=isBlocking;
	ioctl(sockfd,FIONBIO,&n);
}

}
