#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main()
{

	int sockfd;
	int len;
	struct sockaddr_in address;
	int result;
	unsigned int int_buff;
	char buff[128];
	unsigned int readsTotal = 0;
	
	sockfd = socket(PF_INET, SOCK_STREAM, 0);
	
	address.sin_family = AF_INET;
	address.sin_port = htons(5842);
	address.sin_addr.s_addr = inet_addr("176.9.9.172");
	
	len = sizeof(address);
	
	result = connect(sockfd, (struct sockaddr *)&address, len);
	
	if (result == -1)
	{
		perror("Opps: Client\n");
		exit(1);
	}
	else 
		printf("Connection successfull!\n");
	
	for (int i = 0; i < 4; i++)
	{
		result = read(sockfd, &int_buff,4);
		//int_buff = (unsigned)ntohl(int_buff);
		printf("Read %d bytes: %d\n", result, int_buff);
		
		readsTotal += int_buff;
		int_buff = 0;
	}
	
	result = 0;
	
	printf("Sending total of %d back to server\n", readsTotal);
	//readsTotal = htonl(readsTotal);
	write(sockfd, &readsTotal, 4);
	
	printf("Attempting to get user/pass from server\n");
	result = read(sockfd, buff, sizeof(buff));
	buff[result] = '\0';
	printf("Read %d bytes: %s\n", result, buff);

}
