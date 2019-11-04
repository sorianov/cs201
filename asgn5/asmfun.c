#include <stdio.h>

const int INT_REGISTER_LENGTH = 4; // bytes
const double RADIUS = 4.5

double sphereVolume(const double radius) {
    double volume;
    const double four = 4.0;
    const double three = 3.0;

    asm(
        "   fldl        %[three]        \n" // load 3.0
        "   fldl        %[four]         \n" // load 4.0
        "   fdivp                       \n" // 4/3
        "   fldpi                       \n" // load PI constant
        "   fmulp                       \n" // (4/3) * PI
        "   fldl        %[radius]       \n" // load radius argument
        "   fldl        %[radius]       \n"
        "   fldl        %[radius]       \n"
        "   fmulp                       \n" // radius^2
        "   fmulp                       \n" // radius^3
        "   fmulp                       \n" // ((4/3) * PI) * radius^3
        "   fstpl       %[volume]       \n" // store into volume

        :   [volume]    "=m"    (volume)    // output

        :   [four]      "m"     (four),     // inputs
            [three]     "m"     (three),
            [radius]    "m"     (radius)

        :   "st"                            // clobbers. Just in case this
                                            // was already in use. Top of fp
                                            // stack.
    );

    return volume;
}

void printBytesAscii(int r, int numBytes) {
    char* c;

    c = (char*) &r;
    for (size_t i = 0; i < numBytes; ++i) {
        printf("%c", *c);
        ++c;
    }
}

void printCpuVendorID() {
    int b;
    int c;
    int d;

    asm(
            "   mov     $0,     %%eax   \n"     // Make %eax 0 so we get
                                                // vendor id in registers
                                                // %ebx, %edx, and %ecx
            "   cpuid                   \n"
            "   movl    %%ebx,  %[b]    \n"     // first part of vendor id
            "   movl    %%edx,  %[d]    \n"     // second part of vendor id
            "   movl    %%ecx,  %[c]    \n"     // third part of vendor id

            :   [b]         "=m"        (b),    // outputs
                [d]         "=m"        (d)
                [c]         "=m"        (c),
            :                                   // inputs

            :   "eax", "ebx", "ecx", "edx"      // clobbers
        );

    printBytesAscii(b, INT_REGISTER_LENGTH);
    printBytesAscii(d, INT_REGISTER_LENGTH);
    printBytesAscii(c, INT_REGISTER_LENGTH);
    puts("");
}

int main(void) {
    printf("Volume of sphere with radius %.3f: %.3f\n",
        RADIUS,
        sphereVolume(RADIUS)
    );
    printCpuVendorID();

    return 0;
}
