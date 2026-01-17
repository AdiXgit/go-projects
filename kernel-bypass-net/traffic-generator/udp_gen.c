#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int s = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_port = htons(9000),
        .sin_addr.s_addr = inet_addr("127.0.0.1")};
    char buf[64];
    memset(buf, 'A', sizeof(buf));
    while (1)
        sendto(s, buf, sizeof(buf), 0,
               (void *)&addr, sizeof(addr));
}
