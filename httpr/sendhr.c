/*
 * Copyright (C) 2006-2008 Slogical Corporation. All Rights Reserved.
 */

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "sendhr.h"

#include <errno.h>
#include <linux/if.h>
#include <sys/ioctl.h>

static int sofd;
static struct hostent     *shost;
static struct sockaddr_in sv_addr;

int send_httpr(
	char *target_host, 
	char *target_uri, 
	int target_portno,
	FILE *out
) {

//    char *target_host;
//    char target_uri[1024 +1];
//    int  target_portno;

    char http_res[1024];

    /* target_uri の設定 */
    if (strncmp(target_uri, "/", 1) != 0) {
        fprintf(stderr, "URI of request must be started with '/'\n");
        return -1;
    }
    if (strlen(target_uri) >= 1024) {
        fprintf(stderr, "URI of request must be under 1024bytes\n");
        return -1;
    }


    /* target_portno の設定 */
    if (target_portno < 0 || target_portno > 65536) {
        fprintf(stderr, "PORT_NO of httpd server is invalid\n");
        return -1;
    }

    /* ソケットを作成 */
    sofd = socket(AF_INET, SOCK_STREAM, 0);
    if (sofd < 0) {
        fprintf(stderr, "can not open SOCKET.\n");
        return 1;
    }

    /* アドレスを定義 */
    shost = gethostbyname(target_host);
    if (shost == NULL) {
        fprintf(stderr, "err happend in gethostbyname function.\n");
        return 1;
    }

    memset(&sv_addr, '\0', sizeof(sv_addr));
    sv_addr.sin_family = AF_INET;
    sv_addr.sin_port   = htons(target_portno);
    memcpy((char *)&sv_addr.sin_addr, (char *)shost->h_addr, shost->h_length);

    /* コネクトする */
    if (connect(sofd, (const struct sockaddr*)&sv_addr, sizeof(sv_addr)) < 0) {
        fprintf(stderr, "err happend in connect function.\n");
        return 1;
    }

    /* HTTPのやりとり */
    send(sofd, "GET ",      strlen("GET "),      0);
    send(sofd, target_uri,  strlen(target_uri),  0);
    send(sofd, " HTTP/1.0", strlen(" HTTP/1.0"), 0);
    send(sofd, "\r\n",      strlen("\r\n"),      0);
    send(sofd, "Host: ",    strlen("Host: "),    0);
    send(sofd, target_host, strlen(target_host), 0);
    send(sofd, "\r\n",      strlen("\r\n"),      0);
    send(sofd, "\r\n",      strlen("\r\n"),      0);

    while (recv(sofd, http_res, sizeof(http_res), 0)) {
    	if( out != NULL ){
        	fprintf(out, "%s",http_res);
        }
        memset(&http_res, '\0', sizeof(http_res));
    }

    /* クローズする */
    close(sofd);

    return 1;
}

void getClientAddr(char *device_name, char *dest, int dlen){
	
    int s = socket(AF_INET, SOCK_STREAM, 0);
 
    struct ifreq ifr;
    ifr.ifr_addr.sa_family = AF_INET;
    strcpy(ifr.ifr_name, device_name);
    ioctl(s, SIOCGIFADDR, &ifr);
    close(s);
 
    struct sockaddr_in addr;
    memcpy( &addr, &ifr.ifr_ifru.ifru_addr, sizeof(struct sockaddr_in) );
    strncpy(dest, inet_ntoa(addr.sin_addr), dlen);
}

void send_imgFileName(char *file_name){

	char uri[1024];
	char client_addr[128];

	char method_name[] = "/addimg";

	strncpy(uri, SIMGLINK_URI_HEAD, 1024);
	strncat(uri, method_name, 1024);
	getClientAddr(CLIENT_NETWORK_DEVICE, client_addr, 128);
	strncat(uri, "/", 1024);
	strncat(uri, client_addr, 128);
	strncat(uri, "/", 1024);
	strncat(uri, file_name, 1024);

	send_httpr(SIMGLINK_HOST, uri, SIMGLINK_PORTNO, stdout);
}
