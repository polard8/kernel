all:
	#nothing
kernel-info:
	file ../basetier/disk/GRAMADO/KERNEL.BIN
	readelf -S ../basetier/disk/GRAMADO/KERNEL.BIN

# See:
# https://lindevs.com/install-gcc-on-ubuntu/
install-gcc-11:
	sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test
	sudo apt install -y gcc-11
	gcc-11 --version

uninstall-gcc-11:
#Uninstall gcc
#If you want to completely remove gcc and related dependencies, run the following command:
	sudo apt purge --autoremove -y gcc-11
#Remove GPG key and repository:
	#sudo rm -rf /etc/apt/trusted.gpg.d/ubuntu-toolchain-r_ubuntu_test.gpg
	#sudo rm -rf /etc/apt/sources.list.d/ubuntu-toolchain-r-ubuntu-test-focal.list
