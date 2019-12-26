//参考：
//https://blog.csdn.net/u011535541/article/details/83379151
//https://www.runoob.com/w3cnote/git-gui-window.html

//Git是目前世界上最先进的分布式版本控制系统。

//工作原理/流程：
//                                        pull(拉，向下拉)
//        +--------------------------------------------->--------------------------+
//        |                                                                        |
//+--------------+   fetch/clone   +---------------+        checkout        +--------------+
//|              |---------------->|               |----------------------->|              |
//|    Remote    |  push(推,向上推) |   Repository  | commit+--------+  add  |   Workspace  |
//|              |<----------------|               |<------| Index  |<------|              |
//+--------------+                 +---------------+       +--------+       +--------------+
//
//	Workspace:工作区
//	Index/Stage:暂存区
//	Repository:仓库(或本地仓库)或版本库
//	Remote:远程仓库

//SVN是集中式版本控制系统，版本库是集中放在中央服务器的，而干活的时候，用的都是自己的电脑，所以首先要从中央服务器哪里得到最新的版本，然后干活，干完后，需要把自己做完的活推送到中央服务器。集中式版本控制系统是必须联网才能工作，如果在局域网还可以，带宽够大，速度够快，如果在互联网下，如果网速慢的话，就纳闷了。

//Git是分布式版本控制系统，那么它就没有中央服务器的，每个人的电脑就是一个完整的版本库，这样，工作的时候就不需要联网了，因为版本都是在自己的电脑上。既然每个人的电脑都有一个完整的版本库，那多个人如何协作呢？比如说自己在电脑上改了文件A，其他人也在电脑上改了文件A，这时，你们两之间只需把各自的修改推送给对方，就可以互相看到对方的修改了

//安装git
//pacman -S git，在mingw的控制台上输入git，可以看到提示信息，说明安装完毕
//(注意，msys2有他自己的git包，不要在msys2下使用msysgit的git)
//(Vim 也会被安装上，配置vim:
//# vim ~/.vimrc
//然后保存退出vim
//# pwd
//查看到.vimrc文件位置，然后用我的_vimrc覆盖此文件
//)
//(顺便提一下，控制台的设置为：locale:zh_CN   Character set:UTF-8)

//(因为msys2下面绝大多数软件均使用utf-8编码，所以建议使用utf-8字符编码。这样就会造成使用windows自带的软件（如ping,ipconfig等）会显示乱码。不用担心，使用iconv进行实时转换编码，例如：
//ping www.cnblogs.com | iconv -f gbk -t utf-8
//即可正常显示中文字符，为了方便使用:
//新建/usr/bin/win：
//#!/bin/bash
//$@ |iconv -f gbk -t utf-8
//新建/etc/profile.d/alias.sh：
//alias ls="/bin/ls --color=tty --show-control-chars"
//alias grep="/bin/grep --color"
//alias ll="/bin/ls --color=tty --show-control-chars -l"

//alias ping="/bin/win ping"
//alias netstat="/bin/win netstat"
//alias nslookup="/bin/win nslookup"
//alias ipconfig="/bin/win ipconfig"
//改完以后需要重启一下 msys2 ，不然还是会乱码
//)




//安装git gui  (可选)   (参考 https://github.com/valtron/llvm-stuff/wiki/Set-up-Windows-dev-environment-with-MSYS2 中的Git部分)
//pacman -S mingw-w64-x86_64-tk
//在环境变量PATH中添加D:\OtherDocuments\msys64\mingw64\bin
//创建环境变量GIT_GUI_LIB_DIR，值为D:\OtherDocuments\msys64\usr\share\git-gui\lib
//然后使用git gui命令，弹出可视化界面，如果只是想看log，那么使用gitk命令

//安装git后的初始化
//执行：(#是提示符，不是手写的命令，下面都一样)

//# git config --global user.name "lei130102"
//# git config --global user.email "lei1301025@gmail.com"

//(注意--global参数表示你这台机器上所有的Git仓库都会使用这个配置，当然你也可以对某个仓库指定的不同的用户名和邮箱)


//(修复git中文乱码:   参考  http://howiefh.github.io/2014/10/11/git-encoding/
//中文乱码的根源在于 windows 基于一些历史原因无法全面支持 utf-8 编码格式，并且也无法通过有效手段令其全面支持

//(git status 和 git diff 编码)
//lei130102@PC-LEI130102 MINGW64 ~
//# git config --global core.quotepath false

//(图形界面编码)
//lei130102@PC-LEI130102 MINGW64 ~
//# git config --global gui.encoding utf-8

//(提交信息编码，即指定git commit后的注释信息的编码格式，如果该格式与注释信息实际的格式(如果是在控制台输入的，那么控制台决定，如果是在vim中输入的，那么vim决定)不一致会提示并且之后会存在问题)
//lei130102@PC-LEI130102 MINGW64 ~
//# git config --global i18n.commit.encoding utf-8

//(输出 log 编码)
//lei130102@PC-LEI130102 MINGW64 ~
//# git config --global i18n.logoutputencoding utf-8

//(因为 git log 默认使用 less 分页，所以需要 bash 对 less 命令进行 utf-8 编码     所有可用的参数详见https://github.com/unofficial-mirror/less/blob/master/charset.c#L35)
//设置环境变量LESSCHARSET为utf-8

//以上命令等效于：
//在 D:\OtherDocuments\msys64\etc\gitconfig 中添加

//[core]
//    quotepath = false
//[gui]
//    encoding = utf-8
//[i18n]
//    commitencoding = utf-8
//    logoutputencoding = utf-8

//在D:\OtherDocuments\msys64\etc\profile 中添加

//export LESSCHARSET=utf-8

//(我建议直接改文件内容)

//)



//1.创建版本库(仓库、Repository)    他可以简单的理解一个目录，这个目录里面的所有文件都可以被Git管理起来，每个文件的修改，删除，Git都能跟踪，以便任何时刻都可以追踪历史，或者在将来某个时刻还可以将文件”还原”
//先指定一个待创建版本库所在目录D:\OtherDocuments\Test\GitTest\Test1(将在该目录下生成.git文件夹，这个目录是Git来跟踪管理版本的，没事千万不要手动乱改这个目录里面的文件，否则，会把git仓库给破坏了)，然后在该目录中创建版本库(即在该目录中创建.git目录)

