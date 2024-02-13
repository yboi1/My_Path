# use_age = int(input("请输入你的年龄"))
# print("你十年后的年龄是：")
# print(use_age+10)
# a = int(input("请输入一个数"))
# if a>5 :
#     print(" a > 5")
# else:
#     print(" a < 5")
# import random
# import time
# offices = [[],[],[]]
# name = ['A','B','C','D','E','F','G','H']
# for i in name:
#     offices[int(random.randint(0,2))].append(i)
#     #print(int(random.randint(0,2)))
# for i in offices:
#     print("Group num have : ",i)

# dev_list = []
# print(dev_list)
# dev_list.append("鼠标")
# dev_list.append("键盘")
# dev_list.append("电竞椅")    
# dev_list[1] = "硬盘"
# print(dev_list)
# price={198,2000,300}
# max_price = max(price)
# min_price = min(price)
# Sort_price = sorted(price)
# print(max_price)
# print(min_price)
# print(Sort_price)
# i = 2
# for i in range(5,10,2):
#     print(str(i)+"  ")

#计算机小程序
# sum = 0
# i = 0
# item = input("请输入数字")
# while (item)!='0':
#     sum += int(item)
#     i = i + 1
#     item = input("请输入数字:")
# print(sum/i)

# contacts = []
# info_array.append(2023,"兔","马越")
# for name in contacts:
#     message_content='''祝：{3}
# {0}万事如意
# {0}岁岁平安
# {2}年吉祥
# '''

# contacts = ["老余","老林","老陈"]
# info_array = []
# info_array.append(2023)
# info_array.append("兔")
# year = "兔"
# for name in contacts:
#     message_content='''祝：{2}
#     {0}万事如意
#     {0}岁岁平安
#     {1}年吉祥
#     '''.format(info_array[0],info_array[1],name)
#     print(message_content)

# gpa_dict = {"小明":3.251,"小花":3.869,"小李":2.683,
#             "小张":3.685}
# for name,gpa in gpa_dict.items():
#     print("{0}你好，你的当前绩点为：{1:.2f}".format(name,gpa))

# for name in gpa_dict.values():
#     print(name)

# def func(Weight,Hight):
#     return float(Weight/(Hight**2))

# Weight = float(input("请输入一个体重："))  
# Hight = float(input("请输入一个身高"))
# print(func(Weight,Hight))

#定义一个猫类
# class CuteCat:
#     def __init__(self,cat_name,cat_age,cat_color):
#         self.name = cat_name
#         self.age = cat_age
#         self.color = cat_color

# cat1 = CuteCat("huahua",2,"红色")
# print(f"小猫{cat1.name}的年龄为{cat1.age},花色为{cat1.color}")

#定义一个学生类
# class Score:
#     def __init__(self,Chinese,Math,English):
#         self.Chinese = Chinese
#         self.Math = Math
#         self.English = English

#     def SetScore(self,Chinese,Math,English):
#         self.Chinese = Chinese
#         self.Math = Math
#         self.English = English

#     def PrintScore(self):
#         print(f"语文：{self.Chinese}  数学：{self.Math}  英语：{self.English}")

# class Student:
#     def __init__(self,name,num,score):
#         self.name = name
#         self.num = num
#         self.score = score
#         self.grade = {"语文":0,"数学":0,"英语":0}
#     def Change_Grade(self,Subject,Score):
#         for tmp in self.grade:
#             self.grade[tmp] = Score
        
# student1 = Student("花花",201,Score(60,65,61))
# student1.score.SetScore(99,98,77)
# student1.score.PrintScore()
# print(student1.grade)
# student1.Change_Grade("语文",88)
# student1.Change_Grade("数学",99)
# student1.Change_Grade("英语",96)
# print(student1.grade)


#职工类
class Worker:
    def __init__(self,name,id):
        self.name = name
        self.id = id
    def PrinrNomalInfo(self):
        print(f"name : {self.name} id : {self.id}")

class FullWorker(Worker):
    def __init__(self,name,id,allsalary):
        super().__init__(name,id)
        self.allsalary = allsalary

    def Worker_salary(self):
        return self.allsalary

class DailyWorker(Worker):
    def __init__(self,name,id,dailysalary,day):
        super().__init__(name,id)
        self.dailysalary = dailysalary    
        self.day = day
    def Worker_salary(self):
        return   self.dailysalary*self.day


mark = FullWorker("mark","1001",6000)
ami = DailyWorker("ami","1002",150,15)
print(mark.Worker_salary())
print(ami.Worker_salary())