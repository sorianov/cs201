#include <stdio.h>

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
                                            // was already in use.
    );

    return volume;
}


int main(void) {
    double r = 4.5;
    printf("Volume of sphere with radius %.3f: %.3f\n", r, sphereVolume(r));

    return 0;
}
