SET(SOURCES screens/ui_setupScreen.c
    screens/ui_notif.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    ui_events.c)

add_library(ui ${SOURCES})
