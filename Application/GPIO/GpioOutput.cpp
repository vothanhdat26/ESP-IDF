#include "GPIO.h"
namespace GPIO
{
    // esp_err_t GpioInput::_init(const gpio_num_t pin, const bool activeLow)
    // {
    // esp_err_t status{ESP_OK};
    // _activeLow = activeLow;
    // _pin = pin;
    // gpio_config_t cfg;
    // cfg.pin_bit_mask = 1ULL << pin;
    // cfg.mode = GPIO_MODE_INPUT;
    // cfg.pull_up_en = GPIO_PULLUP_DISABLE;
    // cfg.pull_down_en = GPIO_PULLDOWN_DISABLE;
    // cfg.intr_type = GPIO_INTR_POSEDGE;

    // status |= gpio_config(&cfg);

    // return status;
    // cout << "INPUT: " << endl;
    // cout << "pin_bit_mask: " << cfg.pin_bit_mask << endl;
    // cout << "mode: " << cfg.mode << endl;
    // cout << "pull_up_en: " << cfg.pull_up_en << endl;
    // cout << "pulll_down_en: " << cfg.pull_down_en << endl;
    // cout << "intr_type: " << cfg.intr_type << endl;
    // cout << "Status: " << status << endl;
    // }
    // GpioInput::GpioInput(const gpio_num_t pin, const bool activeLow)
    // {
    // _init(pin, activeLow);
    // cout << "COntructor tao GpioInput(pin,activeLow):  " << pin << " " << activeLow << endl;
    // }

    // GpioInput::GpioInput(const gpio_num_t pin)
    // {
    // _init(pin, false);
    // cout << "Contructor GpioInput(pin,false):  " << pin << " " << false << endl;
    // }

    // GpioInput::GpioInput(void)
    // {
    // cout << "Contructor tao GpioInput(void): " << endl;
    // }

    // esp_err_t GpioInput::init(const gpio_num_t pin, const bool activeLow)
    // {
    // return _init(pin, activeLow);
    // cout << "khoi tao GpioInput(pin,activeLow):  " << pin << " " << activeLow << endl;
    // }

    // esp_err_t GpioInput::init(const gpio_num_t pin)
    // {
    // return _init(pin, false);
    // cout << "khoi tao GpioInput(pin,false):  " << pin << " " << false << endl;
    // }

    // int GpioInput::read(void)
    // {
    // return _activeLow ? !gpio_get_level(_pin) : gpio_get_level(_pin);
    // cout << "Read: " << gpio_get_level(_pin) << endl;
    // }
    esp_err_t GpioOutput::_init(const gpio_num_t pin, const bool activeLow)
    {
        esp_err_t status{ESP_OK};

        _activeLow = activeLow;
        _pin = pin;

        gpio_config_t cfg;
        cfg.pin_bit_mask = 1ULL << pin;
        cfg.mode = GPIO_MODE_OUTPUT;
        cfg.pull_up_en = GPIO_PULLUP_DISABLE;
        cfg.pull_down_en = GPIO_PULLDOWN_DISABLE;
        cfg.intr_type = GPIO_INTR_DISABLE;

        status |= gpio_config(&cfg);

        return status;
        cout << "OUTPUT: " << endl;
        cout << "pin_bit_mask: " << cfg.pin_bit_mask << endl;
        cout << "mode: " << cfg.mode << endl;
        cout << "pull_up_en: " << cfg.pull_up_en << endl;
        cout << "pulll_down_en: " << cfg.pull_down_en << endl;
        cout << "intr_type: " << cfg.intr_type << endl;
        cout << "Status: " << status << endl;
    }

    GpioOutput::GpioOutput(const gpio_num_t pin, const bool activeLow)
    {
        _init(pin, activeLow);
        cout << "Contructor Output: " << _init(pin, activeLow) << " " << pin << " " << activeLow << endl;
    }

    GpioOutput::GpioOutput(const gpio_num_t pin)
    {
        _init(pin, false);
        cout << "Contructor Output: " << _init(pin, false) << " " << pin << " " << false << endl;
    }

    GpioOutput::GpioOutput(void)
    {
        cout << "Contructor void" << endl;
    }

    esp_err_t GpioOutput::init(const gpio_num_t pin, const bool activeLow)
    {
        return _init(pin, activeLow);
        cout << "khoi tao init() " << _init(pin, activeLow) << " " << pin << " " << activeLow << endl;
    }

    esp_err_t GpioOutput::init(const gpio_num_t pin)
    {
        return _init(pin, false);
        cout << "khoi tao init()" << _init(pin, false) << " " << pin << " " << false << endl;
    }

    esp_err_t GpioOutput::on(void)
    {
        _level = true;
        return gpio_set_level(_pin, _activeLow ? 0 : 1);
        cout << "Level" << _level << endl;
        cout << "gpio_set_level(on) " << gpio_set_level(_pin, _activeLow) << " " << _pin << " " << _activeLow << endl;
    }

    esp_err_t GpioOutput::off(void)
    {
        _level = false;
        return gpio_set_level(_pin, _activeLow ? 1 : 0);
        cout << "Level: " << _level << endl;
        cout << "gpio_set_level(ofF) " << gpio_set_level(_pin, _activeLow) << " " << _pin << " " << _activeLow << endl;
    }

    esp_err_t GpioOutput::toggle(void)
    {
        _level = _level ? 0 : 1;
        return gpio_set_level(_pin, _level ? 1 : 0);
        cout << "Level: " << _level << endl;
        cout << "gpio_set_level(toggle):  " << gpio_set_level(_pin, _level) << " " << _pin << " " << _level << endl;
    }

    esp_err_t GpioOutput::setLevel(int level)
    {
        _level = _activeLow ? !level : level;
        return gpio_set_level(_pin, _level);
        cout << "setLevel:";
        cout << _level << endl;
        cout << "gpio_set_level(_pin,_level): " << gpio_set_level(_pin, _level) << " " << _pin << " " << _level << endl;
    }
}