//(设置当前目录，注意是/分割)
//# cd D:/OtherDocuments/Test/GitTest/Test1
//(pwd用来显示当前路径，d后面没有:并且用/分割都是正确的)
//# pwd
///d/OtherDocuments/Test/GitTest/Test1
//(必要的话，还需要使用mkdir创建目录)
//# git init
//已初始化空的 Git 仓库于 /d/OtherDocuments/Test/GitTest/Test1/.git/
//(当前目录下会多了一个.git的目录，这个目录是Git来跟踪管理版本的，没事千万不要手动乱改这个目录里面的文件，否则，会把git仓库给破坏了)




//2.把版本库同目录下文件添加到版本库(仓库、Repository)，简称提交文件      首先要明确下，所有的版本控制系统，只能跟踪文本文件的改动，比如txt文件，网页，所有程序的代码等，Git也不列外，版本控制系统可以告诉你每次的改动，但是图片，视频这些二进制文件，虽能也能由版本控制系统管理，但没法跟踪文件的变化，只能把二进制文件每次改动串起来，也就是知道图片从1kb变成2kb，但是到底改了啥，版本控制也不知道
//先将创建好的step.cpp文件添加到(add)暂存区(Index)(注意是暂存区(Index))，然后提交到(commit)版本库中

//(没有任何提示，说明已经添加成功了，如果同时添加多个文件那么用空格隔开，比如git add step1.cpp step2.cpp)
//# git add step.cpp
//(参数-m表示后面跟提交注释)
//# git commit -m "提交step.cpp文件"
//(上面也可以通过git commit -a -m "提交step.cpp文件"这一步完成)
//[master（根提交） 337bfbc] 提交step.cpp文件
// 1 file changed, 0 insertions(+), 0 deletions(-)
// create mode 100644 step.cpp



//3.修改提交文件，查看是否有没有提交的，检查修改了什么
//先修改step.cpp文件，查看是否有没有提交的，检查修改了什么

//(查看是否有没有提交的，发现step.cpp修改后没有提交(commit)，并且也没有暂存(add))
//# git status
//位于分支 master
//尚未暂存以备提交的变更：
//  （使用 "git add <文件>..." 更新要提交的内容）
//  （使用 "git checkout -- <文件>..." 丢弃工作区的改动）

//        修改：     step.cpp

//未跟踪的文件:
//  （使用 "git add <文件>..." 以包含要提交的内容）

//        CMakeLists.txt
//        CMakeLists.txt.user
//        main.cpp

//修改尚未加入提交（使用 "git add" 和/或 "git commit -a"）
//(查看step.cpp修改了什么内容，在@@ -0,0 +1 @@下面可以看到删除了一个空行，添加了一行注释)
//# git diff step.cpp
//diff --git a/step.cpp b/step.cpp
//index d3f5a12..90a6b8f 100644
//--- a/step.cpp
//+++ b/step.cpp
//@@ -1 +1 @@
//-
//+//添加一条注释^M




//4.修改之前提交的文件，然后再添加到版本库(仓库、Repository)，简称提交修改       提交修改和提交文件是一样的2步
//先将修改好的step.cpp文件添加到(add)暂存区(Index)(注意是暂存区(Index))，然后提交到(commit)版本库中

//(没有任何提示，说明已经添加成功了)
//# git add step.cpp

//(这时也可以看看状态，发现变成"要提交的变更"，并且"修改：step.cpp"变成绿色)
//# git status
//位于分支 master
//要提交的变更：
//  （使用 "git reset HEAD <文件>..." 以取消暂存）

//        修改：     step.cpp

//未跟踪的文件:
//  （使用 "git add <文件>..." 以包含要提交的内容）

//        CMakeLists.txt
//        CMakeLists.txt.user
//        main.cpp

//# git commit -m "删除一空行，增加一条注释"
//[master 1a68df7] 删除一空行，增加一条注释
// 1 file changed, 1 insertion(+), 1 deletion(-)

//(这时也可以看看状态，发现没有要提交的变更了)
//# git status
//位于分支 master
//未跟踪的文件:
//  （使用 "git add <文件>..." 以包含要提交的内容）

//        CMakeLists.txt
//        CMakeLists.txt.user
//        main.cpp

//提交为空，但是存在尚未跟踪的文件（使用 "git add" 建立跟踪）



//5.重复4

//# git add step.cpp
//# git commit -m "又增加一条注释"
//[master d1b1e93] 又增加一条注释
// 1 file changed, 1 insertion(+)

//6.查看历史记录
//之前对step.cpp进行了三次修改(第一次修改就是提交文件)

//(commit后面是提交的版本号，从最近到最远的显示日志，我们可以看到最近三次提交，注意，添加(add)是针对某个文件的，提交(commit)是针对所有文件的，这里只有提交的记录，所以一条记录是若干个文件的创建或者修改)
//# git log
//commit bfa8beb05e40a4688850c9cf46cec5aaa624c43a (HEAD -> master)
//Author: lei130102 <lei1301025@gmail.com>
//Date:   Wed Dec 25 22:35:46 2019 +0800

//    又增加一条注释

//commit 1a68df78672b6937a9279a4d8082ce17ab659f0e
//Author: lei130102 <lei1301025@gmail.com>
//Date:   Wed Dec 25 22:34:37 2019 +0800

//    删除一空行，增加一条注释

//commit 3624123af16206bf448c40d1c5a80f5557c329d9
//Author: lei130102 <lei1301025@gmail.com>
//Date:   Wed Dec 25 22:31:25 2019 +0800

//    提交step.cpp文件


//(如果嫌上面显示的信息太多的话，我们可以使用命令 git log --pretty=oneline)
//# git log --pretty=oneline
//bfa8beb05e40a4688850c9cf46cec5aaa624c43a (HEAD -> master) 又增加一条注释
//1a68df78672b6937a9279a4d8082ce17ab659f0e 删除一空行，增加一条注释
//3624123af16206bf448c40d1c5a80f5557c329d9 提交step.cpp文件

//(在msys2中可以使用gitk查看历史，这个工具的部署方式：(详见 https://github.com/valtron/llvm-stuff/wiki/Set-up-Windows-dev-environment-with-MSYS2 中的Git部分)
//运行 pacman -S mingw-w64-x86_64-tk
//条件 $DEV/msys64/mingw64/bin到$PATH)
//# gitk
//(弹出可视化界面)




