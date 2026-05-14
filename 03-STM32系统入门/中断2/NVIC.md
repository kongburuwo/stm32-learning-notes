## NVIC
- 嵌套向量中断控制器，是STM32中的中断控制器，负责管理和协调处理器的中断请求，是STM32中处理异步事件的重要机制，属于内核
- NVIC支持：256个中断（16内核+240外部），支持：256个优先级，允许裁剪
- 中断使能寄存器（ISER）：位数32，寄存器个数8，每个位控制一个中断：32*8=256（保留16位可以使用240位），负责打开中断
- 中断除能寄存器（ICER）：可以使用240位，和中断使能寄存器配对使用，负责关闭中断
- 应用程序中断及复位控制寄存器（AIRCR）：位数32寄存器个数1，位[10：8]控制优先级分组

 *架构逻辑视角*
-中断优先级寄存器（IRP）：每个中断拥有一个独立8位 IPR 寄存器，共 240 个，只用高4位，对应 16 级优先级。
 *实际地址映射视角（寄存器编程视角）*
- IPR 寄存器本身：是 32 位寄存器（NVIC 外设的寄存器都是 32 位对齐的）。
- IPR0(8bit) + IPR1(8bit) + IPR2(8bit) + IPR3(8bit) = 拼成一个 32 位整体

### 中断优先级
1. 抢占优先级（pre）
- 数值越小优先级越高

2. 响应优先级（sub）
- （抢占优先级一样再根据响应优先级来判断）数值越小优先级越高，不能相互打断【【

3. 自然优抢占优先级先级（）
- 由硬件固定，前两者相同时再根据自然优先级判断

4. 优先级执行顺序
- 当多个中断同时触发时，执行顺序按照：（抢占优先级——响应优先级）一一判断，前两者都相同最终由自然优先级判断
- 在中断嵌套的情况下，高抢占优先级可以打断低抢占优先级的中断，但（抢占优先级相同情况下）高响应优先级无法打段低响应优先级的中断

5. 优先级分组
- 优先级寄存器IPR有8位，但实际使用到高4位，用于决定抢占优先级和响应优先级的等级，由AIRCR寄存器来配置
PRIGROUP (3bit) 的不同数值，规定把那固定的 4 位优先级，从哪一刀切开：上面给抢占优先级、下面给子优先级。
一个工程中，一般只设置一次中断优先级分组

### STM32 NVIC的使用
1. 设置中断分组: AIRCR[10:8], HAl_NVIC_SetPriorityGrouping
2. 设置中断优先级: IPRx bit[7:4], HAL_NVIC_SetPriority
3. 使能中断: ISERx, HAL_NVIC_EnableIPQ

例程中，中断分组已经再HAL_Init()函数中设置了分组2（抢占和响应优先级分别占2）




### NVIC相关函数

- *HAL_NVIC_EnableIRQ使能中断函数*
1. HAL_NVIC_EnableIRQ
```c
void HAL_NVIC_EnableIRQ(IRQn_Type IRQn)
{
  /* Check the parameters */
  assert_param(IS_NVIC_DEVICE_IRQ(IRQn));

  /* Enable interrupt */
  NVIC_EnableIRQ(IRQn);
}
```
2. #define NVIC_DisableIRQ             __NVIC_EnableIRQ
操作ISER寄存器
```c
__STATIC_INLINE void __NVIC_EnableIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    NVIC->ISER[(((uint32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
  }
}
```

- *HAL_NVIC_DisableIRQ失去能中断函数*
1. HAL_NVIC_DisableIRQ
```c
void HAL_NVIC_DisableIRQ(IRQn_Type IRQn)
{
  /* Check the parameters */
  assert_param(IS_NVIC_DEVICE_IRQ(IRQn));

  /* Disable interrupt */
  NVIC_DisableIRQ(IRQn);
}
```
2. #define NVIC_DisableIRQ             __NVIC_DisableIRQ
操作ICER寄存器
```c
__STATIC_INLINE void __NVIC_DisableIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    NVIC->ICER[(((uint32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
    __DSB();
    __ISB();
  }
}
```

- *HAL_NVIC_SetPriorityGrouping进行优先级分组*
1. HAL_NVIC_SetPriorityGrouping
```c
void HAL_NVIC_SetPriorityGrouping(uint32_t PriorityGroup)
{
  /* Check the parameters */
  assert_param(IS_NVIC_PRIORITY_GROUP(PriorityGroup));
  
  /* Set the PRIGROUP[10:8] bits according to the PriorityGroup parameter value */
  NVIC_SetPriorityGrouping(PriorityGroup);
}
```
2. #define NVIC_SetPriorityGrouping    __NVIC_SetPriorityGrouping
操作AIRCR寄存器
```c
__STATIC_INLINE void __NVIC_SetPriorityGrouping(uint32_t PriorityGroup)
{
  uint32_t reg_value;
  uint32_t PriorityGroupTmp = (PriorityGroup & (uint32_t)0x07UL);             /* only values 0..7 are used          */

  reg_value  =  SCB->AIRCR;                                                   /* read old register configuration    */
  reg_value &= ~((uint32_t)(SCB_AIRCR_VECTKEY_Msk | SCB_AIRCR_PRIGROUP_Msk)); /* clear bits to change               */
  reg_value  =  (reg_value                                   |
                ((uint32_t)0x5FAUL << SCB_AIRCR_VECTKEY_Pos) |
                (PriorityGroupTmp << SCB_AIRCR_PRIGROUP_Pos) );               /* Insert write key and priority group */
  SCB->AIRCR =  reg_value;
}
```
- *HAL_NVIC_SetPriority函数设置优先级*
1. HAL_NVIC_SetPriority
```c
void HAL_NVIC_SetPriority(IRQn_Type IRQn, uint32_t PreemptPriority, uint32_t SubPriority)
{ 
  uint32_t prioritygroup = 0x00U;
  
  /* Check the parameters */
  assert_param(IS_NVIC_SUB_PRIORITY(SubPriority));
  assert_param(IS_NVIC_PREEMPTION_PRIORITY(PreemptPriority));
  
  prioritygroup = NVIC_GetPriorityGrouping();
  
  NVIC_SetPriority(IRQn, NVIC_EncodePriority(prioritygroup, PreemptPriority, SubPriority));
}
```
2. #define NVIC_SetPriority            __NVIC_SetPriority
操作NVIC->IP，SCB->SHP两个寄存器
```c
__STATIC_INLINE void __NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority)
{
  if ((int32_t)(IRQn) >= 0)
  {
    NVIC->IP[((uint32_t)IRQn)]               = (uint8_t)((priority << (8U - __NVIC_PRIO_BITS)) & (uint32_t)0xFFUL);
  }
  else
  {
    SCB->SHP[(((uint32_t)IRQn) & 0xFUL)-4UL] = (uint8_t)((priority << (8U - __NVIC_PRIO_BITS)) & (uint32_t)0xFFUL);
  }
}
```

