
###########################################################
# GCC template makefile
###########################################################

ESP_SOURCES =
ESP_SOURCES += ESP8266.c
ESP_SOURCES += TCP.c
ESP_SOURCES += HTTP.c
ESP_SOURCES += Web.c
C_SOURCES += $(ESP_SOURCES)