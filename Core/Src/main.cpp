
// #define TAG "MAIN"
// using namespace std;
// #include "main.h"
// Test App;
// void Test::run(void)
// {
//     vTaskDelay(pdMS_TO_TICKS(200));
//     cppLed.setLevel(cppButton.read());
// }
// // void my_event_handler(void *handler_args, esp_event_base_t base, int32_t id, void *event_data)
// // {
// //     ESP_LOGI(TAG, "Event received: base=%s, id=%d", base, id);
// // }
// void Test::setup(void)
// {
//     button_evt_queue = xQueueCreate(10, sizeof(uint32_t));
//     xTaskCreate(gpio_task_example, "gpio_task_example", 2048, NULL, 10, NULL);

//     esp_event_loop_args_t gpio_loop_args;
//     gpio_loop_args.queue_size = 5;
//     gpio_loop_args.task_name = "loop_task"; // Task will be created
//     gpio_loop_args.task_priority = uxTaskPriorityGet(NULL);
//     gpio_loop_args.task_stack_size = 2048;
//     gpio_loop_args.task_core_id = tskNO_AFFINITY;

//     esp_event_loop_create(&gpio_loop_args, &gpio_loop_handle); // Create Custom Event Loop
//     esp_event_loop_create_default();                           // Create System Event Loop

//     cppButton.enableInterrupt(GPIO_INTR_NEGEDGE);
//     cppButton.setQueueHandle(button_evt_queue);

//     cppButton2.enablePullup();
//     cppButton2.enableInterrupt(GPIO_INTR_NEGEDGE);
//     cppButton2.setEventHandler(gpio_loop_handle, &task_custom_event);
// }
// void static Test::button_event_handler(void *handler_args, esp_event_base_t base, int32_t id, void *event_data)
// {
//     std::cout << "Button triggered interrupt with ID: " << id << '\n';
// }

// void static Test::button2_event_handler(void *handler_args, esp_event_base_t base, int32_t id, void *event_data)
// {
//     std::cout << "Button triggered interrupt with ID: " << id << '\n';
// }
// extern "C" void app_main(void)
// {
//     // for (int i = 0; i < 100; i++)
//     // {
//     //     cout << "vo thanh dat HCMUS" << endl;
//     // }
//     // Test App;
//     // // App.test1();
//     // App.testAllFunctions();
//     // while (true)
//     // {
//     //     App.run();
//     // }
//     // GPIO::GpioInput gpio_input;
//     // ESP_ERROR_CHECK(esp_event_loop_create_default());
//     // esp_err_t status = gpio_input.setEventHandler(my_event_handler);
//     // if (status == ESP_OK)
//     // {
//     //     ESP_LOGI(TAG, "Event handler registered successfully");
//     // }
//     // else
//     // {
//     //     ESP_LOGE(TAG, "Failed to register event handler: %s", esp_err_to_name(status));
//     // }
//     // App.setup();

//     App.setup();

//     while (true)
//     {
//         App.run();
//     }
// }

// void Test::button_event_handler(void *handler_args, esp_event_base_t base, int32_t id, void *event_data)
// {
//     std::cout << "Button triggered interrupt with ID: " << id << '\n';
// }

// void Test::button2_event_handler(void *handler_args, esp_event_base_t base, int32_t id, void *event_data)
// {
//     std::cout << "Button triggered interrupt with ID: " << id << '\n';
// }

// void Test::task_custom_event(void *handler_args, esp_event_base_t base, int32_t id, void *event_data)
// {
//     std::cout << "Button triggered interrupt with ID: " << id << " With Custom Loop\n";
// }

// void Test::gpio_task_example(void *arg)
// {
//     uint32_t io_num;
//     for (;;)
//     {
//         if (xQueueReceive(Test::button_evt_queue, &io_num, portMAX_DELAY))
//         {
//             std::cout << "Interrupt triggered from pin " << (int)io_num << " and send to queue\n";
//         }
//     }
// }
#include "main.h"

Test App;

void Test::run(void)
{
    wifiState = Wifi.GetState();
    cppLed.setLevel(cppButton.read());

    switch (wifiState)
    {
    case WIFI::Wifi::state_e::READY_TO_CONNECT:
        std::cout << "Wifi Status: READY_TO_CONNECT\n";
        Wifi.Begin();
        break;
    case WIFI::Wifi::state_e::DISCONNECTED:
        std::cout << "Wifi Status: DISCONNECTED\n";
        Wifi.Begin();
        break;
    case WIFI::Wifi::state_e::CONNECTING:
        std::cout << "Wifi Status: CONNECTING\n";
        break;
    case WIFI::Wifi::state_e::WAITING_FOR_IP:
        std::cout << "Wifi Status: WAITING_FOR_IP\n";
        break;
    case WIFI::Wifi::state_e::ERROR:
        std::cout << "Wifi Status: ERROR\n";
        break;
    case WIFI::Wifi::state_e::CONNECTED:
        std::cout << "Wifi Status: CONNECTED\n";
        break;
    case WIFI::Wifi::state_e::NOT_INITIALIZED:
        std::cout << "Wifi Status: NOT_INITIALIZED\n";
        break;
    case WIFI::Wifi::state_e::INITIALIZED:
        std::cout << "Wifi Status: INITIALIZED\n";
        break;
    }
}

void Test::setup(void)
{
    esp_event_loop_create_default();
    nvs_flash_init();

    Wifi.SetCredentials("TonyTower Mobile", "86868686");
    Wifi.Init();
}

extern "C" void app_main(void)
{
    App.setup();
    while (true)
    {
        vTaskDelay(pdMS_TO_TICKS(1000));
        App.run();
    }
}