set title "QPSK Signal(BitRate 200Hz : Carrier 1kHz)"
set xrange [0:0.015]
set yrange [-2:2]
set xlabel "Time"
set ylabel "Amplitude"
plot "2-3res.txt" using 1:2 with lines title "QPSK wave"