#!/bin/bash
RPMBUILDCHECK=`command -v rmpbuild`
if [ ! -x  $RPMBUILDCHECK ]
then
    echo "need install rmpbuild first"
    echo "yum install rpm-build rpmdevtools"
    exit 1
fi
mkdir -p ~/rpmbuild/{BUILD,RPMS,SOURCES,SPECS,SRPMS}
NAME=project1
VERSION="1.0.0"
RELEASE="1"
PAKNAME=${NAME}-${VERSION}
PAKNAME_TAR_GZ=${PAKNAME}.tar.gz
SRC="include src 3rd CMakeLists.txt"
RPMDIR=~/rpmbuild

mkdir ${PAKNAME}
cp -rf ${SRC} ${PAKNAME}
tar -cvf ${PAKNAME_TAR_GZ} ${PAKNAME}
mv ${PAKNAME_TAR_GZ} ${RPMDIR}/SOURCES/${PAKNAME_TAR_GZ}
rm -rf ${PAKNAME}

cp -f ${NAME}.conf ${RPMDIR}/SOURCES/${NAME}.conf
cp -f ${NAME}.service ${RPMDIR}/SOURCES/${NAME}.service

cp -f ${NAME}.spec ${RPMDIR}/SPECS/${NAME}.spec
sed -i "s/VERSION/${VERSION}/g" ${RPMDIR}/SPECS/${NAME}.spec
sed -i "s/RELEASE/${RELEASE}/g" ${RPMDIR}/SPECS/${NAME}.spec

rpmbuild -bb ${RPMDIR}/SPECS/${NAME}.spec

rm -rf RPMS
mkdir -p RPMS/`arch`/
cp -rf ${RPMDIR}/RPMS/`arch`/${PAKNAME}*.rpm RPMS/`arch`/
rm -rf ~/rpmbuild
