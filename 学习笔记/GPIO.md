# GPIO
## GPIO简介
- GPIO（General Purpose Input/Output）通用输入输出，是一种通用的输入输出接口，用于连接外部设备。
- GPIO接口一般由输入引脚和输出引脚组成，输入引脚用于接收外部信号，输出引脚用于输出信号。

## GPIO八种模式
1. 输入模式：
    1. 浮空输入 GPIO_MODE_INPUT
        - 内部无上拉 / 下拉电阻，引脚悬空时电平随机浮动
        - 适用：外部自带上下拉的按键、串口 RX、外部传感器信号
        - 缺陷：无外接电路时易受干扰，电平不稳定
    2. 上拉输入 GPIO_MODE_INPUT_PULLUP
        - 内置 40k 上拉电阻，默认电平为高电平
        - 适用：独立按键（一端接 GND，一端接 IO），按键按下变低
    3. 下拉输入 GPIO_MODE_INPUT_PULLDOWN
        - 内置 40k 下拉电阻，默认电平为低电平
        - 适用：按键一端接 3.3V，按下变高电平
    4. 模拟输入 GPIO_MODE_ANALOG
        - 关闭上下拉、关闭施密特触发器，纯模拟通路
        - 适用于模拟信号，如ADC、DAC、PWM等。
        - 优势：无数字电路干扰，采样精度最高
2. 输出模式：
    1. 推挽输出 GPIO_MODE_OUTPUT_PP
        - 内部 PMOS+NMOS 双管：输出高 / 低电平均有强驱动能力（最大 20mA）
        - 适用：LED、继电器、普通高低电平控制，最常用输出模式
        - 特点：不用外部上拉，直接驱动负载
    2. 开漏输出 GPIO_MODE_OUTPUT_OD
        - 仅 NMOS 下拉管：输出低电平导通，高电平为高阻态
        - 必须外接上拉电阻才能输出高电平
        - 适用：I2C 通信总线（总线多设备线与）
    3. 复用推挽输出 GPIO_MODE_AF_PP
        - 外设输出信号，推挽驱动
        - 适用：外设输出信号，如UART、SPI、I2C、JTAG、SWD等
    4. 复用开漏输出 GPIO_MODE_AF_OD 
        - 仅 NMOS 上拉管：输出高电平导通，低电平为高阻态
        - 适用：外设输出信号，如UART、SPI、I2C、JTAG、SWD等

## GPIO寄存器
1. GPIOx_MODER 引脚模式寄存器:
    作用: 设置引脚 8 大工作模式（输入 / 输出 / 复用 / 模拟）
2. GPIOx_OTYPER 引脚输出类型寄存器:
    作用: 推挽输出 (0) / 开漏输出 (1)
3. GPIOx_OSPEEDR 引脚输出速度寄存器（仅输出模式有效）:
    作用: 输出速度选择（高速 / 中速 / 低速）
4. GPIOx_PUPDR 引脚上拉/下拉寄存器:
    作用: 上拉 / 下拉 / 无上拉下拉
5. GPIOx_IDR 引脚输入数据寄存器（仅输入模式有效）:
    作用: 只读，读取引脚外部电平
6. GPIOx_ODR 引脚输出数据寄存器:
    作用: 读写，控制引脚输出高低电平
7. GPIOx_BSRR 引脚输出设置寄存器：
    作用：原子操作，单独置 1、清 0，无读改写冲突（HAL 库底层用这个）
8. GPIOx_BRR 引脚复位寄存器：
    作用：仅用来把引脚拉低

## GPIO使用步骤
1. 开启 GPIO 端口外设时钟（例如GPIOA）
    __HAL_RCC_GPIOA_CLK_ENABLE();
2. 引脚参数配置（填充初始化结构体）
    确定 4 项核心参数：端口引脚、工作模式、上下拉电阻、输出速度；
    - Pin：选择引脚 GPIO_PIN_0 | GPIO_PIN_1
    - Mode：8 种 GPIO 模式（输入 / 推挽输出 / 开漏 / 复用推挽 / 复用开漏 / 模拟 / 中断输入）
    - Pull：上下拉 GPIO_NOPULL / GPIO_PULLUP / GPIO_PULLDOWN
    - Speed：输出速度（仅输出模式生效）
3. 执行硬件初始化，写入寄存器
    ```c
    GPIO_InitTypeDef gpio_cfg = {0};
    // 填充配置省略...
    HAL_GPIO_Init(GPIOA, &gpio_cfg);
    ```
4. 引脚常规读写操作
    - 输出模式：设置高 / 低电平、翻转电平
        ```c
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_0);
        ```
    - 输入模式：读取引脚实时电平
        ```c
        HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
        ```
5. 中断配套补充（仅配置外部中断时需要）
    - 配置 NVIC 中断优先级分组、开启中断通道；
    - 编写中断服务函数 EXTIx_IRQHandler()，并在回调函数 HAL_GPIO_EXTI_Callback() 中处理电平变化逻辑。
    
## GPIO应用场景
- 输入：用于接收外部信号，如按键、传感器、外部时钟等。
- 输出：用于输出信号，如LED、继电器、PWM、串口、I2C等。
- 引脚复用：用于复用引脚，将引脚复用为不同的功能，如UART、SPI、I2C、JTAG、SWD等。

## GPIO应用实例
- 按键：用于接收按键信号，并触发相应的操作。
- LED：用于输出LED信号，并显示当前状态。
- 串口：用于串口通信，接收和发送数据。
- PWM：用于产生PWM信号，并控制LED亮度。
- I2C：用于I2C通信，读写传感器数据。
- SPI：用于SPI通信，读写传感器数据。

## GPIO应用实例代码
1. 普通输出 LED（无复用、无中断）：
```c
void LED_Init(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE(); //1.开时钟
    GPIO_InitTypeDef cfg={0};
    cfg.Pin=GPIO_PIN_0;
    cfg.Mode=GPIO_MODE_OUTPUT_PP; //2.配置推挽输出模式
    cfg.Pull=GPIO_NOPULL;
    cfg.Speed=GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA,&cfg); //3.初始化
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_RESET); //4.操作电平
}
```
