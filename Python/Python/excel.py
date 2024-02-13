import xlwt
tn = ['姓名', '性别', '年龄']
wb = ['凌华', '女', '18']

work_boot = xlwt.Workbook(encoding='utf-8')

sheet = work_boot.add_sheet('excel')

for i in range(len(wb)):
   sheet.write(0, i, tn[i])
   sheet.write(1, i, wb[i])

work_boot.save("个人信息.xls")



