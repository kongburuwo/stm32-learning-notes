# **点亮小灯以及流水线灯**


## **点亮LED**

### *初始化LED*

- 建立函数void led_init(void)对小灯进行初始化
1. 使用__HAL_RCC_GPIOB_CLK_ENABLE()函数打开时钟唤醒GPIOB 模块
2. 使用void HAL_GPIO_Init(GPIO_TypeDef  *GPIOx, GPIO_InitTypeDef *GPIO_Init)函数进行初始化，
    *第一个参数GPIO_TypeDef  *GPIOx决定用哪个GPIO，第二个参数为详情结构体*
3. 默认关闭led小灯

```c
void led_init(void)
{
    GPIO_InitTypeDef gpio_initstruct = {0};
    //打开时钟
    __HAL_RCC_GPIOB_CLK_ENABLE();
    
    //GPIO初始化
    gpio_initstruct.Pin = GPIO_PIN_8;
    gpio_initstruct.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_initstruct.Pull = GPIO_PULLUP;
    gpio_initstruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &gpio_initstruct);
    //关闭LED
    led1_off();
}
```


### *点亮LED小灯*
- 建立函数void led1_on(void)点亮LED小灯
1. 调用void HAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState)函数来开启LED小灯
    *第一个参数决定用哪组GPIO，第二个参数决定小灯使用的哪个GPIO，第三个参数决定该GPIO的电位是高还是低，reset为0，一高一低表示通电*

```c
void led1_on(void)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET);
}
```


### *关闭LED小灯*
- 建立函数void led1_off(void)关闭LED小灯
1. 调用void HAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState)函数来开启LED小灯
    *第一个参数决定用哪组GPIO，第二个参数决定小灯使用的哪个GPIO，第三个参数决定该GPIO的电位是高还是低，set为1，两边都是高电平表示通电*
void HAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState)

```c
void led1_off(void)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET);
}
```


### *翻转LED小灯*
- 创建函数void led1_toggle(void)对小灯进行翻转操作
1. 调用void HAL_GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)函数来翻转小灯
    *该函数只用提供GPIO组别以及小灯用的GPIO位置即可*

```c
void led1_toggle(void)
{
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_8);
}
```

### 相关main函数
- 直接使用翻转函数led1_toggle()即可以实现小灯闪烁的场景或led1_on()用led2_off()函数进行开关也可以实现
    *delay_ms(500)用于延迟500毫秒*

```c
int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    led_init();
    
    while(1)
    { 
//      led1_toggle();
        led1_on();
        delay_ms(500);
        led2_off();
    }
}

```


## **流水线灯**

- 大致与点亮LED的代码相符
    *gpio_initstruct.Pin = GPIO_PIN_8 | GPIO_PIN_9;同时配置两个引脚，避免重复写一个函数到达直接初始化两个LED小灯的效果*

```c
void led_init(void)
{
    GPIO_InitTypeDef gpio_initstruct = {0};
    //打开时钟
    __HAL_RCC_GPIOB_CLK_ENABLE();
    
    //GPIO初始化
    gpio_initstruct.Pin = GPIO_PIN_8 | GPIO_PIN_9;
    gpio_initstruct.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_initstruct.Pull = GPIO_PULLUP;
    gpio_initstruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &gpio_initstruct);
    //关闭LED
    led1_off();
    led2_off();
}
```

### 相关main函数
- 两个小灯交替进行开启和关闭

```c
int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    led_init();

    while(1)
    { 
        led1_on();
        led2_off();
        delay_ms(500);
        led2_on();
        led1_off();
        delay_ms(500);
    }
}
```