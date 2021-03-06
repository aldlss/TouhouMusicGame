## 大概架构
首先是一个游戏整体类，游戏整体类里面是一个关卡类
关卡类里面包含各种游戏对象，游戏对象有各种游戏组件
#### 大概流程
大概流程是怎么样呢  
首先是处理用户输入，然后是游戏内部的每帧自然更新  
首先更新游戏整体更新，里面是游戏对象更新，就是游戏组件更新  
值得注意的是渲染应当是独立出来的，因为游戏内部的更新可能后面的更新会对前面的造成影响  
这种影响可能会导致前面已经渲染出来的东西和当前状态不符  

### 对象类
+ 音符类，考虑使用音符组件和渲染组件，变换组件，改变变换组件，音符组件用来处理判定之类的，渲染组件来表示图像的渲染，其实如果加上移动组件的话，然后使用得当的移动路线，应当是能实现，圆圈缩小的观感的  
+ 

### 组件
+ 渲染（精灵）组件，用来渲染出图片，这个需要单独拉出来最后一起处理
+ 音符组件，用来进行音游的判定等
+ 变换组件，主要存放位置、缩放、旋转变量
+ 改变变换组件，这个其实主要还是用来改变上面那个的参数的，具体该怎么实现感觉有待商榷
    + 应该会对于每种音符专门特化一下变换方式
+ 输入组件，我觉得这个是需要添加的，因为音游我觉得需要及时处理输入，也应该说输入是最先处理的，反转了，这个没加
+ 字符组件，这个我觉得最后肯定是要渲染的，想了想觉得还是放到精灵组件下面为好，我看了看，精灵组件的各方面还都可以完美契合，算是正巧抽象得不错（？

