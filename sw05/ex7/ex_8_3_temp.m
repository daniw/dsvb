%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% DSVB Part 1
% Exercise 8: Practical FIR and IIR Filter Design
% Waj, HSLU-T&A
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%% 8.2 Filtering Audio Signals
clear all; close all;

%% 
% 1. Analyze Given signal
load buried;
N=length(s);

S = 20*log10(2*abs(fft(blackman(N).*s)/N)); 
S = S(1:N/2+1);
set(figure,'Name','Exercise 8.3: Given Audio Signal');
title('|S| (dB)');grid on;
plot([0:N/2]/(N/2),S); axis([0,1,-160,0])
title('|S_X| (dB)');grid on;

%soundsc(s,Fs)

%%
% 2. Apply appropriate filter                          ==> ToDo
f_bw = 0.005;
f_1 = 0.1;
f_2 = 0.2;
b1 = fir1(2^10, [[f_1-f_bw f_1+f_bw] [f_2-f_bw f_2+f_bw] 0.49], 'DC-1');
sfilt = filter(b1, 1, s);
sfilt = filter(b1, 1, sfilt);
Sfilt = 20*log10(2*abs(fft(blackman(N).*sfilt)/N)); 
Sfilt = Sfilt(1:N/2+1);
set(figure,'Name','Exercise 8.3: Filtered Audio Signal');
title('|S| (dB)');grid on;
H=20*log10(abs(freqz(b1,1,N)));
subplot(2,1,1);
plot([0:N-1]/N,H); axis([0,1,-90,1]);
subplot(2,1,2);
plot([0:N/2]/(N/2),Sfilt); axis([0,1,-160,0])
title('|S_X| (dB)');grid on;
soundsc(sfilt(2000:end),Fs)
