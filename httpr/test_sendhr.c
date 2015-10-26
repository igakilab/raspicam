#include <stdio.h>
#include "sendhr.h"

int main(void){
	send_httpr("150.89.234.234", "/LabMemberManager/dwr/jsonp/LmmManager/login/test_lin", 8080, stdout);
	return 0;
}
