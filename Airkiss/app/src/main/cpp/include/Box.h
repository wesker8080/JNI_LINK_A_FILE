//
// Created by Wesker on 2020/5/25.
//

#ifndef AIRKISS_BOX_H
#define AIRKISS_BOX_H


class Box {
public:
    double getLength() const;

    void setLength(double length);

    double getBreadth() const;

    void setBreadth(double breadth);

    double getHeight() const;

    void setHeight(double height);
    double sumBox();
    // 构造函数
    Box();
    Box(double height, double breadth, double length);
    //析构函数 对象被删除时执行
    ~Box();
    // 拷贝构造函数 在类中没有定义拷贝构造函数，
    // 编译器会自行定义一个。如果类带有指针变量，并有动态内存分配，则它必须有一个拷贝构造函数
    Box(const Box &box);
    // 友元函数 类方法之外，通过函数访问类的私有成员的一种方法声明
    friend double friendSum(Box &box, Box &box1);
private:
    double length;   // 盒子的长度
    double breadth;  // 盒子的宽度
    double height;   // 盒子的高度
    double *ptr;
};

#endif //AIRKISS_BOX_H
