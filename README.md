# cmd-auto-gen
generate command definition file automatically.

# **C/S 模式命令生成工具**

执行命令 JFCmdParser.exe cmd_def.zdef(file name) -go|-cpp(language)

其中 cmd_def.zdef 为命令描述文件，-go 和 -cpp 为目标代码，目前支持 golang 和 C++

项目使用 flex 词法分析器对命令定义文件进行解析
