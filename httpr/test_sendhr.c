#include <stdio.h>
#include <string.h>
#include "sendhr.h"

int main(void){
	char uri[1024];
	char adr[128];
	strncpy(uri, "/LabMemberManager/dwr/jsonp/LmmManager/login", 1024);
	strncat(uri, "/test_lin_adr[", 1024);
	getClientAddr("eth0", adr, 128);
	strncat(uri, adr, 1024);
	strncat(uri, "]", 1024);
	send_httpr("150.89.234.234", uri, 8080, stdout);
	
	return 0;
}
