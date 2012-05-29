/* socket.h - some of these functions go elsewhere */

#pragma once

#ifndef _INC_SOCKET
#define _INC_SOCKET

#pragma pack(push,8)

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

	
	typedef UINT_PTR        SOCKET;

/*
 * Select uses arrays of SOCKETs.  These macros manipulate such
 * arrays.  FD_SETSIZE may be defined by the user before including
 * this file, but the default here should be >= 64.
 *
 * CAVEAT IMPLEMENTOR and USER: THESE MACROS AND TYPES MUST BE
 * INCLUDED IN WINSOCK.H EXACTLY AS SHOWN HERE.
 */
#ifndef FD_SETSIZE
#define FD_SETSIZE      64
#endif /* FD_SETSIZE */

	typedef struct fd_set {
		u_int   fd_count;               /* how many are SET? */
		SOCKET  fd_array[FD_SETSIZE];   /* an array of SOCKETs */
	} fd_set;

/// Address families.
#define AF_UNSPEC       0               /* unspecified */
#define AF_UNIX         1               /* local to host (pipes, portals) */
#define AF_INET         2               /* internetwork: UDP, TCP, etc. */
#define AF_IMPLINK      3               /* arpanet imp addresses */
#define AF_PUP          4               /* pup protocols: e.g. BSP */
#define AF_CHAOS        5               /* mit CHAOS protocols */
#define AF_IPX          6               /* IPX and SPX */
#define AF_NS           6               /* XEROX NS protocols */
#define AF_ISO          7               /* ISO protocols */
#define AF_OSI          AF_ISO          /* OSI is ISO */
#define AF_ECMA         8               /* european computer manufacturers */
#define AF_DATAKIT      9               /* datakit protocols */
#define AF_CCITT        10              /* CCITT protocols, X.25 etc */
#define AF_SNA          11              /* IBM SNA */
#define AF_DECnet       12              /* DECnet */
#define AF_DLI          13              /* Direct data link interface */
#define AF_LAT          14              /* LAT */
#define AF_HYLINK       15              /* NSC Hyperchannel */
#define AF_APPLETALK    16              /* AppleTalk */
#define AF_NETBIOS      17              /* NetBios-style addresses */
#define AF_VOICEVIEW    18              /* VoiceView */
#define AF_FIREFOX      19              /* FireFox */
#define AF_UNKNOWN1     20              /* Somebody is using this! */
#define AF_BAN          21              /* Banyan */

#define AF_MAX          22

	/// Structure used by kernel to store most addresses.
	struct sockaddr {
		u_short	sa_family;              /* address family */
		char    sa_data[14];            /* up to 14 bytes of direct address */
	};

	/**
	Structures returned by network data base library, taken from the
	BSD file netdb.h.  All addresses are supplied in host order, and
	returned in network order (suitable for use in system calls).
	*/
	struct  hostent {
		char    *h_name;				/* official name of host */
		char    **h_aliases;			/* alias list */
		short   h_addrtype;				/* host address type */
		short   h_length;				/* length of address */
		char    **h_addr_list;			/* list of addresses */
#define h_addr  h_addr_list[0]          /* address, for backward compat */
	};

	/// It is assumed here that a network number fits in 32 bits.
	struct  netent {
		char    * n_name;		/* official name of net */
		char    * * n_aliases;  /* alias list */
		short   n_addrtype;		/* net address type */
		u_long  n_net;			/* network # */
	};

	struct  servent {
		char    *s_name;		/*!< official service name */
		char    **s_aliases;	/*!< alias list */
	#ifdef _WIN64
		char    *s_proto;		/*!< protocol to use */
		short   s_port;			/*!< port # */
	#else
		short   s_port;			/*!< port # */
		char    *s_proto;		/*!< protocol to use */
	#endif
	};

	struct  protoent {
		char    *p_name;		/*!< official protocol name */
		char    **p_aliases;	/*!< alias list */
		short   p_proto;		/*!< protocol # */
	};

/// Constants and structures defined by the internet system, Per RFC 790, September 1981, taken from the BSD file netinet/in.h.

/// Protocols
#define IPPROTO_IP				0			/* dummy for IP */
#define IPPROTO_ICMP			1			/* control message protocol */
#define IPPROTO_IGMP			2			/* group management protocol */
#define IPPROTO_GGP				3			/* gateway^2 (deprecated) */
#define IPPROTO_TCP				6			/* tcp */
#define IPPROTO_PUP				12			/* pup */
#define IPPROTO_UDP				17			/* user datagram protocol */
#define IPPROTO_IDP				22			/* xns idp */
#define IPPROTO_ND				77			/* UNOFFICIAL net disk proto */

#define IPPROTO_RAW				255			/* raw IP packet */
#define IPPROTO_MAX				256			