//7.版本回退

//回退到上一个版本
//# git reset --hard HEAD^
//HEAD 现在位于 1a68df7 删除一空行，增加一条注释
//(查看step.cpp文件，已经发生变化)

//获取所有版本号，根据版本号回到最新版本
//# git reflog
//1a68df7 (HEAD -> master) HEAD@{0}: reset: moving to HEAD^
//bfa8beb HEAD@{1}: commit: 又增加一条注释
//1a68df7 (HEAD -> master) HEAD@{2}: commit: 删除一空行，增加一条注释
//3624123 HEAD@{3}: commit (initial): 提交step.cpp文件
//(通过上面，可以知道最新版本号是bfa8beb)
//# git reset --hard bfa8beb
//HEAD 现在位于 bfa8beb 又增加一条注释
//(查看step.cpp文件，已经发生变化)

//回退到上上个版本
//# git reset --hard HEAD^^
//然后再按照上面的方法恢复

//如果回退到前100个版本，那么
//# git reset --hard HEAD~100




//8.重新梳理一遍概念

//工作区：就是D:\OtherDocuments\Test\GitTest\Test1目录下的除了.git之外的所有(以后需要再新建的目录文件等等都属于工作区范畴)

//版本库：工作区中的.git目录和里面的东西就是版本库。其中版本库里面存了很多东西，其中最重要的就是stage(暂存区)，还有git为我们自动创建了第一个分支master以及指向master的一个指针HEAD

//前面说过使用git提交文件到版本库有两步：
//1.使用 git add 把文件添加进去，实际上就是把文件添加到暂存区
//2.使用 git commit 提交更改，实际上就是把暂存区的所有内容提交到当前分支上

//创建一个step2.cpp文件并且修改step.cpp文件，查看状态，然后把他们提交到版本库
//# git status
//位于分支 master
//尚未暂存以备提交的变更：
//  （使用 "git add <文件>..." 更新要提交的内容）
//  （使用 "git checkout -- <文件>..." 丢弃工作区的改动）

//        修改：     step.cpp

//未跟踪的文件:
//  （使用 "git add <文件>..." 以包含要提交的内容）

//        CMakeLists.txt
//        CMakeLists.txt.user
//        main.cpp
//        step2.cpp

//修改尚未加入提交（使用 "git add" 和/或 "git commit -a"）
//(在“尚未暂存以备提交的变更”中看到“修改：     step.cpp”，提示使用 "git add <文件>..." 更新要提交的内容)
//(在“未跟踪的文件”中看到“step2.cpp”，提示使用 "git add <文件>..." 以包含要提交的内容)
//# git add step.cpp
//# git add step2.cpp
//(这样两个文件都添加到暂存区中，再使用git status来查看下状态)
//# git status
//位于分支 master
//要提交的变更：
//  （使用 "git reset HEAD <文件>..." 以取消暂存）

//        修改：     step.cpp
//        新文件：   step2.cpp

//未跟踪的文件:
//  （使用 "git add <文件>..." 以包含要提交的内容）

//        CMakeLists.txt
//        CMakeLists.txt.user
//        main.cpp
//        main.cpp.autosave
//(接着可以使用git commit一次性提交到分支上)
//# git commit -m "修改step.cpp；添加step2.cpp"
//[master 7d4bfa5] 修改step.cpp；添加step2.cpp
// 2 files changed, 1 insertion(+)
// create mode 100644 step2.cpp




//9.撤销文件修改

//方法1：
//如果知道要删掉那些内容的话，那么直接手动更改去掉那些需要的文件，然后add添加到暂存区，最后commit掉

//方法2：
//可以按以前的方法直接恢复到上一个版本。使用 git reset --hard HEAD^

//方法3：
//修改step2.cpp文件中内容并保存，使用git status查看下当前的状态
//# git status
//位于分支 master
//尚未暂存以备提交的变更：
//  （使用 "git add <文件>..." 更新要提交的内容）
//  （使用 "git checkout -- <文件>..." 丢弃工作区的改动）

//        修改：     step2.cpp

//未跟踪的文件:
//  （使用 "git add <文件>..." 以包含要提交的内容）

//        CMakeLists.txt
//        CMakeLists.txt.user
//        main.cpp
//        main.cpp.autosave

//修改尚未加入提交（使用 "git add" 和/或 "git commit -a"）
//(在“尚未暂存以备提交的变更”中看到“修改：     step2.cpp”，提示使用 "git checkout -- <文件>..." 丢弃工作区的改动)
//# git checkout -- step2.cpp
//(没有任何提示)
//(git checkout -- step2.cpp的意思是把step2.cpp文件在工作区做的修改全部撤销，这里有两种情况：
//1.step2.cpp修改后还没有add(即还没有放到暂存区中)，这样就回到和版本库一模一样的状态
//2.step2.cpp修改后已经add(即已经放到暂存区中)，接着又做了修改，这样就回到和暂存区一模一样的状态
//)

//现在验证一下第二种情况：(一开始称为状态A，也就是与版本库中的step2.cpp一致)，修改step2.cpp并保存(称为状态B)，然后git add step2.cpp，再修改step2.cpp并保存(称为状态C)，然后git checkout -- step2.cpp
//(状态A，同版本库)
//修改文件
//(状态B，即将同暂存区)
//# git status
//位于分支 master
//尚未暂存以备提交的变更：
//  （使用 "git add <文件>..." 更新要提交的内容）
//  （使用 "git checkout -- <文件>..." 丢弃工作区的改动）

//        修改：     step2.cpp

//未跟踪的文件:
//  （使用 "git add <文件>..." 以包含要提交的内容）

//        CMakeLists.txt
//        CMakeLists.txt.user
//        main.cpp

//修改尚未加入提交（使用 "git add" 和/或 "git commit -a"）
//# git add step2.cpp
//# git status
//位于分支 master
//要提交的变更：
//  （使用 "git reset HEAD <文件>..." 以取消暂存）

//        修改：     step2.cpp

//未跟踪的文件:
//  （使用 "git add <文件>..." 以包含要提交的内容）

//        CMakeLists.txt
//        CMakeLists.txt.user
//        main.cpp
//修改文件
//(状态C)
//# git status
//位于分支 master
//要提交的变更：
//  （使用 "git reset HEAD <文件>..." 以取消暂存）

