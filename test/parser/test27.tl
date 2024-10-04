# Hello world 5 times, using recursion

void PrintHelloWorld(int num)
{
    if(num == 5) return;

    print("Hello World!");
    PrintHelloWorld(num + 1);
}

int main()
{
    PrintHelloWorld(0);
    return 0;
}