/// Port/socket numbers: network standard functions
#define IPPORT_ECHO             7
#define IPPORT_DISCARD          9
#define IPPORT_SYSTAT           11
#define IPPORT_DAYTIME          13
#define IPPORT_NETSTAT          15
#define IPPORT_FTP              21
#define IPPORT_TELNET           23
#define IPPORT_SMTP             25
#define IPPORT_TIMESERVER       37
#define IPPORT_NAMESERVER       42
#define IPPORT_WHOIS            43
#define IPPORT_MTP              57

/*
 * Port/socket numbers: host specific functions
 */
#define IPPORT_TFTP             69
#define IPPORT_RJE              77
#define IPPORT_FINGER           79
#define IPPORT_TTYLINK          87
#define IPPORT_SUPDUP           95

/*
 * UNIX TCP sockets
 */
#define IPPORT_EXECSERVER       512
#define IPPORT_LOGINSERVER      513
#define IPPORT_CMDSERVER        514
#define IPPORT_EFSSERVER        520

/*
 * UNIX UDP sockets
 */
#define IPPORT_BIFFUDP          512
#define IPPORT_WHOSERVER        513
#define IPPORT_ROUTESERVER      520
                                        /* 520+1 also used */

/*
 * Ports < IPPORT_RESERVED are reserved for
 * privileged processes (e.g. root).
 */
#define IPPORT_RESERVED         1024

/*
 * Link numbers
 */
#define IMPLINK_IP              155
#define IMPLINK_LOWEXPER        156
#define IMPLINK_HIGHEXPER       158


	/*
 * Options for use with [gs]etsockopt at the IP level.
 */
#define IP_OPTIONS          1           /* set/get IP per-packet options    */
#define IP_MULTICAST_IF     2           /* set/get IP multicast interface   */
#define IP_MULTICAST_TTL    3           /* set/get IP multicast timetolive  */
#define IP_MULTICAST_LOOP   4           /* set/get IP multicast loopback    */
#define IP_ADD_MEMBERSHIP   5           /* add  an IP group membership      */
#define IP_DROP_MEMBERSHIP  6           /* drop an IP group membership      */
#define IP_TTL              7           /* set/get IP Time To Live          */
#define IP_TOS              8           /* set/get IP Type Of Service       */
#define IP_DONTFRAGMENT     9           /* set/get IP Don't Fragment flag   */


#define IP_DEFAULT_MULTICAST_TTL   1    /* normally limit m'casts to 1 hop  */
#define IP_DEFAULT_MULTICAST_LOOP  1    /* normally hear sends if a member  */
#define IP_MAX_MEMBERSHIPS         20   /* per socket; must fit in one mbuf */

/*
 * Argument structure for IP_ADD_MEMBERSHIP and IP_DROP_MEMBERSHIP.
 */
struct ip_mreq {
        struct in_addr  imr_multiaddr;  /* IP multicast address of group */
        struct in_addr  imr_interface;  /* local IP address of interface */
};

/*
 * Definitions related to sockets: types, address families, options,
 * taken from the BSD file sys/socket.h.
 */

/// This is used instead of -1, since the SOCKET type is unsigned.
#define INVALID_SOCKET  (SOCKET)(~0)
#define SOCKET_ERROR            (-1)

/// Types
#define SOCK_STREAM     1               /*!< stream socket */
#define SOCK_DGRAM      2               /*!< datagram socket */
#define SOCK_RAW        3               /*!< raw-protocol interface */
#define SOCK_RDM        4               /*!< reliably-delivered message */
#define SOCK_SEQPACKET  5               /*!< sequenced packet stream */

/// Option flags per-socket.
#define SO_DEBUG        0x0001          /*!< turn on debugging info recording */
#define SO_ACCEPTCONN   0x0002          /*!< socket has had listen() */
#define SO_REUSEADDR    0x0004          /*!< allow local address reuse */
#define SO_KEEPALIVE    0x0008          /*!< keep connections alive */
#define SO_DONTROUTE    0x0010          /*!< just use interface addresses */
#define SO_BROADCAST    0x0020          /*!< permit sending of broadcast msgs */
#define SO_USELOOPBACK  0x0040          /*!< bypass hardware when possible */
#define SO_LINGER       0x0080          /*!< linger on close if data present */
#define SO_OOBINLINE    0x0100          /*!< leave received OOB data in line */

#define SO_DONTLINGER   (u_int)(~SO_LINGER)

/// Additional options.
#define SO_SNDBUF       0x1001          /*!< send buffer size */
#define SO_RCVBUF       0x1002          /*!< receive buffer size */
#define SO_SNDLOWAT     0x1003          /*!< send low-water mark */
#define SO_RCVLOWAT     0x1004          /*!< receive low-water mark */
#define SO_SNDTIMEO     0x1005          /*!< send timeout */
#define SO_RCVTIMEO     0x1006          /*!< receive timeout */
#define SO_ERROR        0x1007          /*!< get error status and clear */
#define SO_TYPE         0x1008          /*!< get socket type */

