#include "handle.h"
#include <cJSON.h>

void analysis_data(char rec_data[])
{
	cJSON_Hooks memoryHook;
	memoryHook.malloc_fn = malloc;
	memoryHook.free_fn = free;
	cJSON_InitHooks(&memoryHook);

	cJSON *IOTJSObject = NULL, *typeJSObject = NULL, *valueJSObject = NULL;
        
	if(NULL != (IOTJSObject = cJSON_Parse(rec_data)))
	{
		typeJSObject = cJSON_GetObjectItem(IOTJSObject, "type");
		valueJSObject = cJSON_GetObjectItem(IOTJSObject, "value");

		if(0 == strcmp(typeJSObject->valuestring,"set_value"))
		{
			control_motor(valueJSObject->valuestring);
		}
	}
	
	cJSON_Delete(IOTJSObject);
}


void handle()
{
	struct sockaddr_in  clent_addr, localaddr;
	int addr_size, socket, status, new_socket, n = 1, recv_cnt;
	char recv_data[GENERAL_SIZE] = {0};

	addr_size=sizeof(clent_addr);
	socket = socket(AF_INET, SOCK_STREAM, 0);

	setsockopt( socket, SOL_SOCKET, SO_REUSEADDR,(const char *) &n, sizeof( n ) );

	memset((char *)&localaddr, 0, sizeof(localaddr));
	localaddr.sin_family      = AF_INET;
	localaddr.sin_len         = sizeof(localaddr);
	localaddr.sin_port        = htons(5001);
	localaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	status = bind(socket, (struct sockaddr *)&localaddr, sizeof(localaddr));
	status = listen(socket, 20);

	while(1)
	{
		new_socket = accept(socket, ( struct sockaddr *)&clent_addr, (socklen_t*)&addr_size);
		if( new_socket < 0 )
		{
			printf("accept failed\n");
			close(new_socket);
			continue;
		}

		while(1)
		{
			recv_cnt = recv(new_socket, recv_data, sizeof(recv_data), 0);
			if (recv_cnt <= 0)
			{
				printf("recv failed\n");
				close(new_socket);
				break;
			}
			printf("recv_data = %s\n", recv_data);
			analysis_data(recv_data);
			memset(recv_data, 0, sizeof(recv_data));
		}
	}	
}
