# Richer
cocos2d-x base richer game. cross platform Android/iOS/Win/Linux

# Auther: lideguo1979
http://blog.csdn.net/lideguo1979/article/details/44168701

 cocos2d-x 3.2 base

# Develop guide (under linux)
 * Download and Install cocos2d-x (https://github.com/cocos2d/cocos2d-x)
    Clone the repo from GitHub.
     $ git clone https://github.com/cocos2d/cocos2d-x.git
    After cloning the repo, please execute download-deps.py to download and install dependencies.
     $ cd cocos2d-x
     cocos2d-x $ python download-deps.py
    After running download-deps.py.
     cocos2d-x $ git submodule update --init

 * Get richer source
 Build and run a new project for Android

$ cocos run -p android -j 4

Build and run a new project for iOS

$ cocos run -p ios

Build and run a new project for OSX

$ cocos run -p mac

Build and run a new project for Linux

if you never run cocos2d-x on Linux, you need to install all dependencies by the script in cocos2d/build/install-deps-linux.sh

$ cd cocos2d-x/build
$ ./install-deps-linux.sh

Then

$ cd NEW_PROJECTS_DIR/MyGame
$ cocos run -p linux

 
 * 
