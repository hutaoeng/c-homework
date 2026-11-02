#include <iostream>
using namespace std;

typedef int DataType;
// 题目给定顺序栈结构体
struct Stack
{
    int top;         // 栈顶下标，栈空时top = -1
    int maxsize;     // 最大容量
    DataType* elements;
};

// 1) 初始化空顺序栈
bool InitStack(Stack &s, int max)
{
    s.elements = new DataType[max];
    if (s.elements == nullptr)
        return false;
    s.maxsize = max;
    s.top = -1;   // 栈空标记
    return true;
}

// 2) 判断栈是否为空
bool StackEmpty(Stack s)
{
    return s.top == -1;
}

// 3) 判断栈是否满
bool StackFull(Stack s)
{
    return s.top == s.maxsize - 1;
}

// 4) 入栈
bool Push(Stack &s, DataType val)
{
    if (StackFull(s))
        return false;
    s.top++;
    s.elements[s.top] = val;
    return true;
}

// 5) 出栈（删除栈顶元素，用参数带出值）
bool Pop(Stack &s, DataType &val)
{
    if (StackEmpty(s))
        return false;
    val = s.elements[s.top];
    s.top--;
    return true;
}

// 6) 获取栈顶元素（只取值，不删除）
bool GetTop(Stack s, DataType &val)
{
    if (StackEmpty(s))
        return false;
    val = s.elements[s.top];
    return true;
}

// 销毁栈（防止内存泄漏，实验可选加上）
void DestroyStack(Stack &s)
{
    delete[] s.elements;
    s.elements = nullptr;
    s.top = -1;
    s.maxsize = 0;
}

// 十进制number转base进制，base∈[2,9]，利用栈
void DecToBase(int number, int base)
{
    if (base < 2 || base > 9)
    {
        cout << "进制base必须在2~9之间！" << endl;
        return;
    }
    if (number == 0)
    {
        cout << "转换结果：0" << endl;
        return;
    }
    Stack st;
    InitStack(st, 100); // 分配足够空间
    int temp = number;
    // 除基取余，余数入栈
    while (temp != 0)
    {
        int rem = temp % base;
        Push(st, rem);
        temp = temp / base;
    }
    cout << number << " 转 " << base << " 进制结果：";
    // 依次出栈输出
    int x;
    while (!StackEmpty(st))
    {
        Pop(st, x);
        cout << x;
    }
    cout << endl;
    DestroyStack(st);
}

int main()
{
    // ===== 栈测试代码 =====
    Stack s;
    InitStack(s, 5);
    cout << "栈是否为空：" << (StackEmpty(s) ? "是" : "否") << endl;
    Push(s, 10);
    Push(s, 20);
    Push(s, 30);
    int topVal;
    GetTop(s, topVal);
    cout << "栈顶元素：" << topVal << endl;
    cout << "栈是否满：" << (StackFull(s) ? "是" : "否") << endl;
    int popVal;
    Pop(s, popVal);
    cout << "出栈元素：" << popVal << endl;
    GetTop(s, topVal);
    cout << "新栈顶：" << topVal << endl;
    DestroyStack(s);

    // ===== 进制转换测试 =====
    DecToBase(15, 2);   // 15转2进制 1111
    DecToBase(20, 8);   // 20转8进制 24
    DecToBase(36, 9);   // 36转9进制 40

    return 0;
}

