//
//  server.h
//  networkTest
//
//  Created by Tyler on 2017/01/27.
//  Copyright © 2017 Tyler Liu. All rights reserved.
//

#ifndef server_h
#define server_h

#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 5181

extern struct sockaddr_in server_server;
extern int server_sockid;
extern int server_client_sockid;
extern struct sockaddr_in * server_client;
extern uint32_t server_len_client_sock;
int accept_init();

//long receive(void *ptr, int64_t len)
#define RECV(ptr,len) recv(server_client_sockid, ptr, len, 0)

//long send(void *ptr, int64_t len)
#define SEND(ptr,len) send(server_client_sockid, ptr, len, 0)

#define CLOSE() close(server_client_sockid);close(server_sockid)


#endif /* server_h */
