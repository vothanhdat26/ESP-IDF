set (SOURCES2  SOURCES2  "E:\\tools_esp\\esp_idf\\components\\freertos\\FreeRTOS-Kernel-SMP\\include\\freertos")
    
idf_component_register(
    SRCS "GPIO/GpioInput.cpp"   "GPIO/GpioOutput.cpp" "E:\\tools_esp\\esp_idf\\components\\esp_event\\include\\esp_event.h" 
    INCLUDE_DIRS "."     
   
     REQUIRES driver esp_event freertos)