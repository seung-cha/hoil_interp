# Multiple funcions

void function1()
{
    function2(15);
}

void function2(int num)
{
    loop(int i = 0; i < num; i++)
    {
        print("hello!");
    }
}

int main()
{
    function1();
    return 0;
}