#ifndef _PTHREAD_H__
#define _PTHREAD_H__

typedef struct {
    char IP[4];
    char Status;
}Net;

typedef struct {
    char *Image_buf;
}Image;

typedef struct {
    char PCDuino;
    char Device;
    char Remote;
    char Switch[4];
}Status;

typedef struct {
    unsigned short up;
    unsigned short down;
    unsigned short left;
    unsigned short right;
    char shift;
    char ctrl;
    int Rate;
    int lRote;
    int rRote;
}Speed;

typedef struct {
    Net net;
    Image image;
    Status status;
    Speed speed;
}APP_Status;

extern APP_Status now_status;
#endif // _PTHREAD_H__
