#include "Script.h"
#include "SagarDisplayScriptDirector.h"

#include "SDSReader.h"

SagarDisplayScriptDirector *SDSFileReader::readScript(){

	ScriptAction **actions;
	Script *script = new Script(Script::repeat);
/* SKULL
	ScrollScriptAction *scrollAction = new ScrollScriptAction(script, 1, 100, 6);
        PauseScriptAction *pauseAction2 = new PauseScriptAction(script, 250);
        ResetScriptAction *resetAction = new ResetScriptAction(script);
        ScrollScriptAction *revScrollAction = new ScrollScriptAction(script, -1, 500, 3);
        PauseScriptAction *pauseAction = new PauseScriptAction(script, 500);

	actions = new ScriptAction*[7];
	actions[0] = scrollAction;
//	actions[1] = resetAction;
	actions[1] = pauseAction2;
	actions[2] = revScrollAction;
	actions[3] = pauseAction2;
	actions[4] = resetAction;
	actions[5] = pauseAction;
	actions[6] = NULL;
*/

/* HEARTBEAT
        ScriptAction *scrollAction1 = new ScrollScriptAction(script, 1, 100, 32);
        ScriptAction *posAction = new PositionScriptAction(script, -6);
	actions = new ScriptAction*[3];
	actions[0] = scrollAction1;
        actions[1] = posAction;
        actions[2] = NULL;
*/        

	ScrollScriptAction *scrollAction = new ScrollScriptAction(script, 1, 100, 17);
        PauseScriptAction *pauseAction2 = new PauseScriptAction(script, 2000);
        ResetScriptAction *resetAction = new ResetScriptAction(script);
        ScrollScriptAction *revScrollAction = new ScrollScriptAction(script, -1, 100, 8);
        PauseScriptAction *pauseAction = new PauseScriptAction(script, 500);

	actions = new ScriptAction*[6];
	actions[0] = scrollAction;
//	actions[1] = resetAction;
	actions[1] = pauseAction2;
	actions[2] = revScrollAction;
	actions[3] = scrollAction;
	actions[4] = resetAction;
	actions[5] = NULL;


        
	SagarDisplayScriptDirector *ret = new SagarDisplayScriptDirector(script, actions);

	script->setScriptState(ret);

	return ret;
}
