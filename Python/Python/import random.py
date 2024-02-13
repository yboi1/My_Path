def jiec(n):
    if n==1 or n==0:
        print("1!=1")
        return 1
    else:
        print(f"{n}!递归到{n-1}!")
        tmp = n*jiec(n-1)
        print(f"{n-1}!回调到{n}!")
        return tmp
n = 5
print(jiec(5))

        

    
