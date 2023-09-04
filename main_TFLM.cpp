#include "mbed.h"
#include "tensorflow/lite/micro/cortex_m_generic/debug_log_callback.h"
#include "examples/hello_world/hello_world_test.h"

// Weak empty variant initialization function.
// May be redefined by variant files.
void initVariant() __attribute__((weak));
void initVariant() { }

void debug_log_printf(const char* s)
{
	printf(s);
}

int main()
{
	initVariant();
	RegisterDebugLogCallback(debug_log_printf);

	while(true) 
	{
		test();
		ThisThread::sleep_for(1000ms);
	}

	// main() is expected to loop forever.
	// If main() actually returns the processor will halt
	return 0;
}