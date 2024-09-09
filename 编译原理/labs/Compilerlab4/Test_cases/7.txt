int main() {
    int i = 0;

    while (i < 11) {
        if (i % 3 == 1) {
            i = i + 2;
            println_int(i);
            continue;
        }

        if (i % 2 == 0) {
            println_int(i);
        }

        i = i + 1;
    }
    return 0;
}
