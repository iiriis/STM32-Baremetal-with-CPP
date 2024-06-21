target extended-remote :3333
monitor reset halt
load
set radix 16
b Reset_Handler
b main
monitor reset init


define np
  n
  info locals
end
