outpx=`./a.out 2`
echo "node = $SLURMD_NODENAME , $outpx"

#nvidia-smi --query-gpu=index,timestamp,power.draw --format=csv --loop-ms=1

count=0
while true;do
    (( count++ ))
    outpx=`./a.out 2`
    datetimex=$(date +"%Y-%m-%d %H:%M:%S.%3N")
    total_watts=`scontrol show nodes ${SLURMD_NODENAME} | grep "CurrentWatts"`
    echo "count = $count, $datetimex, node = $SLURMD_NODENAME , $outpx, $total_watts"
    # do this every 1 ms
    sleep 0.001
done
