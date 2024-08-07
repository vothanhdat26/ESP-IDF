
set(SOURCES ./Src/main.cpp)
set(SOURCES2  "E:/tools_esp/esp-c3/project-c3/Application/GPIO" )
set(SOURCES3 "E:/tools_esp/esp_idf/components/esp_event/include")

idf_component_register(
    SRCS ${SOURCES}
    INCLUDE_DIRS Inc ${SOURCES2} ${SOURCES3}
    REQUIRES driver esp_event freertos esp_wifi GPIO WiFi esp_netif lwip
)

    