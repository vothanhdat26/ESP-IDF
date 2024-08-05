#include "GPIO/GPIO.h"

namespace GPIO
{
    bool GpioInput::_interrupt_service_installed{false};
    portMUX_TYPE GpioInput::_eventChangeMutex = portMUX_INITIALIZER_UNLOCKED;
    esp_err_t GpioInput::_init(const gpio_num_t pin, const bool activeLow)
    {
        esp_err_t status{ESP_OK};
        _activeLow = activeLow;
        _pin = pin;
        gpio_config_t cfg;
        cfg.pin_bit_mask = 1ULL << pin;
        cfg.mode = GPIO_MODE_INPUT;
        cfg.pull_up_en = GPIO_PULLUP_DISABLE;
        cfg.pull_down_en = GPIO_PULLDOWN_DISABLE;
        cfg.intr_type = GPIO_INTR_POSEDGE;
        status |= gpio_config(&cfg);
        return status;
        cout << "INPUT: " << endl;
        cout << "pin_bit_mask: " << cfg.pin_bit_mask << endl;
        cout << "mode: " << cfg.mode << endl;
        cout << "pull_up_en: " << cfg.pull_up_en << endl;
        cout << "pulll_down_en: " << cfg.pull_down_en << endl;
        cout << "intr_type: " << cfg.intr_type << endl;
        cout << "Status: " << status << endl;
    }
    GpioInput::GpioInput(const gpio_num_t pin, const bool activeLow)
    {
        _init(pin, activeLow);
        cout << "COntructor tao GpioInput(pin,activeLow):  " << pin << " " << activeLow << endl;
    }
    GpioInput::GpioInput(const gpio_num_t pin)
    {
        _init(pin, false);
        cout << "Contructor GpioInput(pin,false):  " << pin << " " << false << endl;
    }
    GpioInput::GpioInput(void)
    {
        cout << "Contructor tao GpioInput(void): " << endl;
    }
    esp_err_t GpioInput::init(const gpio_num_t pin, const bool activeLow)
    {
        return _init(pin, activeLow);
        cout << "khoi tao GpioInput(pin,activeLow):  " << pin << " " << activeLow << endl;
    }
    esp_err_t GpioInput::init(const gpio_num_t pin)
    {
        return _init(pin, false);
        cout << "khoi tao GpioInput(pin,false):  " << pin << " " << false << endl;
    }
    int GpioInput::read(void)
    {
        return _activeLow ? !gpio_get_level(_pin) : gpio_get_level(_pin);
        cout << "Read: " << gpio_get_level(_pin) << endl;
    }
    esp_err_t GpioInput::enablePullup(void)
    {
        cout << "fun enablePullup: " << endl;
        return gpio_set_pull_mode(_pin, GPIO_PULLUP_ONLY);
    }
    esp_err_t GpioInput::disablePullup(void)
    {
        cout << "fun disablePullup: " << endl;
        return gpio_set_pull_mode(_pin, GPIO_FLOATING);
    }
    esp_err_t GpioInput::enablePulldown(void)
    {
        cout << "fun enable Pull Down" << endl;
        return gpio_set_pull_mode(_pin, GPIO_PULLDOWN_ONLY);
    }
    esp_err_t GpioInput::disablePulldown(void)
    {
        cout << "Fun disable Pull Down: " << endl;
        return gpio_set_pull_mode(_pin, GPIO_FLOATING);
    }
    esp_err_t GpioInput::enablePullupPulldown(void)
    {
        cout << "Fun Pull Up pull Down: " << endl;
        return gpio_set_pull_mode(_pin, GPIO_PULLUP_ONLY);
    }
    esp_err_t GpioInput::disablePullupPulldown(void)
    {
        cout << "Fun dis pull up pull down" << endl;
        return gpio_set_pull_mode(_pin, GPIO_FLOATING);
    }
    esp_err_t GpioInput::enableInterrupt(gpio_int_type_t int_type)
    {
        esp_err_t status{ESP_OK};
        if (_activeLow)
        {
            switch (int_type)
            {
            case GPIO_INTR_POSEDGE:
                int_type = GPIO_INTR_NEGEDGE;
                /* code */
                break;
            case GPIO_INTR_NEGEDGE:
                int_type = GPIO_INTR_POSEDGE;
                break;
            case GPIO_INTR_LOW_LEVEL:
                int_type = GPIO_INTR_HIGH_LEVEL;
                break;
            case GPIO_INTR_HIGH_LEVEL:
                int_type = GPIO_INTR_LOW_LEVEL;
                break;
            default:
                break;
            }
        }
        if (!_interrupt_service_installed)
        {
            status = gpio_install_isr_service(0);
            if (ESP_OK == status)
            {
                _interrupt_service_installed = true;
            }
        }
        if (ESP_OK == status)
        {
            status = gpio_set_intr_type(_pin, int_type);
        }
        if (ESP_OK == status)
        {
            status = gpio_isr_handler_add(_pin, gpio_isr_callback, (void *)_pin);
        }
        return status;
    }
    esp_err_t GpioInput::setEventHandler(esp_event_handler_t Gpio_e_h)
    {
        esp_err_t status{ESP_OK};

        taskENTER_CRITICAL(&_eventChangeMutex);

        status = _clearEventHandlers();

        status = esp_event_handler_instance_register(INPUT_EVENTS, _interrupt_args._pin, Gpio_e_h, 0, nullptr);

        if (ESP_OK == status)
        {
            _interrupt_args._event_handler_set = true;
        }

        taskEXIT_CRITICAL(&_eventChangeMutex);

        return status;
    }
    esp_err_t GpioInput::setEventHandler(esp_event_loop_handle_t Gpio_e_l, esp_event_handler_t Gpio_e_h)
    {
        esp_err_t status{ESP_OK};

        taskENTER_CRITICAL(&_eventChangeMutex);

        status = _clearEventHandlers();

        status |= esp_event_handler_instance_register_with(Gpio_e_l, INPUT_EVENTS, _interrupt_args._pin, Gpio_e_h, 0, nullptr);

        if (ESP_OK == status)
        {
            _event_handle = Gpio_e_h;
            _interrupt_args._custom_event_loop_handle = Gpio_e_l;
            _interrupt_args._custom_event_handler_set = true;
        }

        taskEXIT_CRITICAL(&_eventChangeMutex);

        return status;
    }
    void IRAM_ATTR GpioInput::gpio_isr_callback(void *args)
    {
        int32_t pin = (reinterpret_cast<struct interrupt_args *>(args))->_pin;
        bool custom_event_handler_set = (reinterpret_cast<struct interrupt_args *>(args))->_custom_event_handler_set;
        bool event_handler_set = (reinterpret_cast<struct interrupt_args *>(args))->_event_handler_set;
        bool queue_enabled = (reinterpret_cast<struct interrupt_args *>(args))->_queue_enabled;
        esp_event_loop_handle_t custom_event_loop_handle = (reinterpret_cast<struct interrupt_args *>(args))->_custom_event_loop_handle;
        xQueueHandle queue_handle = (reinterpret_cast<struct interrupt_args *>(args))->_queue_handle;

        if (queue_enabled)
        {
            xQueueSendFromISR(queue_handle, &pin, NULL);
        }
        else if (custom_event_handler_set)
        {
            esp_event_isr_post_to(custom_event_loop_handle, INPUT_EVENTS, pin, nullptr, 0, nullptr);
        }
        else if (event_handler_set)
        {
            esp_event_isr_post(INPUT_EVENTS, pin, nullptr, 0, nullptr);
        }
    }

    esp_err_t GpioInput::_clearEventHandlers()
    {
        esp_err_t status{ESP_OK};

        if (_interrupt_args._custom_event_handler_set)
        {
            esp_event_handler_unregister_with(_interrupt_args._custom_event_loop_handle, INPUT_EVENTS, _interrupt_args._pin, _event_handle);
            _interrupt_args._custom_event_handler_set = false;
        }
        else if (_interrupt_args._event_handler_set)
        {
            esp_event_handler_instance_unregister(INPUT_EVENTS, _interrupt_args._pin, nullptr);
            _interrupt_args._event_handler_set = false;
        }

        _interrupt_args._queue_handle = nullptr;
        _interrupt_args._queue_enabled = false;

        return status;
    }

}