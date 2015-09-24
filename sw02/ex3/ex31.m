clc;
clear;
close all;

load('spf1');
load('spm1');

W_range = 1:80;
for W = W_range
    spf1_quant = round(spf1 .* 2^(W - 1)) .* 2^(-(W - 1));
    spm1_quant = round(spm1 .* 2^(W - 1)) .* 2^(-(W - 1));
    snrf(W) = snr(spf1, spf1 - spf1_quant);
    snrm(W) = snr(spm1, spm1 - spm1_quant);
end
figure(1);
plot(W_range, snrf, W_range, snrm);
title('Quantisation noise');
legend('spf1', 'spm1');
xlabel('W [Bits]');
ylabel('SNR [dB]');
print -dpdf 'snr';
