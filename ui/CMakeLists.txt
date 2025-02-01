SET(SOURCES screens/ui_Splash.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    images/ui_img_flare_png.c
    images/ui_img_gauge200_png.c
    images/ui_img_needle200_png.c)

add_library(ui ${SOURCES})
