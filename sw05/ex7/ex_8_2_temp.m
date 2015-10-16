%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% DSVB Part 1
% Exercise 8: Practical FIR and IIR Filter Design
% Waj, HSLU-T&A
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%% 8.2 Quantization of Filter Coefficients
run ex_8_1_temp; % IIR filter design

%% Quantization Parameters                                  ==> ToDo
Bx = 16; % # of bits for input signal (full-scale)
Bc = 24; % # of bits for coefficients

%%
% 1. Quantize input x
mx = max(abs(x));
xq = round(x*2^(Bx-1)/mx) /(2^(Bx-1)/mx); 
% calculate spectrum, drop neg. freq. indexes
Sxq = 20*log10(2*abs(fft(blackman(len)'.*xq)/len)); 
Sxq = Sxq(1:len/2+1);
% plot spectrum of quantized input signal
set(figure,'Name','Exercise 8.2.1: Spectrum of Quantized Input Signal');
plot([0:len/2]/(len/2),Sxq); axis([0,1,-90,1])
title(strcat('|S_Xq| (dB), ',num2str(Bx), 'bits'));grid on;

%%
% 2. Quantize FIR und IIR coefficients
% quantize FIR coefficients
b1q= round(b1*2^(Bc-1))/(2^(Bc-1));
% quantize IIR coefficients
sc_ai =ceil(log2(max(abs(ai)))); %%% scale for bringing ai in range (1,-1)
aiq = round((ai/(2^sc_ai))*2^(Bc-1))/(2^(Bc-1));
biq = round(bi*2^(Bc-1))/(2^(Bc-1));

%%
% 3. IIR stability
% plot P/N-Plan IIR quantized
set(figure,'Name','Exercise 8.2.3: IIR Filter P/N quantized');
zplane(biq,aiq); grid on;
title(strcat('B_c=',num2str(Bc)));
% impulse response with quantized coefficients
set(figure,'Name','Exercise 8.2.3: IIR Filter ImpResp quantized');
impz(biq,aiq)
title(strcat('B_c=',num2str(Bc)));

%%
% 4. Compare # of coeff bits required for FIR/IIR 
%%% FIR
%calculate magnitude response (quantized)
Hq = 20*log10(abs(freqz(b1q,1,len)));
% filter quantized input with quantized coeff
yq = filter(b1q,1,xq);
% calculate spectrum, drop neg. freq. indexes
Syq = 20*log10(2*abs(fft(blackman(len)'.*yq)/len)); 
Syq = Syq(1:len/2+1);
% SNR between quantized and unquantized filter
snr_y_fir = snr(yq,yq-y)
% plot magnitude response FIR quantized
set(figure,'Name','Exercise 8.2.4: FIR Filter Spectrum quantized');
subplot(3,1,1)
plot([0:len/2]/(len/2),Sxq); axis([0,1,-90,1])
title(strcat('|S_Xq| (dB), ',num2str(Bx), 'bits'));grid on;
subplot(3,1,2) 
plot([0:len-1]/len,Hq); axis([0,1,-90,1]);
title(strcat('|H(f)| (dB), ',num2str(Bc),' bits'));grid on
subplot(3,1,3)
plot([0:len/2]/(len/2),Syq); axis([0,1,-90,1]);
title('|S_Y| (dB)');grid on

%%% IIR
% calculate magnitude response of IIR filter (quantized)
Hiq = 20*log10(abs(freqz(biq,aiq,len))/(2^sc_ai));
% filtered quantized input with quantized coefficients
yiq = filter(biq,aiq,xq)/(2^sc_ai);
% calculate spectrum, drop neg. freq. indexes
Syiq = 20*log10(2*abs(fft(blackman(len)'.*yiq)/len)); 
Syiq = Syiq(1:len/2+1);
% SNR between quantized and unquantized filter
snr_y_iir = snr(yiq,yiq-yi)
% plot magnitude response IIR quantized
set(figure,'Name','Exercise 8.2.4: IIR Filter Spectrum quantized');
subplot(3,1,1)
plot([0:len/2]/(len/2),Sxq); axis([0,1,-90,1])
title(strcat('|S_Xq| (dB), ',num2str(Bx), 'bits'));grid on;
subplot(3,1,2) 
plot([0:len-1]/len,Hiq); axis([0,1,-90,1]);
title(strcat('|H(f)| (dB), ',num2str(Bc),' bits'));grid on
subplot(3,1,3)
plot([0:len/2]/(len/2),Syiq); axis([0,1,-90,1]);
title('|S_Y| (dB)');grid on

%%
%%% 5. SOS implementation of IIR filter

% filter unquantized input with unquantized coefficients
y_sos = x;
for i=1:size(SOS,1)  % L filter sections
    y_sos = filter(SOS(i,1:3),SOS(i,4:6),y_sos);
end
y_sos = y_sos*G(1);

%calculate spectrum, drop neg. freq. indexes
Sy_sos = 20*log10(2*abs(fft(blackman(len)'.*y_sos)/len)); 
Sy_sos = Sy_sos(1:len/2+1);

% Quantize coefficients
sc_sos=ceil(log2(max(max(abs(SOS))))); %%% scale for range (1,-1)
SOSq= round((SOS/(2^sc_sos))*2^(Bc-1))/(2^(Bc-1));

% calculate magnitude response of IIR-SOS filter (quantized)
[biq_sos,aiq_sos] = sos2tf(SOSq,G);
Hiq_sos = 20*log10(abs(freqz(biq_sos,aiq_sos,len))/(2^sc_sos));

% filter quantized input with quantized coefficients
yq_sos = xq;
for i=1:size(SOSq,1)  % L filter sections
    yq_sos = filter(SOSq(i,1:3),SOSq(i,4:6),yq_sos);
    if i==1 
       yq_sos = yq_sos*G(1);
    end
    %%% round to signal width between stages
    yq_sos = round(yq_sos*2^(Bx-1))/(2^(Bx-1));
end
yq_sos = yq_sos;

% calculate spectrum, drop neg. freq. indexes
Syq_sos = 20*log10(2*abs(fft(blackman(len)'.*yq_sos)/len)); 
Syq_sos = Syq_sos(1:len/2+1);

% plot spectrum
set(figure,'Name','Exercise 8.2.5: IIR Filter Spectrum quantized SOS');
subplot(3,1,1)
plot([0:len/2]/(len/2),Sxq); axis([0,1,-90,1])
title(strcat('|S_Xq| (dB), ',num2str(Bx), 'bits'));grid on;
subplot(3,1,2) 
plot([0:len-1]/len,Hiq_sos); axis([0,1,-90,1]);
title(strcat('|H(f)| (dB), ',num2str(Bc),' bits'));grid on
subplot(3,1,3)
plot([0:len/2]/(len/2),Syq_sos);axis([0,1,-90,1])
title('|S_Y| (dB)');grid on
% plot P/N-Plan IIR-SOS quantized
set(figure,'Name','Exercise 8.2.5: IIR Filter P/N quantized SOS');
zplane(biq_sos,aiq_sos); grid on;
% impulse response with quantized coefficients
set(figure,'Name','Exercise 8.2.5: IIR Filter ImpResp quantized SOS');
impz(biq_sos,aiq_sos,256)

%%
%%% 6. SNR calculation
% SNR between quantized and unquantized IIR filter in SOS form
snr_y_iir_sos = snr(yq_sos,yq_sos-y_sos)
