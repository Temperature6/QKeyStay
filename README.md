# QKeyStay - 鼠标键盘按键模拟

### 功能

​	例：Minecraft里的船不能保持奔跑，这样对于长途划船就不太友好，这个程序可以保持"W"键的按下状态，释放双手

### 使用

*在安装目录中的“config.json"里面设置快捷键

```
{
  "Stop": "Shift+Alt+S",
  "Keyboard": "Alt+K",
  "Mouse": "Alt+M"
}
```

| 键          | 功能                  |
| ---------- | ------------------- |
| "Stop"     | 停止一切保持按下的动作         |
| "Keyboard" | 开始聆听键盘并在按下任意键之后保持按下 |
| "Mouse"    | 开始聆听鼠标并在按下任意键之后保持按下 |

### 糟糕！

程序在Release模式下编译无法正常使用，只能在Debug模式下编译，这会导致程序的依赖库非常大，所以程序的所有文件已经超过了600MB

### 参考

图标来自:[iconfont-阿里巴巴矢量图标库](https://www.iconfont.cn/)

[ddqd/qxtglobalshortcut5: qxtglobalshortcut library qt5 compatibility (github.com)](https://github.com/ddqd/qxtglobalshortcut5)

### 更新日志

2022/10/05 - v1.0 第一个可用的版本