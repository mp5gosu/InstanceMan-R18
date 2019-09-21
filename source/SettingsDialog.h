#pragma once

#include "c4d.h"

#include "c4d_symbols.h"

class SettingsDialog : public GeDialog
{
INSTANCEOF(SettingsDialog, GeDialog)

public:
	Bool CreateLayout()
	{
		SetTitle(resource.LoadString(IDS_SETTINGSDIALOG_TITLE));
		GroupBegin(0, BFH_SCALEFIT | BFV_TOP, 2, 0, "", BFV_GRIDGROUP_EQUALCOLS);
		GroupSpace(4, 4);
		GroupBorderSpace(4, 4, 4, 4);
		AddCheckbox(IDS_INSTANCEMODE, BFH_SCALEFIT | BFV_TOP, 0, 0, resource.LoadString(IDS_LBL_INSTANCEMODE));
		GroupEnd();
		return true;
	}

	Bool InitValues()
	{
		// Populate cycle with available instance modes
		SetBool(IDS_INSTANCEMODE, GetData());
		return true;
	}

	Bool Command(Int32 id, const BaseContainer& msg)
	{
		SetData(); // Save the current selected instance mode
		return GeDialog::Command(id, msg);
	}

	// Get the available instance modes
	static void GetInstanceDescription(BaseContainer& bc)
	{
		AutoAlloc<Description> desc;

		// Get the description of instance objects
		if (desc && desc->LoadDescription(Oinstance))
		{
			const DescID completeId = DescLevel(INSTANCEOBJECT_RENDERINSTANCE, DTYPE_BOOL, 0);

			// Get its parameters
			const auto param = desc->GetParameterI(completeId, nullptr);
			if (param)
				param->GetContainer(DESC_CYCLE).CopyTo(&bc, COPYFLAGS_0, nullptr);
		}
	}

	static Bool GetData()
	{
		// Get the active instance mode from plugin settings
		const auto bc = GetWorldPluginData(PID_IM);
		if (bc)
			return bc->GetBool(DEFAULT_INSTANCEMODE);
		return false;
	}

private:
	void SetData()
	{
		// Read the plugin settings and set the active instance mode
		BaseContainer bc;
		GetBool(IDS_INSTANCEMODE, _isRenderInstance);
		bc.SetBool(DEFAULT_INSTANCEMODE, _isRenderInstance);
		SetWorldPluginData(PID_IM, bc, false);
	}


	Bool _isRenderInstance = false;
};
