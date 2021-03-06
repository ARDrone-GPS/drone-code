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

/* potentially useful commands
void droneTakeOff(void) {
// Take off
snprintf(droneBuf, MAX_COMMAND_LEN,"AT*REF=%u,290718208",droneSeq);
//droneSeq is the sequence number and should be incremented each time
}
void droneLand(void) {
// Land the drone
snprintf(droneBuf, MAX_COMMAND_LEN,"AT*REF=%u,290717696",droneSeq);
}
void droneMove(void) {
// Have the drone hover
snprintf(droneBuf, MAX_COMMAND_LEN,"AT*PCMD=%u,1,%d,%d,%d,%d",droneSeq,pitch,roll,gaz,yaw);
}
void droneHover(void) {
// Have the drone hover
snprintf(droneBuf, MAX_COMMAND_LEN,"AT*PCMD=%u,1,0,0,0,0", droneSeq);
}
void droneUp(void) {
// Move drone up, same as gaze
snprintf(droneBuf, MAX_COMMAND_LEN,"AT*PCMD=%u,1,0,0,1045220557,0" , 
droneSeq);
}
void droneDown(void) {
// Move drone down
snprintf(droneBuf, MAX_COMMAND_LEN, "AT*PCMD=%u,1,0,0,N1102263091,0", 
droneSeq);
}
void droneForward(void) {
// Move drone forward, same as pitch nprintf(droneBuf, MAX_COMMAND_LEN, "AT*PCMD=%u,1,0,N1102263091,0,0", 
droneSeq);
}
void droneBack(void) {
// Move drone back
snprintf(droneBuf, MAX_COMMAND_LEN, "AT*PCMD=%u,1,0,1045220557,0,0",droneSeq);
}
void droneLeft(void) {
// Move drone left, same as roll
snprintf(droneBuf, MAX_COMMAND_LEN, "AT*PCMD=%u,1,N1102263091,0,0,0", 
droneSeq);
}
void droneRight(void) {
// Move drone right
snprintf(droneBuf, MAX_COMMAND_LEN, "AT*PCMD=%u,1,1045220557,0,0,0", 
droneSeq);
}
void droneRotateLeft(void) {
// Rotate drone left, same as yaw
snprintf(droneBuf, MAX_COMMAND_LEN, "AT*PCMD=%u,1,0,0,0,N1085485875", 
droneSeq);
}
void droneRotateRight(void) {
// Rotate drone right
snprintf(droneBuf, MAX_COMMAND_LEN, "AT*PCMD=%u,1,0,0,0,1061997773", 
droneSeq);
}
*/

/*
emergency!reset:!AT*REF=<sequence>,290717952
set!max!altitude!(3!meter):!!AT*CONFIG=1,\"control:altitude_max\",\"3000\"
set!flat!trim:!AT*FTRIM=<sequence>
reset!watchdog!bit:!AT*COMWDG=<sequence>
*/

int main () 
{	
	struct sockaddr_in receiver_addr;
	int sock_fd;

	//command tells drone to take off
	char takeoff[21] = "AT*REF=%u,290718208";
	char land[21] = "AT*REF=%u,290717696";
	sock_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	receiver_addr.sin_family = AF_INET;
	if( inet_aton( "127.0.0.1",  &receiver_addr.sin_addr )== 0) {
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
}
