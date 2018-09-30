#include <Arduino.h>

//#include <time.h>
#include <stdio.h>

#include "Script.h"

#if defined(NARDUINO)
unsigned long millis(){
    clock_t clock_ticks = clock();
    unsigned long milli_ticks = CLOCKS_PER_SEC;
    milli_ticks /= 1000;
    return clock_ticks/milli_ticks; 
}
#endif

void PauseScriptAction::performAction(){
    unsigned long now = millis();

    if (now >= exitTime){
        script->advanceScript();
    }

}

void PauseScriptAction::enterAction(){
    enterTime = millis();
    exitTime = enterTime + duration;
}

PauseScriptAction::PauseScriptAction(Script *script, unsigned short int duration)
    :ScriptAction(script)
    ,duration(duration)
{
}

ScrollScriptAction::ScrollScriptAction(Script *script, short scrollStep, unsigned short int delay, unsigned char count)
    :ScriptAction(script)
    ,scrollStep(scrollStep)
    ,delay(delay)
    ,count(count)
{

}

void ScrollScriptAction::performAction(){
    unsigned long now = millis();

    if (now >= nextScrollTime){
        ScriptState *state = script->getScriptState();
        ++sumSteps;
        state->scrollOffset += scrollStep;

        //printf("%08x %u/%u => %u\n", (int)scrollStep, sumSteps, count, state->scrollOffset);
        state->notifyUpdate();

        if (0 != count){
            if (sumSteps == count){
                script->advanceScript();
            }
        }

        nextScrollTime = enterTime + (1L*(1+sumSteps)*delay);
    }
}

void ScrollScriptAction::enterAction(){
    enterTime = millis();
    nextScrollTime = enterTime + delay;
    //printf("Enter Time %u, nextScroll: %u\n", enterTime, nextScrollTime);
    sumSteps = 0;
}

PositionScriptAction::PositionScriptAction(Script *script, short int position)
    :ScriptAction(script)
    ,position(position)
{

}

void PositionScriptAction::performAction(){
    ScriptState *state = script->getScriptState();
    state->scrollOffset = position;
    state->notifyUpdate();
    script->advanceScript();
}


Script::ScriptState_ Script::GUARD_SCRIPT_STATE;

Script::Script(unsigned short int flags)
    :actionListHead(NULL)
    ,actionListPointer(NULL)
    ,pendingAdvance(false)
    ,scriptState(&Script::GUARD_SCRIPT_STATE)
{
    if (flags & Script::repeat){
        repeatScript = true;
    }
    else {
		repeatScript = false;
	}

    if (flags & Script::wrap){
		wrapDisplay = true;
	}
	else {
		wrapDisplay = false;
	}
}

bool Script::getWrapFlag(){
	return wrapDisplay;

}
bool Script::getRepeatFlag(){
	return repeatScript;
}

void Script::addScriptAction(ScriptAction *action){
    if (NULL == actionListHead){
        actionListHead = actionListPointer = new ScriptActionNode();
        actionListHead->action = action;
    }
    else {
        actionListPointer->next = new ScriptActionNode();
        actionListPointer->next->action = action;
        actionListPointer = actionListPointer->next;
    }
}

void Script::resetScript(){
    actionListPointer = NULL;
}

void Script::advanceScript(){
    //printf("advanceScript (1)\n");
    pendingAdvance = true;
}

void Script::setScriptState(ScriptState *state){
    scriptState = state;
}
ScriptState *Script::getScriptState() {
    return scriptState;
}

void Script::loop(){
    if (NULL == actionListPointer){
        // First call to loop since "reset"
        if (NULL != actionListHead){
            actionListPointer = actionListHead;
            actionListPointer->action->enterAction();
            pendingAdvance = false;
        }
    }

    if (pendingAdvance){
        //printf("advanceScript (2)\n");
        pendingAdvance = false;

        if (actionListPointer){
            //printf("Exit action\n");
            actionListPointer->action->exitAction();
            actionListPointer = actionListPointer->next;
            if (!actionListPointer && repeatScript){
                actionListPointer = actionListHead;
            }
            if (actionListPointer){
                //printf("Enter action\n");          
                actionListPointer->action->enterAction();
            }
        }
    }

    if (actionListPointer){
        actionListPointer->action->performAction();
    }
}
