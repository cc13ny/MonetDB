#!/bin/sh
#
# After patch gdk_bbp.dir revision 1.23.4.2
# on 2001/09/15 you'd loose existing persistent
# bats if you do not run this script;
#   Arjen - arjen@acm.org
#
DBFARM=$1
[ ! -n "$DBFARM" ] && { 
  echo Usage: $0 DBFARM
  exit -1 
}
#
# Note: 
#   refCnt in BBP.dir was usually 0, possibly 1.
#   existing nested persistent bats (latter case)
#   had problems; just in case people used this
#   anyway, we simply increment the old value
#   to 1 resp. 2.
#
cd $DBFARM
for db in *
do
  [ -d $db ] && echo Converting $db
  find $db -name BBP.dir | xargs tar uf $DBFARM/oldBBP.tar
  find $db -name BBP.dir | xargs \
    perl -npi -e 's/1\s+]/2 ]/g; s/0\s+]/1 ]/g'
done
echo backed up BBPs are stored in $DBFARM/oldBBP.tar

