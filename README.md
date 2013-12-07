算法小程序
========

这里都是一些用c或c++编写的小程序，里面都是一些小算法。

推荐大家用gcc或g++编译运行，windows平台可以用Mingw。
在windows平台上，默认的是GBK编码，但程序文件统一用UTF-8，所以大家编译是加一下以下参数，避免乱码。
```sh
gcc/g++ -finput-charset=UTF-8 -fexec-charset=GBK ...
```
为提高效率，建议大家用GVIM等高级文本编码工具，设置快捷键自动完成编译运行。例如我的GVIM相关配置为：
```
" ======= 编译 && 运行 ======= "

" 编译源文件
func! CompileCode()
        exec "w"
        if &filetype == "c"
            exec "!gcc -finput-charset=UTF-8 -fexec-charset=GBK -Wall -std=c99 %<.c -o E:/other/tmp_app/%<"
        elseif &filetype == "cpp"
            exec "!g++ -finput-charset=UTF-8 -fexec-charset=GBK -Wall -std=c++98 %<.cpp -o E:/other/tmp_app/%<"
        elseif &filetype == "java"
            exec "!javac -encoding utf-8 -d E:/other/classes/ %<.java"
        endif
endfunc

" 运行可执行文件
func! RunCode()
        exec "w"
        if &filetype == "c" || &filetype == "cpp" || &filetype == "haskell"
            exec "! E:/other/tmp_app/%<.exe"
        elseif &filetype == "java"
            exec "!java -cp E:/other/classes/ %<"
        endif
endfunc

" 编译运行可执行文件
func! CompileAndRunCode()
	exec CompileCode()
	exec RunCode()
endfunc

" F5 一键保存、编译
map <F5> :call CompileCode()<CR>
map! <F5> <ESC>:call CompileCode()<CR>

" F6 一键保存、运行
map <F6> :call RunCode()<CR>
map! <F6> <ESC>:call RunCode()<CR>

" F9 一键保存、编译和运行
map <F9> :call CompileAndRunCode()<CR>
map! <F9> <ESC>:call CompileAndRunCode()<CR>
```
如果现在不用会此类工具的，又不想现在学的，可以考虑编写一个脚本文件。
