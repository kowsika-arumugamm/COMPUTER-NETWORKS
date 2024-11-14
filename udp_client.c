#include<stdio.h>
#include<winsock2.h>    // For Winsock API
#include<ws2tcpip.h>    // For inet_pton and other functions

#pragma comment(lib,"ws2_32.lib")   // Link Winsock library

void func(SOCKET sockfd, struct sockaddr_in servaddr);

int main() {
    WSADATA wsa;
    SOCKET sockfd;
    struct sockaddr_in servaddr;

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        printf("WSAStartup failed. Error Code: %d\n", WSAGetLastError());
        return 1;
    }

    printf("Winsock initialized.\n");

    // Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == INVALID_SOCKET) {
        printf("Socket creation failed. Error Code: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    printf("\nSocket created.\n");

    // Server address
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(43451);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Perform calculation
    func(sockfd, servaddr);

    // Cleanup
    closesocket(sockfd);
    WSACleanup();

    return 0;
}

void func(SOCKET sockfd, struct sockaddr_in servaddr) {
    int msg;
    int server_len = sizeof(servaddr);

    // Input Principal (P)
    printf("\nEnter the value for principal (P): ");
    scanf("%d", &msg);
    sendto(sockfd, (char*)&msg, sizeof(msg), 0, (struct sockaddr*)&servaddr, server_len);

    // Input Rate of Interest (R)
    printf("\nEnter the value for rate of interest (R): ");
    scanf("%d", &msg);
    sendto(sockfd, (char*)&msg, sizeof(msg), 0, (struct sockaddr*)&servaddr, server_len);

    // Input Number of Years (N)
    printf("\nEnter the value for number of years (N): ");
    scanf("%d", &msg);
    sendto(sockfd, (char*)&msg, sizeof(msg), 0, (struct sockaddr*)&servaddr, server_len);

    // Receive and print Compound Interest
    printf("\nCompound Interest is: ");
    recvfrom(sockfd, (char*)&msg, sizeof(msg), 0, (struct sockaddr*)&servaddr, &server_len);
    printf("%d\n", msg);
}
