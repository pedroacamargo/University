int mdc2(int a, int b) {
    int c = 0; 
    if (a >= b) {
        a -= b;
    } else if (a <= b) {
        b -= a;
    } else if (a == 0 || b == 0) {
        printf("debug" );
        return c;
    }
}