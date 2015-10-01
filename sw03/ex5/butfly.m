function [ao,bo] = butfly(ai, bi, w)

b  = bi * w;
ao = ai + b;
bo = ai - b;
