if [ $# -lt 1 ] 
then
	echo "Please pass filename as command-line argument (without .extension)"
else
read -p "MODEL: " model
read -p "BRAND: " brand
read -p "PRICE: " price
read -p "DISPLACEMENT: " engine
read -p "POWER: " power
read -p "TORQUE: " torque
read -p "FUEL-TYPE: " fuel
read -p "FUEL-CAPACITY: " capacity
read -p "MILEAGE: " mileage
read -p "TRANSMISSION-TYPE: " gear 
read -p "TOP-SPEED: " speed
read -p "RATE: " rate

echo "MODEL:$model\nBRAND:$brand\nPRICE:$price\nDISPLACEMENT:$engine\nPOWER:$power\nTORQUE:$torque\nFUEL-TYPE:$fuel\nFUEL-CAPACITY:$capacity\nMILEAGE:$mileage\nTRANSMISSION-TYPE:$gear\nTOP-SPEED:$speed\nSAFETY-RATE:$rate\n\n" > "./CarModels/$1.car";
echo "VERTEX: " `grep -cE "v " $1.obj` >> "./CarModels/$1.car"
echo "NORMAL: " `grep -cE "vn " $1.obj` >> "./CarModels/$1.car"
echo "TEXCORD: " `grep -cE "vt " $1.obj` >> "./CarModels/$1.car"
echo "FACE: " `grep -cE "f " $1.obj` "\n\n" >> "./CarModels/$1.car"

cat $1.obj >> "./CarModels/$1.car"
cat $1.mtl > "./CarModels/$1.mtl"

echo "./CarModels/$1.car ./CarModels/$1.mtl" >> ./docs/carlist.txt

fi
