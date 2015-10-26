#define SIMGLINK_URI_HEAD "/LabMemberManager/dwr/jsonp/FaceCollector"
#define SIMGLINK_HOST "150.89.234.234"
#define SIMGLINK_PORTNO 8080 

#define CLIENT_NETWORK_DEVICE "eth0"


int send_httpr(
	char *target_host, 
	char *target_uri, 
	int target_portno,
	FILE *out
);

int send_imgFileName(char *file_name);
int getClientAddr(char *client_network_device, char *dest, int dlen);