//        修改：     step2.cpp                               注意！！！这是暂存区的版本，也就是第二新的版本，第三新也就是最旧版本是版本库中的版本

//尚未暂存以备提交的变更：
//  （使用 "git add <文件>..." 更新要提交的内容）
//  （使用 "git checkout -- <文件>..." 丢弃工作区的改动）

//        修改：     step2.cpp                               注意！！！这是最新的修改版本

//未跟踪的文件:
//  （使用 "git add <文件>..." 以包含要提交的内容）

//        CMakeLists.txt
//        CMakeLists.txt.user
//        main.cpp
//# git checkout -- step2.cpp
//(注意，这时是状态B！！！还是丢弃工作区的改动，只不过因为有第二新版本，所以使用第二新版本)
//(
//稍微总结一下：
//  正过程                                                                      反过程
//修改、删除(注意没有添加)工作区中之前已经git add的文件                       git checkout -- <文件>  (有暂存区版本用暂存区版本，没有就用版本库的版本)
// git add/git rm                                                       git reset HEAD <文件>   (注意git rm会删除文件，但反过程不会恢复该文件，还需要再进行git checkout -- <文件>)
//)


//(注意，命令git checkout -- step2.cpp 中的 -- 很重要，如果没有 -- 的话，那么命令变成创建分支了！！！)




//10.删除文件

//a.首选准备文件，在工作区创建一个delete.txt文件然后提交

//# git status
//位于分支 master
//要提交的变更：
//  （使用 "git reset HEAD <文件>..." 以取消暂存）

//        修改：     step2.cpp

//未跟踪的文件:
//  （使用 "git add <文件>..." 以包含要提交的内容）

//        CMakeLists.txt
//        CMakeLists.txt.user
//        delete.txt
//        main.cpp
//(发现delete.txt是未跟踪的文件)
//# git add delete.txt
//# git commit -m "添加delete.txt"
//[master b539e90] 添加delete.txt
// 2 files changed, 1 insertion(+)
// create mode 100644 delete.txt

//b.删除delete.txt文件，然后git status查看状态
//# git status
//位于分支 master
//尚未暂存以备提交的变更：
//  （使用 "git add/rm <文件>..." 更新要提交的内容）
//  （使用 "git checkout -- <文件>..." 丢弃工作区的改动）

//        删除：     delete.txt

//未跟踪的文件:
//  （使用 "git add <文件>..." 以包含要提交的内容）

//        CMakeLists.txt
//        CMakeLists.txt.user
//        main.cpp

//修改尚未加入提交（使用 "git add" 和/或 "git commit -a"）
//(观察到“删除：     delete.txt”)

//c1.从版本库中恢复此文件
//# git checkout -- delete.txt
//(观察到工作区又有了delete.txt文件)

//c2.删除版本库中的该文件，两步git rm和git commit
//# git rm delete.txt     注意!!!如果文件之前没有删除，那么该命令也会删除文件
//rm 'delete.txt'
//# git status
//位于分支 master
//要提交的变更：
//  （使用 "git reset HEAD <文件>..." 以取消暂存）

//        删除：     delete.txt

//未跟踪的文件:
//  （使用 "git add <文件>..." 以包含要提交的内容）

//        CMakeLists.txt
//        CMakeLists.txt.user
//        main.cpp
//        main.cpp.autosave
//# git commit -m "删除delete.txt"
//[master 68de832] 删除delete.txt
// 1 file changed, 0 insertions(+), 0 deletions(-)
// delete mode 100644 delete.txt

//c3.如果git rm delete.txt后又创建了一个其他内容的delete.txt，(此时git checkout -- delete.txt没用，因为他只针对之前进行git add后的文件修改内容丢弃)，git add delete.txt会将暂存区中的"删除delete.txt提交"改为"修改delete.txt提交"





//11.远程仓库
//先注册github账号，由于你的本地Git仓库和github仓库之间的传输是通过SSH加密的，所以需要一点设置：
//第一步：创建SSH Key。在用户主目录下，看看有没有.ssh目录，如果有，再看看这个目录下有没有id_rsa和id_rsa.pub这两个文件，如果有的话，直接跳过此如下命令，如果没有的话，打开命令行，输入如下命令：
//ssh-keygen -t rsa –C “youremail@example.com”
//(id_rsa是私钥，不能泄露出去，id_rsa.pub是公钥，可以放心地告诉任何人)
//# ssh-keygen -t rsa -C "lei1301025@gmail.com"
//Generating public/private rsa key pair.
//Enter file in which to save the key (/home/lei130102/.ssh/id_rsa):
//Created directory '/home/lei130102/.ssh'.
//Enter passphrase (empty for no passphrase):
//Enter same passphrase again:
//Your identification has been saved in /home/lei130102/.ssh/id_rsa.
//Your public key has been saved in /home/lei130102/.ssh/id_rsa.pub.
//The key fingerprint is:
//SHA256:tfqRADi7umaIk41vLcV0Wb28bJK8zXvAFBDAiFbGdAg lei1301025@gmail.com
//The key's randomart image is:
//+---[RSA 3072]----+
//|  E*++o.o+       |
//|  o.+o. . o      |
//| .  o .o ..o     |
//|    .oo. .+.     |
//|   o.. .S=..     |
//|    o.  +o*.     |
//|.= o.   .*o.     |
//|* *..   ..o..    |
//| *+o      oo     |
//+----[SHA256]-----+

//将D:\OtherDocuments\msys64\home\lei130102\.ssh目录裁剪到C:\Users\lei130102\.ssh保留，并做好备份工作

//第二步：登录github,打开“settings”中的SSH Keys页面，然后点击“Add SSH Key”,填上任意title，在Key文本框里黏贴id_rsa.pub文件的内容


//如何添加远程库？
//现在的情景是：我们已经在本地创建了一个git仓库后，又想在github创建一个git仓库，并且希望这两个仓库进行远程同步，这样github的仓库可以作为备份，又可以其他人通过该仓库来协作。

//首先，登录github上，然后在右上角找到“create a new repo”创建一个新的仓库
//在Repository name填入Test1，其他保持默认设置，点击“Create repository”按钮，就成功地创建了一个新的Git仓库

