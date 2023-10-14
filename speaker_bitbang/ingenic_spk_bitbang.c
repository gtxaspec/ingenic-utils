#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

// Define the path to GPIO in the sysfs interface
#define GPIO_PATH "/sys/class/gpio"
// Default GPIO number if none is specified by the user
#define DEFAULT_GPIO_NUMBER "58"

char gpio_number[10];

// Function to check if a GPIO is already exported in userspace
int is_gpio_exported() {
    char path[128];
    snprintf(path, sizeof(path), GPIO_PATH "/gpio%s/direction", gpio_number);
    return (access(path, F_OK) != -1);
}

// Function to export a GPIO to userspace
void export_gpio() {
    int fd = open(GPIO_PATH "/export", O_WRONLY);
    if (fd == -1) {
        perror("Failed to open export for writing");
        exit(1);
    }
    write(fd, gpio_number, strlen(gpio_number));
    close(fd);
    usleep(100000);  // Sleep to give the kernel time to export the GPIO
}

// Function to unexport a GPIO from userspace
void unexport_gpio() {
    int fd = open(GPIO_PATH "/unexport", O_WRONLY);
    if (fd == -1) {
        perror("Failed to open unexport for writing");
        exit(1);
    }
    write(fd, gpio_number, strlen(gpio_number));
    close(fd);
}

// Function to set the direction of a GPIO (input or output)
void set_gpio_direction(const char *direction) {
    char path[128];
    snprintf(path, sizeof(path), GPIO_PATH "/gpio%s/direction", gpio_number);
    int fd = open(path, O_WRONLY);
    if (fd == -1) {
        perror("Failed to open gpio direction for writing");
        exit(1);
    }
    write(fd, direction, strlen(direction));
    close(fd);
}

// Function to set the value (0 or 1) of a GPIO
void set_gpio_value(int value) {
    char path[128];
    snprintf(path, sizeof(path), GPIO_PATH "/gpio%s/value", gpio_number);
    int fd = open(path, O_WRONLY);
    if (fd == -1) {
        perror("Failed to open gpio value for writing");
        exit(1);
    }
    char ch_value = '0' + value;
    write(fd, &ch_value, 1);
    close(fd);
}

// Function to delay for a specified number of microseconds
void udelay(int usec) {
    usleep(usec);
}

// Definitions for each speaker control mode
void speaker_ctl_mode0() {
    set_gpio_value(0);
    udelay(600);
}

void speaker_ctl_mode1() {
    set_gpio_value(0);
    udelay(600);
    set_gpio_value(1);
    udelay(100);
}

void speaker_ctl_mode2() {
    set_gpio_value(0);
    udelay(600);
    set_gpio_value(1);
    udelay(5);
    set_gpio_value(0);
    udelay(5);
    set_gpio_value(1);
    udelay(100);
}

void speaker_ctl_mode3() {
    set_gpio_value(0);
    udelay(600);
    set_gpio_value(1);
    udelay(5);
    set_gpio_value(0);
    udelay(5);
    set_gpio_value(1);
    udelay(5);
    set_gpio_value(0);
    udelay(5);
    set_gpio_value(1);
    udelay(100);
}

void speaker_ctl_mode4() {
    set_gpio_value(0);
    udelay(600);
    set_gpio_value(1);
    udelay(5);
    set_gpio_value(0);
    udelay(5);
    set_gpio_value(1);
    udelay(5);
    set_gpio_value(0);
    udelay(5);
    set_gpio_value(1);
    udelay(5);
    set_gpio_value(0);
    udelay(5);
    set_gpio_value(1);
    udelay(100);
}

int main(int argc, char *argv[]) {
    // Check for proper command line arguments
    if (argc < 2 || argc > 3) {
        printf("Usage: %s <MODE> [GPIO_NUMBER]\n", argv[0]);
        printf("Where MODE is one of: 0, 1, 2, 3, 4\n");
        printf("If no GPIO_NUMBER is provided, it defaults to 58.\n");
        return 1;
    }

    int mode = atoi(argv[1]);
    strcpy(gpio_number, (argc == 3) ? argv[2] : DEFAULT_GPIO_NUMBER);

    // Check if GPIO is already exported, and if not, export it
    int was_exported = is_gpio_exported();
    if (!was_exported) {
        export_gpio();
    }

    // Set the GPIO direction to output
    set_gpio_direction("out");

    // Run the selected mode and print the mode being executed
    printf("Running MODE%d\n", mode);
    switch (mode) {
        case 0:
            speaker_ctl_mode0();
            break;
        case 1:
            speaker_ctl_mode1();
            break;
        case 2:
            speaker_ctl_mode2();
            break;
        case 3:
            speaker_ctl_mode3();
            break;
        case 4:
            speaker_ctl_mode4();
            break;
        default:
            printf("Invalid mode selected.\n");
            return 1;
    }

    // If the GPIO was not previously exported, unexport it
    if (!was_exported) {
        unexport_gpio();
    }

    return 0;
}
