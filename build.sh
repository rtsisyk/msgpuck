mkdir -p rpmbuild/SOURCES

git clone -b $1 https://github.com/tarantool/msgpuck.git
cd msgpuck
git submodule update --init --recursive
tar cvf `cat rpm/msgpuck.spec | grep Version: |sed -e  's/Version: //'`.tar.gz . --exclude=.git
sudo yum-builddep -y rpm/msgpuck.spec

cp *.tar.gz ../rpmbuild/SOURCES/
rpmbuild -ba rpm/msgpuck.spec
cd ../

# move source rpm
sudo mv /home/rpm/rpmbuild/SRPMS/*.src.rpm result/

# move rpm, devel, debuginfo
sudo mv /home/rpm/rpmbuild/RPMS/x86_64/*.rpm result/
ls -liah result
