INNER_DIR=$(pwd)
echo "I am here"
cd $INNER_DIR
apt-get update -y -qq
apt-get install -y -qq software-properties-common
add-apt-repository ppa:git-core/ppa
apt-get update -y -qq
apt-get install -y -qq --fix-missing ninja-build make gcc-multilib g++-multilib libssl-dev wget openjdk-8-jdk zip maven unixodbc-dev libc6-dev-i386 lib32readline6-dev libssl-dev libcurl4-gnutls-dev libexpat1-dev gettext unzip build-essential checkinstall libffi-dev curl libz-dev openssh-client pkg-config

echo "Install"
cd $INNER_DIR
if [ -n "${AARCH64_CROSS_COMPILE}" ]; then
  apt-get install -y -qq gcc-aarch64-linux-gnu g++-aarch64-linux-gnu
fi

echo "Install Git 2.18.5"
cd $INNER_DIR
wget https://github.com/git/git/archive/refs/tags/v2.18.5.tar.gz
tar xvf v2.18.5.tar.gz
cd git-2.18.5
make
make prefix=/usr install
git --version
git checkout ${{ inputs.git_ref }}

echo "Install CMake 3.21"
cd $INNER_DIR
shell: bash
run: |
wget https://github.com/Kitware/CMake/releases/download/v3.21.3/cmake-3.21.3-linux-x86_64.sh
chmod +x cmake-3.21.3-linux-x86_64.sh
./cmake-3.21.3-linux-x86_64.sh --skip-license --prefix=/usr/local
cmake --version

echo "Install Python 3.8"
cd $INNER_DIR
wget https://www.python.org/ftp/python/3.8.17/Python-3.8.17.tgz
tar xvf Python-3.8.17.tgz
cd Python-3.8.17
mkdir -p pythonbin
./configure --with-ensurepip=install
make -j
make install
python3.8 --version
python3.8 -m pip install pip
python3.8 -m pip install requests awscli

echo "Version Check"
cd $INNER_DIR
ldd --version ldd
python3 --version
git --version
git log -1 --format=%h

#- name: Setup vcpkg
#if: ${{ inputs.vcpkg == 1 }}
#uses: lukka/run-vcpkg@v11.1
#with:
#vcpkgGitCommitId: a1a1cbc975abf909a6c8985a6a2b8fe20bbd9bd6

#- name: Setup Ccache
#if: ${{ inputs.ccache == 1 }}
#uses: hendrikmuhs/ccache-action@v1.2.11 # Note: pinned due to GLIBC incompatibility in later releases
#with:
#key: ${{ github.job }}
#save: ${{ github.ref == 'refs/heads/main' || github.repository != 'duckdb/duckdb' }}
#
#- name: Instal OpenSSL through vcpkg
#if: ${{ inputs.openssl == 1 }}
#shell: bash
#run: |
#cd $VCPKG_ROOT && ./vcpkg install openssl --triplet=${{ inputs.aarch64_cross_compile == 1 && 'arm64-linux' || 'x64-linux' }}
