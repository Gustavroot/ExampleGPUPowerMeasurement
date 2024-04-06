count=0
while [[ $count -lt 10 ]];do
    #lscpu
    (( count++ ))
    outpx=`./a.out 2`
    echo "count = $count, node = $SLURMD_NODENAME , $outpx"
    sleep 1
done
