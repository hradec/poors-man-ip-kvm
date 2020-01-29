
export CXXFLAGS=" -fpermissive "
export CFLAGS="$CXXFLAGS"


#git clone  https://github.com/nodejs/node
cd node &&\
git checkout v0.12.9 && \
./configure && \
make -j 10 && \
sudo make install &&\
curl -L https://npmjs.org/install.sh | sudo sh && \
cd .. && \
cd serial-web-terminal && \
rm -rf node-modules && \
npm install
