# How To Build


cd <dontpanic_src_path>
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=/usr -DKDE_INSTALL_USE_QT_SYS_PATHS=ON ../src
make
make install or su -c 'make install'

to uninstall the project:
make uninstall or su -c 'make uninstall'


