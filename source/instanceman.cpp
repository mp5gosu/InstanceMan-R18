#include "c4d.h"

#include "c4d_symbols.h"

#include "constants.h"
#include "Command_Select.h"
#include "Command_Create.h"
#include "Command_Split.h"
#include "Command_Rename.h"
#include "Command_FrameObjects.h"
#include "Command_FrameElements.h"
#include "Command_Swap.h"
#include "Command_MakeEditable.h"
#include "Command_Settings.h"


Bool PluginStart()
{
	// Select
	if (!RegisterCommandPlugin(PID_IM_SELECT, resource.LoadString(IDS_PNAME_IM_SELECT), 0, AutoBitmap(String(PICON_IM_SELECT)), resource.LoadString(IDS_PHELP_IM_SELECT), NewObj(Command_Select)))
		return false;

	// Create
	if (!RegisterCommandPlugin(PID_IM_CREATE, resource.LoadString(IDS_PNAME_IM_CREATE), 0, AutoBitmap(String(PICON_IM_CREATE)), resource.LoadString(IDS_PHELP_IM_CREATE), NewObj(Command_Create)))
		return false;

	// Split
	if (!RegisterCommandPlugin(PID_IM_SPLIT, resource.LoadString(IDS_PNAME_IM_SPLIT), 0, AutoBitmap(String(PICON_IM_SPLIT)), resource.LoadString(IDS_PHELP_IM_SPLIT), NewObj(Command_Split)))
		return false;

	// Rename
	if (!RegisterCommandPlugin(PID_IM_RENAME, resource.LoadString(IDS_PNAME_IM_RENAME), 0, AutoBitmap(String(PICON_IM_RENAME)), resource.LoadString(IDS_PHELP_IM_RENAME), NewObj(Command_Rename)))
		return false;

	// Frame objects
	if (!RegisterCommandPlugin(PID_IM_FRAMEOBJECTS, resource.LoadString(IDS_PNAME_IM_FRAMEOBJECTS), 0, AutoBitmap(String(PICON_IM_FRAMEOBJECTS)), resource.LoadString(IDS_PHELP_IM_FRAMEOBJECTS), NewObj(Command_FrameObjects)))
		return false;

	// Frame elements
	if (!RegisterCommandPlugin(PID_IM_FRAMEELEMENTS, resource.LoadString(IDS_PNAME_IM_FRAMEELEMENTS), 0, AutoBitmap(String(PICON_IM_FRAMEELEMENTS)), resource.LoadString(IDS_PHELP_IM_FRAMEELEMENTS), NewObj(Command_FrameElements)))
		return false;

	// Swap
	if (!RegisterCommandPlugin(PID_IM_SWAP, resource.LoadString(IDS_PNAME_IM_SWAP), 0, AutoBitmap(String(PICON_IM_SWAP)), resource.LoadString(IDS_PHELP_IM_SWAP), NewObj(Command_Swap)))
		return false;

	// Make Editable
	if (!RegisterCommandPlugin(PID_IM_MAKEEDITABLE, resource.LoadString(IDS_PNAME_IM_MAKEEDITABLE), 0, AutoBitmap(String(PICON_IM_MAKEEDITABLE)), resource.LoadString(IDS_PHELP_IM_MAKEEDITABLE), NewObj(Command_MakeEditable)))
		return false;

	// SettingsDialog
	if (!RegisterCommandPlugin(PID_IM, resource.LoadString(IDS_PNAME_IM), 0, AutoBitmap(String(PICON_IM)), resource.LoadString(IDS_PHELP_IM), NewObj(Command_Settings)))
		return false;

	// Separator
	if (!RegisterCommandPlugin(PID_IM_SEPARATOR, String(PNAME_IM_SEPARATOR), 0, nullptr, "", NewObj(Command_Settings)))
		return false;

	return true;
}

Bool PluginMessage(Int32 id, void* data)
{
	switch (id)
	{
		case C4DPL_INIT_SYS:
		{
			return resource.Init();
		}
		default:
			break;
	}
	return true;
}

void PluginEnd()
{
}
