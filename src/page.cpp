#include "page.h"
#include "touchscreen.h"

void Page::Draw(void)
{
    screen->clearDisplay();
    screen->fillScreen(SSD1306_BLACK);

    WidgetIterator widgetIter(widgets);
    while(widgetIter.Current())
    {
        widgetIter.Current()->Draw();
        widgetIter++;
    }
    screen->display();
}  

void PageWidget::OnClick(void)
{
    if(action == RETURN) screen->SetActivePage(target);
}

void PageWidget::Draw(void)
{
    TextWidget::Draw();
    screen->print(displayText);
}
