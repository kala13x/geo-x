/*
 *  utils/socks.c
 * 
 *  Copyleft (C) 2015  Sun Dro (a.k.a. kala13x)
 *
 * This library includes socket operations such as create,
 * bind, connect, listen, select and etc. Use gcc.
 */


#include "stdinc.h"
#include "socks.h"
#include "errex.h"
#include "slog.h"


/* 
 * set_nonblock - Do not wait for the device or file to be ready or 
 * available. After the descryptor is  open, the read() and write() 
 * calls always return  immediately. If non-block will be ok, 1 is 
 * returned. fd is file descryptor on which we want to set non-block.
 */
int set_nonblock(int fd)
{
    /* Get flags */
    int fl = fcntl(fd, F_GETFL);
    if (fl < 0) 
    {
        slog(2, SLOG_ERROR, "fcntl F_GETFL: FD %d: %s", 
            fd, strerror(errno));

        return -1;
    }

    /* Set flags */
    fl |= O_NDELAY; //O_NONBLOCK;
    fl = fcntl(fd, F_SETFL, fl);
    if (fl < 0)
    {
        slog(2, SLOG_ERROR, "fcntl F_SETFL: FD %d: %s", 
            fd, strerror(errno));

        return 1;
    }

    return 1;
}


/*
 * send_socket_buffer - Write data in socket buffer 
 * and send with write. First argument fd is socket 
 * file descryptor, buf is buffer which we want to 
 * send and len is length of buffer.
 */
int send_socket_buffer(int fd, char *buf, int *len)
{
    int x = write(fd, buf, *len);
    if (x < 0) return x;
    if (x == 0) return x;
    if (x != *len) memmove(buf, buf+x, (*len)-x);
    *len -= x;
    return x;
}


/* 
 * set_socket_timeout - Set recieve timeout option on socket.
 * Function sets timeout on socket while useing read or recv.
 * If there is timeout read() will be skipped and errno will 
 * be set at EAGAIN. sock is socket and sec is time value.
 */
void set_socket_timeout(int sock, int sec)
{
    struct timeval sock_timeout;
    sock_timeout.tv_sec = sec; 
    sock_timeout.tv_usec = 0;

    /* Set timeout option on socket */
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, 
        (char*)&sock_timeout, sizeof(sock_timeout));
}


/* 
 * get_info_from_sockaddr - Get information from socket addres such as 
 * host name and addres. Argument addr is sockaddr_in value, len is size 
 * of struct sockaddr and inf pointer where information will be saved.
 */
int get_info_from_sockaddr(struct sockaddr_in addr, int len, char *inf)
{
    struct hostent *hostinfo;
    hostinfo = gethostbyaddr((char *) &addr.sin_addr.s_addr, len, AF_INET);

    if (!hostinfo) 
    {
        sprintf(inf, "%s", inet_ntoa(addr.sin_addr));
        return 0;
    }

    if (hostinfo && inf)
        sprintf(inf, "%s [%s]", hostinfo->h_name, inet_ntoa(addr.sin_addr));

    return 0;
}


/* 
 * open_remote_host - Function creates and returns connected 
 * socket for hosts. First argument host is address for client
 * connection and argument port is port for socket creation.
 */
int open_remote_host(char *host, int port)
{
    struct sockaddr_in rem_addr;
    struct hostent *ghst;
    int len, sock, ret, on = 1;

    /* Get host by name */
    ghst = gethostbyname(host);
    if (!ghst) return (-2);

    /* Create socket */
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) return sock;

    /* Socket options */
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &on, 4);
    len = sizeof(rem_addr);
    memset(&rem_addr, '\0', len);
    rem_addr.sin_family = AF_INET;
    memcpy(&rem_addr.sin_addr, ghst->h_addr, ghst->h_length);
    rem_addr.sin_port = htons(port);

    /* Connect to socket */
    ret = connect(sock, (struct sockaddr *) &rem_addr, len);
    if (ret < 0) 
    {
        slog(0, SLOG_ERROR, "Can not connect client socket");

        close(sock);
        return ret;
    }

    /* Check valid socket and set nonblock */
    if (sock) set_nonblock(sock);

    return sock;
}


/* 
 * create_client_socket - Function creates and returns 
 * connected client socket. If argument addr is NULL, 
 * socket will be created with INADDR_ANY flag. port 
 * argument is port for socket creation.
 */
int create_client_socket(char *addr, int16_t port)
{
    /* Used variables */
    int sock, ret;
    struct sockaddr_in name;

    /* Create the socket. */
    sock = socket (AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        slog(2, SLOG_ERROR, "Can not create client socket: %d", sock);

        return sock;
    }

    /* Give the socket a name. */
    name.sin_family = AF_INET;
    name.sin_port = htons (port);

    /* Socket address */
    if (addr != NULL) name.sin_addr.s_addr = inet_addr(addr);
    else name.sin_addr.s_addr = htonl (INADDR_ANY);

    /* Connect socket */
    ret = connect(sock, (struct sockaddr *) &name, sizeof(name));
    if (ret < 0)
    {
        slog(2, SLOG_ERROR, "Can not connect to socket: %d", sock);

        close(sock);
        return ret;
    }

    return sock;
}


/* 
 * create_server_socket - Function creates and returns 
 * binded server socket. If argument addr is NULL, 
 * socket will be created with INADDR_ANY flag. port 
 * argument is port for socket creation.
 */
int create_server_socket(char *addr, uint16_t port)
{
    /* Used variables */
    int sock, ret;
    struct sockaddr_in name;

    /* Create the socket. */
    sock = socket (PF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        slog(2, SLOG_ERROR, "Can not create server socket: %d", sock);

        return sock;
    }

    /* Socket info */
    name.sin_family = AF_INET;
    name.sin_port = htons (port);

    /* Socket address */
    if (addr != NULL) name.sin_addr.s_addr = inet_addr(addr);
    else name.sin_addr.s_addr = htonl (INADDR_ANY);

    /* Bind socket */
    ret = bind(sock, (struct sockaddr *) &name, sizeof(name));
    if (ret < 0)
    {
        close(sock);
        exit_prog(1, "Can not bind server socket");
    }

    /* Listen to socket */
    ret = listen(sock, 5);
    if (ret < 0) 
        exit_prog(1, "Can not listen to server socket");

    return sock;
}


/* 
 * create_raw_socket - Function creates and returns raw 
 * socket (Root access is required to create raw socket).
 */
int create_raw_socket()
{
    /* Create raw socket */
    int sock = socket(AF_INET , SOCK_RAW , IPPROTO_TCP);
    if (sock < 0) 
    {
        slog(2, SLOG_ERROR, "Can not create raw socket: %d", sock);
    }

    return sock;
}
