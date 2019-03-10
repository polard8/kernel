=begin
Vagrant (https://www.vagrantup.com/) file for setting up a Manjaro build environment.

Set's up a VM with Manjaro & tools ready to build Gramado. 

Usage:
  Install Vagrant

  Run `vagrant up` from within this repo (initial provisioning may take a while).
  Once build and provisioned, run `vagrant ssh` to access the VM shell (here you can build Gramado).
=end

Vagrant.configure("2") do |config|
  # Headless manjaro VM
  config.vm.box = "komcrad/manjaro-cinnamon"

  # NFS mount the Gramado folder in the VM
  config.vm.network "private_network", ip: "192.168.66.6"
  config.vm.synced_folder ".", "/media/gramado-dev", type: "nfs", nfs_udp: false, :mount_options => ['nolock,vers=3,noatime,actimeo=1']

  config.vm.provider "virtualbox" do |vb|
    vb.memory = 4096
    vb.cpus = 2
  end

  # Setup tools
  config.vm.provision 'shell', :inline => "pacman --noconfirm -Syu"
  config.vm.provision 'shell', :inline => "pacman -S --noconfirm gcc binutils nasm make sudo cdrkit cifs-utils"

  # Always move into Gramado folder on SSH
  config.vm.provision 'shell', :inline => "echo \"cd /media/gramado-dev\" >> ~/.bash_profile", :privileged => false
end
