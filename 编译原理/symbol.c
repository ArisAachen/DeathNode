
const int a = 0;
static int b = 0;
int c = 0;

int func() {
    static int b = 2;
    return 1;
}


int main() {
    // const 
    const int a = 1;
    // static 
    static int b = 1;
    // 
    int c = 1;
    // 
    int d = 1;

    return 1;
}


