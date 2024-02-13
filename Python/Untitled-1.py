def istriangle(a,b,c):
    if a+b>c and a+c>b and b+c>a:
        return 'yes'
    return 'no'
a=float(input("请输入边长a:"))
b=float(input("请输入边长b:"))
c=float(input("请输入边长c:"))
print(istriangle(a,b,c))