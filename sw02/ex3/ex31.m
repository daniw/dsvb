clc;
clear;
close all;

load('spf1');
load('spm1');

figure(1);
title('Distribution of values in sample signals');
subplot(2,1,1);
hist(spf1, -0.4:0.01:0.4);
title('spf1');
xlabel('value');
ylabel('appearance');
xlim([-0.5 0.5]);
grid();
subplot(2,1,2);
hist(spm1, -0.4:0.01:0.4);
title('spm1');
xlabel('value');
ylabel('appearance');
xlim([-0.5 0.5]);
grid();
print -dpdf 'hist';

W_range = 1:80;
for W = W_range
    spf1_quant = round(spf1 .* 2^(W - 1)) .* 2^(-(W - 1));
    spm1_quant = round(spm1 .* 2^(W - 1)) .* 2^(-(W - 1));
    snrf(W) = snr(spf1_quant, spf1 - spf1_quant);
    snrm(W) = snr(spm1_quant, spm1 - spm1_quant);
end
figure(2);
plot(W_range, snrf, W_range, snrm, W_range, W_range .* 6, 'LineWidth', 3);
title('Quantisation noise as function of word width');
legend('spf1', 'spm1');
xlabel('Word width [Bits]');
ylabel('SNR [dB]');
grid();
print -dpdf 'snr';
