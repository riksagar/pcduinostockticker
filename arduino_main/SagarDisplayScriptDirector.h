#ifndef __SAGARDISPLAYSCRIPTDIRECTOR_H
#define __SAGARDISPLAYSCRIPTDIRECTOR_H

#include "Script.h"
#include "SagarDisplayControlFileReader.h"


class SagarDisplayScriptDirector: public ScriptState {
	public:
		SagarDisplayScriptDirector(Script *script, ScriptAction **actions);
		virtual ~SagarDisplayScriptDirector();

		bool isStateUpdated();
		ScriptState *getState();

		void setDisplayWidth(unsigned short int width);
		void setContentWidth(unsigned short int width);
		void setPixelData(SDCReader *data);
		unsigned long int const *getPixelDataForColumn(unsigned short int index);

		void loop();

	protected:
		void onUpdate(ScriptState *state);


	private:
		unsigned short int displayWidth;
		unsigned short int contentWidth;
                bool isUpdated;

		SDCReader *pixelData;
                Script *script;
                ScriptAction **actions;
};

#endif //ndef __SAGARDISPLAYSCRIPTDIRECTOR_H



