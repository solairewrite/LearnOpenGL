# LearnOpenGL  
##学习书籍: 计算机图形学(第四版)
##VSCode免密上传Git
修改.git->config文件
url = https://[username:password]@github.com/solairewrite/LearnOpenGL.git  
##VS2017+OpenGL环境配置:
**一,下载GLUT包**  
1,压缩包下的5个文件要分别配置3个目录  
2,glut.h: D:\Software\VS2017\Community\VC\Tools\MSVC\14.16.27023\include\gl(没有gl文件夹就创建)  
3,glut.lib, glut32.lib: D:\Software\VS2017\Community\VC\Tools\MSVC\14.16.27023\lib\x86  
4,glut.dll, glut32.dll: C:\Windows\SysWOW64  
**二,新建项目**  
1,安装VS2017时,单个组件->NuGet包管理器(勾选)  
2,新建一个C++->Windows桌面应用程序项目,项目名右键->管理NuGet程序包  
3,点击浏览,搜索nupengl,下载.core .core.redist两个文件  
##各种错误解决
在不同的电脑VS上打开后,编译可能不通过  
需要管理NuGet程序包,重装两个nupengl文件  
##忽略文件
经测试,Debug文件夹和LearnOpenGL/Debug文件夹可以忽略,直接删除后,再次调试会自动生成  