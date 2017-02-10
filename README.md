# raspicam  
ラズパイの顔認証  

## raspberry piの初期設定
https://igakilab.gitbooks.io/gt-2016-mojava-manual/content/chapter1/raspberrypi.html  
https://igakilab.gitbooks.io/gt-2016-mojava-manual/content/chapter1/raspi-system-settings.html  
を参考に,raspberry piの初期設定を行う.

## プログラムのコンパイルと実行
raspberry pi上で顔認証プログラムを実行するにあたって,リポジトリ上のコードをコンパイルする必要がある.  
1. 前提ライブラリのインストール  
任意の方法でraspberry pi上のCUIを開き,  
sudo apt-get update  
sudo apt-get install libopencv-dev  
と実行する.なお,これらのコマンドは失敗することがある.その場合は同じコマンドを再度実行すること.

2. リポジトリのクローン  
raspberry pi上にこのリポジトリを以下のコマンドによりクローンする.  
cd ~
git clone git://github.com/igakilab/raspicam  
このコマンドが正常に終了すれば, ~/raspicam に各ファイルがクローンされる.lsコマンドなどで確認すること.

3. プログラムのコンパイル
以下のコマンドによりコンパイルする.  
cd ~/raspicam/facesender  
make deploy  

4. プログラムの実行
プログラムはfacesender内のstart.shから実行できる.以下のコマンドを実行すること.  
cd ~/raspicam/facesender
sudo ./start.sh