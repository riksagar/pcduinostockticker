
#ifndef PIN_H__
#define PIN_H__


class Pin {
public:
    static Pin *get(int pin);
    enum Mode {
        output, 
        input
    };

    enum State {
        low,
        high
    };

    virtual void setup(Pin::Mode mode) = 0;
    virtual void digitalWrite(Pin::State value) = 0;
    virtual Pin::State digitalRead() = 0;
    virtual ~Pin(){}

protected: 
    Pin();
};


#endif //ndef PIN_H__


