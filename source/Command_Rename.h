#pragma once

#include "c4d.h"
#include "instance_functions.h"


class Command_Rename : public CommandData
{
INSTANCEOF(Command_Select, CommandData)

public:
	Int32 GetState(BaseDocument* doc) override
	{
		// Disable Menu entry if no object is selected
		const AutoAlloc<AtomArray> arr;
		doc->GetActiveObjects(arr, GETACTIVEOBJECTFLAGS_0);
		if (!arr || arr->GetCount() == 0)
			return 0;
		return CMD_ENABLED;
	}

	Bool Execute(BaseDocument* doc) override
	{
		if (!doc)
			return false;

		doc->StartUndo();

		// Create Array that holds all objects to operate on
		const AutoAlloc<AtomArray> activeObjects;
		doc->GetActiveObjects(activeObjects, GETACTIVEOBJECTFLAGS_0 | GETACTIVEOBJECTFLAGS_CHILDREN);

		// Allocation failed
		if (!activeObjects)
			return false;

		// Detect Key modifiers#
		BaseContainer state;
		GetInputState(BFM_INPUT_KEYBOARD, BFM_INPUT_MODIFIERS, state);
		const auto bCtrl = (state.GetInt32(BFM_INPUT_QUALIFIER) & QCTRL) != 0;
		const auto bShift = (state.GetInt32(BFM_INPUT_QUALIFIER) & QSHIFT) != 0;
		for (auto i = 0; i < activeObjects->GetCount(); ++i)
		{
			auto j = 0;
			const auto atom = activeObjects->GetIndex(i);

			// Something failed
			if (!atom)
				return false;

			// Treat atom as BaseObject
			const auto obj = static_cast<BaseObject*>(atom);

			if (obj->GetType() == Oinstance)
			{
				const auto refObj = g_GetInstanceRef(obj, bCtrl);
				if (refObj)
				{
					// Rename enumerate when Shift is pressed
					auto name = refObj->GetName();
					if (bShift)
						name += "." + String::IntToString(i + 1);
					doc->AddUndo(UNDOTYPE_CHANGE_SMALL, obj);
					obj->SetName(name);
				}
			}
			else
			{
				// Rename instances based on a selected reference object
				auto nInstance = doc->GetFirstObject();
				while (nInstance)
				{
					if (nInstance->GetType() == Oinstance)
					{
						const auto temp = g_GetInstanceRef(nInstance, bCtrl);
						if (temp && temp == obj)
						{
							doc->AddUndo(UNDOTYPE_CHANGE_SMALL, nInstance);
							auto name = temp->GetName();
							if (bShift)
								name += "." + String::IntToString(j + 1);
							nInstance->SetName(name);
							++j;
						}
					}
					nInstance = static_cast<BaseObject*>(g_GetNextElement(nInstance));
				}
			}
		}

		doc->EndUndo();
		EventAdd();

		return true;
	}
};