//现在，我们根据GitHub的提示，在本地的Test1仓库下运行命令：
//# cd D:/OtherDocuments/Test/GitTest/Test1
//# pwd
///d/OtherDocuments/Test/GitTest/Test1
//# git remote add origin https://github.com/lei130102/Test1.git
//把本地库的内容推送到远程，使用 git push命令，实际上是把当前分支master推送到远程。
//# git push -u origin master
//Username for 'https://github.com':
//Password for 'https://lei130102@github.com':
//枚举对象: 24, 完成.
//对象计数中: 100% (24/24), 完成.
//使用 12 个线程进行压缩
//压缩对象中: 100% (15/15), 完成.
//写入对象中: 100% (24/24), 2.07 KiB | 235.00 KiB/s, 完成.
//总共 24 （差异 1），复用 0 （差异 0）
//remote: Resolving deltas: 100% (1/1), done.
//To https://github.com/lei130102/Test1.git
// * [new branch]      master -> master
//分支 'master' 设置为跟踪来自 'origin' 的远程分支 'master'。

//由于远程库是空的，我们第一次推送master分支时，加上了 –u参数，git不但会把本地的master分支内容推送到远程新的master分支，还会把本地的master分支和远程的master分支关联起来，在以后的推送或者拉取时就可以简化命令。推送成功后，可以立刻在github页面中看到远程库的内容已经和本地一模一样了

//从现在起，只要本地作了提交，就可以通过如下命令：
//git push origin master
//把本地master分支的最新修改推送到github上了，现在你就拥有了真正的分布式版本库了。




//如何从远程库克隆？
//现在我们想，假如远程库有新的内容了，我想克隆到本地来
//首先，登录github，创建一个新的仓库，名字叫Test2，勾选Initialize this repository with a README，会自动生成README.md文件
//现在，远程库已经准备好了，下一步是使用命令git clone克隆一个本地库了
//(注意，不需要手动创建Test2文件夹)
//# cd D:/OtherDocuments/Test/GitTest
//# git clone https://github.com/lei130102/Test2.git
//正克隆到 'Test2'...
//remote: Enumerating objects: 3, done.
//remote: Counting objects: 100% (3/3), done.
//remote: Total 3 (delta 0), reused 0 (delta 0), pack-reused 0
//展开对象中: 100% (3/3), 完成.





//12.创建和合并分支
//每次提交，git都把它们串成一条时间线，这条时间线就是一个分支。截止到目前，只有一条时间线，在git里，这个分支叫主分支，即master分支。
//HEAD严格来说不是指向提交，而是指向master，master才是指向提交的，所以，HEAD指向的就是当前分支

//创建dev分支，然后切换到dev分支上
//# cd D:/OtherDocuments/Test/GitTest/Test1
//# git checkout -b dev
//D       abc.txt
//切换到一个新分支 'dev'

//(git checkout 命令加上 –b参数表示创建并切换，相当于如下2条命令
//git branch dev
//git checkout dev)

//查看当前分支，会列出所有的分支，当前分支前面会添加一个星号
//# git branch
//* dev
//  master

//修改step2.cpp，然后提交
//# git status
//位于分支 dev
//尚未暂存以备提交的变更：
//  （使用 "git add/rm <文件>..." 更新要提交的内容）
//  （使用 "git checkout -- <文件>..." 丢弃工作区的改动）

//        修改：     step2.cpp

//未跟踪的文件:
//  （使用 "git add <文件>..." 以包含要提交的内容）

//        CMakeLists.txt
//        CMakeLists.txt.user
//        main.cpp

//修改尚未加入提交（使用 "git add" 和/或 "git commit -a"）
//# git add step2.cpp
//# git commit -m "dev分支上增加内容//@@@@@@@@"
//[dev 54818dc] dev分支上增加内容//@@@@@@@@
// 1 file changed, 1 insertion(+)

//现在dev分支工作已完成，现在我们切换到主分支master上，继续查看readme.txt内容如下：
//# git checkout master
//切换到分支 'master'
//您的分支与上游分支 'origin/master' 一致。

//现在我们可以在master分支上把dev分支上的内容合并到分支master上了
//# git merge dev
//更新 8701e74..54818dc
//Fast-forward
// step2.cpp | 1 +
// 1 file changed, 1 insertion(+)

//合并完成后，我们可以接着删除dev分支了
//# git branch -d dev
//已删除分支 dev（曾为 54818dc）。
//# git branch
//* master

//到此稍微总结一下：
//查看分支：git branch
//创建分支：git branch name
//切换分支：git checkout name
//创建+切换分支：git checkout –b name
//合并某分支到当前分支：git merge name
//删除分支：git branch –d name




//如何解决冲突？
//现在fenzhi1中修改并提交
//# git checkout -b fenzhi1
//切换到一个新分支 'fenzhi1'
//# git branch
//* fenzhi1
//  master
//(修改step2.cpp)
//# git status
//位于分支 fenzhi1
//尚未暂存以备提交的变更：
//  （使用 "git add <文件>..." 更新要提交的内容）
//  （使用 "git checkout -- <文件>..." 丢弃工作区的改动）

//        修改：     step2.cpp

//未跟踪的文件:
//  （使用 "git add <文件>..." 以包含要提交的内容）

//        CMakeLists.txt
//        CMakeLists.txt.user
//        main.cpp

//修改尚未加入提交（使用 "git add" 和/或 "git commit -a"）
//  # git add step2.cpp
//  # git commit -m "添加//1111111111...."
//  [fenzhi1 0ab4206] 添加//1111111111....
//   1 file changed, 1 insertion(+)

//再回到master分支中修改原处并提交
//# git checkout master
//切换到分支 'master'
//您的分支领先 'origin/master' 共 1 个提交。
//  （使用 "git push" 来发布您的本地提交）
//# git branch
//  fenzhi1
//* master
//(原处修改step2.cpp)
//# git add step2.cpp
//# git commit -m "添加//22222222...."
//[master fe2d9bc] 添加//22222222....
// 1 file changed, 1 insertion(+)

//现在我们需要在master分支上来合并fenzhi1
//# git merge fenzhi1
//自动合并 step2.cpp
//冲突（内容）：合并冲突于 step2.cpp
//自动合并失败，修正冲突然后提交修正的结果。
//# git status
//位于分支 master
//您的分支领先 'origin/master' 共 2 个提交。
//  （使用 "git push" 来发布您的本地提交）

//您有尚未合并的路径。
//  （解决冲突并运行 "git commit"）
//  （使用 "git merge --abort" 终止合并）

