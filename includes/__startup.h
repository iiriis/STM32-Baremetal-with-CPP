
#ifdef __cplusplus
extern "C" {
#endif


__dead2 void Reset_Handler(void);
void Default_Handler(void); 
__weak_symbol __attribute__((alias("Default_Handler"))) void NMI_Handler(void);
__weak_symbol __attribute__((alias("Default_Handler"))) void HardFault_Handler(void);
__weak_symbol __attribute__((alias("Default_Handler"))) void MemoryManagementFault_Handler(void);
__weak_symbol __attribute__((alias("Default_Handler"))) void BusFault_Handler(void);
__weak_symbol __attribute__((alias("Default_Handler"))) void UsageFault_Handler(void);



#if (__VFP_FP__)
__always_inline void enableFPU();
__always_inline void enableFPU(){

  asm("LDR.W R0, =0xE000ED88");
  asm("LDR R1, [R0]");
  asm("ORR R1, R1, #(0xF << 20)");
  asm("STR R1, [R0]");
  asm("DSB");
  asm("ISB");
}
#endif

void _init_array();

#ifdef __cplusplus
}
#endif
