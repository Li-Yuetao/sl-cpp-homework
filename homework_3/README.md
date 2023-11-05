### 编译程序

在build文件夹中执行以下命令

```bash
cmake .. && make
```

出现如下情况，编译成功

![image-20231105122159529](/home/lyt/.config/Typora/typora-user-images/image-20231105122159529.png)

将生成四个可执行文件：

![image-20231105122307221](/home/lyt/.config/Typora/typora-user-images/image-20231105122307221.png)

`encrypt`和`decrypt`用于加密解密文本文件，`encrypt_exefile`和`decrypt_exefile`用于加密解密可执行文件

### 项目1：简单文件加密解密系统

#### 运行加密程序

修改[input.txt](data/input.txt)文件中的待加密文本，可以修改为：

```txt
Hello, I am your smart assistant Taoo. Nice to meet you!
```

在build文件夹中执行以下命令

```bash
./encrypt codebook.txt input.txt encrypted.txt
```

程序运行中将会询问：选择`字符串加密-1`和`更新码本文件-1`，运行结果如下：

![image-20231105123751589](/home/lyt/.config/Typora/typora-user-images/image-20231105123751589.png)

#### 运行解密程序

在build文件夹中执行以下命令

```bash
./decrypt codebook.txt encrypted.txt decrypted.txt
```

运行结果：

![image-20231105123859472](/home/lyt/.config/Typora/typora-user-images/image-20231105123859472.png)

### 扩展1——对数字进行加密解密

#### 运行加密程序

修改[input.txt](data/input.txt)文件中的待加密文本，可以修改为`120 2 0 65 30 ...`这种0~255区间的数字，然后在build文件夹中执行以下命令

```bash
./encrypt codebook.txt input.txt encrypted.txt
```

运行程序时候选择`数字加密-2`和`更新码本文件-1`

运行结果，将会输出加密后的结果，存放于`encrypted.txt`文件中：

![image-20231105124224626](/home/lyt/.config/Typora/typora-user-images/image-20231105124224626.png)

#### 运行解密程序

在build文件夹中执行以下命令

```bash
./decrypt codebook.txt encrypted.txt decrypted.txt
```

运行结果如下：

![image-20231105124544188](/home/lyt/.config/Typora/typora-user-images/image-20231105124544188.png)

### 扩展2——对可执行文件进行加密解密

本文预先在`data`文件夹中准备了一个可执行文件`homework_1`，可以直接运行。

#### 运行加密程序

在build文件夹中执行以下命令

```bash
./encrypt_exefile codebook.txt homework_1 homework_1_encrypted
```

程序运行后`codebook.txt`码本文件会自动更新，生成新的加密码本，然后根据新的加密码本来加密可执行文件。

最终程序运行结果如下：

![image-20231105125137338](/home/lyt/.config/Typora/typora-user-images/image-20231105125137338.png)

#### 运行解密程序

在build文件夹中执行以下命令

```bash
./decrypt_exefile codebook.txt homework_1_encrypted homework_1_decrypted
```

运行结果如下：

![image-20231105125504523](/home/lyt/.config/Typora/typora-user-images/image-20231105125504523.png)

检查解密后的可执行文件是否能运行，在此之前需要先添加可执行权限：

```bash
cd ../data/ && chmod +x homework_1_decrypted
./homework_1_decrypted
```

运行结果如下：

![image-20231105125754909](/home/lyt/.config/Typora/typora-user-images/image-20231105125754909.png)

