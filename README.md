# Native-Speaker
Project of application, that would be able to recognize Speakers and aggregging learnign records

###How Deploy App

#### Compile SPro Tools: 
1. Download SPro package from http://spro.gforge.inria.fr/
2. Compile it with instruction in package
3. Sometimes when you try compile SPro, library "libm.a" with some maths function doesn't linking. To resolve that bug, add to running ./configure script argument, which containg path to library:
./configure LIBS="-L/sciezka/do/libm.a -lm" 

#### Compile Alize-Core 

1. Clone repository https://github.com/ALIZE-Speaker-Recognition/alize-core
2. Compile it with instruction in repository
3. When compilation ends, rename generated libary file, in directory lib(created in repository dir), as libalize.a 

#### Download Qt SDK for your arch

1. Download Qt SKD instalator from Qt website: https://www.qt.io/download.
2. Install SKD in some path in your OS

#### App Compilation

1. Run QtCreator. You will find QtCreator in directory Tools in Qt SKD
2. Clone this repo on yout computer 
3. Open project file "Native_Speaker_Project.pro in repository dir
4. Make sure that QtCreator have found QT SKD. Open Tools/Option and configure Qt Kits. Check g++ compiler version.
5. Configure project with installed Qt Kit
6. Create directory "external-libs" in project's repository
6. Copy from alize-core include/ dir into "external-libs"
7. Copy from alize-core lib/ dir into "external-libs" 
8. Check version of project (Debug or Release) and compile them

#### App Deploying
1. Copy tool "sfbcep" from SPro directory into "resources/bin" in repository
2. QtCreator, by default, build project outside resository dir. Check, where is build dir
3. In repository dir run script "deploy-app.sh" with path to build directory and Qt SKD directory. For example:

    	./deploy-app.sh ../build-Native-Speaker-Release/ /opt/Qt/5.12/gcc_64
        
    Path to build directory should point to root of build dir, not to subdirs. Path to Qt SDK should point to directory with Kit for your arch(above for x64 compiler gcc).  
4. Deploy-app.sh create tar.gz archieve with application. You can copy this package on some other machines and run app in another place.

#### App installation
To install application on target machine, unpack deploy archieve and run script *install.sh*. Script will install sox library - if they aren't installed - and set qt.conf file, required by Qt. After that, app is able to run. It's recommended to run them by *native-speaker.sh* script - this bash file will set LD_LIBRARY_DIR before running application automatically.

 


