#include <sys/socket.h>
#include <netinet/ip.h>

int main() {
	struct sockaddr_in servaddr;
	int sockfd;
	char buf[1024];

	sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);

	sendto(sockfd, "\x08\x00\x00\x00\x00\x00\x00\x00");
	recvfrom(sockfd, buf, 1024, MSG_PEEK, servaddr, 
}

