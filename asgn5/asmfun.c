double sphereVolume(double radius) {
    double volume;

    asm(
        "fldl      $3.0             \n"
        "fldl      $4.0             \n"
        "fdivp                    \n"
        "fstpl     %[volume]      \n"
        :   [volume]    "=m"(volume)    // outputs
    );

    return volume;
}

int main(void) {
    double r = 1;
    printf("Volume of sphere with radius %f: %f\n", r, sphereVolume(r));

    return 0;
}
