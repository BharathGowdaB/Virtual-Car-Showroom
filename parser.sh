read -p "MODEL: " model
read -p "BRAND: " brand
read -p "PRICE: " price
read -p "ENGINE: " engine
read -p "FUEL: " fuel
read -p "MILEAGE: " mileage
read -p "AUTOGEAR: " gear 
read -p "RATE: " rate

echo "MODEL:$model\nBRAND:$brand\nPRICE:$price\nENGINE:$engine\nFUEL:$fuel\nMILEAGE:$mileage\nAUTOGEAR:$gear\nRATE:$rate\n\n" > "./CarModels/$1.car";
echo "VERTEX: " `grep -cE "v " $1.obj` >> "./CarModels/$1.car"
echo "NAORMAL: " `grep -cE "vn " $1.obj` >> "./CarModels/$1.car"
echo "TEXCORD: " `grep -cE "vt " $1.obj` >> "./CarModels/$1.car"
echo "FACE: " `grep -cE "f " $1.obj` "\n\n" >> "./CarModels/$1.car"

cat $1.obj >> "./CarModels/$1.car"
cat $1.mtl > "./CarModels/$1.mtl"

echo "./CarModels/$1.car ./CarModels/$1.mtl\n" >> ./docs/carlist.txt
