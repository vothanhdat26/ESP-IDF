
#include "GPIO.h"
class Test final
{
public:
    void run(void);
    void setup(void);

    esp_event_loop_handle_t gpio_loop_handle{};

    // LED pin on my NodeMCU
    GPIO::GpioOutput cppLed{GPIO_NUM_2, true};
    // Repurpose the BOOT button to work as an input
    GPIO::GpioInput cppButton{GPIO_NUM_0};
    // A second input to demonstrate Event_ID different event handlers
    GPIO::GpioInput cppButton2{GPIO_NUM_12};

    //         << "sauu khi khoi tao test output: " << std::endl;
    static void button_event_handler(void *handler_args, esp_event_base_t base, int32_t id, void *event_data);
    // Event Handler for cppButton2
    static void button2_event_handler(void *handler_args, esp_event_base_t base, int32_t id, void *event_data);
    // Event Handler for custom loop
    static void task_custom_event(void *handler_args, esp_event_base_t base, int32_t id, void *event_data);
    // Handle for the queue
    static xQueueHandle button_evt_queue;
    // Prototype for the task
    static void gpio_task_example(void *arg);

    // void testAllFunctions()
    // {
    //     // Testing GpioInput functions
    //     esp_err_t status;
    //     std::cout << "Testing GpioInput functions:" << std::endl;
    //     status = cppButton.init(GPIO_NUM_36, false);
    //     std::cout << "GpioInput init status: " << status << std::endl;
    //     int level = cppButton.read();
    //     std::cout << "GpioInput read level: " << level << std::endl;
    //     GPIO::GpioInput t;

    //     // Testing GpioOutput functions
    //     std::cout
    //         << "Testing GpioOutput functions:" << std::endl;
    //     status = cppLed.init(GPIO_NUM_18, true);
    //     std::cout << "GpioOutput init status: " << status << std::endl;
    //     status = cppLed.on();
    //     std::cout << "GpioOutput on status: " << status << std::endl;
    //     status = cppLed.off();
    //     std::cout << "GpioOutput off status: " << status << std::endl;
    //     status = cppLed.toggle();
    //     std::cout << "GpioOutput toggle status: " << status << std::endl;
    //     status = cppLed.setLevel(1);
    //     std::cout << "GpioOutput setLevel status: " << status << std::endl;
    // }
};
