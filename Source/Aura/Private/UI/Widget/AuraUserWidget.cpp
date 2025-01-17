// Copyright Tone 2025


#include "UI/Widget/AuraUserWidget.h"
#include UAbilitySystemComponent.h

void UAuraUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}

void UAuraUserWidget::WidgetControllerSet()
{
}
