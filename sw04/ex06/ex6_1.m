clc;
clear;
close all;

% Encoder
h_en = [1 -1];
figure(1);
impz(h_en,1,10);
figure(2);
zplane(h_en,1);
figure(3);
freqz(h_en,1,100);

figure(4);
impz(1,h_en,10);
figure(5);
zplane(1,h_en);
figure(6);
freqz(1,h_en,100);
