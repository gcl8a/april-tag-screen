#include <touchscreen.h>
#include <tag-widget.h>

Page* Screen::SetupPages(void)
{
    Serial.println(F("SetupPages"));

    pageTag->AddWidget(new TagWidget(this, 32, 96, 0, 64, 1));
    activePage = pageTag;
    
    Serial.println(F("/SetupPages"));

    return pageTag;
}