/*
 * Options for connect and disconnect data and options.  Used only by
 * non-TCP/IP transports such as DECNet, OSI TP4, etc.
 */
#define SO_CONNDATA     0x7000
#define SO_CONNOPT      0x7001
#define SO_DISCDATA     0x7002
#define SO_DISCOPT      0x7003
#define SO_CONNDATALEN  0x7004
#define SO_CONNOPTLEN   0x7005
#define SO_DISCDATALEN  0x7006
#define SO_DISCOPTLEN   0x7007

/*
 * Option for opening sockets for synchronous access.
 */
#define SO_OPENTYPE     0x7008

#define SO_SYNCHRONOUS_ALERT    0x10
#define SO_SYNCHRONOUS_NONALERT 0x20

/*
 * Other NT-specific options.
 */
#define SO_MAXDG        0x7009
#define SO_MAXPATHDG    0x700A
#define SO_UPDATE_ACCEPT_CONTEXT 0x700B
#define SO_CONNECT_TIME 0x700C

/*
 * TCP options.
 */
#define TCP_NODELAY     0x0001
#define TCP_BSDURGENT   0x7000

	SOCKET PASCAL	accept ( __in SOCKET s, __out_bcount_opt(*addrlen) struct sockaddr *addr, __inout_opt int *addrlen);
	int PASCAL		bind ( __in SOCKET s, __in_bcount(namelen) const struct sockaddr *addr, __in int namelen);
	int PASCAL		closesocket ( IN SOCKET s);
	int PASCAL		connect ( __in SOCKET s, __in_bcount(namelen) const struct sockaddr *name, __in int namelen);
	int PASCAL		ioctlsocket ( __in SOCKET s, __in long cmd, __inout unsigned long *argp);
	struct hostent * PASCAL gethostbyaddr( __in_bcount(len) const char * addr, __in int len, __in int type);
	struct hostent * PASCAL gethostbyname(__in_z const char * name);
	int PASCAL		gethostname ( __out_bcount_part(namelen, return) char * name, __in int namelen);
	int PASCAL		getpeername ( __in SOCKET s,	__out_bcount_part(*namelen, *namelen) struct sockaddr *name, __inout int * namelen);
	struct protoent * PASCAL getprotobyname(__in_z const char * name);
	struct protoent * PASCAL getprotobynumber(__in int proto);
	struct servent * PASCAL getservbyname( __in_z const char * name, __in_z const char * proto);
	struct servent * PASCAL getservbyport( __in int port, __in_z const char * proto);
	int PASCAL		getsockname ( __in SOCKET s, __out_bcount_part(*namelen, *namelen) struct sockaddr *name, __inout int * namelen);
	int PASCAL		getsockopt ( __in SOCKET s, __in int level, __in int optname, __out_bcount(*optlen) char * optval, __inout int *optlen);
	unsigned long PASCAL htonl ( __in u_long hostlong);
	unsigned short PASCAL htons (__in u_short hostshort);
	unsigned long PASCAL inet_addr (__in const char * cp);
	char * PASCAL	inet_ntoa (__in struct in_addr in);
	int PASCAL		listen (	__in SOCKET s,__in int backlog);
	unsigned long PASCAL	ntohl (__in unsigned long netlong);		// Goes to netinet/in.h
	unsigned short PASCAL	ntohs (__in unsigned short netshort);	// Goes to netinet/in.h
	int PASCAL		recv ( __in SOCKET s, __out_bcount_part(len, return) __out_data_source(NETWORK) char * buf, __in int len, __in int flags);
	int PASCAL		recvfrom ( __in SOCKET s, __out_bcount_part(len, return) __out_data_source(NETWORK) char * buf, __in int len, __in int flags,
		__out_bcount_opt(*fromlen) struct sockaddr * from, __inout_opt int * fromlen);
	int PASCAL		select ( __in int nfds, __inout_opt fd_set *readfds, __inout_opt fd_set *writefds, __inout_opt fd_set *exceptfds, __in_opt  const struct timeval *timeout);
	int PASCAL		send ( __in SOCKET s, __in_bcount(len) const char * buf, __in int len, __in int flags);
	int PASCAL		sendto ( __in SOCKET s, __in_bcount(len) const char * buf, __in int len, __in int flags,
						__in_bcount_opt(tolen) const struct sockaddr *to, __in int tolen);
	int PASCAL		setsockopt ( __in SOCKET s, __in int level, __in int optname,
						__in_bcount_opt(optlen) const char * optval, __in int optlen);
	int PASCAL		shutdown ( __in SOCKET s, __in int how);
	SOCKET PASCAL	socket ( __in int af, __in int type, __in int protocol);


#ifdef __cplusplus
}
#endif  /* __cplusplus */

#pragma pack(pop)

#endif  /* _INC_STAT */
