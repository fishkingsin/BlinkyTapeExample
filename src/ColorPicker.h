//
//  ColorPicker.h
//  BlinkyTapeExample
//
//  Created by James Kong on 10/6/14.
//
//

#ifndef __BlinkyTapeExample__ColorPicker__
#define __BlinkyTapeExample__ColorPicker__
#include "ofMain.h"
#include <iostream>
// http://www.julapy.com/processing/ColorPicker.pde
 class ColorPicker
{
public:
    int x, y, w, h, c;
    ofImage cpImage;
    
    ColorPicker ( int x, int y, int w, int h, int c )
    {
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
        this->c = c;
        
        cpImage.allocate(w,h,OF_IMAGE_COLOR);
        
        init();
    }
    
    void init ()
    {
        // draw color.
        int cw = w - 10;
        for( int i=0; i<cw; i++ )
        {
            float nColorPercent = i / (float)cw;
            float rad = (-360 * nColorPercent) * (PI / 180);
            int nR = (int)(cosf(rad) * 127 + 128) << 16;
            int nG = (int)(cosf(rad + 2 * PI / 3) * 127 + 128) << 8;
            int nB = (int)(cosf(rad + 4 * PI / 3) * 127 + 128);
            int nColor = nR | nG | nB;
            
            setGradient( i, 0, 1, h/2, 0xFFFFFF, nColor );
            setGradient( i, (h/2), 1, h/2, nColor, 0x000000 );
        }
        
        // draw black/white.
        drawRect( cw, 0,   5, h/2, 0xFFFFFF );
        drawRect( cw, h/2, 5, h/2, 0 );
        
        // draw grey scale.
        for( int j=0; j<h; j++ )
        {
            int g = 255 - (int)(j/(float)(h-1) * 255 );
            drawRect( w-5, j, 5, 1, ofColor( g, g, g ) );
        }
    }
    
    void setGradient(int x, int y, float w, float h, ofColor c1, ofColor c2 )
    {
        float deltaR = c2.r - c1.r;
        float deltaG = c2.g - c1.g;
        float deltaB = c2.g - c1.b;
        
        for (int j = y; j<(y+h); j++)
        {
            ofColor c ( c1.r+(j-y)*(deltaR/h), c1.g+(j-y)*(deltaG/h), c1.g+(j-y)*(deltaB/h) );
            cpImage.setColor( x, j, c );
        }
    }
    
    void drawRect( int rx, int ry, int rw, int rh, ofColor rc )
    {
        for(int i=rx; i<rx+rw; i++)
        {
            for(int j=ry; j<ry+rh; j++)
            {
                cpImage.setColor( i, j, rc );
            }
        }
    }
    
    void render ()
    {
        cpImage.draw(x,y);
//        image( cpImage, x, y );
//        if( mousePressed &&
//           mouseX >= x && 
//           mouseX < x + w &&
//           mouseY >= y &&
//           mouseY < y + h )
//        {
//            c = get( mouseX, mouseY );
//        }
        ofSetColor( c );
        ofRect( x, y+h+10, w, 20 );
    }
};
#endif /* defined(__BlinkyTapeExample__ColorPicker__) */
