//simplest example of recursion

function foo(n: number): number {
    //Base case
    if (n <= 1) {
        return 1;
    }
    return n * foo (n - 1);
}