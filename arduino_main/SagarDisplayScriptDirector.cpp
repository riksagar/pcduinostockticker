#include <stdio.h>

#include "SagarDisplayScriptDirector.h"

SagarDisplayScriptDirector::SagarDisplayScriptDirector(Script *script, ScriptAction **actions)
	:script(script)
	,actions(actions)
	,displayWidth(0)
	,contentWidth(0)
	,isUpdated(false)
{
	for (int aIndex = 0; NULL != actions[aIndex]; ++aIndex){
//printf("Adding script item: %i", aIndex);
		script->addScriptAction(actions[aIndex]);
	}
	script->resetScript();
}
SagarDisplayScriptDirector::~SagarDisplayScriptDirector(){
       // TODO free-up all the storage 
}


bool SagarDisplayScriptDirector::isStateUpdated(){
	bool ret = isUpdated;
	isUpdated = false;
	return ret;
}


void SagarDisplayScriptDirector::onUpdate(ScriptState *state){
	isUpdated = true;
}


ScriptState *SagarDisplayScriptDirector::getState(){
	return this;
}

void SagarDisplayScriptDirector::setDisplayWidth(unsigned short int width){
	displayWidth = width;
}

void SagarDisplayScriptDirector::setContentWidth(unsigned short int width){
	contentWidth = width;
}

void SagarDisplayScriptDirector::setPixelData(SDCReader *data) {
	pixelData = data;
}

unsigned long int const *SagarDisplayScriptDirector::getPixelDataForColumn(unsigned short int colIdx){
	unsigned long int const *ret;
	static unsigned long int empty = 0;

	if (colIdx >= displayWidth) {
		ret = &empty;
	}
	else {
		int idx = this->scrollOffset + colIdx;
		if (idx < 0){
			ret = &empty;
			// TODO support wrap
		}
		else if (idx >= contentWidth){
			ret = &empty;
			// TODO support wrap
		}
		else {
			ret = pixelData->get(idx);
		}
	}

	return ret;
}


void SagarDisplayScriptDirector::loop(){
//printf("  SagarDisplayScriptDirector::loop()");
	script->loop();
}
