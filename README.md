# mrt_devdr
robsys2018 homework2
ロボットシステム学 課題2用

## 概要
これは, 受け取った数値に対応するLEDを点灯するデバイスドライバです.

## 環境
使用した機器等
- Raspberry Pi 3 Model B V1.2
	- Ubuntu 16.04 LTS
- ブレットボード
- 5 つの LED
	- GPIO25, 24, 23, 22, 21 と GND の間にそれぞれ接続
	- LEDの配置
		- 25: 中央上
		- 24: 中央下
		- 23: 左下
		- 22: 右下
		- 21: どこでも

## 使用方法
1. 任意のディレクトリにこのリポジトリを clone する
	```
	$ git clone https://github.com/MasakazuTamura/mrt_devdr.git -b homework2
	```
1. 任意のディレクトリで enter_pocheee.sh を実行, 例えば
	```
	$ ~/mrt_devdr/enter_pocheee.sh
	```
1. 好きな入力をどうぞ, 例えば
	```
	$ echo 1 > /dev/myled0
	$ echo A > /dev/myled0
	$ echo N > /dev/myled0
	```
	- 受け付ける入力一覧
		- 1 ~ 5: GPIO25, 24, 23, 22, 21 のLEDを点灯
		- A: 全てのLEDを点灯
		- N: 全てのLEDを消灯

1. 終わったら、任意のディレクトリで shigoto_nin.sh を実行, 例えば
	```
	$ ~/mrt_devdr/shigoto_nin.sh
	```
## 用途
https://github.com/MasakazuTamura/mrt_robosys2018_ros

## LICENCE
このリポジトリは, GPLv3ライセンスに基づきます. [LICENSE](./LICENSE)をご覧下さい.