//未合并的路径：
//  （使用 "git add <文件>..." 标记解决方案）

//        双方修改：   step2.cpp

//未跟踪的文件:
//  （使用 "git add <文件>..." 以包含要提交的内容）

//        CMakeLists.txt
//        CMakeLists.txt.user
//        main.cpp

//修改尚未加入提交（使用 "git add" 和/或 "git commit -a"）

//查看step2.cpp内容
////%%%%%%%%%%%%%%%%%%%%%
////-------------------
////@@@@@@@@@@@@@@@@@@
//<<<<<<< HEAD
////22222222222222222222
//=======
////111111111111111111111
//>>>>>>> fenzhi1
//git用<<<<<<<，=======，>>>>>>>标记出不同分支的内容，其中<<<HEAD是指主分支修改的内容，>>>>>fenzhi1 是指fenzhi1上修改的内容
//手动修改step2.cpp为
////%%%%%%%%%%%%%%%%%%%%%
////-------------------
////@@@@@@@@@@@@@@@@@@
////33333333333333333333
//然后提交
//# git add step2.cpp
//# git commit -m "conflict fixed"
//[master f37d763] conflict fixed
//如果我想查看分支合并的情况的话，需要使用命令 git log
//# git log
//commit f37d763bba591b25b4d233dfeb6b232bc7f86c7f (HEAD -> master)
//Merge: fe2d9bc 0ab4206                                                     (注意这一行)
//Author: lei130102 <lei1301025@gmail.com>
//Date:   Thu Dec 26 10:56:15 2019 +0800

//    conflict fixed

//commit fe2d9bca71188d1100e3209dfbce502e43bb0a4d
//Author: lei130102 <lei1301025@gmail.com>
//Date:   Thu Dec 26 10:47:04 2019 +0800

//    添加//22222222....

//commit 0ab4206eddef7a589accc31201955f892fc43259 (fenzhi1)                  (标明了分支)
//Author: lei130102 <lei1301025@gmail.com>
//Date:   Thu Dec 26 10:42:13 2019 +0800

//    添加//1111111111....





//分支管理策略

//通常合并分支时，git一般使用”Fast forward”模式，在这种模式下，删除分支后，会丢掉分支信息，现在我们来使用带参数--no-ff来禁用”Fast forward”模式
//# git checkout -b dev
//切换到一个新分支 'dev'
//# git status
//位于分支 dev
//尚未暂存以备提交的变更：
//  （使用 "git add <文件>..." 更新要提交的内容）
//  （使用 "git checkout -- <文件>..." 丢弃工作区的改动）

//        修改：     step2.cpp

//未跟踪的文件:
//  （使用 "git add <文件>..." 以包含要提交的内容）

//        CMakeLists.txt
//        CMakeLists.txt.user
//        main.cpp

//修改尚未加入提交（使用 "git add" 和/或 "git commit -a"）
//# git add step2.cpp
//  # git commit -m "add merge"
//  [dev db39667] add merge
//   1 file changed, 1 insertion(+)
//# git checkout master
//切换到分支 'master'
//您的分支领先 'origin/master' 共 4 个提交。
//  （使用 "git push" 来发布您的本地提交）
//(合并dev分支，--no-ff表示禁用fast forward)
//# git merge dev --no-ff -m "merge with no-ff"
//Merge made by the 'recursive' strategy.
// step2.cpp | 1 +
// 1 file changed, 1 insertion(+)
//(删除dev分支)
//# git branch -d dev
//已删除分支 dev（曾为 db39667）。                       (版本号db39667)
//# git branch
//  fenzhi1                                           (被删除的分支信息还在)
//* master
//# git log --graph --pretty=oneline --abbrev-commit
//*   c123f7f (HEAD -> master) merge with no-ff
//|\
//| * db39667 add merge                                (版本号db39667)
//|/
//*   f37d763 conflict fixed
//|\
//| * 0ab4206 (fenzhi1) 添加//1111111111....
//* | fe2d9bc 添加//22222222....
//|/
//* 54818dc dev分支上增加内容//@@@@@@@@
//* 8701e74 (origin/master) 空
//* 075e604 空
//* 68de832 删除delete.txt
//* b539e90 添加delete.txt
//* 7d4bfa5 修改step.cpp；添加step2.cpp
//* bfa8beb 又增加一条注释
//* 1a68df7 删除一空行，增加一条注释
//* 3624123 提交step.cpp文件

//分支策略：首先master主分支应该是非常稳定的，也就是用来发布新版本，一般情况下不允许在上面干活，干活一般情况下在新建的dev分支上干活，干完后，比如要发布，或者说dev分支代码稳定后可以合并到主分支master上来

//bug分支：在开发中，会经常碰到bug问题，那么有了bug就需要修复，在git中，分支是很强大的，每个bug都可以通过一个临时分支来修复，修复完成后，合并分支，然后将临时的分支删除掉。

//# git checkout -b dev
//切换到一个新分支 'dev'
//# git status
//位于分支 dev
//未跟踪的文件:
//  （使用 "git add <文件>..." 以包含要提交的内容）

//        CMakeLists.txt
//        CMakeLists.txt.user
//        main.cpp

//提交为空，但是存在尚未跟踪的文件（使用 "git add" 建立跟踪）
//因开发而修改文件
//# git status
//位于分支 dev
//尚未暂存以备提交的变更：
//  （使用 "git add <文件>..." 更新要提交的内容）
//  （使用 "git checkout -- <文件>..." 丢弃工作区的改动）

//        修改：     step2.cpp

//未跟踪的文件:
//  （使用 "git add <文件>..." 以包含要提交的内容）

//        CMakeLists.txt
//        CMakeLists.txt.user
//        main.cpp

//修改尚未加入提交（使用 "git add" 和/或 "git commit -a"）
//这时发现一个bug需要修改，但因开放而做的修改还没有提交
//那么将当前工作现场隐藏起来，开发的修改不见了
//# /bin/win git stash
//保存工作目录和索引状态 WIP on dev: c123f7f merge with no-ff
//这时查看状态，是干净的
//# git status
//位于分支 dev
//未跟踪的文件:
//  （使用 "git add <文件>..." 以包含要提交的内容）

//        CMakeLists.txt
//        CMakeLists.txt.user
//        main.cpp

