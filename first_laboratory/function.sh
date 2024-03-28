mkdir -p HARRY_POTTER/ORDEN_FENIX
mkdir -p HARRY_POTTER/EATH_EATERS
head -c 10  /dev/urandom > HARRY_POTTER/ORDEN_FENIX/DAMBLDOR.txt
touch HARRY_POTTER/ORDEN_FENIX/GRUM.txt
ln -s  HARRY_POTTER/ORDEN_FENIX/DAMBLDOR.txt HARRY_POTTER/ORDEN_FENIX/LUPIN.txt
head -c 2  /dev/zero > HARRY_POTTER/EATH_EATERS/DEMORT.txt
touch HARRY_POTTER/EATH_EATERS/MALFOY.txt 
echo  "Некоторые люди просто рождаются счастливыми. Мы, Малфои, например." >HARRY_POTTER/EATH_EATERS/MALFOY.txt  

touch HARRY_POTTER/ORDEN_FENIX/SNAPE.txt
echo  "Иногда мы должн мы сделать то, что кажется нам невозможным." >HARRY_POTTER/ORDEN_FENIX/SNAPE.txt 
ln HARRY_POTTER/ORDEN_FENIX/SNAPE.txt HARRY_POTTER/EATH_EATERS/SNAPE.txt
umount /dev/sdb  
mount /dev/sdb HARRY_POTTER 


