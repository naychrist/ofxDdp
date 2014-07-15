#include "ofxDdpSender.h"


void ofxDdpSender::setup( string _ip, bool _requirePush)
{
    ip = _ip;

    udpConnection.Create();

    // create packet header
    ddp_header = (struct ddp_hdr_struct *) &dbuf;
    _requirePush ? ddp_header->flags1 = 0x40 : ddp_header->flags1 = 0x41;       //v1 || v1 + push
    ddp_header->reserved1 = 0x00;
    ddp_header->type = 0x00;
    ddp_header->device = 0x01;

    if (_requirePush)
    {
        ddp_header_push = new ddp_hdr_struct;
        ddp_header_push->flags1 = 0x41;       //v1 + push
        ddp_header_push->reserved1 = 0x00;
        ddp_header_push->type = 0x00;
        ddp_header_push->device = 0x01;
        setLength(ddp_header_push, 0);
        setOffset(ddp_header_push, 0);
    }

}


void ofxDdpSender::update( unsigned char * _data, int _length, int _offset)
{
    if (ddp_header_query)//should receive
    {
        //todo: implement and test
        char udpMessage[100000];
        udpConnection.Receive(udpMessage,100000);
        string message=udpMessage;
        if(message!=""){
            cout<<"Receive bytes: "<<message.length()<<endl;
        }
    }
    
    setLength(ddp_header, _length);
    setOffset(ddp_header, _offset);

    //send packet
    memcpy(&dbuf[0]+10,_data,_length);
    udpConnection.Send((const char*) &dbuf[0],10+_length);

}

void ofxDdpSender::connect()
{
    udpConnection.Connect(ip.c_str(),DDP_PORT);
    if (ddp_header_push) udpConnection.SetEnableBroadcast(true);
    udpConnection.SetNonBlocking(true);
}

void ofxDdpSender::close()
{
    udpConnection.Close();
}

void ofxDdpSender::push()
{
    if (ddp_header_push)
    {
        udpConnection.Send((const char*) &ddp_header_push[0],10);
    }
    else
    {
        cout << "Error: DDP not set up to require push!" <<endl;
    }

}

void ofxDdpSender::getStatus()
{

    if (!ddp_header_query)
    {
        ddp_header_query = new ddp_hdr_struct;
        ddp_header_query->flags1 = 0x43;       //v1 + push + query
        ddp_header_query->reserved1 = 0x00;
        ddp_header_query->type = 0x00;
        ddp_header_query->device = 251; //read status
        setLength(ddp_header_push, 0);
        setOffset(ddp_header_push, 0);
    }
    
    udpConnection.Send((const char*) &ddp_header_query[0],10);

}

void ofxDdpSender::setOffset(ddp_hdr_struct* _header, int _offset)
{
    _header->offset1 = (_offset >> 24) & 0xff;
    _header->offset2 = (_offset >> 16) & 0xff;
    _header->offset3 = (_offset >> 8) & 0xff;
    _header->offset4 = _offset & 0xff;
}

void ofxDdpSender::setLength(ddp_hdr_struct* _header, int _length)
{
    if (_length > 1440) {
        _length = 1440;
        cout << "Error: shortened DDP packet data length!" << endl;
    }
    _header->len1 = (_length >> 8) & 0xff;
    _header->len2 = _length & 0xff;
}
