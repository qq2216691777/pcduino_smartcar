#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <termios.h>
#include <errno.h>

#include "net.h"
#include "protocol.h"
#include "pthread.h"

struct u_prot p = { HEADER_U_FLAG,0,0,0,0,0};

#define DEF_TCP_SRV_PORT 19868

char new_image = 0;

int readn(int fd, void *vptr, size_t n)
{
    size_t nleft;
    size_t nread;
    size_t read_count = 0;
    char *ptr;
    struct p_prot *rx_prot = (struct p_prot *)vptr;

//    printf("readn begain\r\n");
    ptr = (char *)vptr;
    nleft = n;

    nread = recv(fd, ptr, nleft,0);
    if( nread<0 )
    {
        perror("recv");
        return -1;
    }
    if( (HEADER_P_FLAG == rx_prot->header) &&(rx_prot->check \
            == (int)(rx_prot->header + rx_prot->status + rx_prot->len) ))
    {
        nleft = rx_prot->len - nread;
        ptr += nread;
    }
    while (nleft > 0)
    {
     //   printf("readn s %d\r\n",nread);
        nread = recv(fd, ptr, nleft,0);

        if ( nread < 0)
        {
            perror("rece");
            if (errno == EINTR)
                nread = 0;
            else
                return(-1);
        }


        read_count += nread;
        nleft -= nread;
        ptr += nread;
    }
    return(read_count);
}


void * Pthread_Net( void *arg )
{
    struct p_prot *rx_prot;
    struct sockaddr_in srv_addr;
    int sock;
    int res;
    int rnum;
    int newfd;
    char * ip_buff = (char *)arg;
    char * buff = (char *)&p;
    char * sbuff = calloc(1,200000);

    //创建套接字
    sock = socket(AF_INET,SOCK_STREAM,0);

    if( -1 == sock )
    {
        printf("create sock failed\r\n");
        now_status.net.Status = 1;
        pthread_exit(NULL);
    }

    //设置要绑定的地址
    bzero( &srv_addr, sizeof(struct sockaddr_in));

    srv_addr.sin_addr.s_addr = inet_addr(ip_buff);
    srv_addr.sin_family = AF_INET;
    srv_addr.sin_port = htons(DEF_TCP_SRV_PORT);

    //连接
    res = connect(sock,(struct sockaddr *)(&srv_addr),sizeof(struct sockaddr));

    if( -1==res)
    {
        printf("connect failed\r\n");
        now_status.net.Status = 1;
        pthread_exit(NULL);
    }
    now_status.net.Status = 3;
    while(1)
    {
        //发送数据
        p.header = HEADER_U_FLAG;
        p.go_back = now_status.speed.up - now_status.speed.down;
        p.left_right = now_status.speed.left - now_status.speed.right;
        p.Rotate = now_status.speed.lRote - now_status.speed.rRote ;
        p.status = 0;
     //   printf("go %d\r\n",p.go_back);
        p.check = (int)(p.header+p.go_back+p.left_right+p.Rotate+p.status);
        res = send( sock, buff, HEADER_U_SIZE,0);
        if( HEADER_U_SIZE==res )
        {
            //发送成功则等待接收
            rnum = readn( sock, sbuff, 200000 );
        //    printf("readn overr %d\n", rnum);
            rx_prot = (struct p_prot *)sbuff;
            if( (HEADER_P_FLAG == rx_prot->header) &&(rx_prot->check \
            == (int)(rx_prot->header + rx_prot->status + rx_prot->len) ))
            {
                //printf("recv     ok+++\n");
                if( rx_prot->status & PCDUINO_DEV)
                {
                    now_status.status.PCDuino = 1;
                    if( rx_prot->status & STM32_DEV)
                    {

                        now_status.status.Device = 1;
                        if( rx_prot->status & REMOTE_DEV)
                            now_status.status.Remote = 1;
                        else
                            now_status.status.Remote = 0;
                    }
                    else
                    {
                        now_status.status.Device = 0;           //mark
                        now_status.status.Remote = 0;
                    }
                }
                else
                {
                    now_status.status.PCDuino = 0;
                    now_status.status.Device = 0;
                    now_status.status.Remote = 0;
                }
                if( rx_prot->status & IMAGE_FLAG )
                {

                    newfd = open( "res.jpg", O_CREAT|O_RDWR ,0777);
                    write( newfd, &sbuff[HEADER_P_SIZE], rx_prot->len -HEADER_P_SIZE );
                    close(newfd);
                    //update_image( &sbuff[HEADER_P_SIZE], rx_prot->len -HEADER_P_SIZE);

                /*    printf("get a pic %d\r\n",rx_prot->len -HEADER_P_SIZE);*/
                    new_image = 1;
                }
            }
            else
                printf("read failed\r\n");
        }
        usleep(1000);
    }

//    printf("please input data:\r\n");
//    fgets(buff,128,stdin);
    //发送数据


    close(sock);


    pthread_exit(NULL);
}
