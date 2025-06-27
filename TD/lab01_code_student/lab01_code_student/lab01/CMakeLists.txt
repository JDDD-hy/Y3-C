project(lab01)
# 每次编辑该txt都要reload
add_executable(task1 task1.c) 
# 如果后面要编译到task1中
# 在后面加文件名即可
add_executable(task2 task2_2.c)
# 注意：两个并在一起的文件不能含有多个main函数
# 切换运行的对象：搜索launch，点击相应的文件