//提交为空，但是存在尚未跟踪的文件（使用 "git add" 建立跟踪）
//通过创建issue-404分支来修复bug，首先我们要确定在哪个分支上修复bug，比如我现在是在主分支master上来修复的，现在我要在master分支上创建一个临时分支
//# git checkout -b issue-404
//切换到一个新分支 'issue-404'
//然后修复bug，提交
//# git add step2.cpp
//# git commit -m "fix bug 404"
//[issue-404 d6fff54] fix bug 404
// 1 file changed, 1 insertion(+), 1 deletion(-)
//修复完成后，切换到master分支上，并完成合并，最后删除issue-404分支
//# git checkout master
//切换到分支 'master'
//您的分支领先 'origin/master' 共 6 个提交。
//  （使用 "git push" 来发布您的本地提交）
//# git merge issue-404 --no-ff -m "merge bug fix 404"
//Merge made by the 'recursive' strategy.
// step2.cpp | 2 +-
// 1 file changed, 1 insertion(+), 1 deletion(-)
//# git branch -d issue-404
//已删除分支 issue-404（曾为 d6fff54）。
//现在，我们回到dev分支上干活了
//# git checkout dev
//切换到分支 'dev'
//# git status
//位于分支 dev
//未跟踪的文件:
//  （使用 "git add <文件>..." 以包含要提交的内容）

//        CMakeLists.txt
//        CMakeLists.txt.user
//        main.cpp
//        main.cpp.autosave

//提交为空，但是存在尚未跟踪的文件（使用 "git add" 建立跟踪）
//工作区是干净的，那么我们工作现场去哪里呢？我们可以使用命令 git stash list来查看下
//# git stash list
//stash@{0}: WIP on dev: c123f7f merge with no-ff
//工作现场还在，git把stash内容存在某个地方了，但是需要恢复一下，可以使用如下2个方法
//a.git stash apply恢复，恢复后，stash内容并不删除，你需要使用命令git stash drop来删除。
//b.另一种方式是使用git stash pop,恢复的同时把stash内容也删除了
//# git stash apply
//位于分支 dev
//尚未暂存以备提交的变更：
//  （使用 "git add <文件>..." 更新要提交的内容）
//  （使用 "git checkout -- <文件>..." 丢弃工作区的改动）

//        修改：     step2.cpp

//未跟踪的文件:
//  （使用 "git add <文件>..." 以包含要提交的内容）

//        CMakeLists.txt
//        CMakeLists.txt.user
//        main.cpp
//        main.cpp.autosave

//修改尚未加入提交（使用 "git add" 和/或 "git commit -a"）
//(查看到有一个)
//# git stash list
//stash@{0}: WIP on dev: c123f7f merge with no-ff
//(删除)
//# /bin/win git stash drop
//丢弃了 refs/stash@{0} (3f77cdc1ef8cd64c2cfb3431bb4e66bcb53627db)
//(这次没有了)
//# git stash list


//(
//git stash和git stash drop命令提示信息乱码解决方法：
//一种是使用/bin/win
//另一种是在文件D:\OtherDocuments\msys64\etc\profile.d\alias.sh中添加如下信息

//function git()
//{
//	if [ "$1" = "stash" -a "$2" = "drop" ]; then
//		command /bin/win git "$@"
//	elif [ "$1" = "stash" ]; then
//		command /bin/win git "$@"
//	else
//		command git "$@"
//	fi
//}
//语法参考https://www.cnblogs.com/skywang12345/archive/2013/05/30/3106570.html#a5
//)




//多人协作
//当你从远程库克隆时候，实际上git自动把本地的master分支和远程的master分支对应起来了，并且远程库的默认名称是origin

//要查看远程库的信息 使用 git remote
//# git remote
//origin

//要查看远程库的详细信息 使用 git remote –v
//# git remote -v
//origin  https://github.com/lei130102/Test1.git (fetch)         抓取
//origin  https://github.com/lei130102/Test1.git (push)          推送




//推送分支
//推送分支就是把该分支上所有本地提交到远程库中，推送时，要指定本地分支，这样，Git就会把该分支推送到远程库对应的远程分支上
//# git push origin master
//Username for 'https://github.com':
//Password for 'https://lei130102@github.com':
//枚举对象: 22, 完成.
//对象计数中: 100% (22/22), 完成.
//使用 12 个线程进行压缩
//压缩对象中: 100% (20/20), 完成.
//写入对象中: 100% (20/20), 1.54 KiB | 789.00 KiB/s, 完成.
//总共 20 （差异 13），复用 0 （差异 0）
//remote: Resolving deltas: 100% (13/13), completed with 1 local object.
//To https://github.com/lei130102/Test1.git
//   8701e74..b239f6e  master -> master

//可以看到 推送成功了，如果我们现在要推送到其他分支，比如dev分支上，我们还是那个命令 git push origin dev
//# git push origin dev
//Username for 'https://github.com':
//Password for 'https://lei130102@github.com':
//总共 0 （差异 0），复用 0 （差异 0）
//remote:
//remote: Create a pull request for 'dev' on GitHub by visiting:
//remote:      https://github.com/lei130102/Test1/pull/new/dev
//remote:
//To https://github.com/lei130102/Test1.git
// * [new branch]      dev -> dev


//master分支是主分支，因此要时刻与远程同步。
//一些修复bug分支不需要推送到远程去，可以先合并到主分支上，然后把主分支master推送到远程去。





//抓取分支
//多人协作时，大家都会往master分支上推送各自的修改。现在我们可以模拟另外一个同事，可以在另一台电脑上（注意要把SSH key添加到github上）或者同一台电脑上另外一个目录克隆
//# cd ../
//# cd ./Tmp
//# git clone https://github.com/lei130102/Test1.git
//正克隆到 'Test1'...
//remote: Enumerating objects: 44, done.
//remote: Counting objects: 100% (44/44), done.
//remote: Compressing objects: 100% (21/21), done.
//remote: Total 44 (delta 14), reused 44 (delta 14), pack-reused 0
//展开对象中: 100% (44/44), 完成.
//现在我们的小伙伴要在dev分支上做开发，就必须把远程的origin的dev分支到本地来，于是可以使用命令创建本地dev分支：git checkout –b dev origin/dev
//# cd Test1
//# git branch
//* master
//# git checkout -b dev origin/dev
//分支 'dev' 设置为跟踪来自 'origin' 的远程分支 'dev'。
//切换到一个新分支 'dev'
//现在小伙伴们就可以在dev分支上做开发了，开发完成后把dev分支推送到远程库
//# git status
//位于分支 dev
//您的分支与上游分支 'origin/dev' 一致。

