#!/bin/bash

DISK_MAX=90
PROC_CPU_MAX=80
echo "time,load1,disk_used_pct,top_process,top_cpu_pct" > perf_log_d.csv
for i in $(seq 1 10); do
  t=$(date +%H:%M:%S)
  l=$(cut -d' ' -f1 /proc/loadavg)
  d=$(df -P . | awk 'NR==2 {gsub("%","",$5); print $5}')
  read pcpu pname < <(ps -eo %cpu,comm --sort=-%cpu | awk 'NR>1 && $2!="ps" && $2!="awk" {print $1, $2; exit}')
  pcpu_int=${pcpu%.*}
  echo "$t,$l,$d,$pname,$pcpu" >> perf_log_d.csv
  if [ "$d" -ge "$DISK_MAX" ]; then
    echo "DISK ALERT at $t: disk is $d% full"
  fi
  if [ "$pcpu_int" -ge "$PROC_CPU_MAX" ]; then
    echo "PROCESS ALERT at $t: $pname is using $pcpu% CPU"
  fi
  sleep 5
done
echo "Done. Data saved in perf_log_d.csv"

chmod +x mini_monitor_d.sh
./mini_monitor_d.sh

sed -i 's/^DISK_MAX=90$/DISK_MAX=0/' mini_monitor_d.sh
grep "^DISK_MAX=" mini_monitor_d.sh

yes > /dev/null &
./mini_monitor_d.sh
pkill yes

sed -i 's/^DISK_MAX=0$/DISK_MAX=90/' mini_monitor_d.sh
grep "^DISK_MAX=" mini_monitor_d.sh
