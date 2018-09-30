//#include <Arduino.h>

#include <stdio.h>
#include <memory.h>
#include <stdarg.h>


#include "SdffParser.h"


namespace sdff {


unsigned short Stream::getUint16(bool littleendian){
    unsigned short ret = 0;
    unsigned short size = getSize();
    unsigned short pos = getPosition();

    unsigned char first;
    unsigned char second;

    if ( (pos+1) < size){
        first = getUint8();
        second = getUint8();

        if (littleendian){
            ret = second;
            ret <<= 8;
            ret |= first;
        }
        else {
            ret = first;
            ret <<= 8;
            ret |= second;
        }
    }
    else {
        //todo throw
    }

    return ret;
}

unsigned char ByteStream::getUint8(){
    unsigned char ret;
    unsigned short pos = getPosition();
    unsigned short size = getSize();

    if (pos < size){
        ret = bytes[pos];
        setPosition(pos+1);
    }

    return ret;
}



SagarDisplayBox::SagarDisplayBox(unsigned char version, unsigned short flags, unsigned short width, unsigned short height)
    :Box("disp", 2+4+2+1+1+(4*width), version, flags)
    ,width(width)
    ,height(height)
    ,data(NULL)
{
    data = new unsigned long int[width];
    for (int idx = 0; idx != width; ++idx){
        data[idx] = 0;
    }
}

void SagarDisplayBox::addData(unsigned char column, unsigned char offset, unsigned char colbyte){
    if ( (column < width) && (offset < 4) ){
        data[column] |= (colbyte<<((3-offset)*8));
    }
}

SagarDisplayBox::~SagarDisplayBox(){
    delete [] data;
}

unsigned long int const *SagarDisplayBox::getColumn(unsigned short columnIndex){
    if (columnIndex < width){
        return &data[columnIndex];
    }

    return NULL;
}

BoxParser::BoxParser(unsigned short supports, const char *type, ...)
    :supportedCount(supports)
    ,supported(NULL)
{
    va_list args;
    supported = new char *[supports];
    supported[0] = new char[1+strlen(type)];
    strcpy(supported[0], type);

    if (supportedCount >  1){
        va_start(args, type);

        for (int idx=1; idx != supportedCount; ++idx){
            const char *type;

            type = va_arg(args, char *);

            supported[idx] = new char[1+strlen(type)];
            strcpy(supported[idx], type);
        }

        va_end(args);
    }
}

bool BoxParser::canParse(const char *type){
    bool ret = false;
    if (NULL != supported){
        for (int idx=0; idx != supportedCount; ++idx){
            if (0 == strncmp(type, supported[idx], 4)){
                ret = true;
                break;
            }
        }
    }

    return ret;
}

Box *ScriptActionBoxParser::parse(unsigned short size, char *type, unsigned char version, unsigned short flags, Stream *stream){
    Box *ret = NULL;

    if (0 == strncmp("spos", type, 4)){
        if (0 == version){
            unsigned short pos = stream->getUint16();

            ret = new PositionScriptActionBox(pos);
        }
    }
    else if (0 == strncmp("spau", type, 4)){
        if (0 == version){
            unsigned short duration = stream->getUint16();
            ret = new PauseScriptActionBox(duration);
        }
    }
    else if (0 == strncmp("sscr", type, 4)){
        if (0 == version){
            short step = stream->getUint16();
            unsigned short delay = stream->getUint16();
            unsigned char count = stream->getUint8();

            ret = new ScrollScriptActionBox(step, delay, count); 
        }
    }

    return ret;
}

Box *ScriptBoxParser::parse(unsigned short size, char *type, unsigned char version, unsigned short flags, Stream *stream){
    Box *ret = new ScriptBox(version, flags);

    return ret;
}

Box *SagarDisplayBoxParser::parse(unsigned short size, char *type, unsigned char version, unsigned short flags, Stream *stream){
    SagarDisplayBox *ret = NULL;

    if (1 == version){
        unsigned char width = stream->getUint8();
        unsigned char height = stream->getUint8();

        ret = new SagarDisplayBox(version, flags, width, height);

        for (int w = 0; w != width; ++w){
            for (int h = 0; h != 4; ++h){
                unsigned long int val = stream->getUint8();
                printf("%ix%i (%i) - %04lx\n", w, h, w*4+h, val);
                ret->addData(w, h, val);
            }
        }
    }


    return ret;
}

SdffParser::SdffParser()
    :handler(NULL)
{
    parserCount = 3;
    parsers = new BoxParser*[parserCount];
    parsers[0] = new ScriptActionBoxParser();
    parsers[1] = new ScriptBoxParser();
    parsers[2] = new SagarDisplayBoxParser();

}

SdffParser::~SdffParser(){
    for (int idx=0; idx != parserCount; ++idx){
        delete parsers[idx];
    }

    delete [] parsers;
}

void SdffParser::parse(Stream *stream){
    char boxType[4];
    unsigned short int boxSize;
    unsigned char boxVersion;
    unsigned short boxFlags;
    int idx = 0;

    unsigned short streamSize = stream->getSize();
    while (streamSize > stream->getPosition() && (streamSize - stream->getPosition() > 8)){
        unsigned short offset = stream->getPosition();
        boxSize = stream->getUint16();

        for (idx=0; idx != 4; ++idx){
            boxType[idx] = stream->getUint8();
        }

        unsigned short vandf = stream->getUint16();
        boxVersion = (vandf>>12);
        boxFlags = vandf&0x0fff;

        for (idx=0; idx != parserCount; ++idx){
            printf("Box type:  %s, checking parser: %d\n", boxType, idx);
            if (parsers[idx]->canParse(boxType)){
                printf(" Can parse\n");
                Box *box = parsers[idx]->parse(boxSize, boxType, boxVersion, boxFlags, stream);

                if (NULL != handler && NULL != box){
                    handler->parsedBox(box);
                }

                delete box;
                break;
            }
        }

        stream->setPosition(offset+boxSize);
    }
}

void SdffParser::setHandler(ParseHandler *handler){
    this->handler = handler;
}


} // namespace
