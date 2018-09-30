#ifndef __SCRIPT_H
#define __SCRIPT_H


#include <memory.h>

class Script;

class ScriptAction {
    public:
        virtual void performAction() = 0;
        virtual void enterAction(){};
        virtual void exitAction(){};
        virtual ~ScriptAction(){}

    protected:
        ScriptAction(Script *s)
            :script(s)
        {

        }
        Script *script;
};


class PauseScriptAction: public ScriptAction {
    public:
        PauseScriptAction(Script *script, unsigned short int duration);
        virtual ~PauseScriptAction(){}

        void enterAction();
        void performAction();
    private:
        unsigned long enterTime;
        unsigned long exitTime;
        unsigned short int duration;
};

class ScrollScriptAction: public ScriptAction {
    public:
        ScrollScriptAction(Script *script, short scrollStep, unsigned short int delay, unsigned char count);
        virtual ~ScrollScriptAction(){}

        void enterAction();
        void performAction();

    private:
        short scrollStep;
//        unsigned char scrollWidth; // range: 0 ... scrollWidth-1
        unsigned short int delay;
        unsigned char count;
//        unsigned char sumScroll;
        unsigned char sumSteps;
        unsigned long int nextScrollTime;
        unsigned long int enterTime;
};

class PositionScriptAction: public ScriptAction {
    public:
        PositionScriptAction(Script *script, short int position);
        virtual ~PositionScriptAction(){}

        void performAction();

    private:
        short int position;

};

class ResetScriptAction: public PositionScriptAction {
    public:
        ResetScriptAction(Script *script)
            :PositionScriptAction(script, 0)
        {}
        virtual ~ResetScriptAction(){}
};

typedef struct ScriptActionNode {
    ScriptActionNode(){
        action = NULL;
        next = NULL;
    }
    ScriptAction *action;
    struct ScriptActionNode *next;
} ScriptActionNode;

class ScriptState {
    public:
        ScriptState(short o=0, unsigned short dat=0, unsigned short dis=0)
            :scrollOffset(o), dataMaxCol(dat), displayMaxCol(dis){}
        virtual ~ScriptState(){}

        short int scrollOffset;
        unsigned short int dataMaxCol;
        unsigned short int displayMaxCol;
        void notifyUpdate(){
            onUpdate(this);
        }
    protected:
        virtual void onUpdate(ScriptState *state) = 0;
};

class Script {
    public:
        enum Flags {
            repeat = 0x01,
            wrap = 0x02
        };
        
        Script(unsigned short int flags);
        void addScriptAction(ScriptAction *);
        void loop();
        void advanceScript();
        void resetScript();

        void setScriptState(ScriptState *state);
        ScriptState *getScriptState();

        bool getWrapFlag();
        bool getRepeatFlag();

    private:
        ScriptActionNode *actionListHead;
        ScriptActionNode *actionListPointer;        
        int activeAction;
        int actionCount;
        bool repeatScript;
        bool wrapDisplay;
        bool pendingAdvance;
        ScriptState *scriptState;

        static class ScriptState_: public ScriptState {
            void onUpdate(ScriptState *){}
        } GUARD_SCRIPT_STATE;
};

#endif //ndef __SCRIPT_H

