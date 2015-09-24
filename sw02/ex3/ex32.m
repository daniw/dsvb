clc;
clear;
close all;

load('spf1');
load('spm1');

mu = 10;

spf1_mu = mulaw(spf1, mu);
spm1_mu = mulaw(spm1, mu);

W_range = 1:8;
for W = W_range
    spf1_quant = round(spf1 .* 2^(W - 1)) .* 2^(-(W - 1));
    spm1_quant = round(spm1 .* 2^(W - 1)) .* 2^(-(W - 1));
    snrf(W) = snr(spf1_quant, spf1 - spf1_quant);
    snrm(W) = snr(spm1_quant, spm1 - spm1_quant);
    spf1_quant_log = round(spf1_mu .* 2^(W - 1)) .* 2^(-(W - 1));
    spm1_quant_log = round(spm1_mu .* 2^(W - 1)) .* 2^(-(W - 1));
    %spf1_quant_log = mulaw(spf1, W);
    %spm1_quant_log = mulaw(spm1, W);
    snrf_log(W) = snr(spf1_quant_log, spf1_mu - spf1_quant_log);
    snrm_log(W) = snr(spm1_quant_log, spm1_mu - spm1_quant_log);
end
figure(2);
plot(W_range, snrf, W_range, snrm, W_range, snrf_log, W_range, snrm_log, W_range, W_range .* 6, 'LineWidth', 3);
title('Quantisation noise as function of word width');
legend('spf1', 'spm1', 'spf1 log', 'spm1 log');
xlabel('Word width [Bits]');
ylabel('SNR [dB]');
grid();
print -dpdf 'snr';