//尚未暂存以备提交的变更：
//  （使用 "git add <文件>..." 更新要提交的内容）
//  （使用 "git checkout -- <文件>..." 丢弃工作区的改动）

//        修改：     step2.cpp

//修改尚未加入提交（使用 "git add" 和/或 "git commit -a"）
//# git add step2.cpp
//# git commit -m "修改"
//[dev ff7add0] 修改
// 1 file changed, 1 insertion(+)
//# git push origin dev                                      把现在的dev分支推送到远程去
//Username for 'https://github.com':
//Password for 'https://lei130102@github.com':
//枚举对象: 5, 完成.
//对象计数中: 100% (5/5), 完成.
//使用 12 个线程进行压缩
//压缩对象中: 100% (3/3), 完成.
//写入对象中: 100% (3/3), 284 bytes | 284.00 KiB/s, 完成.
//总共 3 （差异 2），复用 0 （差异 0）
//remote: Resolving deltas: 100% (2/2), completed with 2 local objects.
//To https://github.com/lei130102/Test1.git
//   c123f7f..ff7add0  dev -> dev

//小伙伴们已经向origin/dev分支上推送了提交，而我在我的目录文件下也对同样的文件同个地方作了修改，也试图推送到远程库
//# cd ../../Test1
//# git checkout dev
//已经位于 'dev'
//# git status
//位于分支 dev
//尚未暂存以备提交的变更：
//  （使用 "git add <文件>..." 更新要提交的内容）
//  （使用 "git checkout -- <文件>..." 丢弃工作区的改动）

//        修改：     step2.cpp

//未跟踪的文件:
//  （使用 "git add <文件>..." 以包含要提交的内容）

//        CMakeLists.txt
//        CMakeLists.txt.user
//        main.cpp

//修改尚未加入提交（使用 "git add" 和/或 "git commit -a"）
//# git add step2.cpp
//# git commit -m "我进行了修改"
//[dev f373463] 我进行了修改
// 1 file changed, 1 insertion(+)
//# git push origin dev                                 推送到远程库时发生错误，不同的人推同样的文件，修改同个文件同一个地方报错
//Username for 'https://github.com':
//Password for 'https://lei130102@github.com':
//To https://github.com/lei130102/Test1.git
// ! [rejected]        dev -> dev (fetch first)
//error: 推送一些引用到 'https://github.com/lei130102/Test1.git' 失败
//提示：更新被拒绝，因为远程仓库包含您本地尚不存在的提交。这通常是因为另外
//提示：一个仓库已向该引用进行了推送。再次推送前，您可能需要先整合远程变更
//提示：（如 'git pull ...'）。
//提示：详见 'git push --help' 中的 'Note about fast-forwards' 小节。
//由上面可知：推送失败，因为我的小伙伴最新提交的和我试图推送的有冲突，解决的办法也很简单，上面已经提示我们，先用git pull把最新的提交从origin/dev抓下来，然后在本地合并，解决冲突，再推送
//# git pull
//remote: Enumerating objects: 5, done.
//remote: Counting objects: 100% (5/5), done.
//remote: Compressing objects: 100% (1/1), done.
//remote: Total 3 (delta 2), reused 3 (delta 2), pack-reused 0
//展开对象中: 100% (3/3), 完成.
//来自 https://github.com/lei130102/Test1
//   c123f7f..ff7add0  dev        -> origin/dev
//当前分支没有跟踪信息。
//请指定您要合并哪一个分支。
//详见 git-pull(1)。

//    git pull <远程> <分支>

//如果您想要为此分支创建跟踪信息，您可以执行：

//    git branch --set-upstream-to=origin/<分支> dev
//git pull也失败了，原因是没有指定本地dev分支与远程origin/dev分支的链接，根据提示，设置dev和origin/dev的链接
//# git branch --set-upstream-to=origin/dev dev
//分支 'dev' 设置为跟踪来自 'origin' 的远程分支 'dev'。
//# git pull                                         pull成功了，但是有冲突，需要解决，再pull
//自动合并 step2.cpp
//冲突（内容）：合并冲突于 step2.cpp
//自动合并失败，修正冲突然后提交修正的结果。
//这回git pull成功，但是合并有冲突，需要手动解决，解决的方法和分支管理中的 解决冲突完全一样。解决后，提交，再push
//# git status
//位于分支 dev
//您的分支和 'origin/dev' 出现了偏离，
//并且分别有 1 和 1 处不同的提交。
//  （使用 "git pull" 来合并远程分支）

//您有尚未合并的路径。
//  （解决冲突并运行 "git commit"）
//  （使用 "git merge --abort" 终止合并）

//未合并的路径：
//  （使用 "git add <文件>..." 标记解决方案）

//        双方修改：   step2.cpp

//未跟踪的文件:
//  （使用 "git add <文件>..." 以包含要提交的内容）

//        CMakeLists.txt
//        CMakeLists.txt.user
//        main.cpp

//修改尚未加入提交（使用 "git add" 和/或 "git commit -a"）
//# git add step2.cpp
//# git commit -m "merge & fix step2.cpp"
//[dev 079da15] merge & fix step2.cpp
//# git push origin dev                             继续推送到远程库中
//Username for 'https://github.com':
//Password for 'https://lei130102@github.com':
//枚举对象: 8, 完成.
//对象计数中: 100% (8/8), 完成.
//使用 12 个线程进行压缩
//压缩对象中: 100% (4/4), 完成.
//写入对象中: 100% (4/4), 416 bytes | 416.00 KiB/s, 完成.
//总共 4 （差异 3），复用 0 （差异 0）
//remote: Resolving deltas: 100% (3/3), completed with 2 local objects.
//To https://github.com/lei130102/Test1.git
//   ff7add0..079da15  dev -> dev

//因此：多人协作工作模式一般是这样的：
//首先，可以试图用git push origin branch-name推送自己的修改.
//如果推送失败，则因为远程分支比你的本地更新早，需要先用git pull试图合并。
//如果合并有冲突，则需要解决冲突，并在本地提交。再用git push origin branch-name推送




#include <iostream>

int main(int argc, char** argv)
{

}
