#include <amtest.h>
#define MTIME_ADDR     0x20000000
#define MTIMECMP_ADDR  (MTIME_ADDR + 0x8)

Context *simple_trap(Event ev, Context *ctx) {
  // printf("event is %d\n", ev.event);
  switch(ev.event) {
    case EVENT_IRQ_TIMER:
      *((uint64_t *)MTIMECMP_ADDR) += 0x500000;
      putch('t'); break;
    case EVENT_IRQ_IODEV:
      putch('d'); break;
    case EVENT_YIELD:
      putch('y'); break;
    default:
      break;
  }
  return ctx;
}

void hello_intr() {
  printf("Hello, AM World @ " __ISA__ "\n");
  printf("  t = timer, d = device, y = yield\n");
  io_read(AM_INPUT_CONFIG);
  iset(1);
  while (1) {
    for (volatile int i = 0; i < 100000; i++) ;
    yield();
  }
}
