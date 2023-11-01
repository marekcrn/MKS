clear all
close all
clc

data = csvread('ntc.csv');
t = data(:,1);
r = data(:,2);

ad = 1024.*r./(r+10);

p = polyfit(ad, t, 10);

ad2 = 0:1023;
t2 = round(polyval(p, ad2), 1);

figure(1)
plot(ad,t,'o')
hold on 
plot(ad2, t2, 'r');

dlmwrite('data.dlm', t2*10, ',');