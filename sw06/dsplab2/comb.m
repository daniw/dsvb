clc;
clear;
close all;

N = 32;

bp = [1 zeros(1,N-1)  1];
bn = [1 zeros(1,N-1) -1];

figure(1);
zplane(bp);
title('Comb filter positive');
figure(2);
freqz(bp);
title('Comb filter positive');
figure(3);
zplane(bn);
title('Comb filter negative');
figure(4);
freqz(bn);
title('Comb filter negative');
