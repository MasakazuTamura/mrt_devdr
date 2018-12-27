# mrt_devdr
robsys2018 homework1
ロボットシステム学 課題1

## 概要
これは, 数値を受け取って2進数でLED表示するデバイスドライバです.

## 環境
使用した機器等
- Raspberry Pi 3 Model B V1.2
	- Raspbian
- ブレットボード
- 5 つの LED
	- GPIO25, 24, 23, 22, 21 と GND の間にそれぞれ接続

## 使用方法
1. 任意のディレクトリにこのリポジトリを clone する
	```
	$ git clone https://github.com/MasakazuTamura/mrt_devdr.git
	```
1. 任意のディレクトリで enter_pocheee.sh を実行
	```
	$ bash enter_pocheee.sh
	```
1. 好きな入力をどうぞ, 例えば
	```
	$ echo 1 > /dev/myled0
	$ echo a > /dev/myled0
	$ echo F > /dev/myled0
	```
	- 受け付ける入力一覧
		- 1 ~ 9: 1から9の値として出力
		- a ~ f: 10から15の値として出力
		- A ~ f: 10から15の値として出力
		- +: 和算モードに切り替え, 総計をリセット
		- q: 表示モードに切り替え

1. 終わったら、任意のディレクトリで shigoto_nin.sh 実行
	```
	$ bash shigoto_nin.sh
	```

## LICENCE
このリポジトリは, GPLv3ライセンスに基づきます. [LICENSE](./LICENSE)をご覧下さい.


## 動画

### リンク
URL: https://youtu.be/AKpFtrsYF9M

### 動画概要
LEDは左から2^3(赤), 2^2(黄), 2^1(赤), 2^0(黄)ビットと, sum_flag(赤)をそれぞれ意味する
1. makeとかをする
	```
	$ cd mrt_devdr
	$ bash enter_pocheee.sh
	```
1. LEDチカチカ
	1. 入れた数字を2進数で表示(表示モード)
		```
		$ echo 1 > /dev/myled0
		$ echo 2 > /dev/myled0
		$ echo 4 > /dev/myled0
		$ echo 8 > /dev/myled0
		$ echo 0 > /dev/myled0
		$ echo + > /dev/myled0
		```
	1. 和算モードに切り替え
		```
		$ echo 3 > /dev/myled0
		```
	1. 入れた数字を足してゆき、結果を2進数で表示(和算モード)
		```
		$ echo c > /dev/myled0
		$ echo 1 > /dev/myled0
		$ echo F > /dev/myled0
	1. 表示モードに切り替え
		```
		$ echo q > /dev/myled0
		```
1. make cleanとか
	```
	$ bash shigoto_nin.sh
	```
