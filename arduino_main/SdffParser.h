#ifndef __SDFF_PARSER_H
#define __SDFF_PARSER_H


namespace sdff {

    class Stream {
        public:
            virtual unsigned int getSize() = 0;
            virtual unsigned int getPosition() = 0;
            virtual void setPosition(unsigned int pos) = 0;
            virtual unsigned char getUint8() = 0;
            virtual unsigned short getUint16(bool littleendian = false);

            virtual ~Stream(){}
        protected:
            Stream(){};
    };

    class ByteStream: public Stream {
        public:
            ByteStream(unsigned short size, unsigned char *bytes)
                :size(size)
                ,bytes(bytes)
                ,position(0) {}
            virtual ~ByteStream(){}

            virtual unsigned int getSize(){
                return size;
            }
            virtual unsigned int getPosition(){
                return position;
            }
            virtual void setPosition(unsigned int pos){
                position = pos;
            }
            virtual unsigned char getUint8();

        private:
            unsigned short size;
            unsigned char *bytes;
            unsigned short position;

    };


    class Box {
        public:
            virtual const char *getType(){ return type; }
            virtual unsigned int getSize(){ return size; }
            virtual unsigned char getVersion(){ return version; }
            virtual unsigned short getFlags(){ return flags; }

        protected:
            Box(const char *type, unsigned int size, unsigned char version, unsigned short flags)
                :type(type)
                ,size(size)
                ,version(version&0x0f)
                ,flags(flags&0x0fff) {}

            const char *type;
            unsigned int size;
            unsigned char version:4;
            unsigned short flags:12;

    };

    class ScrollScriptActionBox: public Box {
        public:
            short int getStep() { return step; }
            unsigned short int getCount() { return count; }
            unsigned short int getDelay() { return delay; }

            ScrollScriptActionBox(short int step, unsigned short int delay, unsigned char count)
                :Box("sscr", 13, 0, 0)
                ,step(step)
                ,delay(delay)
                ,count(count) {}

        private:
            short step;
            unsigned short delay;
            unsigned char count;            
    };

    class PauseScriptActionBox: public Box {
        public:
            unsigned short getDuration() { return duration; }

            PauseScriptActionBox(unsigned short duration)
                :Box("spau", 10, 0, 0)
                ,duration(duration){}

        private:
            unsigned short duration;
    };

    class PositionScriptActionBox: public Box {
        public:
            unsigned short getPosition() { return position; }

            PositionScriptActionBox(unsigned short position)
                :Box("spos", 10, 0, 0)
                ,position(position){}

        private:
            unsigned short position;
    };

    class ScriptBox: public Box {
        public:
            ScriptBox(unsigned char version, unsigned short flags)
                :Box("scpt", 8, version, flags){}
            virtual ~ScriptBox(){}
    };

    class SagarDisplayBox: public Box {
        public:
            SagarDisplayBox(unsigned char version, unsigned short flags, unsigned short width, unsigned short height);
            virtual ~SagarDisplayBox();

            unsigned short getWidth() { return width; }
            unsigned short getHeight() { return height; }
            unsigned long int const *getColumn(unsigned short dataColumn);
            void addData(unsigned char column, unsigned char offset, unsigned char data);

        private:
            unsigned char width;
            unsigned char height;
            unsigned long int *data;
            unsigned short dataColumns;

    };

    class BoxParser {
        public:
            virtual Box *parse(unsigned short size, char *type, unsigned char, unsigned short, Stream *stream) = 0;
            virtual ~BoxParser(){}
            virtual bool canParse(const char *type);

        protected:
            BoxParser(unsigned short supports, const char *type, ...);

        private:
            char **supported;
            unsigned short supportedCount;
    };

    class ScriptActionBoxParser: public BoxParser {

        public:
            ScriptActionBoxParser()
                :BoxParser(3, "sscr", "spau", "spos") {}
            virtual ~ScriptActionBoxParser(){}
            Box *parse(unsigned short int boxsize, char *boxtype, unsigned char boxversion, unsigned short boxflags, Stream *stream);
    };

    class ScriptBoxParser: public BoxParser {
        public:
            ScriptBoxParser()
                :BoxParser(1, "scpt"){}
            virtual ~ScriptBoxParser(){}
            Box *parse(unsigned short size, char *type, unsigned char version, unsigned short flags, Stream *stream);
    };

    class SagarDisplayBoxParser: public BoxParser {
        public:
            SagarDisplayBoxParser()
                :BoxParser(1, "disp") {}
            ~SagarDisplayBoxParser(){}
            
            Box *parse(unsigned short size, char *type, unsigned char flags, unsigned short version, Stream *stream);

    };

    class ParseHandler {
        public:
            virtual void parsedBox(Box *box) = 0;
    };

    class SdffParser {
        public: 
            SdffParser();
            ~SdffParser();

            void parse(Stream *stream);
            void setHandler(ParseHandler *handler);

        private:
            unsigned int parserCount;
            BoxParser **parsers;
            ParseHandler *handler;
    };

}//namespace 


#endif //def __SDFF_PARSER_H
