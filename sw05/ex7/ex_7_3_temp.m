%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% DSVB Part 1
% Exercise 7: Design of FIR Filters
% Waj, HSLU-T&A
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%% 7.3 FIR Design with Matlab
close all;

% Parameters
fc = 0.4;   % center of passband
wb = 0.2;   % width of passband
off = 0.01; % offset from band edge
len = 2^14; % # of time samples
N = 2^9;      % FIR filter order                  ==> ToDo: adapt filter order
Nstr = num2str(N);
%%
% 1. Generate test signal
%       0.29         0.31       0.49         0.51 
f =[fc-wb/2-off  fc-wb/2+off  fc+wb/2-off  fc+wb/2+off];
x=0;
for i=1:4
    x = x + 2*cos(2*pi*f(i)*[0:1:len-1]/2);
end

%%
% 2. Design FIR filter with fir1();                           ==> ToDo
%b1=fir1(N,[[0.25 0.30] [0.50 0.55]], 'DC-1');
%b1=fir1(N,[0.300 0.500], kaiser(N+1,6));
b1=fir1(N,[0.300 0.500], hann(N+1));

%%
% 3. magnitude response FIR and magnitude spectrum x[n]
% use window for FFT; fft*2 because half of spectrum is dropped below
Sx = 20*log10(2*abs(fft(blackman(len)'.*x)/len)); 
% drop negative frequencies
Sx=Sx(1:len/2+1);
% calculate magnitude response
H=20*log10(abs(freqz(b1,1,len)));
% plot
set(figure,'Name','Exercise 7.3: FIR Filter Spectrum');
subplot(3,1,1)
plot([0:len/2]/(len/2),Sx); axis([0,1,-90,1]);
title('|S_X| (dB)');grid on;
subplot(3,1,2) 
plot([0:len-1]/len,H); axis([0,1,-90,1]);
title(strcat('|H(f)| (dB) [N=',Nstr,']'));grid on

%%
% 4. Generate filter output and plot spectrum
y = filter(b1,1,x);
Sy = 20*log10(2*abs(fft(blackman(len)'.*y)/len)); 
Sy = Sy(1:len/2+1);
subplot(3,1,3)
plot([0:len/2]/(len/2),Sy); axis([0,1,-90,1]);
title('|S_Y| (dB)'); grid on;

%%
% 5. Determine filter order for 60 dB attenuation   ==> ToDo: adapt N above

%%
% 6. plot P/N-plan
set(figure,'Name','Exercise 7.3: FIR Filter P/N');
zplane(b1,1); grid on

%%
% 7. Design FIR filter with fdatool                 ==> ToDo

