### SqlServer数据库C++版本demo

#### 1. 使用VS搭建新项目使用demo

* 这里不需要导入任何第三方包
* 注意下：如何vs爆红线，重新生成即可。

```c++
// 下面导入dll的时候会报红线，但是重新生成就ok了
#import "c:\program files\common files\system\ado\msado15.dll"  no_namespace rename("EOF", "adoEOF")
```

