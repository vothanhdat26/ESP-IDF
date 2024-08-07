set(SOURCES GpioInput.cpp GpioOutput.cpp)
idf_component_register(SRCS ${SOURCES}
    REQUIRES driver esp_event
) 