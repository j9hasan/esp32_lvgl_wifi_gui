SET(SOURCES
    screens/ui_mainScreen.c
    screens/ui_setupScreen.c
    screens/ui_memScreen.c
    screens/ui_checkin_checkout.c
    ui.c
    ui_events.cpp
    ui_helpers.c

    )
idf_component_register(SRCS ${SOURCES}
                       INCLUDE_DIRS .
                       REQUIRES lvgl shared_task wifi_app system_status inventory helper_func sd_fat json
                       )