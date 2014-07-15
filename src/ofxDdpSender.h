#pragma once

#include "ofMain.h"
#include "ofxNetwork.h"


// DDP protocol header definitions
typedef unsigned char byte;
#define DDP_PORT    4048
#define MAX_DBUFLEN 1512


// DDP header format
// header is 10 bytes
struct ddp_hdr_struct {
    byte flags1;
    byte reserved1;
    byte type;
    byte device;
    byte offset1;
    byte offset2;
    byte offset3;
    byte offset4;
    byte len1;
    byte len2;
};


class ofxDdpSender
{
public:
    
    void setup( std::string _ip, bool _requirePush = false);
    void update( unsigned char * _data, int _length, int _offset = 0);
    
    void connect();
    void close();

    void push();
    void getStatus();//todo: receive status


private:

    ddp_hdr_struct* ddp_header;
    ddp_hdr_struct* ddp_header_query;
    ddp_hdr_struct* ddp_header_push;
    byte            dbuf[MAX_DBUFLEN];

    std::string     ip;
    ofxUDPManager   udpConnection;

    void setOffset(ddp_hdr_struct* _header, int _offset);
    void setLength(ddp_hdr_struct* _header, int _length);


};//class Sender