### 想法
1. 对的，应当把输入处理放在最前，渲染放在最后，然后再把其他的自然更新放在中间，毕竟交互嘛
1. 突然想到输入作为一个特殊的、独立于全局的东西，应当是附着在关卡类里面的，而不是作为一个组件
1. 渲染呢？渲染确实还是根据于游戏内对象的，这个倒是不必变化
1. 想了想，还是应当需要输入处理组件，这样可降低耦合性
1. 关卡类应当抽象到只要读取音符数据就可以运行
1. 铺面相关：
    + 谱面编写规范：(音轨:int),(键的种类(0/1/2)),(起始时间:Uint32),(结束时间(如果有的话):Uint32),{便于读写，最后都加了逗号
    + 铺面文件开头第一行应当是单个数字，表示有几个音轨（？先不搞这个，考虑固定音轨（
    + 通过文件输入流一行一行读取为，然后存放至对应音轨的queue结构体中（先不创建），每帧检测队列头的是否可以放出，若起始时间已小于当前相对时间，则放出，创建对象，直到放出不了为止
    + 放出后则正常进行判断，并加入到运行时音轨中，对于敲击，则判断运行时音轨最前面的音符
    + 音符有两种消亡的情况：
        1. 超时。此时应该是update过程中发现，除了正常的物品销毁流程外，还要在队列头将其销毁。考虑到是60帧，应当不会出现要销毁的不在队列头的情况。
        2. 敲击。此时是在event过程中，可以直接删除，并也方便删除队列的。

        这两种情况之后，都是要显现出MISS、或者combo之类的判定的，也是要增加一下（。然而不幸的是，突然想到两者都是要拉去等待销毁的，难搞了
1. 应当设置属于某个音轨的话就会在音轨上面自动跑动(
1. 考虑一切以毫秒为单位，毕竟底层实现就是这样的
1. 对于音符的位置之类的如何确定，考虑先确定击打时间，然后我参考了这篇文章：[音游判定原理详解——从触摸屏幕到判定音符](https://www.bilibili.com/read/cv13690032/)，看到有由设置的速度计算下落时间的公式，大喜过望，索性偷了过来。有了这项科学合理数据之后，可以很简单算出起始时间；然后只要自己在设置起始终止状态，那么变化方程也可以很简单地求出来。只能说得亏看到了这篇文章，不然不知道我又要拿什么神奇的数据来算。
1. 之前觉得event的函数应当拆分出来，现在想来似乎并不是必要的，只要保证在需要的时候isRunning为false并且准确地返回toLevel信息就好了。再补充一下，这样子我每次切换关卡只要在TheGame的函数里面根据返回的值delete再new一遍就可以切换关卡了，而我指针用的是base的指针，因此也可以泛用。不同关卡的不同内容可以在初始化的时候布置，这样看来，有点像Qt（？
1. 承接第7点，我觉得如果音符会根据音轨的位置而调整的话，又可以省下不少维护精力，而且布局的时候也可以更加灵活一点，毕竟你音符总是要落到判定点上的。
1. 完善了判定时间，大致参考了这两篇文章：[音符判定范围详解——不同音符的不同判定区间【Project SEKAI攻略】](https://www.bilibili.com/read/cv13712799/)、[这几个音游哪个判定最严格啊](https://tieba.baidu.com/p/6789994052)，主要还是pjsk的判定看说是有点严的，而且还细分的比我多，所以根据其他人的评价优化了一下，还顺便捉了个之前发现不了的bug（

### 踩坑：
1. SDL相关的都是指针多，但现在的大多是用引用，要分清（
2. 记一次非常谔谔的编译错误：
    1. 首先，编译，无法找到引用的外部符号，虽然我这里没用模板类函数，但因为之前cpp模板的问题，我还以为是模板的问题，查了资料，说内联可解决，于是内联，内联后继续报错找不到符号，不过是调用这个函数的地方报错了，之前是这个函数报错
    1. 然后我就不懂了，还以为是模板不够给力，模板嵌模板再嵌结构体不行，bug一堆。之后找了好久，无果
    1. 后来一个个试，再加上网上查资料，终于解决了问题。其实这个是两个问题来着：
        1. 那个函数内部报错，是因为我在里面调用了另一个函数，而那个函数我之前写的时候，是写在类外边的，然后我复制的时候顺手把他的声明放进类里面了。然而于此同时，定义里我没有给那个函数加类的命名空间，最后就是有定义，但是找不到实现，报错- -
        2. 那调用那个函数报错的是怎么会事呢，其实我原本以为加了static，函数内部的问题就解决了，所以就到调用报错了。然而并不是这样，其实是报错得更早了。网上查了资料，是说如果使用内联，而且定义和声明分开的话，那么那个函数是不能被其他文件引用的：[函数设置为内联inline之后编译报错LINK ERROR 2019相关](https://blog.csdn.net/LL596214569/article/details/83794264)
    1. 只能说麻中麻，原来是两个错误合在一起，而且之前以为是模板问题又给我带偏了，结果还是自己太烂了
1. 记得要把自己用来测试的代码删掉- -
1. 刚刚出现了什么“不是类或命名空间名称”的错误，后面发现又是头文件相互包含了- -，感觉如果有奇奇怪怪的错误的话，有很大可能是头文件乱套了，包括连接失败什么的。因为这次调用的是静态成员，所以才说找不到类，不然估计也是连接炸了。刚说完，就链接炸了，仔细一看，竟然写出了自己包含自己的高级操作。静态类成员必须要初始化，也就是要在类外写一下，这个也要值得注意，不然也会报连接不到
1. 初始化顺序要写对，不然拿的变量是假的（
1. 麻，调用`TTF_RenderText_Blended`的时候总是报错，而且毫无根据，一开始还不知道什么原因，后面慢慢排查，发现一样的设置，如果你输出"com"字符串就报错，然而输出"co"就没事，就差一个字符；但是有时候如果没碰到特殊的字符组合的话就没事，比如"wa1f5w31"也可能是没事的，这个问题就很玄学知道吧。上Google、Stack Overflow搜了搜，都没有答案；也看了看官方的API介绍，也没有发现什么。主要是就很怪异，想到过是不是颜色的问题，是不是texture设置的问题，是不是打开字体的方式不对，结果都不是。最后尝试着改了一下字体的大小，发现当字体大小在61及以下的时候是没问题的，但是一旦大于61，马上给你报错。我还以为是SDL不行，直到我试了试另一个字体，发现它连160都不会报错，然后我又试了试我这个字体的可变版本，结果又没问题了- -。最后没办法，只好换到这个可变大小的版本了，估计是因为我之前那个字体是static的，可能大小是有上限的（？至于为什么我之前不用可变版本的，因为那个版本的字体weight不够大啊，这个SDL我看了所有TTF的API，都没看见能调weight的。至于那个可变大小的版本，我明明看见用Windows自带的字体管理器预览是能看到有一页有我想要的weight，但我就是不知道怎么打开那一页啊，用`TTF_OpenFontIndex`也没有用，只能打开第0页，就是比较细的那一页。那能怎么办，字体太细总好过报错了，做游戏就是要学会妥协，或者说做游戏的时候很多地方都是不能完美的，有时候甚至可能要用一些小技巧糊弄一下玩家，这也是鵺酱和真心酱之前说过的，也是值得记住的。然而我的浪费一天的时间在这里debug谁给我补啊
1. 绷，新引入了imgui库，结果这个库是cpp文件和h文件直接全部丢给你的，也就是说是raw的。我直接引用h吧，报错LNK2019，未连接的外部符号，本来以为是怎么回事呢。后来想了想，我只引入了h文件，那cpp文件呢？实现有编译吗？好吧，结果就是发现还要把cpp文件引入进来，但是手动引进来也好麻烦啊，还好是有例子的，于是就把例子编译一下导出成.lib静态库，然后引入之后就可以嗯造了
1. imgui这个字体，是按顺序的，是按最先引入的字体展示，怪不得我说中文显示不出来（
1. 记一个小问题引发的大错误：
    + 背景：我想在加载的同时让游戏不阻塞，不至于卡死这样，于是决定引入多线程。分成了一个为加载线程，渲染预加载好的画面（需要的内存不多）；另一个即为创建关卡的线程，这样确实是可以在创建的同时不阻塞然后显示加载画面了，虽然都是基本上一晃就过去了
    + 问题：问题是什么呢，我发现加载的时候，有一定概率会卡死在加载界面，游戏卡死，只有音乐还在播。用调试也调试不出是哪里出问题了，而且似乎如果等待画面渲染前等待创建关卡看是否完成的时间调多的话卡死概率疑似会变小，但仍不能彻底解决
    + 分析：考虑到加了这个异步前是没有这个问题的，于是考虑是异步的问题，会不会是异步的多线程太烂了呢？或者说SDL的多线程支持有问题——之前在网上确实是有看到过这个说法的。本来想着崩也没办法，就重启吧，反正概率也不是很大。但后面还是想了下，一般按理说异步多线程最大的问题就是资源占用问题。想到确实我的两个线程都是需要用到渲染器这个资源的，那么同时调用这个资源导致其崩溃也不是不可能的，毕竟这操作不仅不是原子的，而且内部的实现估计还不少，而且崩溃是只有画面不动了，音乐还能播，似乎也印证了这个
    + 解决：那么对于资源占用问题，最普遍的解决方案还是用锁。于是又学习了一下标准库中的锁的用法，发现这个RAII的用法还挺不错，于是最后就用这种方法写了。最后经过多次测试，确实没有再碰到这个问题，而且没有感觉出与之前正常的时候有任何延迟之类的，算是成功解决了

### 注意事项：
1. globalObject的只会在level销毁的时候清除，所以有可能出现里面的object已经在vector里被删除但是在这里还没删除的情况。之所以我不写，是因为目前来说globalObject只会在关卡生成时候产生，在关卡结束时消亡，所以并不会出现上述问题。后面如果有变动的话，这里是值得注意的。

### 记录：
+ drawOrder大小：
    1. 背景图:10
    1. trackObject:50
    1. musicalNote:100
    1. textObject:120