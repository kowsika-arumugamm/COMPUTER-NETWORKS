#include<stdio.h>
#include<winsock2.h>    // For Winsock API
#include<ws2tcpip.h>    // For inet_pton and other functions
#include<math.h>        // For power function

#pragma comment(lib,"ws2_32.lib")   // Link Winsock library

void func(SOCKET sockfd, struct sockaddr_in *cliaddr, int len);

int main() {
    WSADATA wsa;
    SOCKET sockfd;
    struct sockaddr_in servaddr, cliaddr;
    int len = sizeof(cliaddr);

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        printf("Winsock initialization failed. Error Code: %d\n", WSAGetLastError());
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

    // Prepare the sockaddr_in structure
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(43451);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Bind
    if (bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == SOCKET_ERROR) {
        printf("\nBind failed. Error Code: %d\n", WSAGetLastError());
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    printf("\nBind successfully.\n");

    // Process the client request
    func(sockfd, &cliaddr, len);

    // Cleanup
    closesocket(sockfd);
    WSACleanup();

    return 0;
}

void func(SOCKET sockfd, struct sockaddr_in *cliaddr, int len) {
    int p, r, n, ci;
    int client_len = sizeof(*cliaddr);

    // Receive value for principal (P)
    recvfrom(sockfd, (char*)&p, sizeof(p), 0, (struct sockaddr*)cliaddr, &client_len);
    printf("Received P = %d\n", p);

    // Receive value for rate of interest (R)
    recvfrom(sockfd, (char*)&r, sizeof(r), 0, (struct sockaddr*)cliaddr, &client_len);
    printf("Received R = %d\n", r);

    // Receive value for number of years (N)
    recvfrom(sockfd, (char*)&n, sizeof(n), 0, (struct sockaddr*)cliaddr, &client_len);
    printf("Received N = %d\n", n);

    // Calculate compound interest
    double amount = p * pow((1 + (double)r/100), n); 
    ci = (int)(amount - p);

    printf("The compound interest is: %d\n", ci);

    // Send the result back to the client
    sendto(sockfd, (char*)&ci, sizeof(ci), 0, (struct sockaddr*)cliaddr, client_len);
}
 