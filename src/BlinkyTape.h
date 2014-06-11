//
//  BlinkyTape.h
//  BlinkyTapeExample
//
//  Created by James Kong on 10/6/14.
//
//

#ifndef __BlinkyTapeExample__BlinkyTape__
#define __BlinkyTapeExample__BlinkyTape__
#include "ofMain.h"
#include <iostream>     // std::cout
class BlinkyTape
{
public:
    BlinkyTape(string portName, int numberOfLEDs);
    
    bool isConnected();
    
    // Attempt to close the serial port gracefully, so we don't leave it hanging
    void close();
    
    string getPortName();
    
    void resetTape();
    
    void render(float x1, float y1, float x2, float y2);
    
    // Update the blinkyboard with new colors
    void render(ofColor c, float x1, float y1, float x2, float y2);
    void send();
    int m_currentChunkPos;
    
    void startSend();
    
    // returns false if done
    bool sendNextChunk();
    
    // Some very simple routines for sending single pixels.
    void pushPixel(ofColor c);
    int getindex();
    void setIndex(int i);
    
    // finalize - for use with pushPixel
    void update();
private:
    string m_portName;  // TODO: How to request cu.* devices?
    ofSerial m_outPort;
    
    int m_numberOfLEDs;
    
    bool m_enableGammaCorrection;
    float m_gammaValue;
    
    vector<uint8_t> m_data;
    int m_dataIndex;
};
#endif /* defined(__BlinkyTapeExample__BlinkyTape__) */
