
# Thunder-Platformer
<<<<<<< HEAD

## Compiling on Linux

```bash

git clone https://github.com/FalcoDJ/Thunder-Platformer.git

cd Thunder-Platformer/

make

./Thunder

```

## Compiling on Windows

### Setup

#### 1. Get MySys2 installed on your system (https://www.msys2.org/)

#### 2. Launch mysys2 command line and enter the following lines of code to update it:

```bash

pacman -Syu #it will close after this command has finished.

pacman -Su #This finishes updating mysys2

```

#### 3. Install mingw inside of mysys2

##### 64bit
```bash

pacman -S mingw-w64-x86_64-gcc

pacman -S mingw-w64-x86_64-make

```

##### 32bit
```bash

pacman -S mingw-w64-i686-gcc

pacman -S mingw-w64-i686-make

```

#### 4. Configure the path to mingw:

1.get the path to mingw (e.g. 'C:mysys64\mingw64\bin')

2. Set Path Environment variable
    1.Open 'Advanced System Settings'
    2. Click 'Environment Variables'
    3. Select 'Path' from 'System Variables' and click edit
    4. In the window that appears click 'New'
    5. set the path as your path to mingw (e.g. 'C:mysys64\mingw64\bin')

3. Open (windows) command line, type gcc -v (it should tell you the version of gcc)
4. Still in the command line, cd into the directory where you downloaded Thunder-Platformer's source code. (e.g. cd Path\To\Directory)
5. To (finally) compile the game type: ```g++ -o Thunder.exe *.cpp -luser32 -lgdi32 -lopengl32 -lgdiplus -lShlwapi -ldwmapi -lstdc++fs -static -std=c++17``` into the command line and execute it.
 
=======
 ## Compiling on Linux
 ```bash
 git clone https://github.com/FalcoDJ/Thunder-Platformer.git
 cd Thunder-Platformer/
 make
 ./Thunder
 ```
>>>>>>> master
