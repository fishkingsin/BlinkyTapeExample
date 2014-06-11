//
//  BlinkyTape.cpp
//  BlinkyTapeExample
//
//  Created by James Kong on 10/6/14.
//
//

#include "BlinkyTape.h"
BlinkyTape::BlinkyTape(string portName, int numberOfLEDs) {

    m_data.reserve(numberOfLEDs * 3 + 1);
    m_portName = portName;
    m_numberOfLEDs = numberOfLEDs;
    
    m_enableGammaCorrection = true;
    m_gammaValue = 1.8;
    
    ofLogVerbose() << "Connecting to BlinkyTape on: " << portName;

    m_outPort.setup( portName, 115200);

    
    for (int i=0; i < numberOfLEDs; i++) {
        m_data[i] = 0;
    }
}

bool BlinkyTape::isConnected() {
    return(m_outPort.isInitialized());
}

// Attempt to close the serial port gracefully, so we don't leave it hanging
void BlinkyTape::close() {
//    if(isConnected()) {
//        try {
//            m_outPort.stop();
//        }
//        catch (Exception e) {
//            println("LedOutput: Exception while closing: " + e);
//        }
//    }
    
    m_outPort.close();
}

string BlinkyTape::getPortName() {
    return m_portName;
}

void BlinkyTape::resetTape() {
    m_outPort.close();
    ofSerial s;
    s.setup( m_portName, 1200);  // Magic reset baudrate
//    delay(100);
    s.close();
}

void BlinkyTape::render(float x1, float y1, float x2, float y2) {
//    render( x1, y1, x2, y2);
}

// Update the blinkyboard with new colors
void BlinkyTape::render(ofColor c, float x1, float y1, float x2, float y2) {
/*    m_outPort.close();
    
    image.loadPixels();
    */
    // Note: this should be sized appropriately
    vector<u_int8_t> data ;//= new vector<u_int8_t>;//new u_int8_t[m_numberOfLEDs*3 + 1];
//    data.reserve(m_numberOfLEDs*3 + 1);
    int dataIndex = 0;
    
    // data is R,G,B
    for(int i = 0; i < m_numberOfLEDs; i++) {
        // Sample a point along the line
        int x = (int)((x2 - x1)/m_numberOfLEDs*i + x1);
        int y = (int)((y2 - y1)/m_numberOfLEDs*i + y1);
        
        int r = c.r ;//int(red(image.pixels[y*image.width+x]));
        int g = c.g ;//int(green(image.pixels[y*image.width+x]));
        int b = c.b ;//int(blue(image.pixels[y*image.width+x]));
        
        if (m_enableGammaCorrection) {
            r = (int)(powf(r/256.0,m_gammaValue)*256);
            g = (int)(powf(g/256.0,m_gammaValue)*256);
            b = (int)(powf(b/256.0,m_gammaValue)*256);
        }
        
//        data[dataIndex++]
        data.push_back( (u_int8_t)min(254, r));
//        data[dataIndex++] = (u_int8_t)min(254, g);
//        data[dataIndex++] = (u_int8_t)min(254, b);
        data.push_back((u_int8_t)min(254, g));
        data.push_back((u_int8_t)min(254, b));
    }
    
    // Add a 0xFF at the end, to signal the tape to display
    data[dataIndex] = (u_int8_t)255;
    
    m_dataIndex = dataIndex;
    m_data = data;
//    memcpy(&m_data, data.data(), m_data.size());
}

void BlinkyTape::send() {
    startSend();
    while(sendNextChunk()) {
//        sleep(1);
    };
}

int m_currentChunkPos;

void BlinkyTape::startSend() {
    m_currentChunkPos = 0;
}

// returns false if done
bool BlinkyTape::sendNextChunk() {
    // Don't send data too fast, the arduino can't handle it.
    int maxChunkSize = 63;

    if( m_currentChunkPos >= m_numberOfLEDs*3 + 1) {
        return false;
    }

    int currentChunkSize = min(maxChunkSize, m_numberOfLEDs*3 + 1 - m_currentChunkPos);
    u_int8_t* test = new u_int8_t[currentChunkSize];

    for(int i = 0; i < currentChunkSize; i++) {
        test[i] = m_data[m_currentChunkPos + i];
    }
    
    m_outPort.writeBytes(test,currentChunkSize);
    m_outPort.flush();
    m_currentChunkPos += maxChunkSize;
    return true;
}

// Some very simple routines for sending single pixels.
void BlinkyTape::pushPixel(ofColor c) {
    m_data[m_dataIndex++] = (u_int8_t)fmin(254, c.r);
    m_data[m_dataIndex++] = (u_int8_t)fmin(254, c.g);
    m_data[m_dataIndex++] = (u_int8_t)fmin(254, c.b);
}

int BlinkyTape::getindex() {
    return m_dataIndex;
}
void BlinkyTape::setIndex(int i) {
    m_dataIndex = i;
}

// finalize - for use with pushPixel
void BlinkyTape::update() {
    if( m_data[m_dataIndex] != (u_int8_t)255) {
        m_data[m_dataIndex++] = (u_int8_t)255;
    }
    send();
    m_dataIndex = 0;
}