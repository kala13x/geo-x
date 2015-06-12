/*
 *  utils/socks.c
 * 
 *  Copyleft (C) 2015  Sun Dro (a.k.a. kala13x)
 *
 * This library includes socket operations such as create,
 * bind, connect, listen, select and etc. Use gcc.
 */


/* For include header in CPP code */
#ifdef __cplusplus
extern "C" {
#endif


/*
 * set_nonblock - Do not wait for the device or file to be ready or 
 * available. After the descryptor is  open, the read() and write() 
 * calls always return  immediately. If non-block will be ok, 1 is 
 * returned. fd is file descryptor on which we want to set non-block.
 */
int set_nonblock(int fd);


/*
 * send_socket_buffer - Write data in socket buffer 
 * and send with write. First argument fd is socket 
 * file descryptor, buf is buffer which we want to 
 * send and len is length of buffer.
 */
int send_socket_buffer(int fd, char *buf, int *len);


/* 
 * set_socket_timeout - Set recieve timeout option on socket.
 * Function sets timeout on socket while useing read or recv.
 * If there is timeout read() will be skipped and errno will 
 * be set at EAGAIN. sock is socket and sec is time value.
 */
void set_socket_timeout(int sock, int sec);


/* 
 * get_info_from_sockaddr - Get information from socket addres such as 
 * host name and addres. Argument addr is sockaddr_in value, len is size 
 * of struct sockaddr and inf pointer where information will be saved.
 */
int get_info_from_sockaddr(struct sockaddr_in addr, int len, char *inf);


/* 
 * open_remote_host - Function creates and returns connected 
 * socket for hosts. First argument host is address for client
 * connection and argument port is port for socket creation.
 */
int open_remote_host(char *host, int port);


/* 
 * create_client_socket - Function creates and returns 
 * connected client socket. If argument addr is NULL, 
 * socket will be created with INADDR_ANY flag. port 
 * argument is port for socket creation.
 */
int create_client_socket(char *addr, int16_t port);


/* 
 * create_server_socket - Function creates and returns 
 * binded server socket. If argument addr is NULL, 
 * socket will be created with INADDR_ANY flag. port 
 * argument is port for socket creation.
 */
int create_server_socket(char *addr, uint16_t port);


/* 
 * create_raw_socket - Function creates and returns raw socket.
 */
int create_raw_socket();


/* For include header in CPP code */
#ifdef __cplusplus
}
#endif