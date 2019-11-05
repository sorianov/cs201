/**************************************************************************
 * Author: Victor Soriano Mendoza
 * Instructor: Rich Albers
 * Date: 2019-11-04
 * Title: Assignment 5: Embedded Assembly
 *************************************************************************/
#include <stdio.h>

const int INT_REGISTER_LENGTH = 4; // bytes
const double RADIUS = 4.5;

/**
 * Prints the name of the author of this code.
 */
void printAuthor() {
    puts("Author: Victor Soriano Mendoza\n");
}

/**
 * Calculates the volume of a sphere with a given radius.
 *
 * Input:
 * const double radius - The radius to be used in the calculation
 *
 * Return:
 * double volume - The calculated volume of the sphere
 */
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

/**
 *  Given an integer value r, prints the ascii representation of every
 *  byte for numBytes.
 *
 *  Inputs:
 *  int r - The value holding the bytes to be printed
 *  int numBytes - The number of bytes to print of the value r
 *
 *  Outputs:
 *  Prints ascii representation of every byte of r for numBytes.
 */
void printBytesAscii(int r, int numBytes) {
    char* c;

    c = (char*) &r;
    for (size_t i = 0; i < numBytes; ++i) {
        printf("%c", *c);
        ++c;
    }
}

/**
 * Prints the VendorID of the CPU.
 *
 * Outputs:
 * The 12-character VendorId string is printed to the console,
 * along with a newline.
 */
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
                [d]         "=m"        (d),
                [c]         "=m"        (c)
            :                                   // inputs

            :   "eax", "ebx", "ecx", "edx"      // clobbers
        );

    printf("VendorID: ");
    // Each register holds 4 characters. VendorIds
    // are 12 characters.
    printBytesAscii(b, INT_REGISTER_LENGTH);
    printBytesAscii(d, INT_REGISTER_LENGTH);
    printBytesAscii(c, INT_REGISTER_LENGTH);
    puts("");
}

/**
 * Calculates the positive root of a function given variables
 * a, b, and c by using the quadratic formula.
 *
 * Inputs:
 * double a - Quadratic argument a
 * double b - Quadratic argument b
 * double c - Quadratic argument c
 *
 * Return:
 * double posRoot - The positive root result from feeding
 *                  a, b, and c into the quadratic formula.
 */
double quadraticFormula(double a, double b, double c) {
    double posRoot;
    const double four = 4.0;
    double negB = -b;

    // In the comments, the " character has been used to substitute
    // the result from the above line. This was done to keep lines within
    // a width of 80 characters.
    asm(
            "   fld1                    \n  "       // load 1
            "   fld1                    \n  "       // load 1
            "   faddp                   \n  "       // 1 + 1
            "   fldl        %[a]        \n  "       // load a
            "   fmulp                   \n  "       // 2 * a
            "   fldl        %[negB]     \n  "       // load -b
            "   fldl        %[four]     \n  "       // load 4.0
            "   fldl        %[a]        \n  "       // load a
            "   fldl        %[c]        \n  "       // load c
            "   fmulp                   \n  "       // a * c
            "   fmulp                   \n  "       // 4 * (a * c)
            "   fldl        %[b]        \n  "       // load b
            "   fldl        %[b]        \n  "
            "   fmulp                   \n  "       // b^2
            "   fsubp                   \n  "       // " - (4 * (a * c))
            "   fsqrt                   \n  "       // sqrt(")
            "   faddp                   \n  "       // -b + "
            "   fdivp                   \n  "       // " / (2 * a)
            "   fstpl       %[posRoot]  \n  "       // store into posRoot

            :   [posRoot]   "=m"        (posRoot)   // output

            :   [a]         "m"         (a),        // inputs
                [b]         "m"         (b),
                [c]         "m"         (c),
                [four]      "m"         (four),
                [negB]      "m"         (negB)

            :   "st"                                // clobbers


       );

    return posRoot;
}

int main(void) {
    printAuthor();

    printf("Volume of sphere with radius %.3f: %.3f\n\n",
        RADIUS,
        sphereVolume(RADIUS)
    );

    printCpuVendorID();
    puts("");

    printf("Quadratic(+): %.3f\n", quadraticFormula(3, 10, -3));

    return 0;
}
