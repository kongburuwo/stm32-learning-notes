# SysTick
## SysTick简介
- Systick：即滴答定时器，是一个集成在 ARM Cortex-M 内核中的 24位向下计数器 定时器
- 主要用途：
    1. 操作系统心跳时钟：为实时操作系统（RTOS，如 FreeRTOS、RT-Thread、uC/OS）提供*时基*，用于任务调度、延时和超时管理。
    2. 精确*延时*：在不使用操作系统的裸机开发中，常用于实现微秒（us）或毫秒（ms）级的精确延时函数。

## 相关寄存器
1. LOAD (Reload Value Register): 重装载值寄存器。设定计数的初始值。
    - 有效位为 [23:0]，最大值为 $2^{24} - 1 = 16,777,215$。
2. VAL (Current Value Register): 当前值寄存器。计数器当前的数值。
    - 该寄存器只有低 24 位有效（[23:0]），高 8 位保留。这意味着最大计数值为 $2^{24} - 1 = 16,777,215$。
3. CTRL (Control and Status Register): 控制和状态寄存器。用于使能定时器、选择时钟源、开启中断等。
    - 16位：COUNTFLAG计数标志位，1: 自上次读取该寄存器后，计数器曾减到 0，0: 计数器未减到 0
    - 2位： CLKSOURCE时钟源选择位，1: 选择处理器时钟 (HCLK, 通常为 72MHz/168MHz 等)， 0: 选择外部参考时钟 (HCLK/8)
    - 1位： TICKINT异常请求使能位，1: 当计数器减到 0 时，产生 SysTick 异常（中断），0: 计数器减到 0 时，不产生中断
    - 0位： ENABLE计数器使能位，1: 使能 SysTick 计数器，0: 禁用 SysTick 计数器

## 工作流程
1. 初始化：
    - 向 LOAD 寄存器写入一个初始值 $N$。
    - 将 VAL 寄存器清零（硬件会自动将 VAL 设置为 $N$）。
    - 配置 CTRL 寄存器，选择时钟源（通常是 HCLK 或 HCLK/8），并使能计数器。
2. 计数过程：
    - SysTick 在每个时钟周期自动将 VAL 的值减 1。
    - 当 VAL 从 1 减到 0 时，产生一个计数结束事件。
3. 重装载与中断：
    - 当计数器减到 0 后，硬件会自动将 LOAD 寄存器中的值重新加载到 VAL 中，开始下一轮计数。
    - 如果在 CTRL 寄存器中使能了异常请求（TickInt），则在每次计数到 0 时，会触发 SysTick 异常中断。
4. 时间计算：
    - 假设时钟频率为 $f_{clk}$，重装载值为 $N$。
    - 一次计数周期的时间 $T = \frac{N + 1}{f_{clk}}$。
    - 通过设置不同的 $N$ 值，可以实现微秒（us）或毫秒（ms）级的精确定时。
## HAL_Delay 
- HAL_Delay 是一个基于中断计数的软件轮询延时。它巧妙利用了无符号整数运算的特性来处理时间溢出，并通过弱定义方便用户定制。它是 STM32 裸机开发中最基础的时间管理工具，但需注意其阻塞性和不可在中断中调用的限制。

### HAL_Delay
    ```c
        __weak void HAL_Delay(uint32_t Delay)
    {
        //1. 获取当前时间戳（起始点）
      uint32_t tickstart = HAL_GetTick();   
        // 2. 准备等待的目标值
      uint32_t wait = Delay;     
   
      // 3. 安全补偿机制
      if (wait < HAL_MAX_DELAY) // HAL_MAX_DELAY 通常为 0xFFFFFFFF
      {
        // 增加一个频率因子（通常为1），确保延时“至少”达到设定值
        wait += (uint32_t)(uwTickFreq);
      }
        // 4. 阻塞等待循环
      while ((HAL_GetTick() - tickstart) < wait)
      {
        // 空转，直到时间差达到目标
      }
    }
    ```
### SysTick_Handler
    ```c
    void SysTick_Handler(void)  // SysTick 定时器的中断服务函数
    {
      HAL_IncTick(); // 调用 HAL 库提供的 tick 递增函数
    }
    ```
### HAL_IncTick
    ```c
        __weak void HAL_IncTick(void)
    {
      uwTick += uwTickFreq; 
    }
    ```

## 配置delay延时
```c
void delay_us(uint32_t nus)
{
    uint32_t temp;
    /* 1. 确定数多少个数，HCLK 72Mhz = 1秒72M次 -> 72M = 1S -> 1S = 1000ms = 1M us
    72M = 1M us -> 72 = 1 us -> 相当于数72个数等于1us */
    SysTick->LOAD = 72 * nus;
    // 2. 清空当前计数
    SysTick->VAL = 0x00;
    // 3. 配置分频系数
    SysTick->CTRL |= 1<<2;
    // 4. 开启定时器
    SysTick->CTRL |= 1<<0;
    
    do
    {
        temp = SysTick->CTRL; //临时变量获取CTRL的状态
    }
    while((temp & 0x01) && !(temp & (1 << 16)));
    
    SysTick->CTRL &= ~(1 << 0); //按位取反
    SysTick->VAL = 0x00; //清零
}

/**
  * @brief  毫秒级延时
  * @param  nms 延时时长，范围：0~4294967295
  * @retval 无
  */
void delay_ms(uint32_t nms)
{
    while(nms--)
        delay_us(1000);
}
 
/**
  * @brief  秒级延时
  * @param  ns 延时时长，范围：0~4294967295
  * @retval 无
  */
void delay_s(uint32_t ns)
{
    while(ns--)
        delay_ms(1000);
}

/**
  * @brief  重写HAL_Delay函数
  * @param  nms 延时时长，范围：0~4294967295
  * @retval 无
  */
void HAL_Delay(uint32_t nms)
{
    delay_ms(nms);
}

```

## 系统延时函数
```c
void delay_us(uint32_t nus)
{
    uint32_t ticks;
    uint32_t tcnt = 0, told, tnow;
    uint32_t reload = SysTick->LOAD;
    
    ticks = nus * 72;
    told = SysTick->VAL;
    
    while(1)
    {
        tnow = SysTick->VAL;
        if(tnow != told)
        {
            if(tnow < told)
                tcnt += told - tnow;
            else
                tcnt += reload - (tnow - told);
            
            told = tnow;
            
            if(tcnt >= ticks)
                break;
        }
    }
}
```