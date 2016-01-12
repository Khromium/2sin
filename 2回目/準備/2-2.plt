set title "FSK Signal(BitRate 200Hz : Carrier 1kHz)"
set xrange [0:0.03]
set yrange [-1.2:1.2]
set xlabel "Time"
set ylabel "Amplitude"
plot "2-2res.txt" using 1:2 with lines title "FSK Signal"