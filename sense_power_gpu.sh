outpx=`./a.out 2`
echo "node = $SLURMD_NODENAME , $outpx"

nvidia-smi --query-gpu=index,timestamp,power.draw --format=csv --loop-ms=1

#count=0
#while true;do
#    (( count++ ))
#    outpx=`./a.out 2`
#    echo "count = $count, node = $SLURMD_NODENAME , $outpx"
#    nvidia-smi
#    # do this every 1 ms
#    sleep 0.001
#done
