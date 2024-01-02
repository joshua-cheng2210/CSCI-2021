int isLessOrEqual(int x, int y) {
    int sign_x = (x >> 31); // 1 for x < 0; 0 for x >=0
    int sign_y = (x >> 31); // 1 for y < 0; 0 for y >=0
    int sign_diff = sign_x ^ sign_y; // 1 for different signs; 0 for same

    // return (sign_diff ^ !((y + (~x + 1) >> 31)));
    if (sign_diff == 0) {
        return (sign_diff ^ !(((y + (~x + 1)) >> 31)));
    } else {
        // printf("%d\n", sign_diff);
        return (sign_diff & sign_x);
    }

}

// isLessOrEqual(((int)-2147483648), ((int)2147483647));
int x = -2147483648;
int y = 2147483647;
int out = isLessOrEqual(x, y);
// printf("%d\n", isLessOrEqual(x, y));