/*
    Simple udp client
*/
#include<stdio.h> 				//printf
#include<string.h> 				//memset
#include<stdlib.h> 				//exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>

#define SERVER "127.0.0.1"
#define BUFLEN 64  				//Max length of buffer
#define PORT 666    			//The port on which to send data

void die(char *s)
{
    perror(s);
    exit(1);
}


int main(int argc, char **argv)
{

    struct sockaddr_in si_other;
    int s, slen=sizeof(si_other);
    char buf[BUFLEN];
    char message[BUFLEN];

    //Tworzenie gniazda
    if ( (s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        die("socket");
    }

    memset((char *) &si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(PORT);

    if (inet_aton(SERVER , &si_other.sin_addr) == 0)			//inte_aton konwertuje adres IP na binerne dane i laduje do struktury in_adr
    {
        fprintf(stderr, "inet_aton() failed\n");
        exit(1);
    }

    //send the message
    if (sendto(s, message, strlen(message) , 0 , (struct sockaddr *) &si_other, slen)==-1)
    {
        die("sendto()");
    }

    printf("\n\rWait for server...");

    //receive a reply and print it
    //clear the buffer by filling null, it might have previously received data
    memset(buf,'\0', BUFLEN);

    //try to receive some data, this is a blocking call
    if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen) == -1)
    {
        die("recvfrom()");
    }


    close(s);
    return 0;
}
