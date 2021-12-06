#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include "cmsis_os2.h"
#include "main.h"
#include "teslactrl.h"
#include "app.h"

extern "C" osMessageQueueId_t guiQueueHandle;
extern "C" app_state appState;

Model::Model() : modelListener(0)
{
}

void Model::tick()
{
	tesla_handler temp;
	osStatus_t stat;
	stat = osMessageQueueGet(guiQueueHandle, &temp, 0, 0);
	if(stat == osOK)
	{
		switch(appState)
		{
		case state_cellCapacityDisplay:
			modelListener->setNewValue(temp.cellCapacities[0]);
			break;
		case state_cellTempDisplay:
			modelListener->setNewValue(temp.cellTemps[0]);
			break;
		case state_cellVoltageDisplay:
			modelListener->setNewValue(temp.cellVoltages[0]);
			break;
		case state_chargerStatDisplay:
			modelListener->setNewValue(temp.chargerStats[secChargerDcCurr]);
			break;
		}
	}
}
