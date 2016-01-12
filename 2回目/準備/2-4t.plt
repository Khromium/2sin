set title "LPF Output(LPFactor 0.95:Carrier 1kHz)"
set xlabel "Time"  
set ylabel "Signal Value"  
set xrange [0:0.015]  
set yrange [-1.2:1.2]  
plot "2-4res.txt" using 1:3 with lines title "rQ(t)"