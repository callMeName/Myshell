MYshell 用户手册


1. 环境变量

	环境变量就是系统预定义的参数。

	环境变量名可以用到程序里，程序可以获得它的值，根据值决定如何操作，运行，找路径，文件夹等等。

2. 用户名和当前路径
	
	用户名是当前用户的名字。路劲则是用户现在处在的位置。

	在每行myshell程序的开头会出现用户名和当前路径。

	例如：

	[xuyuhao@localhost ~/demo]$		xuyuhao为用户名， ~/demo为当前路径。

3. 程序环境
	
		在linux内核的操作系统上运行。

4. Myshell命令示例


常用命令语法及功能（命令每一个单词或符号间都应该有一个或以上的空格）

　　echo "Hello World!": 将文字内容打印在屏幕上

　　ls: 输出文件列表

　　wc 计算文件行数计算文件中的单词数或字符数

　　cp sourcefile destfile: 文件拷贝

　　mv oldname newname : 重命名文件或移动文件

　　rm file: 删除文件

　　grep 'pattern' file: 在文件内搜索字符串比如：grep 'searchstring' file.txt

　　sort file.txt: 对file.txt文件中的行进行排序

　　expr: 进行数学运算Example: add 2 and 3expr 2 "+" 3

　　find: 搜索文件比如：根据文件名搜索find . -name filename -print

　　basename file: 返回不包含路径的文件名比如： basename /bin/tux将返回 tux

　　dirname file: 返回文件所在路径比如：dirname /bin/tux将返回 /bin

　　head file: 打印文本文件开头几行

　　tail file : 打印文本文件末尾几行

　　cat file.txt: 输出文件内容到标准输出设备（屏幕）上

　　file somefile: 得到文件类型

　　read var: 提示用户输入，并将输入赋值给变量


5. 后台程序执行

　　后台程序执行：后台程序检查每个任务是否具备运行条件，通过一定的调度算法来完成相应的操作。对于实时

性要求特别严格的操作通常由中断来完成，仅在中断服务程序中标记事件的发生，不再做任何工作就退出中断，经

过后台程序的调度，转由前台程序完成事件的处理，这样就不会造成在中断服务程序中处理费时的事件而影响后续

和造成其他中断。

　　＆命令

    当在前台运行某个作业时，终端被该作业占据；而在后台运行作业时，它不会占据终端，可以使用＆命令把作业

放在后台执行。

    格式为：

    命令 & (请注意中间含有空格)

	例如；
		cat file_list >result.txt &

6. I/O 重定向

　　I/O重定向就是重新定义输入输出的接受端，这个接收端可以为其他终端，文件或者应用程序。

　　> 写入文件并覆盖旧文件

　　>> 加到文件的尾部，保留旧文件内容。
	
	< 从文件中读入数据

	例如；
		CMD > file                       把 stdout 重定向到 file 文件中
	  	CMD >> file                      把 stdout 重定向到 file 文件中(追加)
	  	CMD < file1 >file2                cmd 命令以 file1 文件作为 stdin，以 file2 文件作为 stdout


7. 批量文件处理
	myshell命令可以从文件中提取命令输入,并将文件中命令执行。

	这个批处理文件应该包含一组命令集，当到达文件结尾时shell 退出。
	
	如果shell 被调用时没有使用参数，它会在屏幕上显示提示符请求用户输入。

	格式为：

	myshell filename

	例如：
	myshell batchfile 				调用batchfile中文件的命令集


