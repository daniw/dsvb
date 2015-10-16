%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% DSVB Part 1
% Exercise 8: Practical FIR and IIR Filter Design
% Waj, HSLU-T&A
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%% 8.1 IIR Filter Design
run ex_7_3_temp; % FIR filter design

%%
% 1. design IIR filter with fdatool                       ==> ToDo
% Convert to "Single section" after export to Workspace
[bi,ai]=sos2tf(SOS,G);
%bi = [1 1 1 1];
%ai = [1 0 0 0];

%%
% 2. Plot and compare spectrum 
% calculate magnitude response of IIR filter
Hi = 20*log10(abs(freqz(bi,ai,len)));
% apply filter to input
yi = filter(bi,ai,x);
% calculate spectrum
Syi = 20*log10(2*abs(fft(blackman(len)'.*yi)/len)); 
Syi = Syi(1:len/2+1);
% plot
set(figure,'Name','Exercise 8.1: IIR Filter Spectrum');
subplot(3,1,1)
plot([0:len/2]/(len/2),Sx); axis([0,1,-90,1]);
title('|S_X| (dB)');grid on;
subplot(3,1,2) 
plot([0:len-1]/len,Hi); axis([0,1,-90,1]);
title(strcat('|H(f)| (dB) [N=',int2str(length(ai)-1),']'));grid on
subplot(3,1,3)
plot([0:len/2]/(len/2),Syi); axis([0,1,-90,1]);
title('|S_Y| (dB)'); grid on;

%%
% 3. Compare P/N-plots
set(figure,'Name','Exercise 8.1: IIR Filter P/N');
zplane(bi,ai); grid on


