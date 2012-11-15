/* EECS 541 - Drone Takeoff Program
 * Paul Bennett, Ty Hayden, Rebekah Patterson
 *
 * Proof of concept for sending AT commands to drone from program run on the drone's ARM processor
 *
 * Modified version of the code used by:
 * http://taghof.github.com/Navigation-for-Robots-with-WIFI-and-CV/blog/2012/01/23/UDPing-ATcommands-from-inside-the-drone/
 * Must be compiled with toolchain listed on website above
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 5556 //port that listens for AT commands

char takeoff[21] = "AT*REF=101,290718208\r";
char land[21] = "AT*REF=102,290717696\r";
//char throttle[21] =
int main () 
{
	struct sockaddr_in receiver_addr;
	int sock_fd;
	char key = 't';
	//command tells drone to take off
	sock_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	receiver_addr.sin_family = AF_INET;
	if( inet_aton( "192.168.1.1",  &receiver_addr.sin_addr )== 0) {
		printf("Couldn't establish connection\n");
		close(sock_fd);
		return;
	}
	receiver_addr.sin_port = htons( PORT );
	while(key!='q'){
		if(key == 't')
			sendto(sock_fd, takeoff, 21, 0,(struct sockaddr*)&receiver_addr,sizeof(receiver_addr));
		if (key == 'l')
			sendto(sock_fd, land, 21, 0,(struct sockaddr*)&receiver_addr,sizeof(receiver_addr));
		fgets (key, 1, stdin);
	}
	
	close(sock_fd);
	
	//printf("Takeoff message successfully sent to client\n");
	/*int i = 0;
	int j = 1;
	while(j)
	{
		i = i + 1;
		printf(i + " ");
	}		*/
}
