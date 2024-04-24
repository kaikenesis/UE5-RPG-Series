#include "Widgets/CInventoryWidget.h"
#include "Engine/DataTable.h"

void UCInventoryWidget::NativePreConstruct()
{
}

void UCInventoryWidget::NativeConstruct()
{
	ItemDataList->GetAllRows<FItemList>("", Items);
}
