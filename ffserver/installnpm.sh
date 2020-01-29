#git clone  https://github.com/nodejs/node
cd node
./configure
make -j 10
sudo make install
curl -L https://npmjs.org/install.sh | sudo sh
