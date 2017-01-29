//
//  server.c
//  networkTest
//
//  Created by Tyler on 2017/01/27.
//  Copyright © 2017 Tyler Liu. All rights reserved.
//

#include "server.h"
#include <errno.h>
#include <string.h>

struct sockaddr_in server_server = {
    .sin_family = AF_INET,
    .sin_addr = htonl(INADDR_ANY),
    .sin_port = htons(PORT)
};

int server_sockid;
int server_client_sockid;
struct sockaddr_in * server_client;
uint32_t server_len_client_sock;


int accept_init(){
    server_sockid = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (server_sockid == -1 || bind(server_sockid, (struct sockaddr *)&server_server, sizeof(server_server)) == -1) {
        printf("error: %s(errno: %d)\n",strerror(errno),errno);
        return -1;

    }
    listen(server_sockid, 1);
    server_client_sockid = accept(server_sockid, (struct sockaddr *)server_client, &server_len_client_sock);
    return 0;
}
