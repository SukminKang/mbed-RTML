#include "mbed.h"
#include "SDBlockDevice.h"

// Weak empty variant initialization function.
// May be redefined by variant files.
void initVariant() __attribute__((weak));
void initVariant() { }

// Instantiate the SDBlockDevice by specifying the SPI pins connected to the SDCard
// socket. The PINS are:
//     MOSI (Master Out Slave In)
//     MISO (Master In Slave Out)
//     SCLK (Serial Clock)
//     CS (Chip Select)
SDBlockDevice sd(D11, D12, A7, A6);
uint8_t block[512] = "Hello World!\n";

int sdTest()
{
	// Call the SDBlockDevice instance initialisation method
    if (0 != sd.init()) {
        printf("Init failed \n");
        return -1;
    }

	printf("sd size: %llu\n",         sd.size());
    printf("sd read size: %llu\n",    sd.get_read_size());
    printf("sd program size: %llu\n", sd.get_program_size());
    printf("sd erase size: %llu\n",   sd.get_erase_size());

    // Set the frequency
    if (0 != sd.frequency(8000000)) {
        printf("Error setting frequency \n");
    }

    if (0 != sd.erase(0, sd.get_erase_size())) {
        printf("Error Erasing block \n");
    }

    // Write data block to the device
    if (0 == sd.program(block, 0, 512)) {
        // Read the data block from the device
        if (0 == sd.read(block, 0, 512)) {
            // Print the contents of the block
            printf("%s", block);
        }
    }

    // Call the SDBlockDevice instance de-initialisation method
    sd.deinit();

	return 0;
}

int main()
{
	initVariant();

	int cnt = 0;
	DigitalOut main_led(LED1);
	DigitalOut red_led(LED2);
	DigitalOut green_led(LED3);
	DigitalOut blue_led(LED4);

	while(true) 
	{
		printf("Hello world from Mbed CE! %d\n", cnt++);
		main_led = 1;
		ThisThread::sleep_for(500ms);
		main_led = 0;
		red_led = 1;
		ThisThread::sleep_for(500ms);
		red_led = 0;
		green_led = 1;
		ThisThread::sleep_for(500ms);
		green_led = 0;
		blue_led = 1;
		ThisThread::sleep_for(500ms);
		blue_led = 0;

		sdTest();
		ThisThread::sleep_for(500ms);
	}

	// main() is expected to loop forever.
	// If main() actually returns the processor will halt
	return 0;
}