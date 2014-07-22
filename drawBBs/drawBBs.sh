#!/bin/sh
# green
./drawBBs -g 255 ../../../BaoDataBase/ ../../../BaoDataBase/.metaface/
# red
./drawBBs -r 255 -a ../../../BaoDataBase/ ../../../BaoDataBase/metaface/haarcascade_frontalface_alt/
# blue
./drawBBs -b 255 -a ../../../BaoDataBase/ ../../../BaoDataBase/metaface/haarcascade_frontalface_alt2/
# yellow
./drawBBs -r 255 -g 255 -a ../../../BaoDataBase/ ../../../BaoDataBase/metaface/haarcascade_frontalface_alt_tree
# violet
./drawBBs -r 255 -b 255 -a ../../../BaoDataBase/ ../../../BaoDataBase/metaface/haarcascade_frontalface_default/
# cyan
./drawBBs -b 255 -g 255 -a ../../../BaoDataBase/ ../../../BaoDataBase/metaface/haarcascade_profileface/
# white
./drawBBs -r 255 -b 255 -g 255 -a ../../../BaoDataBase/ ../../../BaoDataBase/metaface/lbpcascade_frontalface/
